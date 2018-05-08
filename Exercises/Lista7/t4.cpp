#include <iostream>
#include <climits>
#include <cmath>
#include <vector>
#include <utility> //for std::pair

/* polygon triangulation using dynamic programming */
namespace ASD
{
    template<typename T = size_t>
    constexpr T binomialCoefficient(T n, T k)
    {
        size_t res = 1;
        if(k > n - k)
            k = n-k;
        for(size_t i = 0; i < k; ++i)
        {
            res *= (n-i);
            res /= (i+1);
        }
        return res;
    }
    template<typename T = size_t>
    constexpr T catalan(const T& n)
    {
        return binomialCoefficient(2*n,n)/(n+1);
    }
    template<typename T = size_t>
    constexpr T f(const T& n)
    {
        return catalan(n-2);
    }
    template<typename T = double>
    constexpr T cost(const std::vector<std::pair<T,T>>& points, const size_t& i, const size_t& j, const size_t& k)
    {
        auto p1 = points[i], p2 = points[j], p3 = points[k];
        auto dist = [](const auto& p1, const auto& p2) { return sqrt(pow(p1.first-p2.first,2)+pow(p1.second-p2.second,2)); } ;
        return dist(p1,p2) + dist(p2,p3) + dist(p3,p1); 
    }
    template<typename T = double>
    constexpr T g(const std::vector<std::pair<T,T>>& points)
    {
        if(points.size() < 3)
            return 0;
        T arr[points.size()][points.size()] = {0};
        
        for(size_t gap = 0; gap < points.size(); ++gap)
            for(size_t i = 0, j = gap; j < points.size(); ++i, ++j)
                if(j - i < 2)
                    arr[i][j] = 0;
                else
                {
                    arr[i][j] = 1000000000.0;
                    for(size_t k = i+1; k < j; ++k)
                    {
                        T val = arr[i][k] + arr[k][j] + cost(points,i,j,k);
                        if(arr[i][j] > val)
                            arr[i][j] = val;
                    }
                }
        return arr[0][points.size()-1];
    } 
}
int main()
{
    const std::vector<std::pair<double,double>> v = {{0,0}, {1,0}, {2,1}, {1,2}, {0,2}};
    std::cout << ASD::g(v) << std::endl;
    std::cout << ASD::f(10) << std::endl;
}
