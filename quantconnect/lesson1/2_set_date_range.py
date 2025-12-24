# endregion
class BootCampTask(QCAlgorithm):

    def initialize(self):
        
        #1-2. Set Date Range
        self.set_start_date(2017, 1, 1)
        self.set_end_date(2017, 10,31)
        self.add_equity("SPY", Resolution.DAILY)
        
    def on_data(self, data):
        pass
