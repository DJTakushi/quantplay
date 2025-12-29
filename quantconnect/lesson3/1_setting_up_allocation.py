# region imports
from AlgorithmImports import *
# endregion
class MomentumBasedTacticalAllocation(QCAlgorithm):

    def initialize(self):
        self.set_start_date(2007, 8, 1)  # Set Start Date
        self.set_end_date(2010, 8, 1)  # Set End Date
        
        #1. Subscribe to SPY -- S&P 500 Index ETF -- using daily resolution
        spy = self.add_equity("SPY", Resolution.DAILY, data_normalization_mode=DataNormalizationMode.RAW)
        
        #2. Subscribe to BND -- Vanguard Total Bond Market ETF -- using daily resolution
        bnd = self.add_equity("BND", Resolution.DAILY, data_normalization_mode=DataNormalizationMode.RAW)
        
        #3. Set strategy cash to $3000
        self.set_cash(100000)

    def on_data(self, data):
        pass 
     
