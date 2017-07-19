#include "../src/ad_graph.hpp"
#include "../src/ad_dual.hpp"
#include <iomanip>
#include <cmath>

using namespace std;

template <typename T>
T f(T x1, T x2)
{
    return 3.*x1 + 4.*x2;
}


void example()
{
    ad_graph GRAPH;   

    ad_dual v1(GRAPH, 3.);
    ad_dual v2(GRAPH, 4.);
    ad_dual v3(GRAPH, 5.);
    ad_dual w1(GRAPH, 6.);
    ad_dual w2(GRAPH, 7.);
    ad_dual w3(GRAPH, 8.);

    vector<ad_dual> v = {v1,v2,v3};
    vector<ad_dual> w = {w1,w2,w3};
    vector<ad_dual> ret(3);

    // auto y = f(v, w);
    for (int i = 0; i < 3; ++i){
        ret[i] = f(v[i],w[i]);
    }
    cout << "ret[0] = " << ret[0].get_value() << endl;
    cout << "ret[1] = " << ret[1].get_value() << endl;
    cout << "ret[2] = " << ret[2].get_value() << endl;

    cout << endl;
    cout << ">>> Symbolic differentiation Value Results." << endl;
    cout << "dy_dx1 = " << 4 << endl;
    cout << "dy_dx2 = " << 3 << endl;

    cout << endl;
    cout << ">>> Automatic differentiation" << endl;
    cout << "dy_dx1 = " << GRAPH.get_derivative(ret[0] , w1) << endl;
    cout << "dy_dx2 = " << GRAPH.get_derivative(ret[2] , v3) << endl;

    // double d=1E-8;
    // while(d>=1E-16){
    //     cout << "\n>>> Finite difference method with d=" << d << endl;
    //     cout << "dy_dx1 = " << (f(3. + d, 4.) - f(3. - d, 4.)) / (2 * d) << endl;
    //     cout << "dy_dx2 = " << (f(3., 4. + d) - f(3., 4. - d)) / (2 * d) << endl;
    //     d /= 10.;
    // }
}

int main()
{
    example();
    return 0;
}