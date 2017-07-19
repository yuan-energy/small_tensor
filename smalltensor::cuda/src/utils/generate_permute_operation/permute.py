import itertools
import sys

core_file_name = sys.argv[1]
permute_num = sys.argv[2]

# core_file_name = raw_input("Please enter your operation _core filename: ")
# permute_num = raw_input("Please enter your permutation number (2|3|4) : ")

generate = itertools.permutations(range(int(permute_num)))
permute = list(generate)
index=['i1','i2','i3','i4']
num  =['n1','n2','n3','n4']
Dimen=['d1','d2','d3','d4']
ABCD=['A','B','C','D']
abcd=['a','b','c','d']
D123=['D1','D2','D3','D4']
index_all=[]
num_all=[]
dim_all=[]
for row in xrange(len(permute)) :
	index_line =[]
	num_line =[]
	dim_line =[]
	for col	in xrange(len(permute[0])):
		index_line.append(index[permute[row][col]])
		num_line.append(num[permute[row][col]])
		dim_line.append(Dimen[permute[row][col]])
	index_all.append(index_line)
	num_all.append(num_line)
	dim_all.append(dim_line)

# core_file_name = "expr3_plus_core.h"
wrapper_filename = core_file_name.replace("_core.",".")
file_macro_name= wrapper_filename.replace('.','_small_tensor_')

with open(wrapper_filename, 'w') as f1:
	f1.write("#ifndef " + file_macro_name.upper()  + "\n")
	f1.write("#define " + file_macro_name.upper()  + "\n\n\n")
	for row in xrange(len(index_all)) :
		for col in xrange(len(index_all[0])) :
			f1.write('#define '+ ABCD[col] +' ' +index_all[row][col] + '\n')
			f1.write('#define '+ abcd[col] +' ' +num_all[row][col] + '\n')
			f1.write('#define '+ D123[col] +' ' +dim_all[row][col] + '\n')
		f1.write('#include ' + '"' + core_file_name + '"'+ '\n')	
		for col in xrange(len(index_all[0])) :
			f1.write('#undef '+ ABCD[col] + '\n')
			f1.write('#undef '+ abcd[col] + '\n')
			f1.write('#undef '+ D123[col] + '\n')
		f1.write('\n\n\n')
	f1.write("#endif")