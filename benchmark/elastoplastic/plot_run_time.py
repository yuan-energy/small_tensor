import numpy as np
import matplotlib.pyplot as plt

# --------------------------------------------
# --------------------------------------------
# --------------------------------------------

# # #############################
import matplotlib.pylab as pylab
params = {
'legend.fontsize': 'x-large',
          'figure.figsize': (16, 12),
         'axes.labelsize': 'x-large',
         'axes.titlesize':'x-large',
         'xtick.labelsize':'x-large',
         'ytick.labelsize':'x-large'
}
pylab.rcParams.update(params)
# #############################
import matplotlib
font = {'family' : 'normal',
        'weight' : 'bold',
        'size'   : 22}
matplotlib.rc('font', **font)
# #############################
# --------------------------------------------
# --------------------------------------------




import matplotlib.pyplot as plt; plt.rcdefaults()
import numpy as np
import matplotlib.pyplot as plt
 
objects = ('LTensor', 'SmallTensor')
y_pos = np.arange(len(objects))
performance = [0.126,0.084]

plt.bar(y_pos, performance, align='center', alpha=0.5)
plt.xticks(y_pos, objects)
plt.ylabel('Run Time [seconds] ')
plt.title('Run Time of Elastoplastic Examples  ')
 
plt.savefig('run_time_elastoplastic_examples.jpg')
plt.show()


