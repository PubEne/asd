#include <iostream>
#include <cmath>

double Bernoulli_trial(const int &k,const int &n,const double &p)
{
    const double q = 1-p;
    const double p_q = p/q;
    double probability = pow(q,n);
    double sum = probability;
    for(size_t i = 1; i < k; ++i)
    {
        probability *= ((n+1-i)*p_q)/i;
        sum += probability;
    }
    return sum;
}
int main()
{
    std::cout << Bernoulli_trial(8,14,0.6) << std::endl;
}
