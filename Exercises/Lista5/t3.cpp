#include <iostream>

template<typename T>
constexpr void printArray(T* a,const size_t& n)
{
    for(size_t i = 0; i < n; ++i)
        std::cout << a[i] << " ";
    std::cout << std::endl;
}
void insertion_sort(double t[],const size_t& n)
{
    int counter = 0;
    for(size_t i = 1; i < n; ++i)
        for(size_t j = i; j > 0 && ++counter && t[j-1] > t[j]; --j)
            std::swap(t[j],t[j-1]);
    std::cout << counter << std::endl;
}
int main()
{
    double t[] = {7,6,5,4,3,2,1};
    double t2[] = {1,2,3,4,5,6,7};
    //printArray(t,7);
    insertion_sort(t,7);
    //printArray(t,7);
}
