#include <iostream>
#include <utility>
#include <vector>

std::pair<double,double> getMinMax(const std::vector<double> & vec)
{
    //min's 1st, max's 2nd
    std::pair<double,double> min_max;
    int i;
    //if size is even then initialize the first two elements as minimum and maximum
    if(!(vec.size() & 1))
    {
        if(vec[0] > vec[1])
        {
            min_max.first = vec[1];
            min_max.second = vec[0];
        }
        else
        {
            min_max.first = vec[0];
            min_max.second = vec[1];
        }
        i = 2;
    }
    else
    {
        min_max.first = vec[0];
        min_max.second = vec[0];
        i = 1;
    }
    while(i < vec.size()-1)
    {
        if(vec[i] > vec[i+1])
        {
            if(min_max.second < vec[i])
                min_max.second = vec[i];
            if(min_max.first > vec[i+1] )
                min_max.first = vec[i+1];
        }
        else
        {
            if(min_max.second < vec[i+1])
                min_max.second = vec[i+1];
            if(min_max.first > vec[i])
                min_max.first = vec[i];
        }
        i+=2;
    }
    return min_max;
}
int main()
{
    const std::vector<double> v {334,1231,230,231,545,691,321,31,5,10,5,4};
    const auto minmax = getMinMax(v);
    std::cout << "size: "  << v.size() 
              << "\nmin: " << minmax.first
              << "\nmax: " << minmax.second << std::endl;
}
