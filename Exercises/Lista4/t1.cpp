#include <iostream>

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
    size_t occurrences[n];
    size_t temp[n];

    while(c--)
        exp *= 10;
    for(size_t i = 0; i < n; ++i)
        occurrences[i] = 0;
    for(size_t i = 0; i < n; ++i) 
        ++occurrences[(t[i]/exp)%10];
    for(size_t i = 1; i < n; ++i) 
        occurrences[i] += occurrences[i-1];
    for(size_t i = 0; i < n; ++i) 
        temp[--occurrences[(t[i]/exp)%10]] = t[i];
    for(size_t i = 0; i < n; ++i)
        t[i] = temp[i];
}

int main()
{
    size_t t[] = {9,8,7,6,5,4,3,7,6,5};
    const size_t n = sizeof(t)/sizeof(*t);
    printArray(t,n);
    counting_sort(t,n,0);
    printArray(t,n);
}
