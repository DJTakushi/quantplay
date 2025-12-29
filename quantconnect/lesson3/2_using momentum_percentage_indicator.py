# region imports
from AlgorithmImports import *
# endregion
class MomentumBasedTacticalAllocation(QCAlgorithm):

    spy_momentum = None
    bond_momentum = None

    def initialize(self):
        self.set_start_date(2007, 6, 1)  
        self.set_end_date(2010, 6, 1)  
        self.set_cash(3000)   
        
        self.spy = self.add_equity("SPY", Resolution.DAILY)  
        self.bnd = self.add_equity("BND", Resolution.DAILY)  
        
        #1. Add 50-day Momentum Percent indicator for SPY
        self.spy_momentum = self.MOMP("SPY", 50, Resolution.DAILY)
        
        #2. Add 50-day Momentum Percent indicator for BND
        self.bond_momentum = self.MOMP("BND", 50, Resolution.DAILY)

    def on_data(self, data):
        pass

