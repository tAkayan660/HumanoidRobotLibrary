import numpy as np
import matplotlib.pyplot as plt

#Constant parameter
dt          = 0.01
max_time    = 0.8
height_z    = 0.8
gravity     = 9.81
Tc          = np.sqrt(height_z/gravity)

#Calculation motion for Pendlum
def calc_x(x0, x0_dot):
    
    x = np.zeros(max_time/dt)
    t = 0.0
    for i in range(int(max_time/dt)):
       x[i] = x0*np.cosh(t/Tc)+Tc*x0_dot*np.sinh(t/Tc)
       t = t + dt
    return x
       
fig, axes = plt.subplots(2, 2, sharex=True, sharey=True)

#Plot
axes[0,0].plot(calc_x(-0.151,0.467))
axes[0,1].plot(calc_x(-0.2,0.791))
axes[1,0].plot(calc_x(0.2,-0.791))
axes[1,1].plot(calc_x(0.151, -0.467))

#Set Label
for i in range(2):
    for j in range(2):
        axes[i,j].set_xlabel('time [s]')
        axes[i,j].set_ylabel('x [m]')

#Graph show
plt.show()
