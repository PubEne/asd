#include <iostream>
#include <queue>
#include <utility>

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
lnode* getMiddle(lnode*const& head)
{
    if(head)
    {
        lnode* slow = head;
        lnode* fast = head;
        while(fast && fast->m_next)
        {
            fast = fast->m_next->m_next;
            slow = slow->m_next;
        }
        return slow;
    }
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
lnode* merge(lnode* L1, lnode* L2)
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
void insertion_sort(lnode*& head)
{
    for(lnode* i = head; i; i = i->m_next)
        for(lnode* j = i->m_next; j; j = j->m_next)
            if(i->m_key > j->m_key)
                std::swap(i->m_key,j->m_key); 
}
void insertion_sort2(lnode*& head)
{
    if(!head->m_next || !head)
        return;
    lnode* sorted = nullptr;
    while(head)
    {
        lnode* cur = head;
        lnode** ptr = &sorted;
        head = head->m_next;
        while(*ptr && cur->m_key > (*ptr)->m_key)
        {
            ptr = &(*ptr)->m_next;
        }
        cur->m_next = *ptr;
        *ptr = cur;
    }
    head = sorted;
}
namespace ASD
{
    constexpr size_t size(const lnode* head)
    {
        size_t s = 0;
        while(head && ++s)
            head = head->m_next;
        return s;
    }
}
void merge_sort(lnode*& head)
{
    size_t size = ASD::size(head);
    if (size < 2) return;

    size_t i,j;
    lnode* arr[size+1];

    for(i = 0; i < size; i++) //array of nodes
    {
        arr[i] = head;
        head = head->m_next;
        arr[i]->m_next = nullptr;
    }
    arr[i] = nullptr;

    for(size_t mid = size; mid > 1; mid = (mid+1)/2) //merge pairs of nodes
    {
        for(i = j = 0; i < mid; j++, i+=2)
        {
            arr[j] = merge(arr[i], arr[i+1]);
            std::cout << "arr[" << j << "] = merge(arr[" << i << "],arr[" << i+1 << "])" << std::endl;
        }
        arr[j] = nullptr;
    }
    head = arr[0];
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
    auto head = lnode::createNode(5);
    for(size_t i = 0; i < 5; ++i)
        head->append(head,10-i*i);
    printList(head);
    merge_sort(head);
    printList(head);
/*    std::cout << "length: " << head->getLength(head) << std::endl;
    std::cout << "nth_tail: " << head->nth(4,head) << std::endl;
    std::cout << "nth_head: " << head->nth(0,head) << std::endl;
    std::cout << "nth6: " << head->nth(5,head) << std::endl;
    std::cout << "nth_3: " << head->nth(3,head) << std::endl;  */
    deleteList(head); //I know - it would be better to do it in destructor
}
