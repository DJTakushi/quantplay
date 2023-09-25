import algo
import databaseconnector
from datetime import datetime
import pandas as pd
from sqlalchemy import create_engine
from daydata import DayData
import time
from algo import Algo
# TODO: move daily tracker out to another class to keep simplify manager
# TODO: move portolio out to another class
# TODO: relocate time measurement into functions for better organization of main
  # class-member lists to track multiple instances

class algomanager:
  algo_ = None
  transactions_ = []
  shares_ = 0
  value_current_ = 0.0
  balance_ = 0.0
  current_date_ = None # date entry
  df_ = pd.DataFrame() # main dataframe
  daily_f_ = pd.DataFrame() # daily frame
  ticker_ = ""

  def __init__(self, ticker):
    self.ticker_ = ticker
    self.getData()
    self.algo_ = Algo(self.ticker_)
    self.algo_.getData()
    self.daily_f_ = pd.DataFrame(columns=["date","open","high","low","close",
                                            "portfolio"])

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

  def getEquityValue(self):
    return self.shares_*self.value_current_

  def getPortfolioValue(self):
    return self.balance_ + self.getEquityValue()

  def log_day(self):
    if self.current_date_ != None:
      date_ = self.current_date_.date
      open_ = self.current_date_.open
      high_ = self.current_date_.high
      low_ = self.current_date_.low
      close_ = self.current_date_.close
      self.daily_f_.loc[len(self.daily_f_)]=[date_, open_,high_,low_,close_,self.getPortfolioValue()]

  def simulate(self):
    for index, row in self.df_.iterrows():
      time_end_p_ = row['datetime'].strftime('%Y-%m-%d')

      if self.current_date_:
        if time_end_p_ != self.current_date_.date:
          self.log_day()
          self.current_date_ = DayData(time_end_p_)
          self.current_date_.open = row['open']
      else:
        self.current_date_ = DayData(time_end_p_)
        self.current_date_.open = row['open']

      self.current_date_.close = row['close']
      self.value_current_ = row['close']

      time_ = row['datetime'].strftime('%Y-%m-%d %X')
      result_ = self.algo_.process(time_)
      if result_ != None:
        self.transactions_.append(result_)
        if result_.transaction_ == "buy":
          self.shares_+=1
          self.balance_-=result_.value_
        elif result_.transaction_ == "sell":
          self.shares_-=1
          self.balance_+=result_.value_

    self.log_day()# log the final date

  def analyze(self):
    # compute metrics (profit/loss)
    for t in self.transactions_:
      t.print()
    print("balance  : "+str(self.balance_))
    print("equity   : "+str(self.getEquityValue()))
    print("portfolio: "+f"{self.balance_+self.getEquityValue():.2f}")

    # TODO: calculate sharpe ratio using daily data

if __name__ == "__main__":
  start_time_ = time.time()
  manager_ = algomanager("IBM")
  get_data_time_ = time.time()
  manager_.algo_.getData()
  simulate_time_ = time.time()
  manager_.simulate()
  analyze_time_ = time.time()
  manager_.analyze()
  fin_time_ = time.time()
  print("get_data_time_ dur:"+f" {simulate_time_-get_data_time_:.3f}")
  print("simulate_time_ dur:"+f" {analyze_time_-simulate_time_:.3f}")
  print("analyze_time_ dur :"+f" {fin_time_-analyze_time_:.3f}")

  print(manager_.daily_f_)