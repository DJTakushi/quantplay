import mysql.connector
INTRADAY_TABLE_ = "intraday_ohlcv"
host_ = "localhost"
port_ = "3308"
user_ = "my_user"
password_ = "my_password"
database_ = "quant"

mydb = mysql.connector.connect(
  host=host_,
  port=port_,
  user=user_,
  password=password_,
  database=database_
)