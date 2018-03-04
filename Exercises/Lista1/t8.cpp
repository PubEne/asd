#include <iostream>

namespace ASD
{
    template<typename T>
    class Fraction
    {
        public:
            explicit Fraction(T numerator=0,T denominator=1) : m_numerator(numerator), m_denominator(denominator) {}
            bool canSimplify() const
            {
                for(int i = m_numerator; i >= 2; --i)
                    if((!(m_numerator % i) && !(m_denominator % i)))
                        return true;
                return false;
            }
            Fraction operator*(const Fraction& fraction) const
            {
                return Fraction(m_numerator*fraction.m_numerator,m_denominator*fraction.m_denominator);
            }
            Fraction operator*(const T& num) const
            {
                return Fraction(m_numerator*num,m_denominator*num);
            }
            Fraction operator/(const Fraction& fraction) const
            {
                return Fraction(m_numerator*fraction.m_denominator,m_denominator*fraction.m_numerator);
            }
            Fraction operator+(const Fraction& fraction) const
            {
                return Fraction(m_numerator*fraction.m_denominator+m_denominator*fraction.m_numerator,m_denominator*fraction.m_denominator);
            }
            Fraction operator-(const Fraction& fraction) const
            {
                return Fraction(m_numerator*fraction.m_denominator-m_denominator*fraction.m_numerator,m_denominator*fraction.m_denominator);
            }
            friend std::istream &operator>>(std::istream &in, Fraction & fraction)
            {
                return in >> fraction.m_numerator >> fraction.m_literal >> fraction.m_denominator;
            }
            friend std::ostream &operator<<(std::ostream &out, const Fraction & fraction) 
            {
                if(fraction.canSimplify())
                    return out << "fraction can be simplified";
                if(fraction.m_denominator == 1)
                    return out << fraction.m_numerator;
                if(fraction.m_numerator && fraction.m_denominator)
                    return out << fraction.m_numerator << "/" << fraction.m_denominator;
                if(!fraction.m_numerator)
                    return out << 0;
                if(!fraction.m_denominator)
                    throw std::overflow_error("Divide by zero exception");
            }
        private:
            T m_numerator;
            T m_denominator;
            char m_literal;
    };
}
int main()
{
    try {
            ASD::Fraction<int> fraction;
            std::cin >> fraction;
            std::cout << fraction << std::endl;
        }
    catch(const std::overflow_error &e) 
        {
            std::cout << e.what() << std::endl;
        }
}
