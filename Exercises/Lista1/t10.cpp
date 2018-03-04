#include <iostream>
#include <memory>

//container adaptors - queue, stack, priority_queue
namespace ASD
{
    template<typename T,size_t max_size=100>
    class stack
    {
        public:
            explicit stack() : m_top(0) {} 
            void push(const T& val)
            {
                if(m_top > max_size)
                    return;
                else
                    m_arr[m_top++] = val;
            }
            void pop()
            {
                if(!m_top)
                    return;
                else
                    m_arr[m_top--] = 0;
            }
            size_t size() const { return m_top; }
            T top() const { return m_arr[m_top-1]; }
            bool empty() const { return size() ? false : true; }
            ~stack() {}
        private:
            size_t m_top;
            T m_arr[max_size];
             
    };
    template<typename T>
    class queue
    {
        public:
            explicit queue() : m_front{nullptr}, m_back{nullptr}, m_size{0} {}
            T front() const { return !m_front ? 0 : m_front->m_key; } // i assumed that if queue doesn't have elements then return 0(too lazy to throw exception)
            T back() const { return !m_back ? 0 : m_back->m_key; }
            bool empty() const { return m_size ? false : true; }
            size_t size() const { return m_size; }
            void push(const T& val)
            {
                auto new_nlode = lnode::createNode(val);
                if(!m_front && !m_back)
                    m_front = m_back = new_nlode;
                else
                    m_back = m_back->m_next = new_nlode;
                ++m_size;
            }
            void pop() 
            { 
                if(!m_front)
                    return;
                if(m_front == m_back)
                    m_front = m_back = nullptr;
                else
                    m_front = m_front->m_next;
                --m_size; 
            }
        private:
            struct lnode
            {
                explicit lnode(const std::shared_ptr<lnode>& ln = nullptr,const T& k = 0) : m_next{ln}, m_key{k} {}
                T m_key;
                std::shared_ptr<lnode> m_next;
                static std::shared_ptr<lnode> createNode(const T &x=0) { return std::make_shared<lnode>(nullptr,x); }
            };    
            std::shared_ptr<lnode> m_front;
            std::shared_ptr<lnode> m_back;
            size_t m_size;
    };
} 
int main()
{
    
/*------------------STACK------------------------
    ASD::stack<int> stack;
    std::cout << stack.size() << std::endl;
    stack.push(5);
    stack.push(45);
    std::cout << stack.size() << std::endl;
    std::cout << stack.top() << std::endl;
    stack.pop();
    std::cout << stack.size() << std::endl;
    std::cout << stack.top() << std::endl;
    std::cout << "isEmpty? " << stack.empty() << std::endl;
    stack.pop();
    stack.pop();
    std::cout << "isEmpty? " << stack.empty() << std::endl;
    std::cout << stack.top() << std::endl; */
    
    ASD::queue<int>  my_queue;
    my_queue.push(5);
    my_queue.push(45);
    my_queue.push(410);
    std::cout << "5,45,410" << std::endl;
    std::cout << "front val:" << my_queue.front() << std::endl;
    std::cout << "back val:" << my_queue.back() << std::endl;
    std::cout << "size: " << my_queue.size() << std::endl;
    my_queue.pop();
    std::cout << "after pop front val is:" << my_queue.front() << std::endl;
    my_queue.pop();
    std::cout << "after pop front val is:" << my_queue.front() << std::endl;
    my_queue.pop();
    std::cout << "after pop front val is:" << my_queue.front() << std::endl;
    my_queue.push(2);
    std::cout << "front val:" << my_queue.front() << std::endl;
    std::cout << "back val:" << my_queue.back() << std::endl;
}
