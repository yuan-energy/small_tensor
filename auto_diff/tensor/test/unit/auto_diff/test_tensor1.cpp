#include "../include_small_tensor.h"

#include <iostream>
#include <functional>
using namespace std;

double finite_difference(function<double(double)> f, double x)
{
    double d = 1e-6;
    return (f(x + d) - f(x - d)) / (2 * d);
}

double finite_difference(function<double(double, double)> f, double x, double y, int which)
{
    double d = 1e-6;
    if (which==0)
        return (f(x + d, y) - f(x - d, y)) / (2 * d);
    else
        return (f(x, y + d) - f(x, y - d)) / (2 * d);
}



int main(int argc, char const *argv[])
{
	{
		ad_graph<double> GRAPH;
		ad_dual<double> a(GRAPH, 3.);
		ad_dual<double> b(GRAPH, 4.);
		auto f = [&](auto x, auto y)->auto {
			return 8.*x + 9.*y + 17. ;
		};
		ASSERT_MSG(f(a,b) == 77.            , "Real-Value Computation Error!");
		ASSERT_MSG(GRAPH.get_derivative(f(a,b),a) == 8. , "Derivative Error!");
		ASSERT_MSG(GRAPH.get_derivative(f(a,b),b) == 9. , "Derivative Error!");
	}

	{
		ad_graph<double> GRAPH;
		ad_dual<double> a(GRAPH, 3.);
		ad_dual<double> b(GRAPH, 4.);
		auto f = [&](auto x, auto y)->auto {
			return - 17. - 8.*x - 9.*y  ;
		};
		ASSERT_MSG(f(a,b) == -77.            , "Real-Value Computation Error!");
		ASSERT_MSG(GRAPH.get_derivative(f(a,b),a) == -8. , "Derivative Error!");
		ASSERT_MSG(GRAPH.get_derivative(f(a,b),b) == -9. , "Derivative Error!");
	}

	{
		ad_graph<double> GRAPH;
		ad_dual<double> a(GRAPH, 3.);
		ad_dual<double> b(GRAPH, 4.);
		auto f = [&](auto x, auto y)-> auto {
			return 8.*x - y * 9. + 17 ;
		};
		ASSERT_MSG(f(a,b) ==   5.            , "Real-Value Computation Error!");
		ASSERT_MSG(GRAPH.get_derivative(f(a,b),a) ==  8. , "Derivative Error!");
		ASSERT_MSG(GRAPH.get_derivative(f(a,b),b) == -9. , "Derivative Error!");
	}

	{
		ad_graph<double> GRAPH;
		ad_dual<double> a(GRAPH, 3.);
		ad_dual<double> b(GRAPH, 2.);
		auto f = [&](auto x, auto y)-> auto {
			return 5.*x * 3.* y * 2. - 30. ;
		};
		ASSERT_MSG(f(a,b) == 150.            , "Real-Value Computation Error!");
		ASSERT_MSG(GRAPH.get_derivative(f(a,b),a) == 60. , "Derivative Error!");
		ASSERT_MSG(GRAPH.get_derivative(f(a,b),b) == 90. , "Derivative Error!");
	}

	{
		ad_graph<double> GRAPH;
		ad_dual<double> a(GRAPH, 4.);
		ad_dual<double> b(GRAPH, 2.);
		auto f = [&](auto x, auto y)-> auto {
			return 1./ x + y / 2. + 17. ;
		};
		ASSERT_MSG(f(a,b) == 18.25               , "Real-Value Computation Error!");
		ASSERT_MSG(GRAPH.get_derivative(f(a,b),a) == -1./16. , "Derivative Error!");
		ASSERT_MSG(GRAPH.get_derivative(f(a,b),b) ==  0.5 ,    "Derivative Error!");
	}

	{
		ad_graph<double> GRAPH;
		ad_dual<double> a(GRAPH, 4.);
		ad_dual<double> b(GRAPH, 2.);
		auto f = [&](auto x, auto y)-> auto {
			return  2.*x / (4.* y)  + 17. ;
		};
		ASSERT_MSG(f(a,b) == 18                 , "Real-Value Computation Error!");
		ASSERT_MSG(18     == f(a,b)             , "Real-Value Computation Error!");
		ASSERT_MSG(f(a,b) == f(a,b)             , "Comparison Operator    Error!");
		ASSERT_MSG(f(a,b)  > 17.                , "Comparison Operator    Error!");
		ASSERT_MSG(17.     < f(a,b)             , "Comparison Operator    Error!");
		ASSERT_MSG(f(a,b)  < 19.                , "Comparison Operator    Error!");
		ASSERT_MSG(f(a,b)  < 19.                , "Comparison Operator    Error!");
		ASSERT_MSG(19.     > f(a,b)             , "Comparison Operator    Error!");
		ASSERT_MSG(GRAPH.get_derivative(f(a,b),a) ==  1./4. , "Derivative Error!");
		ASSERT_MSG(GRAPH.get_derivative(f(a,b),b) == -0.5 ,   "Derivative Error!");
	}


	{
		ad_graph<double> GRAPH;
		ad_dual<double> a(GRAPH, 4.);
		ad_dual<double> b(GRAPH, 2.);
		auto f = [&](auto x, auto y)-> auto {
			return log(pow(x,2)) + x + exp(y) ;
		};
		ASSERT_MSG(f(a,b)==log(pow(4.,2.))+4.+ exp(2.),"Real-Value Computation Error!");
		ASSERT_MSG(GRAPH.get_derivative(f(a,b),a) == 1.5,          "Derivative Error!");
		ASSERT_MSG(GRAPH.get_derivative(f(a,b),b) == exp(2.),      "Derivative Error!");
	}

	return 0;
}