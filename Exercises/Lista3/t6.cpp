#include <iostream>

int getSum(int* a,size_t n,size_t k)
{
    int largestSum = 0;
    int previousSum = 0;
    for(size_t i = 0; i <= n - k; ++i)
    {
        if(!i)
        {
            for(size_t j = 0; j < k; ++j)
                largestSum += a[j];
            previousSum = largestSum;
        }
        else
        {
            int currentSum = previousSum - a[i-1] + a[i+k-1];
            if(currentSum > largestSum)
                largestSum = currentSum;
            previousSum = currentSum;
        }
        std::cout << "Sum:" << previousSum << std::endl;
    }
    return largestSum;
}

int main()
{
    int t[] = {5,2,3,6,8,14,6334,23};
    size_t t_size = sizeof(t)/sizeof(*t);
    std::cout << getSum(t,t_size,3) << std::endl;
}
