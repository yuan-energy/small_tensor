sed -i "s/DTensor2/stresstensor/g" *.cpp
sed -i "s/DTensor2/stresstensor/g" *.h

sed -i "s/(3,3,0\.)/()/g" *.cpp



sed -i "s/DTensor1/VECT3/g" *.cpp
sed -i "s/DTensor1/VECT3/g" *.h
sed -i "s/DTensor4/stifftensor/g" *.cpp
sed -i "s/DTensor4/stifftensor/g" *.h