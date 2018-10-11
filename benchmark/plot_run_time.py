import numpy as np
import matplotlib.pyplot as plt


# --------------------------------------------
# Collect data from txt files
# --------------------------------------------
libxsmm_float = {}
libxsmm_float['3x3x3'] = np.loadtxt('libxsmm/float_time3x3x3.txt').item(0)
libxsmm_float['8x3x3'] = np.loadtxt('libxsmm/float_time8x3x3.txt').item(0)
libxsmm_float['20x3x3'] = np.loadtxt('libxsmm/float_time20x3x3.txt').item(0)
libxsmm_float['27x3x3'] = np.loadtxt('libxsmm/float_time27x3x3.txt').item(0)

libxsmm_double = {}
libxsmm_double['3x3x3'] = np.loadtxt('libxsmm/double_time3x3x3.txt').item(0)
libxsmm_double['8x3x3'] = np.loadtxt('libxsmm/double_time8x3x3.txt').item(0)
libxsmm_double['20x3x3'] = np.loadtxt('libxsmm/double_time20x3x3.txt').item(0)
libxsmm_double['27x3x3'] = np.loadtxt('libxsmm/double_time27x3x3.txt').item(0)

print(libxsmm_float)
print(libxsmm_double)

# --------------------------------------------

smalltensor_float = {}
smalltensor_float['3x3x3'] = np.loadtxt('smalltensor/float_time3x3x3.txt').item(0)
smalltensor_float['8x3x3'] = np.loadtxt('smalltensor/float_time8x3x3.txt').item(0)
smalltensor_float['20x3x3'] = np.loadtxt('smalltensor/float_time20x3x3.txt').item(0)
smalltensor_float['27x3x3'] = np.loadtxt('smalltensor/float_time27x3x3.txt').item(0)

smalltensor_double = {}
smalltensor_double['3x3x3'] = np.loadtxt('smalltensor/double_time3x3x3.txt').item(0)
smalltensor_double['8x3x3'] = np.loadtxt('smalltensor/double_time8x3x3.txt').item(0)
smalltensor_double['20x3x3'] = np.loadtxt('smalltensor/double_time20x3x3.txt').item(0)
smalltensor_double['27x3x3'] = np.loadtxt('smalltensor/double_time27x3x3.txt').item(0)

print(smalltensor_float)
print(smalltensor_double)

# --------------------------------------------

ltensor_float = {}
ltensor_float['3x3x3'] = np.loadtxt('ltensor/float_time3x3x3.txt').item(0)
ltensor_float['8x3x3'] = np.loadtxt('ltensor/float_time8x3x3.txt').item(0)
ltensor_float['20x3x3'] = np.loadtxt('ltensor/float_time20x3x3.txt').item(0)
ltensor_float['27x3x3'] = np.loadtxt('ltensor/float_time27x3x3.txt').item(0)

ltensor_double = {}
ltensor_double['3x3x3'] = np.loadtxt('ltensor/double_time3x3x3.txt').item(0)
ltensor_double['8x3x3'] = np.loadtxt('ltensor/double_time8x3x3.txt').item(0)
ltensor_double['20x3x3'] = np.loadtxt('ltensor/double_time20x3x3.txt').item(0)
ltensor_double['27x3x3'] = np.loadtxt('ltensor/double_time27x3x3.txt').item(0)

print(ltensor_float)
print(ltensor_double)

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




# # data to plot
def plot_performance(tensor_size):
	n_groups = 2
	ltensor_res = (ltensor_float[tensor_size], ltensor_double[tensor_size])
	libxsmm_res = (libxsmm_float[tensor_size], libxsmm_double[tensor_size])
	smalltensor_res = (smalltensor_float[tensor_size], smalltensor_double[tensor_size])

	# # create plot
	fig, ax = plt.subplots()
	index = np.arange(n_groups)
	bar_width = 0.2
	opacity = 0.8
	 
	rects1 = plt.bar(index, ltensor_res, bar_width,
	                 alpha=opacity,
	                 color='b',
	                 label='ltensor')
	 
	rects2 = plt.bar(index + bar_width, libxsmm_res, bar_width,
	                 alpha=opacity,
	                 color='g',
	                 label='libxsmm')

	rects3 = plt.bar(index + bar_width*2, smalltensor_res, bar_width,
	                 alpha=opacity,
	                 color='r',
	                 label='smalltensor')

	# plt.xlabel('Tensor Library')
	plt.ylabel('Runtime[milliseconds] ')
	plt.title('Tensor Contraction of Size ' + tensor_size )
	plt.xticks(index + bar_width, ('single-precision', 'double-precision'))
	plt.legend(loc=2)
	plt.ylim([0, 3500])

	plt.tight_layout()
	plt.savefig('performance'+ tensor_size + '.jpg')
	plt.show()


plot_performance('3x3x3')
plot_performance('8x3x3')
plot_performance('20x3x3')
plot_performance('27x3x3')
