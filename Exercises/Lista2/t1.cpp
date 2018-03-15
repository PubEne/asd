#include <iostream>
#include <vector>
#include <cmath>

namespace ASD
{
    template<typename T>
    constexpr T binary_search(const std::vector<T>& v, const T& x)
    {
        T min {}, max = v.size()-1;
        while(max >= min)
        {
            T m = std::floor(max+min)/2;
            if(x == v[m])
                return m;
            else if(x > v[m])
                min = m + 1;
            else
                max = m - 1;
        }
        return -1;
    }
}
int main()
{
    std::vector<int> v{2,5,7,14,41};
    int i = ASD::binary_search(v,41);
    std::cout << "index " << i << std::endl;
}
