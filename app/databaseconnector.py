import mysql.connector
INTRADAY_TABLE_ = "intraday_ohlcv"

mydb = mysql.connector.connect(
  host="localhost",
  port="3308",
  user="my_user",
  password="my_password",
  database="quant"
)