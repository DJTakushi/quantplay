from datetime import datetime
import json
import apigetter
import csvconverter
import databaseconnector
import csv, sys

def createIntradyTable():
  mycursor = databaseconnector.mydb.cursor()
  cmd_  = "CREATE TABLE IF NOT EXISTS "
  cmd_ += databaseconnector.INTRADAY_TABLE_
  cmd_ += " ("
  cmd_ += "ticker varchar(255),"
  cmd_ += "datetime DATETIME, "
  cmd_ += "open float(2), "
  cmd_ += "high float(2), "
  cmd_ += "low float(2), "
  cmd_ += "close float(2), "
  cmd_ += "volume int, "
  cmd_ += "refresh DATETIME);"
  mycursor.execute(cmd_)

def insert_TIME_SERIES_INTRADAY(data):
  # inserts an intraday time series into the database
  mycursor = databaseconnector.mydb.cursor()
  j_ = json.loads(data)
  ticker_ = j_["Meta Data"]["2. Symbol"]
  refresh_ = j_["Meta Data"]["3. Last Refreshed"]

  # get json key for Time Series (which varies by api call)
  time_series_key_ = ""
  for key, val in j_.items():
    if "Time Series (" in key:
      time_series_key_ = key

  deleted_dates_ = set() #dates that have already been deleted
  entries_ = []
  for datetime_ , data in j_[time_series_key_].items():
    mycursor = databaseconnector.mydb.cursor()

    # remove preexisting records that match ticker & date
    date_ = datetime_[:10]
    if date_ not in deleted_dates_:
      cmd_ = "DELETE FROM " +databaseconnector.INTRADAY_TABLE_
      cmd_ += " WHERE ticker = \"" + ticker_ + "\" "
      cmd_ += "AND DATE(datetime) = \"" + date_ + "\";"
      mycursor.execute(cmd_)
      databaseconnector.mydb.commit()
      deleted_dates_.add(date_) #cache cleared date

    # add entry from json to entries
    entry_ = (ticker_,datetime_,data["1. open"],data["2. high"],
              data["3. low"],data["4. close"],data["5. volume"],refresh_)
    entries_.append(entry_)

  # insert into table
  cmd_ = "INSERT INTO " + databaseconnector.INTRADAY_TABLE_
  cmd_ += " (ticker, datetime, open, high, low, close, volume, refresh) "
  cmd_ += "VALUES (%s,%s,%s,%s,%s,%s,%s,%s)"
  mycursor.executemany(cmd_,entries_)# executemany is MUCH faster than execute
  databaseconnector.mydb.commit()

if __name__ == "__main__":
  print("Creating intraday table...")
  createIntradyTable()

  TICKER_PREFIX="ticker="
  FILE_PREFIX="file="
  JSON_SUFFIX=".json"
  CSV_SUFFIX=".csv"
  DEFAULT_="DEFAULT"
  ticker_=""
  filepath_=""
  mode_=DEFAULT_
  args = sys.argv[1:]
  for a in args:
    if TICKER_PREFIX in a:
      ticker_=a.replace(TICKER_PREFIX,"")
      mode_=TICKER_PREFIX
    elif FILE_PREFIX in a:
      mode_=FILE_PREFIX
      filepath_=a.replace(FILE_PREFIX,"")
      if JSON_SUFFIX in filepath_:
        mode_=JSON_SUFFIX
      elif CSV_SUFFIX in filepath_:
        mode_=CSV_SUFFIX

  if mode_==DEFAULT_:
    mode_=JSON_SUFFIX

  data=""
  if mode_==TICKER_PREFIX:
    print("getting data for ticker: "+ticker_)
    data_ = apigetter.get_TIME_SERIES_INTRADAY(ticker_)
    timestamp_ = datetime.now().isoformat()[:18]
    timestamp_ = timestamp_.replace(":","-")
    output_filename_ = ticker_+"_"+timestamp_+".json"
    f = open(output_filename_, "a")
    f.write(data_)
    f.close()
    print("saved data to "+output_filename_)
  elif mode_==JSON_SUFFIX:
    if filepath_ == "":
      filepath_="testdata/intraday_ibm_large.json"
    print("getting json data from "+filepath_+"...")
    file = open (filepath_)
    data_ = file.read()
  elif mode_==CSV_SUFFIX:
    data_ = csvconverter.CsvConverter.toAlphaVantageJson(filepath_,"IBM")
  insert_TIME_SERIES_INTRADAY(data_)