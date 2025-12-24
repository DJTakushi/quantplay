import pandas as pd
import numpy as np
from pathlib import Path

pd.options.display.float_format = '{:.16f}'.format


# read ige data into dataframe
script_dir = Path(__file__).parent.absolute()   
ige_ = pd.read_csv(f'{script_dir}/data/3_4_ige.csv')

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
total_ret = ige_["ExcessDailyRet"].sum()
n = ige_["ExcessDailyRet"].count()
avg_ = ige_["ExcessDailyRet"].mean()
variance_= ige_["ExcessDailyRet"].var()
std_ = ige_["ExcessDailyRet"].std()
sharpe_ = np.sqrt(252) * avg_ / std_

# print data
print(ige_.to_string())
print(ige_.info())

print("Adj Close:"+ ige_["ExcessDailyRet"].to_string())
print("total_ret_:"+str(total_ret))
print("n_:"+str(n))
print("avg_:"+str(avg_))
print("variance_:"+str(variance_))
print("std_:"+str(std_))
print("sharpe_:"+str(sharpe_))

print("min Adj Close:"+ str(ige_["Adj Close"].min()))
print("max Adj Close:"+ str(ige_["Adj Close"].max()))