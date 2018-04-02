#include <iostream>

int partition(int t[],int l,int r)
{
    //if(l >= r) return l;
    int x = t[r/2];
    --l;
    for(;;)
    {
        while (t[--r] > x);
        while (t[++l] < x);
        if (r > l)
            std::swap(t[r],t[l]);
        else
            return l;
    }
    return l;
}
int quick_select(int* t,int l,int r,const int& k)
{
    if(l == r)
        return t[l];
    int p = partition(t,l,r);
    if(p < k)
        return quick_select(t,p+1,r,k);
    return quick_select(t,l,p,k);
}
int main()
{
    int t[] = {10,1,100,3,5};
    const int n = sizeof(t)/sizeof(*t);
    for(size_t i = 0; i < n; ++i)
        std::cout << quick_select(t,0,n,i) << " ";
    std::cout << std::endl;
}
