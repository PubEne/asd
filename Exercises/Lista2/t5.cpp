#include <iostream>
#include <memory>

struct lnode
{
    explicit lnode(lnode*const ln = nullptr,const int& k = 0) : m_next{ln}, m_key{k} {}
    int m_key;
    lnode * m_next;

    static lnode* createNode(const int &k) { return new lnode(nullptr,k); }
    int getLength(const lnode*const head) const
    {
        int length{};
        auto temp = head;
        while(temp && ++length)
            temp = temp->m_next;
        return length;
    }
    void append(lnode*& head, const int & num) const
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
    int nth(const size_t & n,const lnode* head) const
    {
        int counter{};
        if(head && n >= head->getLength(head))
            return 0;
        auto temp = head;
        while(temp && n != counter++)
            temp = temp->m_next;
        return temp->m_key;
    }
    ~lnode() { }
};
void printList(const lnode *const& head)
{
    auto temp = head;
    while(temp)
    {
        std::cout << temp->m_key << " ";
        temp = temp->m_next;
    }
    std::cout << std::endl;
}
void reverse(lnode*& head)
{
    lnode *next, *prev = nullptr;
    while(head)
    {   
        next = head->m_next;
        head->m_next = prev;
        prev = head;
        head = next;
    }
    head = prev;
}
void deleteList(lnode *& head)
{
    lnode *next;
    while(head)
    {
        next = head->m_next;
        delete head;
        head = next;
    }
}
int main()
{
    auto head = lnode::createNode(333);
    for(size_t i = 0; i < 4; ++i)
        head->append(head,1+i*i);
    printList(head);
    reverse(head);
    printList(head);
/*    std::cout << "length: " << head->getLength(head) << std::endl;
    std::cout << "nth_tail: " << head->nth(4,head) << std::endl;
    std::cout << "nth_head: " << head->nth(0,head) << std::endl;
    std::cout << "nth6: " << head->nth(5,head) << std::endl;
    std::cout << "nth_3: " << head->nth(3,head) << std::endl;  */
    deleteList(head); //I know - it would be better to do it in destructor
}
