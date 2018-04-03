#include <iostream>

namespace ASD
{
    template<typename T>
    class priority_queue final
    {
        public:
            constexpr explicit priority_queue(T*const& t = nullptr,const size_t& size = 0) noexcept : m_arr{t},m_size{size},m_was_allocated(m_arr ? false : true)
            {
                //build_heap
                size_t i = size/2;
                while(i)
                    siftDown(--i,size);
            }
            constexpr size_t size() { return m_size; }
            constexpr bool empty() { return !m_size; }
            void push(const T& num)
            {
                siftUp(m_size++,num);
            }
            const T& top() const
            {
                return m_arr[0];
            }
            void pop()
            {
                m_arr[0] = m_arr[--m_size];
                siftDown(0,m_size);
            }
            ~priority_queue()
            {
                if(m_was_allocated)
                    delete[] m_arr;
            }
        private:
            T* m_arr;
            size_t m_size;
            bool m_was_allocated;
            void siftDown(size_t i,const size_t& n)
            {
                if(!m_arr) m_arr = new T[100];
                size_t k;
                T x = m_arr[i];
                while(( (k=2*i+2) < n && m_arr[k] > x && m_arr[k] > m_arr[k-1]) || ( --k < n && m_arr[k] > x))
                {
                    m_arr[i] = m_arr[k];
                    i = k;
                }
                m_arr[i] = x;
            }
            void siftUp(size_t i,const T& x)
            {
                if(!m_arr) m_arr = new T[100];
                size_t k;
                while(i && m_arr[k=(i-1)/2] < x)
                {
                    m_arr[i] = m_arr[k];
                    i = k;
                }
                m_arr[i] = x;
            }
    };
}
int main()
{
    //int t[] = {5,4,3,2,1,100,5,7,8};
    double t[]={32,5,6,7,645,34,54,23,3,32,1231,43,24,26,62,7,4,5};

    const size_t n = sizeof(t)/sizeof(*t);
    ASD::priority_queue<double> pq;
    for(size_t i = 0; i < n; ++i)
        pq.push(t[i]);
    for(size_t i = 0; i < n; ++i)
    {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << std::endl;
}
