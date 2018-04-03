#include <iostream>
#include <algorithm>

template<typename T=size_t>
constexpr void printArray(const T*const arr,const size_t& n = 0) 
{
    for(size_t i = 0; i < n; ++i)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}
void counting_sort(size_t*const& t,const size_t& n,size_t c)
{
    size_t exp = 1;
    size_t occurrences[10] = {0};
    size_t temp[n];

    while(c--)
        exp *= 10;
    for(size_t i = 0; i < n; ++i) 
        ++occurrences[(t[i]/exp)%10];
    for(size_t i = 1; i < 10; ++i) 
        occurrences[i] += occurrences[i-1];
    for(int i = n-1; i >= 0; --i) 
        temp[--occurrences[(t[i]/exp)%10]] = t[i];
    for(size_t i = 0; i < n; ++i)
        t[i] = temp[i];
}
size_t getDigits(int m)
{
    size_t digits = 0;
    if(m < 0) digits = 1;
    while(m)
    {
        m/=10;
        ++digits;
    } 
    return digits;
}
void radix_sort(size_t*const& t,const size_t& n)
{
    int m = *std::max_element(t,t+n);
    for(size_t exp = 0; exp < getDigits(m); ++exp)
    {
        counting_sort(t,n,exp);
        printArray(t,n);
    }
}
int main()
{
    size_t t[] = {91,82,73,64,55,46,39,78,69,50,36,39};
    size_t* a = t;
    const size_t n = sizeof(t)/sizeof(*t);
    printArray(t,n);
    radix_sort(t,n);
    counting_sort(a,n,1);
    printArray(a,n);
}
