import databaseconnector
from datetime import datetime
import pandas as pd
from sqlalchemy import create_engine
from daydata import DayData
import time
from algo import Algo, AlgoData
from dayrecorder import dayRecorder
from portfolio import portfolio
import numpy as np
import sys

NO_RISK_RATE=0.04
class algomanager:
  algo_ = None
  ticker_ = ""
  df_ = pd.DataFrame() # main dataframe

  portfolio_ = portfolio
  dayRecorder_ = dayRecorder
  exec_time_ = {} # dictionary of execution times
  sharpe_ = None

  def __init__(self, ticker, loadData = False):
    self.ticker_ = ticker
    self.getData()
    self.algo_ = Algo(self.ticker_)
    if loadData:
      self.algo_.loadData()
    self.dayRecorder_ = dayRecorder()
    self.portfolio_ = portfolio(5000)

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

  def simulate(self, add_data = False):
    simulate_time_ = time.time()
    for index, row in self.df_.iterrows():
      time_end_p_ = row['datetime'].strftime('%Y-%m-%d')

      if time_end_p_ != self.dayRecorder_.getCurrentDate() :
        self.dayRecorder_.startNewDay(time_end_p_,row['open'])

      self.portfolio_.setCurrentValue(row['close'])

      if add_data:
        self.algo_.addData(AlgoData(row))

      result_ = self.algo_.process(row['datetime'])
      if result_ != None:
        self.portfolio_.addTransaction(result_)

      self.dayRecorder_.setCurrentClose(row['close'])
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

    df_=self.dayRecorder_.getDataFrame()
    df_["prev_portfolio"] = df_["portfolio"].shift(1)
    df_["daily_ret"]=(df_["portfolio"]-df_["prev_portfolio"]) \
                      /df_["prev_portfolio"]
    df_["excess_daily_ret"]=df_["daily_ret"]-(NO_RISK_RATE/252)
    avg_ = df_["excess_daily_ret"].mean()
    std_ = df_["excess_daily_ret"].std()
    self.sharpe_ = np.sqrt(252) * avg_ / std_
    self.exec_time_["analyze"] = time.time()-analyze_time_

if __name__ == "__main__":
  preload_data_ = False
  for i, arg in enumerate(sys.argv):
    if arg == "preload":
      preload_data_ = True
  manager_ = algomanager("IBM")
  if preload_data_:
    manager_.algo_.loadData()
  manager_.simulate(not preload_data_)
  manager_.analyze()

  for key, val in manager_.exec_time_.items():
    print(key + ": "+ "{:.{}f}".format(val, 3) + " (s)")

  print(manager_.dayRecorder_.getDataFrame())
  print("data rows:"+str(len(manager_.algo_.df_.index)))
  print("sharpe ratio:{:.{}f}".format(manager_.sharpe_, 3))