class Transaction:
  time_ = None
  value_ = 0.00
  transaction_ = ""

  def __init__(self, time, value, transaction):
    self.time_ = time
    self.value_ = value
    self.transaction_ = transaction

class Algo:
  transactions_ = []
  def __init__(self):
    pass
  def getData(self, time_start, time_end):
    # retrieve data from database to populate dataframe
    pass
  def process(self, time_end=None):
    # process data and generate a position at time_end (end of data by default)
    pass
  def buy(self, time, value):
    self.transactions_.append(Transaction(time, value, "buy"))
  def sell(self, time, value):
    self.transactions_.append(Transaction(time, value, "sell"))
  def analyze(self):
    # compute metrics (profit/loss)
    pass