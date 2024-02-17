# todo
- [ ] accept/record times in UTC, only print in local
  - [ ] convert input times to UTC
  - [ ] put values into table in UTC using timestamp (https://planetscale.com/blog/datetimes-vs-timestamps-in-mysql)
  - [ ] switch c++ code to use better class that can easily display converted time
- [x] algocontroller
- [ ] dataretriever
  - [ ] create data table (with override option)
  - [x] get_data() from table
    - [ ] override option to get data from test table
  - [ ] unittest loads data into table
- [ ] api fetcher
  - take in struct
    - target table
    - mysql query(?)
  - [ ] override in unittests to populate from csv
## convert
- [x] algo.py
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