#include <iostream>
#include <map>
#include <string>
#include <fstream>

std::map<char,int> countOccurrences(const std::string & filename)
{
    std::fstream file;
    std::string line;
    std::map<char, int> occurrences;

    file.open(filename);
    while(file.is_open() && !file.eof())
    {
        getline(file,line);
        for(const char & character: line)
            occurrences[character] += 1;
    } 
    file.close();
    return occurrences;

}
int main()
{
    std::map<char,int> occurrences = countOccurrences("letter2.txt");
    for (const auto& entry : occurrences)
        std::cout << entry.first << '=' << entry.second << std::endl;
}

