import databaseconnector
from datetime import datetime, timedelta
import pandas as pd
from sqlalchemy import create_engine
from transaction import Transaction

class AlgoData:
  datetime_ = ""
  open_ = 0.0
  close_ = 0.0
  volume_ = 0
  def __init__(self, data):
    self.datetime_ = data['datetime']
    self.open_ = data['open']
    self.close_ = data['close']
    self.volume_ = data['volume']
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
    self.df_ = pd.DataFrame(columns=AlgoData.getAttributes())

  def addData(self, d):
    # add data to existing dataframe
    t_ = pd.DataFrame(d.getData(), columns = AlgoData.getAttributes())
    if self.df_.empty: # pandas doesn't appreciate concating empty dataframes
      self.df_ = t_
    else:
      self.df_ = pd.concat([self.df_,t_], axis=0, ignore_index=True)

  def loadData(self, time_start=None, time_end=None):
    # retrieve data from database to populate dataframe
    time_start_ = ""
    time_end_ = ""
    if time_end == None:
      time_end_ = datetime.now().isoformat()[:18]
    else:
      time_end_ = time_end.strftime('%Y-%m-%d %X')
    if time_start == None:
      if time_end == None: # get full dataset
        time_start_ = "0001-01-01 00:00:00" #min datetime
      else: #get last day
        time_start_calc_ = time_end - timedelta(seconds=60)
        time_start_ =time_start_calc_.strftime('%Y-%m-%d %X')
    else:
      time_start_ = time_start.strftime('%Y-%m-%d %X')

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

    time_end_ = time_end.strftime('%Y-%m-%d %X')
    latest_ = self.df_[(self.df_['datetime'] == time_end_)]
    # TODO: return None if data entry not found
    val_ = latest_.iloc[0]["close"] # get 0 index, "close" attribute
    self.value_last_ = val_

    ret_ = None
    # for now, only return a single buy at the first instance
    if self.process_count_== 0:
      ret_ = Transaction(time_end_, val_, "buy")
    self.process_count_+=1
    return ret_


if __name__=="__main__":
  a_ = Algo("dummy")
  row_ = {"datetime":"0001-01-01 00:00:00","open":10.00,"close":11.11,"volume":10}
  a_.addData(AlgoData(row_))
  row_ = {"datetime":"0001-11-11 11:11:11","open":11.11,"close":22.22,"volume":30}
  a_.addData(AlgoData(row_))
  print(a_.df_)