#include <iostream>
#include <cmath>

int binary_search(int* a,int l,int r,int p);
void printArray(int *a,const size_t& n);

void rotateImpl(int* a,int start,int end,int rotation)
{
    for(size_t i = 0; i < rotation; ++i)
    {
        int temp = a[end];
        for(size_t j = end; j > start; --j)
            a[j] = a[j-1];
        a[start] = temp;
    }
}
void rotate(int* a,int first,int second,int end)
{
    if(first != second)
    {
        int rotation = first - second;
        if(rotation < 0)
            rotation = rotation + (end - first + 1);
        rotateImpl(a,first,end,rotation);
    }
}
void printArray(int *a,const size_t& n)
{
    for(size_t i = 0; i < n; ++i)
        std::cout << a[i] << " ";
    std::cout << std::endl; 
}
void symmerge(int* arr,const int& first1,const int& first2,const int& last)
{
    /*first1 - begin of the array,
      first2 - middle of the array,
      last - end of the array     
    */
    if(first1 < first2 && first2 < last)
    {
        int m = (first1+last)/2; //int - floor is taken;
        int n = m + first2;
        int start;
        if(first2 > m)
            start = binary_search(arr,n-last,m,n-1); 
        else
            start = binary_search(arr,first1,first2,n-1);
        int end = n - start; 

        rotate(arr,start,first2,end-1);
        symmerge(arr,first1,start,m);
        symmerge(arr,m,end,last);

    }
}

int binary_search(int* a,int l,int r,int p)
{
    while(l < r)
    {
        int m = (l+r)/2;
        if(a[m] <= a[p-m])
            l = m+1;
        else
            r = m;
    }
    return l;
}

void mergeSort(int* arr,const int& l,const int& r)
{
    if(r - l > 1)
    {
        int middle = (l+r)/2;
        mergeSort(arr,l,middle);
        mergeSort(arr,middle,r);
        symmerge(arr,l,middle,r);
    }
}
int main()
{
    int a[] = {2,0,-1,4,60,33,5,4};
    const size_t n = sizeof(a)/sizeof(*a);
    printArray(a,n);
    mergeSort(a,0,n);
    printArray(a,n);
}
