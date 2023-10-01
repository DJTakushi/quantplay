import databaseconnector
from datetime import datetime
import pandas as pd
from sqlalchemy import create_engine
from transaction import Transaction
# TODO: restructure Algo to receive data from manager
  # process will then be run on the top data
  # this will simplify index finding AND reduce Algo's data maintenance burden
SUPPORT_INCREMENTAL_DATA = False
if SUPPORT_INCREMENTAL_DATA:
  class AlgoData:
    datetime_ = ""
    open_ = 0.0
    close_ = 0.0
    volume_ = 0
    def __init__(self, datetime, open, close, volume):
      self.datetime_ = datetime
      self.open_ = open
      self.close_ = close
      self.volume_ = volume
    def getAttributes():
      return ["datetime","open","close","volume"]
    def getData(self):
      return[[self.datetime_,self.open_,self.close_,self.volume_]]
class Algo:
  ticker_=""
  df_ = pd.DataFrame()
  process_count_ = 0
  def __init__(self,ticker):
    self.ticker_=ticker
    if SUPPORT_INCREMENTAL_DATA:
      # initialize empty dataframe
      self.df_ = pd.DataFrame(columns=AlgoData.getAttributes())

  def addData(self, d): # DOES NOT WORK
    # add data to dataframe
    t_ = pd.DataFrame(d.getData(), columns = AlgoData.getAttributes())
    print("t:")
    print(t_)
    if self.df_.empty:
      t_ = pd.DataFrame(d.getData(), columns = AlgoData.getAttributes())
      self.df_ = t_
    else:
      # TODO: fix this; it's not working.  Reconsider this though; it's slow
      print("concatting...")
      pd.concat([t_,self.df_], axis=1, ignore_index=True)
    # self.df_.loc[-1] = [d.datetime_,d.open_,d.close_,d.volume_]

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

    ret_ = None
    # for now, only return a single buy at the first instance
    if self.process_count_== 0:
      ret_ = Transaction(time_end, val_, "buy")
    self.process_count_+=1
    return ret_


if __name__=="__main__":
  a_ = Algo("dummy")
  if SUPPORT_INCREMENTAL_DATA:
    a_.addData(AlgoData("0001-01-01 00:00:00",10.00,11.11,10))
    a_.addData(AlgoData("0001-11-11 11:11:11",10.00,11.11,10))
  print(a_.df_)