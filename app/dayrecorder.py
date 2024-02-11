from daydata import DayData
import pandas as pd
### manages daily records

class dayRecorder:
  days = []
  def __init__(self):
    pass

  def getCurrentDate(self):
    if len(self.days) > 0:
      return self.days[-1].date
    return None # default null

  def getDataFrame(self):
    return pd.DataFrame.from_records([s.to_dict() for s in self.days])

  def startNewDay(self, date, open=None):
    self.days.append(DayData(date))
    if open:
      self.setCurrentOpen(open)

  def setCurrentOpen(self, open):
    self.days[-1].open=open

  def setCurrentClose(self, close):
    self.days[-1].close=close

  def setCurrentPortfolio(self,portfolio):
    self.days[-1].portfolio=portfolio
