# region imports
from AlgorithmImports import *
# endregion

class BootCampTask(QCAlgorithm):
    
    # Order ticket for our stop order, Datetime when stop order was last hit
    stop_market_ticket = None
    stop_market_fill_time = datetime.min
    
    def initialize(self):
        self.set_start_date(2018, 12, 1)
        self.set_end_date(2019, 4, 1)
        self.set_cash(100000)
        spy = self.add_equity("SPY", Resolution.DAILY, data_normalization_mode=DataNormalizationMode.RAW)
        
    def on_data(self, data):
        
        #4. Check that at least 15 days (~2 weeks) have passed since we last hit our stop order
        if ((self.time - self.stop_market_fill_time).days < 15):
            return
        
        if not self.portfolio.invested:
            self.market_order("SPY", 500)
            
            #1. Create stop loss through a stop market order
            self.stop_market_ticket = self.stop_market_order("SPY",  -500, 0.9*self.securities["SPY"].close)

    def on_order_event(self, order_event):
        
        if order_event.status != OrderStatus.FILLED:
            return

        # Printing the security fill prices.
        self.debug(self.securities["SPY"].close)

        #2. Check if we hit our stop loss (Compare the order_event.id with the stop_market_ticket.order_id)
        #   It's important to first check if the ticket isn't null (i.e. making sure it has been submitted)
        if self.stop_market_ticket is not None and self.stop_market_ticket.order_id == order_event.order_id :
            #3. Store datetime
            self.stop_market_fill_time = self.time
