from transaction import Transaction
class portfolio:
  transactions_ = []
  balance_ = 0.0
  shares_ = 0
  value_current_ = 0.0
  def __init__(self):
    pass

  def getEquityValue(self):
    return self.shares_*self.value_current_

  def getPortfolioValue(self):
    return self.balance_ + self.getEquityValue()

  def setCurrentValue(self, val):
    self.value_current_ = val

  def addTransaction(self, t_):
    self.transactions_.append(t_)
    if t_.transaction_ == "buy":
      self.shares_+=1
      self.balance_-=t_.value_
    elif t_.transaction_ == "sell":
      self.shares_-=1
      self.balance_+=t_.value_
