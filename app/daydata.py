class DayData:
  date=""
  open=None
  high=None
  low=None
  close=None
  portfolio=0
  def __init__(self, date_):
    self.date = date_
  def to_dict(self):
    # used for easy conversion to dataframe
    return{
      'date': self.date,
      'open': self.open,
      'close': self.close,
      'portfolio':self.portfolio
    }
