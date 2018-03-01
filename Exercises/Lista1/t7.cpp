#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

std::vector<double> readPoly(const std::string& filename)
{
    std::string line;
    std::vector<double> v;    
    std::ifstream file(filename);

    if(file.is_open())
    {
        while(!file.eof())
            file >> line;
        file.close();
    }
    else
        return std::vector<double>();
    std::stringstream ss(line);
    double i;
    while(ss >> i)
    {
        v.emplace_back(i);
        if(ss.peek() == ',')
            ss.ignore();
    }
    return v;
}
std::vector<double> multiplyPoly(const std::vector<double> & poly1, const std::vector<double> &poly2)
{
    std::vector<double> v;
    if(!(poly1.empty() && poly2.empty()))
        v.resize((poly1.size()+poly2.size()-1));
    for(size_t i = 0; i < poly1.size(); i++)
        for(size_t j = 0; j < poly2.size(); j++)
            v[i+j] += poly1[i]*poly2[j];
    return v;
}
void writePoly(const std::vector<double>& poly)
{
    std::ofstream out_file;
    out_file.open("c.txt");
    for(auto it = poly.begin(); it!=poly.end(); it++)
    if(it == poly.end()-1)
        out_file << *it;
    else
        out_file << *it << ",";
    out_file.close();
}
int main()
{
    const std::vector<double> poly1 = readPoly("a.txt");
    const std::vector<double> poly2 = readPoly("b.txt");
    const std::vector<double> mult_poly = multiplyPoly(poly1,poly2);

    writePoly(mult_poly);
    for(const auto& element : poly1)
        std::cout << element << " ";
    std::cout << "\n";
    for(const auto& element : poly2)
        std::cout << element << " ";
    std::cout << "\n";
    for(const auto& element : mult_poly)
        std::cout << element << " ";
    std::cout << "\n";
}
