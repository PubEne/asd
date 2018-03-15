#include <iostream>

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
            auto min = nd->right;
            while(min->left)
                min = min->left;
            nd->key = min->key; 
            delete min;
            min = nullptr;
            nd->right = nd->parent;  
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
void inorder(const node *const t)
{
    if(t)
    {
        inorder(t->left);
        std::cout << t->key << " ";
        inorder(t->right);
    }
}
int main()
{
    node* root = nullptr;

    insert(root,5);
    insert(root,22);
    insert(root,25);
    insert(root,17);
    insert(root,16);
    insert(root,19);
    inorder(root);
    remove(root,7);
    std::cout << std::endl;
    inorder(root);
    //std::cout << root->left->key << "," << root->left->parent->key << std::endl;
}
