# todo
- [ ] metric calculations
  - [x] sharpe ratio
    - [ ] programatic zero-risk rate
  - [x] max drawdown
    - [x] refactor to return timestamps
  - [x] max drawdown duration
    - [ ] refactor to return timestamps
  - [ ] return over maximum drawdown
  - [ ] Calmar Ratio
  - [ ] print function from analzyer to print all relevant metrics (neatly) for comparison
- [ ] try different algos
- [ ] live usage
- [ ] plot portfolio value
- [ ] timestamps entered into database for grafana usage

## docekrize
- set up database
- populate database
- real control

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