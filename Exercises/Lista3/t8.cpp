#include <iostream>
#include <cassert>
#include <vector>

struct node
{
    explicit node(const int& k) : key{k},left{nullptr},right{nullptr},counter{0} {}
    int key;
    node* left;
    node* right;
    size_t counter; // number of nodes in subtree 
};

inline void recursive_insert(node*& nd,const int& key)
{
	if(!nd)
		nd = new node(key);
	else
    {
        if(key > nd->key)
        {
            ++nd->counter;
            recursive_insert(nd->right,key);
        }
        else
            recursive_insert(nd->left,key);
    }
}  
constexpr int min(const node* nd)
{
    assert(nd && "oops");
    while(nd->left)
        nd = nd->left;
    return nd->key;
}

void subtract_counter(std::vector<node*>& vec,node*const& nd)
{
    for(auto it = vec.begin(); it != vec.end();) //go over parents node besides root, if they have counter then subtract by 1
        if((*it)->key > nd->key) 
            it = vec.erase(it++); //only in left subtree this option is possible
        else
        {
            (*it)->counter ? --(*it)->counter : 1;
            std::cout << "|" << (*it)->key << "|";
            it = vec.erase(it++);
        } 
}
void recursive_remove(node*& nd,const int& key,node* parent=nullptr)  
{
    if(!nd) return;

    static std::vector<node*> v;

    if(parent && parent->counter)
        v.emplace_back(parent); //vector of non-nullptr and non-zero counter parents
    if(nd->key == key)
    {
        if(!nd->left) //right child or leaf
        {
            subtract_counter(v,nd);
            node* temp = nd->right;
            std::cout << "node which doesn't have left child or leaf" << std::endl;
            delete nd;
            nd = temp;
        }
        else 
        {
            if(!nd->right) //node doesn't have right child
            {   
                subtract_counter(v,nd);
                node* temp = nd->left;	
                delete nd;
                nd = temp;
                std::cout << "node which doesn't have right child" << std::endl;
            }
            else //two children
            {  
                nd->key = min(nd->right); //replace key with the smallest element in right subtree
                std::cout << "two children" << std::endl;
                recursive_remove(nd->right,nd->key,nd); //delete that smallest element
            } 
        }
        v.clear();
    }
    else
        recursive_remove(key > nd->key ? nd->right : nd->left,key,nd);
} 
void inorder2(const node*const root)
{
    if(root)
    {
        inorder2(root->left);
        std::cout << root->key << " ";
        inorder2(root->right);
    }
}
void inorder(const node*const root)
{
    if(root)
    {
        inorder(root->left);
        std::cout << root->counter << " ";
        inorder(root->right);
    }
}
void reverse_inorder(const node*const root)
{
    if(root)
    {
        inorder(root->right);
        std::cout << root->key << " ";
        inorder(root->left);
    }
}
constexpr int getCounter(const node* nd,const int& key)
{
    while(nd && nd->key != key)
        nd = key > nd->key ? nd->right : nd->left;
    return nd ? nd->counter : -1;
}
const node* nth_largest_element(const node* nd,int n)
{
    const node* nth = nullptr;
    if(nd)
    {
        while(nd)
        {
            if(nd->counter + 1 == n)
            {
                nth = nd;
                break;
            }
            else if(n > nd->counter)
            {
                n -= nd->counter + 1;
                nd = nd->left;
            }
            else
                nd = nd->right;
        } 
    }
    return nth;
}
void destroy(node*& root)
{
    if(root)
    {
        destroy(root->right);
        destroy(root->left);
        delete root;
        root = nullptr;
    }
}
int main()
{
    node* root = nullptr;
    recursive_insert(root,5);
    recursive_insert(root,2);
    recursive_insert(root,1);
    recursive_insert(root,15);
    recursive_insert(root,3);
    recursive_insert(root,4);
    recursive_insert(root,17);
    recursive_insert(root,16);
    
    inorder2(root);
    std::cout << std::endl; 
    inorder(root);
    std::cout << std::endl; 
    recursive_remove(root,5);
    recursive_remove(root,15);
    recursive_remove(root,17);
    recursive_remove(root,3);
    recursive_remove(root,4);
    inorder2(root);
    std::cout << std::endl; 
    inorder(root);
    std::cout << std::endl; 
    for(size_t i = 1; i < 10; ++i)
        while(nth_largest_element(root,i))
        {
            std::cout << nth_largest_element(root,i)->key << " ";
            break;
        }
    std::cout << std::endl;

    destroy(root);
}
