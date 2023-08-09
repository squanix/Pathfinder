import matplotlib.pyplot as plt
import pandas as pd
from statistics import mean, median
import numpy as np

df = pd.read_csv("/home/squanix/vscodeserver/Pathfinder/dataB.csv") ## Two path
dg = pd.read_csv("/home/squanix/vscodeserver/Pathfinder/dataA.csv") ## Four path

def my_min_function(somelist):
    min_value = None
    for value in somelist:
        if not min_value:
            min_value = int(value)
        elif int(value) < min_value:
            min_value = int(value)
    return min_value

def my_max_function(somelist):
    max_value = None
    for value in somelist:
        if not max_value:
            max_value = int(value)
        elif int(value) > max_value:
            max_value = int(value)
    return max_value

print ("Two path")
print (df.describe())
print ("Four path")
print (dg.describe())

##plt.hist(df, color='lightgreen', ec='black', bins=15)
###plt.hist(dg, color='lightblue', ec='black', bins=15)
##plt.savefig('/home/squanix/vscodeserver/Pathfinder/Data2Path.png')