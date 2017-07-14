#include "../src/ad_graph.hpp"
#include "../src/ad_dual.hpp"
#include <iomanip>

using namespace std;

template <typename T>
T f(T x1, T x2)
{
    return x1 - log(x2)*exp(x1) + x2 * x2 * x2;
}

void example()
{
    ad_graph GRAPH;   

    ad_dual x1(GRAPH, 3);
    ad_dual x2(GRAPH, 4);

    ad_dual y = f(x1, x2);
    cout << "y = " << y.get_value() << endl;

    cout << endl;
    cout << ">>> Automatic differentiation" << endl;
    cout << "dy_dx1 = " << GRAPH.get_derivative(y, x1) << endl;
    cout << "dy_dx2 = " << GRAPH.get_derivative(y, x2) << endl;

    double d = 1e-10;
    cout << "\n>>> Finite difference method" << endl;
    cout << "dy_dx1 = " << (f(3. + d, 4.) - f(3. - d, 4.)) / (2 * d) << endl;
    cout << "dy_dx2 = " << (f(3., 4. + d) - f(3., 4. - d)) / (2 * d) << endl;
}

int main()
{
    example();
    return 0;
}