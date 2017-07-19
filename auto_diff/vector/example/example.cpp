#include "../app/smalltensor.h"
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

// void example2(){
//     double* pA = new double[3];
//     ad_dual<double>* pB = new ad_dual<double>[3];

//     *(pA+1) = 3.8;
//     (pB+1)->set_value(4.1) ; 
//     cout<<"pA + 1 = " << *(pA+1) <<endl;
//     cout<<"pB + 1 = " << (pB+1)->get_value() <<endl;

//     cout<<"Memcpy: " <<endl;
//     double* cpyA = new double[3];
//     ad_dual<double>* cpyB = new ad_dual<double>[3];
    
//     std::memcpy(cpyA, pA, sizeof(double)*3);
//     cout<<"cpyA + 1 = " << *(cpyA+1) <<endl;

//     std::memcpy(cpyB, pB, sizeof(ad_dual<double>)*3 );
//     cout<<"cpyB + 1 = " << (cpyB+1)->get_value() <<endl;


//     delete cpyA;
//     delete cpyB;
//     delete pA;
//     delete pB;
// }

void example()
{


    ad_graph<double> GRAPH;   

    ad_dual<double> x1(GRAPH, 3);
    ad_dual<double> x2(GRAPH, 4);

    ad_dual<double> y = f(x1, x2);
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

int main()
{
    example();
    // example2();
    return 0;
}