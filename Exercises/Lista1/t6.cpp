#include <iostream>

struct MinMax
{
    MinMax() : min(0), max(0) {}
    int min;
    int max;
    MinMax getMinMax()
    {
        return MinMax();
    }
};
std::ostream& operator<<(std::ostream& stream, const MinMax& minmax)
{
    stream << minmax.min << "," << minmax.max << std::endl;
    return stream;
}
int main()
{
    MinMax a = MinMax().getMinMax();
    std::cout << a;
}
