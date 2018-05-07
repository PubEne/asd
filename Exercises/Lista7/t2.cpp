#include <iostream>
#include <cmath>

constexpr size_t f(const size_t& n)
{
    return __builtin_popcount(n); //O(1) 
}
int main()
{
    std::cout << f(50) << std::endl;
}

