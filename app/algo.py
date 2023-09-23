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
  def print(self):
    print(self.time_ +": "+self.transaction_+" at "+str(self.value_))
class Algo:
  transactions_ = []
  ticker_=""
  shares_ = 0
  value_last_ = 0.0
  balance_ = 0.0
  df_ = pd.DataFrame()
  datetimes_ = []
  def __init__(self,ticker):
    self.ticker_=ticker
    self.shares_=0
  def getData(self, time_start="", time_end=""):
    # retrieve data from database to populate dataframe
    time_start_ = time_start
    time_end_ = time_end
    if time_start_ == "":
      time_start_ = "0001-01-01 00:00:00" #min datetime
    if time_end_ == "":
      time_end_ = datetime.now().isoformat()[:18]

    cmd_ = "SELECT * FROM " + databaseconnector.INTRADAY_TABLE_
    cmd_ += " WHERE ticker=\""+self.ticker_+"\""
    cmd_ += " AND datetime >= \""+time_start_+"\""
    cmd_ += " AND datetime <= \""+time_end_+"\""
    cmd_ += " ORDER BY datetime ASC"
    cmd_ += ";"

    # pandas vocally prefers sqlalchemy
    db_connection_str = "mysql+pymysql://"
    db_connection_str+=databaseconnector.user_+":"+databaseconnector.password_
    db_connection_str+="@"+databaseconnector.host_+":"+databaseconnector.port_
    db_connection_str+="/"+databaseconnector.database_
    db_connection = create_engine(db_connection_str)

    self.df_ = pd.read_sql(cmd_, db_connection)

  def process(self, time_end):
    # process data and generate a position at time_end (end of data by default)
    latest_ = self.df_[(self.df_['datetime'] == time_end)]
    val_ = latest_.iloc[0]["close"] # get 0 index, "close" attribute
    self.value_last_ = val_

    if self.shares_== 0:
      self.buy(time_end,val_)

  def buy(self, time, value):
    self.transactions_.append(Transaction(time, value, "buy"))
    self.shares_+=1
    self.balance_-=value

  def sell(self, time, value):
    self.transactions_.append(Transaction(time, value, "sell"))
    self.balance_+=value

  def simulate(self):
    l_ = self.df_['datetime'].tolist()
    for i in l_:
      time_ = i.strftime('%Y-%m-%d %X')
      self.process(time_)

  def analyze(self):
    # compute metrics (profit/loss)
    for t in self.transactions_:
      t.print()
    print("balance: "+str(self.balance_))
    equity_ = self.shares_*self.value_last_
    print("equity: "+str(equity_))
    print("total (balance + equity):"+str(self.balance_+equity_))

if __name__ == "__main__":
  a_ = Algo("IBM")
  a_.getData()
  a_.simulate()
  a_.analyze()