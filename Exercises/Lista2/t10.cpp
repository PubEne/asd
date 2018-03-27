#include <iostream>

struct node
{
    explicit node(const int& k) : key{k},left{nullptr},right{nullptr} {}
    int key;
    node* left;
    node* right;
};
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
                hasLeftChild? parent->left = right_child : parent->right = right_child;
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
void inorder(const node *const t)
{
    if(t)
    {
        inorder(t->left);
        std::cout << t->key << " ";
        inorder(t->right);
    }
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
/*    insert(root,5);
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
    //remove(root,15);
    //remove(root,10);
    remove(root,3);
    inorder(root);
    std::cout << std::endl;
    destroy(root);
}
