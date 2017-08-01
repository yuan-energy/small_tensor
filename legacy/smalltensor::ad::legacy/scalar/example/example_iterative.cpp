#include "../src/ad_graph.hpp"
#include "../src/ad_dual.hpp"
#include <iomanip>
#include <cmath>

using namespace std;

template <typename T>
T f(T x1, T x2)
{
    return x1 - log(x2) * exp(x1) + x2 * x2 * x2;
}

template <typename T>
T df_dx1(T x1, T x2)
{
    return 1 - log(x2) * exp(x1) ;
}

template <typename T>
T df_dx2(T x1, T x2)
{
    return -1./x2 * exp(x1) + 3. * x2 * x2;
}

void example()
{
    ad_graph GRAPH;   

    ad_dual x1(GRAPH, 3);
    ad_dual x2(GRAPH, 4);

    ad_dual y = f(x1, x2);
    cout << "y = " << y.get_value() << endl;

    cout << endl;
    cout << ">>> Symbolic differentiation Value Results." << endl;
    cout << "dy_dx1 = " << df_dx1(3.,4.) << endl;
    cout << "dy_dx2 = " << df_dx2(3.,4.) << endl;

    cout << endl;
    cout << ">>> Automatic differentiation" << endl;
    cout << "dy_dx1 = " << GRAPH.get_derivative(y, x1) << endl;
    cout << "dy_dx2 = " << GRAPH.get_derivative(y, x2) << endl;

    double d=1E-8;
    while(d>=1E-16){
        cout << "\n>>> Finite difference method with d=" << d << endl;
        cout << "dy_dx1 = " << (f(3. + d, 4.) - f(3. - d, 4.)) / (2 * d) << endl;
        cout << "dy_dx2 = " << (f(3., 4. + d) - f(3., 4. - d)) / (2 * d) << endl;
        d /= 10.;
    }
}

void iterative_example()
{
    ad_graph x1(GRAPH, 33)  ;
    ad_graph y(GRAPH, 0)  ;
    ad_graph x0(GRAPH, 3.5)  ;
    
    // cout << "Enter a value to be square rooted: " << endl;
    // cin >> y;
    // x0 = log(y);
    cout << x0 << endl;
    
    do 
    {
      x1 = (x0 - (((x0 * x0) - y)/(2* x0)));
      x0 = x1;
      
      cout << "x1= " << x1.get_value() << endl;
      
    } while ((x1 * x1) > y);
}

int main()
{
    // example();
    iterative_example();
    return 0;
}