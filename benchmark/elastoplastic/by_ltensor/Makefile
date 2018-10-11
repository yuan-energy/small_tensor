OBJS = test_tensor1.o test_tensor2.o test_tensor3.o test_tensor4.o
CC = g++
DEBUG = -g -DDEBUG
CFLAGS = -Wall -std=c++11 -O3 $(DEBUG)
LFLAGS = -Wall -std=c++11 -O3 $(DEBUG)

INCLUDE_HEADER_LOCATION=\
-I../../unit/ltensor/ltensor/

LINK_LIB_LOCATION=\
# -L../../
LINK_LIB_NAME=\
# -pthread \
# -lblas \
# -llapack \
# -ldl


vm:
	g++ -o multi_ys_VM \
		test_multi_ys_shear.cpp vonMises_multi_surface.cpp MultiYieldSurfaceMaterial.cpp \
		$(CFLAGS) \
		$(INCLUDE_HEADER_LOCATION)
	python test_vonMises_multi_shear.py
	
dp:
	g++ -o multi_ys_DP \
		test_multi_ys_DP_shear.cpp DruckerPrager_multi_yield_surface.cpp MultiYieldSurfaceMaterial.cpp \
		$(CFLAGS) \
		$(INCLUDE_HEADER_LOCATION)
	python test_GUI_MYS_DP.py



rmc:
	g++ -o test_MYS_RMC_equal_shear \
		test_MYS_RMC_equal_shear.cpp RoundedMohrCoulomb_multi_surface.cpp MultiYieldSurfaceMaterial.cpp \
		$(CFLAGS) \
		$(INCLUDE_HEADER_LOCATION)
	python test_GUI_MYS_RMC.py	

# compile: 
# 	g++ -o multi_ys_DP test_multi_ys_DP_shear.cpp DruckerPrager_multi_yield_surface.cpp -std=c++11 -Wall

# plot:
# 	python plot.py

# GUI:
# 	python test_GUI_MYS_DP.py
	
clean:
	-rm -f  multi_ys
	-rm -f  strain_stress.txt
	-rm -f  results.pdf