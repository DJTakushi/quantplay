# region imports
from AlgorithmImports import *
# endregion
class MomentumBasedTacticalAllocation(QCAlgorithm):

    def initialize(self):
        self.set_start_date(2007, 8, 1) 
        self.set_end_date(2010, 8, 1) 
        self.set_cash(3000)   
        
        self.spy = self.add_equity("SPY", Resolution.DAILY)  
        self.bnd = self.add_equity("BND", Resolution.DAILY)  
        
        self.spy_momentum = self.momp("SPY", 50, Resolution.DAILY)
        self.bond_momentum = self.momp("BND", 50, Resolution.DAILY) 
        
        self.set_benchmark("SPY")  
        self.set_warm_up(50) 
        
    def on_data(self, data):
        
        # Don't place trades until our indicators are warmed up:
        if self.is_warming_up:
            return
        
        #1. If SPY has more upward momentum than BND, then we liquidate our holdings in BND and allocate 100% of our equity to SPY
        if self.spy_momentum.current.value > self.bond_momentum.current.value:
            self.liquidate("BND")
            self.set_holdings("SPY",1.0)

        #2. Otherwise we liquidate our holdings in SPY and allocate 100% to BND
            self.liquidate("SPY")
            self.set_holdings("BND",1.0)
        
