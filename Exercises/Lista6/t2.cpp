#include <iostream>
#include <string>
#include <algorithm>

namespace ASD
{
    namespace Hashing
    {
        namespace Chaining
        {
            template<typename T,size_t size = 1000>
            class HashMap final
            {
                private:
                    struct node;
                public:
                    HashMap(){};
                    void insert(const T& key)
                    {
                        const size_t hash = hash_str(key);
                        if(hash >= size)
                            return;
                        node* nd = m_arr[hash];
                        if(!nd)
                            m_arr[hash] = new node(hash);
                        else
                        {
                            node* prev = nullptr;
                            while(nd)
                            {
                                prev = nd;
                                nd = nd->m_next;
                            }
                            nd = new node(hash);
                            prev->m_next = nd;
                        }
                    }
                    void remove(const T& key)
                    {
                        const size_t hash = hash_str(key);
                        if(hash >= size)
                            return;
                        node* nd = m_arr[hash];
                        if(!nd)
                            return;
                        else
                        {
                            if(nd && nd->m_key == hash)
                            {
                                m_arr[hash] = nd->m_next;
                                delete nd;
                                return;
                            }
                            node* prev = nullptr;
                            while(nd && hash != nd->m_key)
                            {
                                prev = nd;
                                nd = nd->m_next;
                            }
                            prev->m_next = nd->m_next;
                            delete nd;
                        }
                    }
                    node* find(const T& key)
                    {
                        const size_t hash_key = hash_str(key);
                        node* nd = m_arr[hash_key];
                        while(nd && hash_key != nd->m_key)
                            nd = nd->m_next;
                        return nd;
                    }
                    size_t hash_str(const std::string& s)
                    {
                        size_t h = 0; 
                        for(const char& c : s)
                            h = h * 33 ^ c;
                        return h % 1000;
                    }
                    ~HashMap()
                    {
                        for(size_t i = 0; i < size; ++i)
                            while(m_arr[i])
                            {
                                node* prev = m_arr[i];
                                m_arr[i] = m_arr[i]->m_next;
                                delete prev;
                            }  
                    };
                private:
                    struct node
                    {
                        explicit node(const size_t& key,node*const nd = nullptr) : m_key{key},m_next{nd} {}
                        size_t m_key;
                        node* m_next;
                        ~node(){}
                    };
                    node* m_arr[size] = {nullptr};
            };
        }
    }
    std::string random_string(const size_t& length)
    {
        auto randchar = []() -> char
        {
            const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
            const size_t max_index = (sizeof(charset) - 1);
            return charset[ rand() % max_index ];
        };
        std::string str(length,0);
        std::generate_n(str.begin(),length,randchar);
        return str;
    }
}

int main()
{
    ASD::Hashing::Chaining::HashMap<std::string> hTable;
    std::string arr[1000];
    for(size_t i = 0; i < 1000; ++i)
        arr[i] = ASD::random_string(i);
    for(size_t i = 0; i < 1000; ++i)
        hTable.insert(arr[i]);
    for(size_t i = 0; i < 200; ++i)
        hTable.remove(arr[i]);
    std::cout << hTable.find(arr[201])->m_key << std::endl;
    //std::cout << hTable.find(arr[199])->m_key << std::endl; doesn't belong
}
