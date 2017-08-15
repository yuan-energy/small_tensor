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

// This is a Newton iteration process to calculate the square root.
// f(x) = sqrt(x).
// f'(x) = 0.5 / sqrt(x).
// If input is 33. 
// Symbolic results should be f(33)  = 5.74456
// Symbolic results should be f'(33) = 0.0870388
void iterative_example()
{
    ad_graph GRAPH;   
    ad_dual y_next(GRAPH, 0.)  ;
    ad_dual input(GRAPH, 33.)  ;
    ad_dual y_guess(GRAPH, 0.5)  ; 
    
    cout << y_guess.get_value() << endl;
    
    do 
    {
      y_next = (y_guess - (((y_guess * y_guess) - input)/(2* y_guess)));
      y_guess = y_next;
      
      cout<<"------------------------------"<<endl;
      cout << "y_rest    = " << y_next.get_value() << endl;
      cout << "dy_dx     = " << GRAPH.get_derivative(y_next, input) <<endl;
    } while ((y_next.get_value() * y_next.get_value()) > input.get_value());

    cout<<"------------------------------"<<endl;
    cout<<"Symbolic y_rest= " << sqrt(input.get_value()) << endl;
    cout<<"Symbolic dy_dx = " << 0.5*sqrt(1./input.get_value()) << endl;

}



int main()
{
    // example();
    iterative_example();
    return 0;
}