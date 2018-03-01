#include <iostream>
#include <memory>

struct lnode
{
    explicit lnode(const std::shared_ptr<lnode>& ln = nullptr,const int& k = 0) : m_next{ln}, m_key{k} {}
    int m_key;
    std::shared_ptr<lnode> m_next;

    static std::shared_ptr<lnode> createNode(const int & x)
    {
        return std::make_shared<lnode>(nullptr,x);
    }
    int getLength(const std::shared_ptr<lnode>& head)
    {
        int length{};
        auto temp = head;
        while(temp && ++length)
            temp = temp->m_next;
        return length;
    }
    void append(std::shared_ptr<lnode> & head, const int & num)
    {
        auto new_nlode = createNode(num);
        auto temp = head;
        if(!head)
            head = new_nlode;
        else
            while(temp->m_next)
                temp = temp->m_next;
        temp->m_next = new_nlode;
    }
    ~lnode() {}
};
int nth(const size_t & n,const std::shared_ptr<lnode>& head)
{
    int counter{};
    if(head && n >= head->getLength(head))
        return 0;
    auto temp = head;
    while(temp && n != counter++)
        temp = temp->m_next;
    return temp->m_key;
}
int main()
{
    auto head = lnode::createNode(5);
    for(size_t i = 0; i < 4; ++i)
        head->append(head,1+i*i);
    auto temp = head;
    while(temp)
    {
        std::cout << temp->m_key << std::endl;
        temp = temp->m_next;
    }
    std::cout << "length: " << head->getLength(head) << std::endl;
    std::cout << "nth: " << nth(4,head) << std::endl;
}
