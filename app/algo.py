import databaseconnector
from datetime import datetime
import pandas as pd
from sqlalchemy import create_engine

class Transaction:
  time_ = None
  value_ = 0.00
  transaction_ = ""

  def __init__(self, time, value, transaction):
    self.time_ = time
    self.value_ = value
    self.transaction_ = transaction

class Algo:
  transactions_ = []
  ticker_=""
  def __init__(self,ticker):
    self.ticker_=ticker
  def getData(self, time_start="", time_end=""):
    # retrieve data from database to populate dataframe
    time_start_ = time_start
    time_end_ = time_end
    if time_start_ == "":
      time_start_ = "0001-01-01 00:00:00" #min datetime
    if time_end_ == "":
      time_end_ = datetime.now().isoformat()[:18]

    # mycursor = databaseconnector.mydb.cursor()
    cmd_ = "SELECT * FROM " + databaseconnector.INTRADAY_TABLE_
    cmd_ += " WHERE ticker=\""+self.ticker_+"\""
    cmd_ += " AND datetime >= \""+time_start_+"\""
    cmd_ += " AND datetime <= \""+time_end_+"\";"

    # pandas vocally prefers sqlalchemy
    db_connection_str = "mysql+pymysql://"
    db_connection_str+=databaseconnector.user_+":"+databaseconnector.password_
    db_connection_str+="@"+databaseconnector.host_+":"+databaseconnector.port_
    db_connection_str+="/"+databaseconnector.database_
    db_connection = create_engine(db_connection_str)

    df_ = pd.read_sql(cmd_, db_connection)
    print(df_)

  def process(self, time_end=None):
    # process data and generate a position at time_end (end of data by default)
    pass
  def buy(self, time, value):
    self.transactions_.append(Transaction(time, value, "buy"))
  def sell(self, time, value):
    self.transactions_.append(Transaction(time, value, "sell"))
  def analyze(self):
    # compute metrics (profit/loss)
    pass

if __name__ == "__main__":
  a_ = Algo("IBM")
  a_.getData()