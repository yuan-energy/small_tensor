for D in */
do
    # echo $D
    cd $D
    echo $PWD
    # sed  -i '5i using namespace smalltensor::ad ;' test_tensor*.cpp
    sed  -i '8i ad_graph<double> GRAPH;' test_tensor*.cpp
    # sed  -i 's/double/ad_dual<double>/' test_tensor*.cpp
    # sed  -i 's/obj1;/obj1(GRAPH,0.);/' test_tensor*.cpp

    
    cd ..
done

