import itertools

# print "#################################################################################"
# print "#                                                                               #"
# print "#  Generate_Permutation_Operations:: Python Script to generate a permutation    #"             #"
# print "#                                    Wrapper of core operations                 #"
# print "#  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -#"
# print "#                                                                               #"
# print "#  Yuan Feng (June, 2017)                                                       #"
# print "#  Computational Mechanics Lab                                                  #"
# print "#  University of California, Davis                                              #"
# print "#################################################################################\n\n\n"

# core_file_name = raw_input("Please enter your operation _core filename: ")
# permute_num = raw_input("Please enter your permutation number (2|3|4) : ")
permute_num=4
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
# wrapper_filename = core_file_name.replace("_core.",".")
# file_macro_name= wrapper_filename.replace('.','_small_tensor_')

# inline expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>& 
# operator=(expr4<dat_t,d1,d2,d4,d3,i1,i2,i4,i3> const& RHS_);

with open("expr4_equal_inc.h", 'w') as f1:
	# f1.write("#ifndef " + file_macro_name.upper()  + "\n")
	# f1.write("#define " + file_macro_name.upper()  + "\n\n\n")
	for row in xrange(1,len(index_all)) :
		f1.write('inline expr4<dat_t,')
		for col in xrange(len(index_all[0])) :
			f1.write(dim_all[0][col] +',')
		for col in xrange(len(index_all[0])) :
			if col==len(index_all[0])-1:
				f1.write(index_all[0][col] +'>&\n')
			else:
				f1.write(index_all[0][col] +',')
		f1.write('operator=(expr4<dat_t,')
		for col in xrange(len(index_all[0])) :
			f1.write(dim_all[row][col] +',')
		for col in xrange(len(index_all[0])) :
			if col==len(index_all[0])-1:
				f1.write(index_all[row][col] +'> const& RHS_);\n\n')
			else:
				f1.write(index_all[row][col] +',')
	f1.write("/*Done!*/")