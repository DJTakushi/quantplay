# todo
- [x] optimize for performance
  - [x] don't handle so little data in each sql commant
- [ ] metric calculations
  - [x] sharpe ratio
    - [x] fix intermittent failures (unsteady hours from csv)
      - [x] try clearing database at startup in this version of main (no)
  - [x] max drawdown
  - [ ] max drawdown duration
  - [ ] return over maximum drawdown
  - [ ] Calmar Ratio
- [x] unit-test new content
  - [x] quantitative trading content
  - [x] database creation (completed implicitly in test)
- [x] update_database takes filestring argument; gets data from api otherwise
- refactor algo1_data_retriever::update_database to have options
  - [x] update with whole json (-1)
  - [x] update with single row from json (will need to reorder json) (step)
  - [ ] update with data from API
- [x] ohlcv_data base class
  - [x] algo1_data
  - [x] daydata
  - [x] snapshot (for tracking portfolio over time)
    - [x] update snapshot in process
    - [x] append updated snapshot to list
    - [x] print snapshot list
- [x] remove data table from algo; algo should have the single responsibility of processing data, not managing it [eh, data scoping and management is part of the algo]
- [x] daydata replaced with latest day snapshots
- [x] refactor portfolio to include balance and current value
- [x] accept/record times in UTC, only print in local
  - [x] convert input times to UTC
  - [x] put values into table in UTC using timestamp (https://planetscale.com/blog/datetimes-vs-timestamps-in-mysql)
  - [x] switch c++ code to use better class that can easily display converted time[not necessary]
- [x] algocontroller
- [ ] dataretriever
  - [x] create data table (with override option)
  - [x] get_data() from table
    - [x] override option to get data from test table (no, populate table)
  - [x] unittest loads data into table
- [ ] api fetcher
  - take in struct
    - target table
    - mysql query(?)
  - [x] override in unittests to populate from csv
## convert
- [x] algo.py
  - [x] algo
    - [x] AlgoData struct ("snapshot")
      - algo will handle its own internal data
    - [x] addData
    - [x] loadData [no, manager will load data.  algo has 1 responsibility]
    - [x] process (verdict)
- [x] algomanager.py
  - [x] init
  - [x] getData
  - [x] simulate (process with data in unit-tests)
  - [x] analyze
- [ ] apigetter.py
- [x] csvconverter.py
- [x] databaseconnector.py
- [x] datagetter.py
- [x] daydata.py
- [x] recorder.py
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






# Notes
```
mariadb -h 127.0.0.1 -P 3306 -u root -p quant
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
## mysql integration
- https://github.com/mysql/mysql-connector-cpp
```
mkdir thirdparty && cd thirdparty
git clone https://github.com/mysql/mysql-connector-cpp.git
cd mysql-connector-cpp/
git checkout 8.0
mkdir build && cd build
cmake .. && sudo make install
sudo ldconfig
```
```
g++ -std=c++17 -I/home/danny/Downloads/mysql-connector-c++-8.3.0-linux-glibc2.28-x86-64bit/include/ -L/usr/local/mysql/connector-c++-8.0.33/lib64/debug/ ../app_cpp/main.cpp -lmysqlcppconn8 -o app
```
- https://dev.mysql.com/doc/connector-cpp/1.1/en/connector-cpp-examples-connecting.html
- connection problems 
  - 8.0 fails to detect connection
    ```
    terminate called after throwing an instance of 'mysqlx::abi2::r0::Error'
    what():  CDK Error: unexpected message
    Aborted (core dumped)
    ```
  - 5.x complains my sqlx connection is out of order

## mariadb notes
My attempts to connect to a mysql container using the mysql-connector-cpp were unsuccessful, so I switched to mariadb.  The documentation seems clearer (mysql's docker image documentation is regrettably unclear to me), and I appreciate the ethos of the MariaDB fork.

### container
- https://hub.docker.com/_/mariadb
### mardiaDB Connector/C++
- https://mariadb.com/docs/server/connect/programming-languages/cpp/install/
- download C++ connector for Ubuntu (I used version for 23.04 AMD64)
- installation instructions (I believe):
```
sudo apt install libmariadb3 libmariadb-dev
cd ~/Downloads

tar -xvzf mariadb-connector-cpp-*.tar.gz

cd mariadb-connector-cpp-*/

sudo install -d /usr/include/mariadb/conncpp
sudo install -d /usr/include/mariadb/conncpp/compat

sudo install include/mariadb/* /usr/include/mariadb/
sudo install include/mariadb/conncpp/* /usr/include/mariadb/conncpp
sudo install include/mariadb/conncpp/compat/* /usr/include/mariadb/conncpp/compat

sudo install -d /usr/lib/mariadb
sudo install -d /usr/lib/mariadb/plugin

sudo install lib/mariadb/libmariadbcpp.so /usr/lib
sudo install lib/mariadb/plugin/* /usr/lib/mariadb/plugin
```
#### useful links
- https://mariadb.com/docs/server/connect/programming-languages/cpp/connect/

## nlohmann json installation
```
git clone git@github.com:nlohmann/json.git
sudo cp -r json/include/nlohmann /usr/local/include/
```