#include <iostream>
#include <cmath>

template<typename T = double>
T f(T x=.0)
{
   return pow(x,3)-x-2; 
}

double bisection(const double& a,const double& b)
{
    if(f(a) * f(b) >= 0)
        return 0;
    double c = a;
    while( b-a >= 0)
    {
        c = (a+b)/2;
        if(!f(c))
            break;
        f(c)*f(a) < 0 ? b = c : a = c;
    }
    return c;
}
int main()
{
    std::cout << bisection(1,5) << std::endl;
}
