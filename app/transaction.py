class Transaction:
  time_ = None
  value_ = 0.00
  transaction_ = ""

  def __init__(self, time, value, transaction):
    self.time_ = time
    self.value_ = value
    self.transaction_ = transaction
  def print(self):
    print(self.time_ +": "+self.transaction_+" at "+str(self.value_))
