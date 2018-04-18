#include <iostream>
#include <string>

//Dan Bernsein hash function
size_t hash_str(const std::string& s)
{
    size_t h = 0; 
    for(const char& c : s)
        h = h * 33 ^ c;
    return h;
}

int main()
{
    std::cout << hash_str("dsds") << std::endl;
}
