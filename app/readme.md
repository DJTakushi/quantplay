```mermaid
---
title: class diagram
---
classDiagram
  class algo{
    +addData(d)
    +getData(time_start,time_end)
    +process(time_end) Transaction
  }

  class algomanager{
    -ticker_
    -df_
    +__init__(ticker)
    +getData(time_start,time_end)
    +simulate()
    +analyze()
  }
  algomanager --* algo : algo_
  algomanager --* portfolio : portfolio_
  algomanager --* dayRecorder : dayRecorder_

  class apigetter{
    +get_TIME_SERIES_INTRADAY()
  }

  class datagetter{
    createIntradyTable()
    insert_TIME_SERIES_INTRADAY()
  }
  class DayData{
    -date
    -open
    -high
    -low
    -close
    -portfolio
  }
  class dayRecorder{
    -days []
    +getCurrentData()
    +getDataFrame()
    +startNewDay(date,open)
    +setCurrentOpen(open)
    +setCurrentClose(close)
    +setCurrentPortfolio(portfolio)
  }
  dayRecorder --* DayData : days []

  class portfolio{
    getEquityValue()
    getPortfolioVaue()
    setCurrentValue(val)
    addTransaction(t_)
  }
  portfolio --* Transaction : transactions_[]

  class Transaction{
    -time_
    -value_
    -transaction_
    +__init__(time,value,transaction)
    +print()
  }
```

```
mysql -h 127.0.0.1 -P 3308 -u my_user -p quant
```

### Sample Queries
```
CREATE TABLE ibm_ohlcv (ticker varchar(255), date DATE, open float(2), high float(2), low float(2), close float(2), volume int);

INSERT INTO ibm_ohlcv (ticker, date, open, high, low, close, volume) VALUES ("ibm", "2023-09-17", 0.00, 0.01, 0.002, 0.003, 69);

SELECT * FROM ibm_ohlcv WHERE ticker="ibm";
```

```
CREATE TABLE intraday_ohlcv_IBM (ticker varchar(255), datetime DATETIME, open float(2), high float(2), low float(2), close float(2), volume int, refresh DATETIME);

INSERT INTO intraday_ohlcv_IBM (ticker, datetime, open, high, low, close, volume, refresh) VALUES ("IBM","2023-09-15 19:55:00", 146.0300, 146.0300,146.0300, 146.0300,1,"2023-09-17 16:18");
```


```
python3 -m pip install mysql-connector
python3 -m pip install jupyter
python3 -m pip install SQLAlchemy
python3 -m pip install pymysql
```
```
jupyter notebook
```

### Sample API requests
```
https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=IBM&interval=5min&apikey=demo
```

# Resources
- https://medium.com/@chrischuck35/how-to-create-a-mysql-instance-with-docker-compose-1598f3cc1bee
- https://stackoverflow.com/questions/1650946/mysql-create-table-if-not-exists-error-1050