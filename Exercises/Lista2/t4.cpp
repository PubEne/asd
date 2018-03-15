#include <iostream>

constexpr int gcd(const int& a,const int& b) { return !b ? a : gcd(b,a%b); }
void shift(int *a,size_t n)
{
    int temp = a[n-1];
    for(size_t i = n-1; i > 0; i--)
        a[i] = a[i-1];
    a[0] = temp;
}
void print(int *a,size_t n)
{
    for(size_t i = 0; i < n; i++)
        std::cout << a[i] << " "; 
    std::cout << std::endl;
}
void shiftk(int *a,const int& n,int k)
{
    k%=n;
    if(k == 0)
        return;
    int i{};
    while(i < gcd(n,k))
    {
        int x = a[i];
        int j = i+k;
        if(j >= n)
            j -= n;
        while(j != i)
        {
            int y = a[j];
            a[j] = x;
            x = y;
            j+=k;
            if(j >= n)
                j -= n;
            print(a,n);
        }
        a[i++] = x;
        print(a,n);
    }
}
void shiftArr(int *a, size_t n,size_t k=0)
{
    for(size_t i = 0; i < k; i++)
        shift(a,n);
}
int main()
{
    int arr[] = {1,2,3,4,5,6,7,8,9};
    print(arr,sizeof(arr)/sizeof(arr[0]));
    //shiftArr(arr,sizeof(arr)/sizeof(arr[0]),5);
    shiftk(arr,sizeof(arr)/sizeof(arr[0]),3); 
    print(arr,sizeof(arr)/sizeof(arr[0]));
}
