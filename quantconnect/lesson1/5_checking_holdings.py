# region imports
from AlgorithmImports import *
# endregion
class BootCampTask(QCAlgorithm):

    def initialize(self):
        self.set_start_date(2017, 6, 1)
        self.set_end_date(2017, 6, 2)
        
        #1. Update the add_equity command to request IBM data
        self.ibm = self.add_equity("IBM", Resolution.DAILY)
        
    def on_data(self, data):
        
        #2. Display the quantity of IBM Shares You Own
        self.debug("Number of IBM Shares: " + str(self.portfolio["IBM"].hold_stock))
        
