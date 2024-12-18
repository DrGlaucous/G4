import csv
import matplotlib.pyplot as plt 
import numpy as np


#this function sucks
def rsqval(slope: float, intercept: float, val_x: list, actual_val_y: list) -> float:
    unique_x = np.array(val_x)
    unique_y = np.array(actual_val_y)

    calculated_y = np.array(unique_x * slope + intercept)

    corr_mat = np.corrcoef(unique_y, calculated_y)
    corr = corr_mat[0, 1]
    return corr ** 2
    




files_old = [("old_speed_200.csv", "Speed: 200"),
         ("old_speed_300.csv", "Speed: 300"),
         ("old_speed_400.csv", "Speed: 400"),
         ("old_speed_500.csv", "Speed: 500"),
         ("old_speed_600.csv", "Speed: 600"),
         ]


files_new = [("speed_200.csv", "NSpeed: 200"),
         ("speed_300.csv", "NSpeed: 300"),
         ("speed_400.csv", "NSpeed: 400"),
         ("speed_500.csv", "NSpeed: 500"),
         ("speed_600.csv", "NSpeed: 600"),
         ]


#all_files = [files_old, files_new]
all_files = [files_new,]


slope_relations = [[200,
                   300,
                   400,
                   500,
                   600],
                   [0.0,
                   0.0,
                   0.0,
                   0.0,
                   0.0],
                   ]


for i, fileset in enumerate(all_files):
    plt.figure(i)
    for j, linn in enumerate(fileset):
        with open(linn[0]) as FP:
            x = []
            y = []
            line_reader = csv.reader(FP, delimiter=',')
            for row in line_reader:
                x.append(float(row[1])) #voltage
                y.append(float(row[0])) #RPM
            plt.scatter(x, y, label = linn[1])#, c=[1.0,0.0,1.0])
            slope_arr_x = np.unique(x)
            slope_arr_y = np.poly1d(np.polyfit(x, y, 1))(np.unique(x))
            linslope = (slope_arr_y[-1] - slope_arr_y[0])/(slope_arr_x[-1] - slope_arr_x[0])
            lincept = slope_arr_y[0]  - linslope * slope_arr_x[0]
            
            rq = rsqval(linslope, lincept, x, y)
            print("Plot: {} had r^2 of {}".format(linn[1], rq))

            plt.plot(np.unique(x), np.poly1d(np.polyfit(x, y, 1))(np.unique(x)), label = ("{} * Volt + {}".format(linslope, lincept)))
            
            #put slopes into slope relation list
            slope_relations[1][j] = linslope


    plt.xlabel('Voltage')
    plt.ylabel('RPM')
    plt.legend()
    print("--------------------")



plt.figure(all_files.__len__())
plt.scatter(slope_relations[0], slope_relations[1], label = "Wow")

fitvals = np.polyfit(slope_relations[0], slope_relations[1], 1)
slar_x = np.array(slope_relations[0])
slar_y = np.poly1d(fitvals)(slar_x)

plt.plot(slar_x, slar_y, label = "wow3")

plt.xlabel('Spin Speed')
plt.ylabel('Slope of RPM change given Voltage')

print(fitvals)

plt.show()


