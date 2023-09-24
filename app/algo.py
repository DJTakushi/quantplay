import databaseconnector
from datetime import datetime
import pandas as pd
from sqlalchemy import create_engine
import time
# TODO: move daily tracker out to another class to keep Algo single-use
# TODO: relocate time measurement into functions for better organization of main
# TODO: move simulator to another class to keep Algo single-use
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

class DayData:
  date=""
  open=None
  high=None
  low=None
  close=None
  def __init__(self, date_):
    self.date = date_

class Algo:
  transactions_ = []
  ticker_=""
  shares_ = 0
  value_last_ = 0.0
  balance_ = 0.0
  df_ = pd.DataFrame()
  datetimes_ = []
  daily_f_ = pd.DataFrame()
  current_date_ = None
  def __init__(self,ticker):
    self.ticker_=ticker
    self.shares_=0
    self.daily_f_ = pd.DataFrame(columns=["date","open","high","low","close",
                                            "portfolio"])

  def getEquityValue(self):
    return self.shares_*self.value_last_

  def getPortfolioValue(self):
    return self.balance_ + self.getEquityValue()

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

  def pre_process(self, time_end):
    # update date content if necessary
    time_end_p_ = time_end[:10]
    if self.current_date_:
      if time_end_p_ != self.current_date_.date:
        self.log_day()
        self.current_date_ = DayData(time_end_p_)
    else:
      self.current_date_ = DayData(time_end_p_)

  def post_process(self, val):
    # isolate supporting functionality to support function

    # update current_date_.open if this is a new date
    if self.current_date_.open == None:
      self.current_date_.open = val

    # update close; when date exists, last value will accurately rep last value
    self.current_date_.close = val

  def process(self, time_end):
    # process data and generate a position at time_end (end of data by default)
    self.pre_process(time_end)

    latest_ = self.df_[(self.df_['datetime'] == time_end)]
    val_ = latest_.iloc[0]["close"] # get 0 index, "close" attribute
    self.value_last_ = val_

    if self.shares_== 0:
      self.buy(time_end,val_)

    self.post_process(val_)

  def log_day(self):
    if self.current_date_ != None:
      date_ = self.current_date_.date
      open_ = self.current_date_.open
      high_ = self.current_date_.high
      low_ = self.current_date_.low
      close_ = self.current_date_.close
      self.daily_f_.loc[len(self.daily_f_)]=[date_, open_,high_,low_,close_,self.getPortfolioValue()]

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
    self.log_day()# log the final date

  def analyze(self):
    # compute metrics (profit/loss)
    for t in self.transactions_:
      t.print()
    print("balance  : "+str(self.balance_))
    print("equity   : "+str(self.getEquityValue()))
    print("portfolio: "+f"{self.balance_+self.getEquityValue():.2f}")

    # calculate sharpe ratio using daily data

if __name__ == "__main__":
  start_time_ = time.time()
  a_ = Algo("IBM")
  get_data_time_ = time.time()
  a_.getData()
  simulate_time_ = time.time()
  a_.simulate()
  analyze_time_ = time.time()
  a_.analyze()
  fin_time_ = time.time()
  print("get_data_time_ dur:"+f" {simulate_time_-get_data_time_:.3f}")
  print("simulate_time_ dur:"+f" {analyze_time_-simulate_time_:.3f}")
  print("analyze_time_ dur :"+f" {fin_time_-analyze_time_:.3f}")

  print(a_.daily_f_)