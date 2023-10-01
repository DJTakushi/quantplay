import databaseconnector
from datetime import datetime
import pandas as pd
from sqlalchemy import create_engine
from daydata import DayData
import time
from algo import Algo
from dayrecorder import dayRecorder
from portfolio import portfolio

class algomanager:
  algo_ = None
  ticker_ = ""
  df_ = pd.DataFrame() # main dataframe

  portfolio_ = portfolio
  dayRecorder_ = dayRecorder
  exec_time_ = {} # dictionary of execution times

  def __init__(self, ticker):
    self.ticker_ = ticker
    self.getData()
    self.algo_ = Algo(self.ticker_)
    self.algo_.getData()
    self.dayRecorder_ = dayRecorder()
    self.portfolio_ = portfolio()

  def getData(self, time_start="", time_end=""):
    # retrieve data from database to populate dataframe
    getData_time_ = time.time()
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
    self.exec_time_["getData"] = time.time()-getData_time_

  def simulate(self):
    simulate_time_ = time.time()
    for index, row in self.df_.iterrows():
      time_end_p_ = row['datetime'].strftime('%Y-%m-%d')

      if time_end_p_ != self.dayRecorder_.getCurrentDate() :
        self.dayRecorder_.startNewDay(time_end_p_,row['open'])

      self.portfolio_.setCurrentValue(row['close'])

      time_ = row['datetime'].strftime('%Y-%m-%d %X')
      result_ = self.algo_.process(time_)
      if result_ != None:
        self.portfolio_.addTransaction(result_)

      self.dayRecorder_.setCurrentClose=row['close']
      self.dayRecorder_.setCurrentPortfolio(self.portfolio_.getPortfolioValue())
    self.exec_time_["simulate"] = time.time()-simulate_time_

  def analyze(self):
    # compute metrics (profit/loss)
    analyze_time_ = time.time()
    for t in self.portfolio_.transactions_:
      t.print()
    print("balance  : "+str(self.portfolio_.balance_))
    print("equity   : "+str(self.portfolio_.getEquityValue()))
    print("portfolio: "+f"{self.portfolio_.getPortfolioValue():.2f}")

    # TODO: calculate sharpe ratio using daily data
    self.exec_time_["analyze"] = time.time()-analyze_time_

if __name__ == "__main__":
  manager_ = algomanager("IBM")
  manager_.algo_.getData()
  manager_.simulate()
  manager_.analyze()
  for key, val in manager_.exec_time_.items():
    print(key + ": "+ "{:.{}f}".format(val, 3) + " (s)")

  print(manager_.dayRecorder_.getDataFrame())
  # print(manager_.algo_.df_.columns)