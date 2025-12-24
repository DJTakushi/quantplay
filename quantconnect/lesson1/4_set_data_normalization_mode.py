# region imports
from AlgorithmImports import *
# endregion
class BootCampTask(QCAlgorithm):

    def initialize(self):
        self.set_start_date(2017, 6, 1)
        self.set_end_date(2017, 6, 15)
        
        #1-2. Change the data normalization mode for SPY and set the leverage for the IWM Equity
        self.spy = self.add_equity("SPY", Resolution.DAILY)
        self.spy.set_data_normalization_mode(DataNormalizationMode.RAW)

        self.iwm = self.add_equity("IWM", Resolution.DAILY)
        self.iwm.SetLeverage(1)

    def on_data(self, data):
        pass
    
