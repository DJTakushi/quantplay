import databaseconnector
from datetime import datetime
import pandas as pd
from sqlalchemy import create_engine
from transaction import Transaction
# TODO: restructure Algo to receive data from manager
  # process will then be run on the top data
  # this will simplify index finding AND reduce Algo's data maintenance burden
class Algo:
  ticker_=""
  df_ = pd.DataFrame()
  process_count_ = 0
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
