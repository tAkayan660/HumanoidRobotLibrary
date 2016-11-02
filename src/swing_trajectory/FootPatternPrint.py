import numpy as np
import matplotlib.pyplot as plt

time = []
foot_pos_x = []
foot_pos_y = []
foot_pos_z = []

data = np.loadtxt('swing_foot_trajectory.csv')

print len(data)

for i in range(len(data)):
    time.append(data[i][0])
    foot_pos_x.append(data[i][1])
    foot_pos_y.append(data[i][2])
    foot_pos_z.append(data[i][3])

fig = plt.figure()
ax1 = fig.add_subplot(2,1,1)
ax2 = fig.add_subplot(2,1,2)

ax1.plot(time, foot_pos_x, 'r', label='Foot Trajectory X axis')
ax1.grid()

ax2.plot(time, foot_pos_z, 'g', label='Foot Trajectory Z axis')
ax2.grid()

ax1.legend(loc='best')
ax2.legend(loc='best')

plt.show()
