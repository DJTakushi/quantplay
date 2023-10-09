import csv, datetime, json, os
from datetime import datetime
class CsvConverter:
  def __init__(self,fp):
    # read a csv and print it out
    with open(fp,newline='') as csvfile:
      spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
      for row in spamreader:
        print(', '.join(row))

  @staticmethod
  def toAlphaVantageJson(fp, ticker):
    # read csv and return an AlphaVantage json copy of it
    j_={}

    # metadata creation
    metadata_ = {}
    metadata_["1. Information"]=""
    metadata_["2. Symbol"]=ticker

    rtime = datetime.fromtimestamp(os.path.getmtime(fp)).isoformat()
    rtime = rtime.split('.')[0]
    rtime=rtime.replace("T"," ")

    metadata_["3. Last Refreshed"]=rtime
    metadata_["4. Interval"]=""
    metadata_["5. Output Size"]=""
    metadata_["6. Time Zone"]=""
    j_["Meta Data"]=metadata_

    # time series
    ts_={}

    with open(fp,newline='') as csvfile:
      spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
      for row in spamreader:
        entry_ = {}
        r_ = row[0].split(',')

        if r_[0] != "Date":
          d_=r_[0].split("/")
          date_ = datetime(int(d_[2]),int(d_[0]),int(d_[1]))
          datetime_=date_.isoformat()
          datetime_=datetime_.split('.')[0]
          datetime_=datetime_.replace("T"," ")

          entry_["1. open"]=r_[1]
          entry_["2. high"]=r_[2]
          entry_["3. low"]=r_[3]
          entry_["4. close"]=r_[6]
          entry_["5. volume"]=r_[5]

          ts_[datetime_]=entry_

    j_["Time Series ("]=ts_

    return json.dumps(j_)

if __name__=="__main__":
  j_ = CsvConverter.toAlphaVantageJson(
    "../quantitativetradingdemos/data/3_4_ige.csv","IBM")
  print(j_)