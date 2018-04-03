#include <iostream>

unsigned long long catalan(const size_t& n)
{
    if(n <= 1) return 1;
    
    unsigned long long sum = 0;
    for(size_t i = 0; i < n; ++i)
        sum += catalan(i)*catalan(n-i-1);
    return sum;    
    //Time complexity O(2^n)
}
unsigned long long catalan2(const size_t& n)
{
    unsigned long long arr[n+1];
    arr[0] = arr[1] = 1;
    for(size_t i = 2; i <= n; ++i)
    {
        arr[i] = 0;
        for(size_t j = 0; j < i; ++j)
            arr[i] += arr[j]*arr[i-j-1];
    }
    return arr[n];
    //Time complexity O(n^2)
}

int main()
{
    //std::cout << catalan(20) << std::endl;
    std::cout << catalan2(36) << std::endl;
}
