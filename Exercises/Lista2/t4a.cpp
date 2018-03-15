#include <iostream>


constexpr int gcd(const int& a,const int& b) { return !b ? a : gcd(b,a%b); }
void print(int *a,size_t n)
{
    for(size_t i = 0; i < n; i++)
        std::cout << a[i] << " "; 
    std::cout << std::endl;
}
void shiftk(int *a,const int& n,int k)
{
    k%=n;
    if(k == 0 || gcd(n,k)!=1)
        return;
    int x = a[0];
    int j = k;
    while(j)
    {
        int y = a[j];
        a[j] = x;
        x = y;
        j += k;
        if(j >= n)
            j -= n;
        print(a,n);
    }
    a[0] = x;
    print(a,n);
}

int main()
{
    int arr[] = {1,2,3,4,5,6,7};
    print(arr,sizeof(arr)/sizeof(arr[0]));
    shiftk(arr,sizeof(arr)/sizeof(arr[0]),3); 
    print(arr,sizeof(arr)/sizeof(arr[0]));
}
