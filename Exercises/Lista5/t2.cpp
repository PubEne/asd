#include <iostream>

template<typename T>
constexpr void printArray(T* a,const size_t& n)
{
    for(size_t i = 0; i < n; ++i)
        std::cout << a[i] << " ";
    std::cout << std::endl;
}

int partition(double t[],size_t n)
{
    int k = -1;
    double x = t[0];
    for(;;)
    {
        printArray(t,7);
        while(t[--n] > x);
        while(t[++k] < x);
        if(k < n)
            std::swap(t[k],t[n]);
        else
            return k;
    }
    printArray(t,7);
}
int main()
{
    double t[] = {7,6,5,4,3,2,1};
    partition(t,7);
}
