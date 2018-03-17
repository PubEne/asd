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
lnode * merge(lnode* L1, lnode* L2)
{
    if(!L1) return L2;  // 1
    if(!L2) return L1;  // 2

    lnode * head;
    if(L1->m_key < L2->m_key)  head = L1; // 3
    else 
    {
        head = L2;
        L2 = L1;
        L1 = head;
    }
    while(L1->m_next) 
    {
        if(L1->m_next->m_key > L2->m_key)
        {
            lnode * tmp = L1->m_next;
            L1->m_next = L2;
            L2 = tmp;
        }
        L1 = L1->m_next;
    }
    L1->m_next = L2;
    return head;
}
void deleteList(lnode *& head)
{
    if(head)
    {
        deleteList(head->m_next);
        delete head;
        head = nullptr;
    }
}
int main()
{
    auto head = lnode::createNode(0);
    auto head2 = lnode::createNode(1);
    for(size_t i = 0; i < 4; ++i)
    {
        head->append(head,1+i*i);
        head2->append(head2,3+i*i);
    }
    printList(head);
    printList(head2);
    auto head3 = merge(head,head2);
    printList(head3);
/*    std::cout << "length: " << head->getLength(head) << std::endl;
    std::cout << "nth_tail: " << head->nth(4,head) << std::endl;
    std::cout << "nth_head: " << head->nth(0,head) << std::endl;
    std::cout << "nth6: " << head->nth(5,head) << std::endl;
    std::cout << "nth_3: " << head->nth(3,head) << std::endl;  */
    deleteList(head); //I know - it would be better to do it in destructor
}
