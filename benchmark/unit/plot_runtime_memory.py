import numpy as np
import matplotlib.pyplot as plt


# # #############################
import matplotlib.pylab as pylab
params = {
'legend.fontsize': 'xx-large',
          'figure.figsize': (16, 12),
         'axes.labelsize': 'xx-large',
         'axes.titlesize':'xx-large',
         'xtick.labelsize':'xx-large',
         'ytick.labelsize':'xx-large'
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
 
objects = ('LTensor', 'libxsmm', 'SmallTensor')
y_pos = np.arange(len(objects))
performance = [3.316, 9.896, 3.26]
 
plt.bar(y_pos, performance, align='center', alpha=0.5)
plt.xticks(y_pos, objects)
plt.ylabel('Memory [MB] ')
plt.title('RunTime Peak Memory')
 
plt.savefig('runtime_peak_memory.jpg')
plt.show()


