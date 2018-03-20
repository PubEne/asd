#include <iostream>
#include <stack>
#include <vector>

struct node
{
    explicit node(const int& k,node*const n=nullptr) : key{k},left{nullptr},right{nullptr},parent{n} {}
    int key;
    node* left;
    node* right;
    node* parent;
};

void insert(node *& root,const int& key)
{
    node** current = &root,*prev = nullptr;
    while(*current)
    {
        prev = *current;
        current = key > (*current)->key ? &(*current)->right : &(*current)->left;
    }
    *current = new node(key,prev); 
}
node* find(node* nd,const int& key)
{
    while(nd && nd->key!=key)
        nd = key > nd->key ? nd->right : nd->left;
    return nd;
}
void remove(node *&root,const int& key)
{
    node** nde = &root;
    while((*nde) && (*nde)->key!=key)
        nde = key > (*nde)->key ? &(*nde)->right : &(*nde)->left;
    auto& nd = *nde;
    if(nd)
    {
        if(nd->right && nd->left) //two children
        {
            node** child = &(nd->right); //right subtree
            bool hasLeftChild = false;

            while((*child)->left)
            {
                child = &(*child)->left;
                hasLeftChild = true;
            }
            nd->key = (*child)->key; //take most left child value
            if((*child)->right) //has right kids ?
            {
                node* right_child = (*child)->right;
                node* parent = (*child)->parent;
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
            node* parent = nd->parent;
            delete nd;
            nd = temp;
            nd->parent = parent;
        }
        else
        {
            node* temp = nd->left;
            node* parent = nd->parent;
            delete nd;
            nd = temp;
            nd->parent = parent;
        }
    }  
}
void inorder(const node*const root)
{
    if(root)
    {
        inorder(root->left);
        std::cout << root->key << " ";
        inorder(root->right);
    }
}
void g(node* root)
{
    root->key += 5;
}
void inorder_do(node* root,void f(node*))
{
    node *prev = nullptr;
    while(root)
    {
        if(prev == root->parent)
        {
            if(root->left)
            {
                prev = root;
                root = root->left;
                continue;
            }
            else
                prev = nullptr;
        }
        if(prev == root->left)
        {
            f(root);
            if(root->right)
            {
                prev = root;
                root = root->right;
                continue;
            }
            else
                prev = nullptr;
        }
        if(prev == root->right)
        {
            prev = root;
            root = root->parent;
        }
    }
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
    /*insert(root,5);
    insert(root,2);
    insert(root,10);
    insert(root,7);
    insert(root,6); 
    insert(root,15); 
    insert(root,14); 
    insert(root,13); 
    insert(root,16);*/   

    insert(root,3); 
    insert(root,4); 
    insert(root,1); 
    insert(root,7); 
    insert(root,-4); 
    insert(root,9); 
    insert(root,2); 

    inorder(root);
    std::cout << std::endl; 
    remove(root,3);
    inorder(root);
    std::cout << std::endl;
    inorder_do(root,g);
    destroy(root);
    //std::cout << root->left->key << "," << root->left->parent->key << std::endl;
}
