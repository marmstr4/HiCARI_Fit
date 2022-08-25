import matplotlib.pyplot as plt
import numpy as np

file = open('output_file.csv', 'r')
life1, life2, chi1, chi2, chi3 = [], [], [], [], []
data = []
for line in file.readlines():
    fields = line.split(' ')
    life1.append(fields[0])
    life2.append(fields[1])
    chi1.append(fields[2])
    chi2.append(fields[3])
    chi3.append(fields[4])
    data.append([fields[0],fields[1],fields[4]])

#for i in range(len.fields()):
#    for j in range(len.fields()):
#        data[i][j] = fields[4]

fig,ax=plt.subplots(1,1)
cp = ax.contourf(data,100,cmap="magma")
fig.colorbar(cp) # Add a colorbar to a plot
ax.set_title('Filled Contours Plot')
#ax.set_xlabel('x (cm)')
ax.set_ylabel('y (cm)')
plt.show()
