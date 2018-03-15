#include <iostream>
#include <vector>

int scalar(const std::vector<int> &v,const std::vector<int> &v2)
{
    int in_product{};
    for(size_t i = 0; i < v.size(); ++i)
            in_product += v[i]*v2[i];
    return in_product;
}
//(b) Horner's method Lista1/t3.cpp O(n)
//(c) O(n^2) Lista1/t7.cpp
//(d) O(n^3)
//e O(n!)
int main()
{
    const std::vector<int> v = {1,2,3};
    const std::vector<int>v2 = {4,5,6};
    std::cout << scalar(v,v2) << std::endl;
}
