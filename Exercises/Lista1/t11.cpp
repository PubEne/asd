#include <iostream>
#include <vector>
#include <cmath>

namespace ASD
{
    void SoE(const size_t& n)
    {
        std::vector<bool> primes(n,true);
        primes[0] = false, primes[1] = false;

        for(size_t i = 2; pow(i,2) < n; ++i)
            if(primes[i])
                for(size_t j = i*i; j < n; j +=i)
                    primes[j] = false;
        for(size_t i = 0; i < n; ++i)
            if(primes[i]) 
                std::cout << i << std::endl;
    }
}
int main()
{
    ASD::SoE(48);
}
