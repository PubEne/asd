#include <iostream>
#include <set>
#include <limits>
#include <utility>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <fstream>

//Bitonical tour implementation
namespace ASD
{
    std::vector<std::pair<double,double>> FillAndSortVector(size_t& numberOfCities,const std::string& filename="miasta.txt")
    {
        std::vector<std::pair<double,double>> crd;
        std::ifstream inFile;
        inFile.open(filename);
        if(inFile.is_open())
        {
            inFile >> numberOfCities;
            double x = 0,y = 0;
            while(!inFile.eof() && inFile >> x >> y)
                crd.emplace_back(x,y);
        }
        inFile.close();
        std::sort(crd.begin(),crd.end(),[](const auto& a,const auto& b) { return a.first < b.first; });
        return crd;
    }
    void BitonicalTour()
    {
        size_t numberOfCities = 0;
        constexpr double inf = std::numeric_limits<double>::max();
        std::vector<std::pair<double,double>> crd = FillAndSortVector(numberOfCities);

        std::vector<std::vector<double>> bitonicDistances(numberOfCities+1,std::vector<double>(numberOfCities+1,0));
        std::vector<std::vector<int>> result(numberOfCities+1,std::vector<int>(numberOfCities+1,-1));

        auto euclideanDistance = [](const auto& a,const auto b) -> double { return sqrt(pow(a.first - b.first,2)+pow(a.second - b.second,2)); };

        for(size_t i = 1; i <= numberOfCities; ++i)
            for(size_t j = i+1; j <= numberOfCities; ++j)
            {
                if(i < j - 1)
                    bitonicDistances[i][j] = bitonicDistances[i][j-1] + euclideanDistance(crd[j-2],crd[j-1]);
                else if(i == j -1)
                {
                    double min_dis = bitonicDistances[1][j-1] + euclideanDistance(crd[0],crd[j-1]);
                    size_t no = 1;
                    for(size_t k = 2; k < j -1; ++k)
                    {
                        double tmp_dis = euclideanDistance(crd[k-1],crd[j-1]);
                        if(bitonicDistances[k][j-1] + tmp_dis < min_dis)
                        {
                            min_dis = bitonicDistances[k][j-1] + euclideanDistance(crd[k-1],crd[j-1]);
                            no = k;
                        }
                    }    
                    bitonicDistances[i][j] = min_dis;
                    result[i][j] = no;
                } 
            }
        double cost = bitonicDistances[numberOfCities-1][numberOfCities] + euclideanDistance(crd[numberOfCities-2], crd[numberOfCities-1]);
        std::cout << cost << std::endl;
                
        std::set<int> s1,s2;
        for (int i = 0; i < numberOfCities; ++i)
            s1.insert(i);
        int i = numberOfCities - 1, j = numberOfCities;
        s1.erase(i);
        s2.insert(i);
        while (result[i][j] != -1) 
        {
            s1.erase(result[i][j] - 1);
            s2.insert(result[i][j] - 1);
            i = result[i][j] < i ? result[i][j] : i;
            j = result[i][j] >= i ? result[i][j] : i;
        }
        s1.insert(0);
        s2.insert(0);
        for(const auto& el : s2)
            std::cout << el << " ";
        for (auto itr = s1.rbegin(); itr != s1.rend(); itr++)
            std::cout << *itr << " ";
         std::cout << std::endl;
    }
}
int main()
{
    ASD::BitonicalTour();
}

