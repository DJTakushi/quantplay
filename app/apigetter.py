import requests
import os
from datetime import date
ALPHAVANTAGE_API_KEY = os.environ['ALPHAVANTAGE_API_KEY']

def get_TIME_SERIES_INTRADAY(symbol, interval="1min", month=""):
  if month == "":
    now_ = date.today()
    month = str(now_.year)+"-"+str(now_.month)
  call_ = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&"
  call_ += "symbol="+symbol
  call_ += "&interval="+interval
  call_ += "&month="+month
  call_ += "&outputsize=full&apikey="+ALPHAVANTAGE_API_KEY
  ret_ = requests.get(call_)
  return ret_.text
