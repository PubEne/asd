#include <iostream>
#include <cmath>

/* whole task is wrong */
constexpr int binomialCoeff(const int & n,const int &k)
{
    return (k==0 || k==n) ? 1 : binomialCoeff(n-1,k-1)+binomialCoeff(n-1,k);
}
double Bernoulli_trial(const int &k,const int &n,const double &p)
{
    double probability{};
    for(int i = 0; i < k; i++)
        probability += binomialCoeff(n,k)*pow(p,i)*pow(1-p,n-i);
    return probability;
}
int main()
{
    std::cout << Bernoulli_trial(5,10,1) << std::endl;
}
