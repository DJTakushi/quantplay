# region imports
from AlgorithmImports import *
# endregion
class BootCampTask(QCAlgorithm):

    def initialize(self):
        self.set_start_date(2017, 6, 1)
        self.set_end_date(2017, 6, 15)
        
        # Manually Select Data
        self.spy = self.add_equity("SPY", Resolution.MINUTE)
        self.iwm = self.add_equity("IWM", Resolution.MINUTE)
        
    def on_data(self, data):
        pass
