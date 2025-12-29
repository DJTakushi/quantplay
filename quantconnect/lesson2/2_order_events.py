# region imports
from AlgorithmImports import *
# endregion

class BootCampTask(QCAlgorithm):

    def initialize(self):
        
        self.set_start_date(2018, 12, 1) 
        self.set_end_date(2019, 4, 1) 
        self.set_cash(100000) 
        spy = self.add_equity("SPY", Resolution.DAILY, data_normalization_mode=DataNormalizationMode.RAW)
        self.last_order_event = None
        
    def on_data(self, data):
    
        if not self.portfolio.invested:
            self.market_order("SPY", 500)
            self.stop_market_order("SPY", -500, 0.9 * self.securities["SPY"].close)
        
    def on_order_event(self, order_event):
        
        #1. Write code to only act on fills
        if order_event.status == OrderStatus.FILLED:
            #2. Save the order_event to last_order_event, use debug to print the event order_id
            self.last_order_event = order_event
            self.debug(order_event.order_id)
