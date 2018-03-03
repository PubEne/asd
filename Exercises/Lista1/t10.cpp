#include <iostream>

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
            ~stack() {}
        private:
            size_t m_top;
            T m_arr[max_size];
             
    };
} 
int main()
{
    ASD::stack<int> stack;
    std::cout << stack.size() << std::endl;
    stack.push(5);
    stack.push(45);
    std::cout << stack.size() << std::endl;
    std::cout << stack.top() << std::endl;
    stack.pop();
    std::cout << stack.size() << std::endl;
    std::cout << stack.top() << std::endl;
}
