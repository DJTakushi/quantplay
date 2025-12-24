# region imports
from AlgorithmImports import *
# endregion
class BootCampTask(QCAlgorithm):

    def initialize(self):
        self.set_cash(100000)
        self.add_equity("SPY", Resolution.DAILY)
        
        
    def on_data(self, data):
        pass

