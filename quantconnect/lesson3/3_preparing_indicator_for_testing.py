# region imports
from AlgorithmImports import *
# endregion
class MomentumBasedTacticalAllocation(QCAlgorithm):

    def initialize(self):
        self.set_start_date(2007, 8, 1)  
        self.set_end_date(2010, 8, 1)  
        self.set_cash(3000)  
        
        self.add_equity("SPY", Resolution.DAILY)  
        self.add_equity("BND", Resolution.DAILY) 
        
        self.spy_momentum = self.momp("SPY", 50, Resolution.DAILY) 
        self.bond_momentum = self.momp("BND", 50, Resolution.DAILY) 
        
        #1. Set SPY Benchmark
        self.set_benchmark("SPY")

        #2. Warm up algorithm for 50 days to populate the indicators prior to the start date
        self.set_warm_up(50)
    
    def on_data(self, data):
        # You should validate indicators are ready before using them:
        if self.spy_momentum is None or self.bond_momentum is None or not self.bond_momentum.is_ready or not self.spy_momentum.is_ready:
            return

  