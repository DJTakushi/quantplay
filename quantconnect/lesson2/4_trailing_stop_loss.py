# region imports
from AlgorithmImports import *
# endregion
class BootCampTask(QCAlgorithm):
    
    # Order ticket for our stop order, Datetime when stop order was last hit
    stop_market_ticket = None
    stop_market_order_fill_time = datetime.min
    highest_spy_price = 0
    
    def initialize(self):
        self.set_start_date(2018, 12, 1)
        self.set_end_date(2018, 12, 10)
        self.set_cash(100000)
        spy = self.add_equity("SPY", Resolution.DAILY, data_normalization_mode=DataNormalizationMode.RAW)
        
    def on_data(self, data):
        
        if (self.time - self.stop_market_order_fill_time).days < 15:
            return

        if not self.portfolio.invested:
            self.market_order("SPY", 500)
            self.stop_market_ticket = self.stop_market_order("SPY", -500, 0.9 * self.securities["SPY"].close)
            # The initial highest price is the current price
            self.highest_spy_price = self.securities["SPY"].close
        else:
            
            #1. Check if the SPY price is higher that highest_spy_price.
            if self.securities["SPY"].close > self.highest_spy_price:
                
                #2. Save the new high to highest_spy_price; then update the stop price to 90% of highest_spy_price 
                self.highest_spy_price = self.securities["SPY"].close
                self.stop_market_ticket = self.stop_market_order("SPY", -500, 0.9 * self.securities["SPY"].close)

                #3. Print the new stop price with debug()
                self.debug(self.highest_spy_price)
            pass
                
    def on_order_event(self, order_event):
        if order_event.status != OrderStatus.FILLED:
            return
        if self.stop_market_ticket and self.stop_market_ticket.order_id == order_event.order_id: 
            self.stop_market_order_fill_time = self.time
            
