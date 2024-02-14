
# Notes
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

# todo
- [x] algocontroller
  - [ ] dataretriever

## convert
- [ ] algo.py
  - [x] algo
    - [x] AlgoData struct ("snapshot")
      - algo will handle its own internal data
    - [x] addData
    - [x] loadData [no, manager will load data.  algo has 1 responsibility]
    - [x] process (verdict)
- [ ] algomanager.py
  - [ ] init
  - [ ] getData
  - [ ] simulate
  - [ ] analyze
- [ ] apigetter.py
- [ ] csvconverter.py
- [ ] databaseconnector.py
- [ ] datagetter.py
- [x] daydata.py
- [x] dayrecorder.py
- [x] portfolio.py
- [x] transaction.py

## create algoController
- handles algo data & updates for algoManager
- algoController(*dbConnection)
  - (-) dbConnection
  - (-) algo
  - (-) latest_data_update_ts (timestamp for latest update of data; used for searching data)
  - (-) dataRetriever
    - list<*algoData> get_data() (gets data from database)
      - algoData is a derived struct unique to each algo
      - list<*algoData> get_dataSingle() (gets ONE data from database)
   - [x] (+) updateData() gets list from dataRetriever and updates data in algo
    - [x] (+) updateDataSingle() gets ONE from dataRetriever
  - [x] (+) getTransaction()

## docekrize
- set up database
- populate database
- real control

## doxygen demo
- [x]

## restructure
- [x] common (transactions, daydata)
- [x] algoX
- algoManager
  - algoManager
  - portfolio