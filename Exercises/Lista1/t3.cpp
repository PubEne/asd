#include <iostream>
#include <vector>
#include <cmath>

double polynomial(const std::vector<double> & v,const size_t & n,const double & x)
{
    double result {};
    for(int i = 0; i < n; i++)
        result = std::fma(result,x,v[i]);
    return result;
}

int main()
{
    std::vector<double> v {2,-6,2,-1}; // from n to n^0
    std::cout << polynomial(v,v.size(),3) << std::endl;
}
