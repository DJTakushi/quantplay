import mysql.connector
import json
import apigetter

INTRADAY_TABLE_ = "intraday_ohlcv"

mydb = mysql.connector.connect(
  host="localhost",
  port="3308",
  user="my_user",
  password="my_password",
  database="quant"
)

def createIntradyTable():
  mycursor = mydb.cursor()
  cmd_  = "CREATE TABLE IF NOT EXISTS "
  cmd_ += INTRADAY_TABLE_
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
  mycursor = mydb.cursor()
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
    mycursor = mydb.cursor()

    # remove preexisting records that match ticker & date
    date_ = datetime_[:10]
    if date_ not in deleted_dates_:
      print("clearing "+date_+" entries for "+ticker_)
      cmd_ = "DELETE FROM " +INTRADAY_TABLE_
      cmd_ += " WHERE ticker = \"" + ticker_ + "\" "
      cmd_ += "AND DATE(datetime) = \"" + date_ + "\";"
      mycursor.execute(cmd_)
      mydb.commit()
      deleted_dates_.add(date_) #cache cleared date

    # add entry from json to entries
    entry_ = (ticker_,datetime_,data["1. open"],data["2. high"],
              data["3. low"],data["4. close"],data["5. volume"],refresh_)
    entries_.append(entry_)

  # insert into table
  cmd_ = "INSERT INTO " + INTRADAY_TABLE_
  cmd_ += " (ticker, datetime, open, high, low, close, volume, refresh) "
  cmd_ += "VALUES (%s,%s,%s,%s,%s,%s,%s,%s)"
  mycursor.executemany(cmd_,entries_)# executemany is MUCH faster than execute
  mydb.commit()

if __name__ == "__main__":
  print("Creating intraday table...")
  createIntradyTable()

  # get data, but this takes an API call
  # data_ = apigetter.get_TIME_SERIES_INTRADAY("IBM")
  # f = open("output.json", "a")
  # f.write(data_)
  # f.close()
  # print("data_:"+data_)

  # file = open ("testdata/intraday_ibm.json")
  file = open ("testdata/intraday_ibm_large.json")
  data_ = file.read()
  insert_TIME_SERIES_INTRADAY(data_)