import mysql.connector
import json

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
  # TODO: delete previous records for the day if they already exist
  mycursor = mydb.cursor()
  j_ = json.loads(data)
  ticker_ = j_["Meta Data"]["2. Symbol"]
  refresh_ = j_["Meta Data"]["3. Last Refreshed"]
  for datetime_ , data in j_["Time Series (5min)"].items():
    mycursor = mydb.cursor()

    cmd_ = "INSERT INTO " + INTRADAY_TABLE_
    cmd_ += "(ticker, datetime, open, high, low, close, volume, refresh) "
    cmd_ += "VALUES (\""
    cmd_ += ticker_ +"\", \""
    cmd_ += datetime_ +"\", "
    cmd_ += data["1. open"] +", "
    cmd_ += data["2. high"] +", "
    cmd_ += data["3. low"] +", "
    cmd_ += data["4. close"] +", "
    cmd_ += data["5. volume"] +", "
    cmd_ += "\""+refresh_+"\");"
    mycursor.execute(cmd_)
    mydb.commit()


if __name__ == "__main__":
  print("Creating intraday table...")
  createIntradyTable()

  file = open ("testdata/intraday_ibm.json")
  insert_TIME_SERIES_INTRADAY(file.read())