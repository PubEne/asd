#include <iostream>
#include <stack>

struct node
{
    explicit node(const int& k) : key{k},left{nullptr},right{nullptr} {}
    int key;
    node* left;
    node* right;
};
namespace ASD
{
    class iterator
    {
        public:
            explicit iterator(node* root = nullptr,const std::stack<node*> ss = std::stack<node*>()) : current{root}, s{ss} {}
            ~iterator() {}
            iterator& operator=(const iterator& it) 
            {
                current = it.current; 
                s = it.s;
                return *this; 
            }
            iterator& operator++()
            {
                if(current->right)
                {
                    s.emplace(current);
                    current = current->right;
                    while(current->left)
                    {
                        s.emplace(current);
                        current = current->left;
                    }
                    return* this;
                }
                while(!s.empty())
                {
                    if(current == s.top()->left)
                    {
                        current = s.top();
                        s.pop();
                        return *this;
                    }
                    current = s.top();
                    s.pop();
                }
                current = nullptr;
                return *this;
            }
            iterator operator++(int)
            {
                iterator temp = *this;
                ++(*this);
                return temp;
            }
            int& operator*() const
            {
                return current->key;
            }
            bool operator!=(const iterator& it) const { return current != it.current; }
        private:
            node* current;
            std::stack<node*> s;
    };
}
ASD::iterator begin(node* root) //starting from most left
{
    std::stack<node*> s;
    while(root && root->left)
    {
        s.emplace(root);
        root = root->left;
    }
    return ASD::iterator(root,s);
}
ASD::iterator end(node* root)
{
    return ASD::iterator(); //ending in one element beyond most right - means nullptr
}
void insert(node*& root,const int& key)
{
    node** current = &root;
    while(*current)
        current = key > (*current)->key ? &(*current)->right : &(*current)->left;
    *current = new node(key);   
}
node* find(node* nd,const int& key)
{
    while(nd && nd->key!=key)
        nd = key > nd->key ? nd->right : nd->left;
    return nd;
}
void remove(node*& root,const int& key)
{
    node** nde = &root;
    while((*nde) && (*nde)->key!=key)
        nde = key > (*nde)->key ? &(*nde)->right : &(*nde)->left;
    auto& nd = *nde;
    if(nd) 
    {
        if(nd->right && nd->left) //two children
        {
            node** child = &(nd); 
            node* parent = *child;
            child = &(nd->right);
            bool hasLeftChild = false;

            while((*child)->left)
            {
                parent = *child;
                child = &(*child)->left;
                hasLeftChild = true;
            }
            nd->key = (*child)->key; //take most left child value
            if((*child)->right) //has right kids ?
            {
                //take kids and connect them to their grandparents
                node* right_child = (*child)->right;                 
                delete *child;
                *child = nullptr;
                hasLeftChild ? parent->left = right_child : parent->right = right_child;
            }
            else
            {
                delete *child;
                *child = nullptr;
            }
        }
        else if(!nd->right && !nd->left) //leaf 
        {
            delete nd;
            nd = nullptr;
        }
        else if(!nd->left) // has right child
        {   
            node* temp = nd->right;
            delete nd;
            nd = temp;
        }
        else //left
        {
            node* temp = nd->left;
            delete nd;
            nd = temp;
        }
    }  
}
void inorder(const node *const root)
{
    if(root)
    {
        inorder(root->left);
        std::cout << root->key << " ";
        inorder(root->right);
    }
}
void inorder_do(node*const root,void f(node*const))
{
    if(root)
    {
        inorder_do(root->left,f);
        f(root);
        inorder_do(root->right,f);
    }
}
void g(node*const root)
{
    std::cout << ++++++++root->key << " ";
}
void destroy(node*& root)
{
    if(root)
    {
        destroy(root->left);
        destroy(root->right);
        delete root;
        root = nullptr;
    }
}
int main()
{
    node* root = nullptr;
    insert(root,5);
    insert(root,2);
    insert(root,1);
    insert(root,3);
    insert(root,10);
    insert(root,7);
    insert(root,6); 
    insert(root,15); 
    insert(root,14); 
    insert(root,13); 
    insert(root,16);   

    inorder(root);
    std::cout << std::endl;
    for(ASD::iterator i = begin(root); i != end(root);++i) //iterator
    {
        std::cout << *i << " ";
    }
    destroy(root);
}
