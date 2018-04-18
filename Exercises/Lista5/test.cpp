#include <iostream>
#include <algorithm>
#include <vector>

template<typename T>
constexpr void printArray(T* a,const size_t& n)
{
    for(size_t i = 0; i < n; ++i)
        std::cout << a[i] << " ";
    std::cout << std::endl;
}
//œœœœœœœœœœœœinsertion sortœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœ
template<typename T>
void insertion_sort(T t[],const size_t& n)
{
    for(size_t i = 1; i < n; ++i)
        for(size_t j = i; j > 0 && t[j-1] > t[j]; --j)
            std::swap(t[j],t[j-1]);
}
//œœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœ

//œœœœœœœœœœœœœœœœinsertion sort with sentinelœœœœœœœœœœœœœœ
template<typename T>
void insertion_sort_with_sentinel(T t[],const size_t& n)
{
    for(size_t i = n-1; i; --i) //set smallest on the beginning of the array(pseudo-sentinel)
        if(t[i] < t[i-1])
            std::swap(t[i],t[i-1]);
    for(size_t i = 2; i < n; ++i)
        for(size_t j = i; t[j-1] > t[j]; --j)
            std::swap(t[j],t[j-1]);
}
//œœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœ

//œœœœœœœœœœœœœœœœ quick sort œœœœœœœœœœœœœœœœœœœœœœœœœœœœœœ
template<typename T>
int partition(T t[],size_t n)
{
    int k = -1;
    double x = t[n/2];
    for(;;)
    {
        while(t[--n] > x);
        while(t[++k] < x);
        if(k < n)
            std::swap(t[k],t[n]);
        else
            return k;
    }
}
template<typename T>
void quick_sort(T t[],const size_t& n)
{
    if(n > 1)
    {
        size_t m = partition(t,n);
        quick_sort(t,m); //sort left
        quick_sort(t+m,n-m); //sort right ???
    }
}
//œœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœ

//œœœœœœœœœœœœœœœœ merge sort œœœœœœœœœœœœœœœœœœœœœœœœœœœœœœ
template<typename T>
void merge(T t[],const size_t& m,const size_t& n)
{
    T temp[n] = {0};
    size_t i = 0, j = m, l = 0;
    while(i < m && j < n)
        temp[l++] = t[i]<=t[j] ? t[i++] : t[j++];
    while(i < m)
        temp[l++] = t[i++];    
    for(i = 0; i < n; ++i) //copying
        t[i] = temp[i]; 
}
template<typename T>
void merge_sort(T t[],const size_t& n)
{
    if(n > 1)
    {
        size_t m = n/2;
        merge_sort(t,m);
        merge_sort(t+m,n-m);
        merge(t,m,n);
    }
}
//œœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœ

//œœœœœœœœœœœœœœœœœ counting sort œœœœœœœœœœœœœœœœœœœœœœœœœœ
template<typename T>
void counting_sort(T t[],const size_t& n)
{
    T occurrences[10] = {0};
    T temp[n];

    for(size_t i = 0; i < n; ++i)
        ++occurrences[t[i]];
    for(size_t i = 1; i < 10; ++i)
        occurrences[i] += occurrences[i-1]; 
    for(int i = n-1; i >= 0; --i)
        temp[--occurrences[t[i]]] = t[i];
    for(size_t i = 0; i < n; ++i)
        t[i] = temp[i];
}
//œœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœ

//œœœœœœœœœœœœœœœœœœœœ radix sort œœœœœœœœœœœœœœœœœœœœœœœœœœ
template<typename T>
void radix_sort(T t[],const size_t& n)
{
    T max_el = *std::max_element(t,t+n); //from <algorithm>
    for(size_t exp = 1; exp < max_el; exp*=10)
    {
        T occurrences[10] = {0};
        T temp[n];
        for(size_t i = 0; i < n; ++i) 
            ++occurrences[(t[i]/exp)%10];
        for(size_t i = 1; i < 10; ++i)
            occurrences[i] += occurrences[i-1]; 
        for(int i = n-1; i >= 0; --i)
            temp[--occurrences[(t[i]/exp)%10]] = t[i];
        for(size_t i = 0; i < n; ++i)
            t[i] = temp[i];
    }
}
//œœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœ

//œœœœœœœœœœœœœœœœœœœœ bucket sort œœœœœœœœœœœœœœœœœœœœœœœœœœ
template<typename T>
void bucket_sort(T arr[],const size_t& n)
{
    T bucket[10][n+1];
    for(size_t i = 0; i < 10; ++i)
        bucket[i][n] = 0;
    T max_el = *std::max_element(arr,arr+n); //from <algorithm>
    //for each digit 
    for(size_t digit = 1; digit < max_el; digit *= 10)
    {
        //array to bucket
        for(size_t i = 0; i < n; ++i)
        {
            size_t num = (arr[i]/digit)%10; //0-9
            //add to bucket and increment count
            bucket[num][bucket[num][n]++] = arr[i];
        }
        //bucket to array
        size_t index = 0;
        for(size_t i = 0; i < 10; ++i)
        {
            for(size_t j = 0; j < bucket[i][n]; ++j)
                arr[index++] = bucket[i][j];
            //reset internal bucket counters
            bucket[i][n] = 0;
        }
    }
}
//œœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœ

//œœœœœœœœœœœœœœœœœœœœ heap sort œœœœœœœœœœœœœœœœœœœœœœœœœœ
template<typename T>
void siftDown(T t[],const size_t& n,size_t parent)
{
    T parent_key = t[parent];
    for(;;)
    {
        size_t k = 2*parent + 2; //right child
        /*check if right child exists and is greater than parent and brother
          OR if left child exists and is greater than parent
          SEE! We don't have to check if left child is greater than right child - since we know if we're already in the second condition, it would mean  that right child doesn't exist or is smaller than left
        */
        if((k < n && t[k] > parent_key && t[k] > t[k-1]) || (--k < n && t[k] > parent_key))
        {
            t[parent] = t[k]; //replace
            parent = k; //go down
        }
        else
        {
            t[parent] = parent_key; //save replaced key
            return;
        }
    } 
}
template<typename T>
void heap_sort(T t[],size_t n)
{
    for(int i = n/2; i >= 0; --i)
        siftDown(t,n,i); //start with the most right parent
    while(--n) 
    {
        /* swap the largest with the smallest value, and siftDown the smallest, decrease by 1 size, so we don't change our largest value(freeing heap)
        */
        std::swap(t[0],t[n]); 
        siftDown(t,n,0);
    }
}
//œœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœœ

int main()
{
    int t[] = {9,8,7,6,5,4,3,2,1};
    printArray(t,9);
    //insertion_sort(t,9); //+
    //insertion_sort_with_sentinel(t,9); //+
    //quick_sort(t,9); //+
    //merge_sort(t,9); //+
    //counting_sort(t,9); //+
    //radix_sort(t,9); //+
    //heap_sort(t,9); //+
    bucket_sort(t,9); 
    printArray(t,9);
}
