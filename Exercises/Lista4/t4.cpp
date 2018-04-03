#include <iostream>

void printArray(int t[], int n)
{
    for(size_t i = 0; i < n; ++i)
        std::cout << t[i] << " ";
    std::cout << std::endl;
}
int partition(int t[],int l,int r)
{
    int x = t[(l+r)/2]; 
    for(;;)
    {
        while (t[--r] > x);
        while (t[++l] < x);
        if (r > l)
            std::swap(t[r],t[l]);
        else
            return r;
    }
}
int quick_select(int* t,int l,int r,const int& k)
{
    if(l == r)
        return t[l];
    int p = partition(t,l-1,r+1);
    if(p > k)
        return quick_select(t,l,p,k);
    return quick_select(t,p+1,r,k);
}
int main()
{
    int a[] = {1,2,3,4,5,4,3,2,1};
    const int n = sizeof(a)/sizeof(*a);
    for(size_t i = 0; i < n; ++i)
        std::cout << quick_select(a,0,n-1,i) << " ";
    std::cout << std::endl;
}
