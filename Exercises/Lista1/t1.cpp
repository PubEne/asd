#include <iostream>
#include <typeinfo>
#include <cmath>
namespace ASD
{
    template<typename T0, typename T1>
    auto inline Rpow(T0 const& x, T1 const& n) -> decltype(x*n)
    {
        using value_type = decltype(x*n);
        if(!n)
            return 1;
        value_type temp = Rpow(x, n/2);
        if(!std::fmod(n,2))
            return temp*temp;
        return n > 0 ? x*temp*temp : (temp*temp)/x;
    }
    template<typename T0,typename T1>
    auto inline pow(T0 x,T1 n) -> decltype(x*n)
    {
        decltype(x*n) res = 1;
        while(n)
        {
            if(n & 1)
                res *= x;
            n >>= 1;
            std::cout << n << std::endl;
            x *= x;
        }
        return res;
    }
}
int main()
{
//    std::cout << ASD::Rpow(2.3,-3) << std::endl;
    std::cout << ASD::pow(2,4) << std::endl;
}
