#include <iostream>

int max(const int t[],int n)
{
    int x = t[n];
    while(n--)
        if(x < t[n])
            x = t[n];
    return x;
}
constexpr int max(int a, int b) { return a > b ? a : b; }
int max2(const int t[],size_t n)
{
    if(n)
        return max(t[n],max2(t,n-1));
    return -1; 
}
int max3(const int t[], size_t begin=0,size_t end=0) //divide and conquer
{
    if(begin == end)
        return t[end];
    int m = (begin+end)/2; // it's int so floor is taken
    int left_max = max3(t,begin,m);
    int right_max = max3(t,m+1,end);
    if(left_max > right_max)
        return left_max;
    return right_max;
}
int main()
{
    const int tab[10] = {555,2254,1,2,3,466,5,7,4,1};
    const int max_num = max(tab,(sizeof(tab)/sizeof(tab[0]))-1);
    const int max_num2 = max2(tab,(sizeof(tab)/sizeof(tab[0]))-1);
    const int max_num3 = max3(tab,0,(sizeof(tab)/sizeof(tab[0]))-1);
    std::cout << max_num2 << "," << max_num << "," << max_num3 << std::endl;
}
