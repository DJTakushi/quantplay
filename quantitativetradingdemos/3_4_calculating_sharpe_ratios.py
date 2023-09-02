import pandas as pd

# read ige data into dataframe
ige_ = pd.read_csv('data/3_4_ige.csv')

# correct date to common datetime format
ige_['Date']=pd.to_datetime(ige_['Date'])

# sort by Date ascending
ige_.sort_values(by='Date',inplace=True)

# add Dailyret
ige_["Dailyret"]=0.0

# populate Dailyret values
#todo https://stackoverflow.com/questions/16476924/how-to-iterate-over-rows-in-a-dataframe-in-pandasgit

print(ige_.to_string())
print(ige_.info())