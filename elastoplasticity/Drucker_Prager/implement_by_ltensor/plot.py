import matplotlib.pyplot as plt 
import numpy as np 


file = np.loadtxt('strain_stress.txt')
strain = file[:,0]
stress = file[:,1]

plt.plot(strain, stress)
plt.show()