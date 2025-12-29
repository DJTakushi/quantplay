# region imports
from AlgorithmImports import *
# endregion

class EquitiesStaticTemplateAlgorithm(QCAlgorithm):
    _symbols = []
    _tolerance = 0.0025
    _previous_day = 0

    def initialize(self):
        self.set_start_date(2024, 9, 1)
        self.set_end_date(2024, 12, 31)
        self.set_cash(100000)
        
        self.settings.automatic_indicator_warm_up = True

        for ticker in ["SPY", "QQQ", "IWM"]:
            equity = self.add_equity(ticker)
            equity.macd = self.macd(equity.symbol, 12, 26, 9, MovingAverageType.EXPONENTIAL, Resolution.DAILY)
            self.plot_indicator(equity.symbol.value, equity.macd)
            self._symbols.append(equity.symbol)
            

    def on_data(self, data: Slice):
        if self._previous_day == self.time.day: return

        for symbol in self._symbols:
            match self._get_order_direction(symbol):
                case OrderDirection.BUY:
                    self.set_holdings(symbol, 1 / len(self._symbols))
                case OrderDirection.SELL:
                    self.liquidate(symbol)

        self._previousDay = self.time.day
    
    def _get_order_direction(self, symbol) -> OrderDirection:
        security = self.securities[symbol]
        quantity = security.holdings.quantity
        macd = security.macd
        signal_delta_percent = (macd.current.value - macd.signal.current.value)/macd.fast.current.value
        if quantity <= 0 and signal_delta_percent > self._tolerance:
            return OrderDirection.BUY
        if quantity >= 0 and signal_delta_percent < -self._tolerance:
            return OrderDirection.SELL
        return OrderDirection.HOLD