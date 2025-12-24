# region imports
from AlgorithmImports import *
# endregion

class BootCampTask(QCAlgorithm):

    def initialize(self):
        self.set_start_date(2017, 6, 1)
        self.set_end_date(2017, 6, 15)

        self.iwm = self.add_equity("IWM",Resolution.MINUTE)
        self.iwm.set_data_normalization_mode(DataNormalizationMode.RAW)

        #1,2. Select IWM minute resolution data and set it to RAW normalization mode

    def on_data(self, data):

        #3. Place an order for 100 shares of IWM and print the average fill price
        if not  self.portfolio.invested:
            self.MarketOrder("IWM",100)

            #4. Debug the average price of IWM
            self.Debug(str(self.portfolio["IWM"].average_price))

