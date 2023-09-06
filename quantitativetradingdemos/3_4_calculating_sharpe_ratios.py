import pandas as pd
import numpy as np

# read ige data into dataframe
ige_ = pd.read_csv('data/3_4_ige.csv')

# correct date to common datetime format
ige_['Date']=pd.to_datetime(ige_['Date'])

# sort by Date ascending
ige_.sort_values(by='Date',inplace=True)

# populate Dailyret values
ige_["PrevClose"] = ige_["Adj Close"].shift(1)
ige_["Dailyret"]=(ige_["Adj Close"]-ige_["PrevClose"])/ige_["PrevClose"]

# excess excedes adjusted annual 4%
ige_["ExcessDailyRet"]=ige_["Dailyret"]-(0.04/252)

# calculate Sharpe Ratio
avg_ = ige_["ExcessDailyRet"].mean()
std_ = ige_["ExcessDailyRet"].std()
sharpe_ = np.sqrt(252) * avg_ / std_

# print data
print(ige_.to_string())
print(ige_.info())
print("avg_:"+str(avg_))
print("std_:"+str(std_))
print(sharpe_)