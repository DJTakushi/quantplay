# region imports
from AlgorithmImports import *
# endregion

class BootCampTask(QCAlgorithm):

    def initialize(self):
        self.set_start_date(2018, 12, 1) # Set Start Date
        self.set_end_date(2019, 4, 1) # Set End Date
        self.set_cash(100000) # Set Strategy Cash
        
        #1. Subscribe to SPY in raw mode
        spy = self.add_equity("SPY", Resolution.DAILY)
        spy.set_data_normalization_mode(DataNormalizationMode.RAW)
        self.lastOrderEvent = None

    def on_data(self, data):
        
        if not self.portfolio.invested:
            #2. Create market order to buy 500 units of SPY
            self.market_order("SPY", 500)

            #3. Create a stop market order to sell 500 units at 90% of the SPY current price
            self.stop_market_order("SPY", -500, 0.9*self.securities["SPY"].Close)
