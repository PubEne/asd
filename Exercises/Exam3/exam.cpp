#include <iostream>


/* -------------------- Zadanie1 -------------------------
1. Zapisz warunki jakie muszą spełniać klucze drzewa BST

Odp: Klucz w każdym węzle musi być większy lub równy od klucza w lewym poddrzewie oraz mniejszy lub równy od klucza w prawym poddrzewie.
----------------------- Zadanie2 -------------------------
2. Napisz procedurę node* find(node* tree,int x), która zwraca wskaźnik na węzeł zawierający x lub NULL jeśli nie ma takiego węzła

Odp:
node* find(node* tree,int x) //non-recursive version
{
    while(tree && tree->key != x)
        tree = x > tree->key ? tree->right : tree->left; 
    return tree;
}
node* find(node* tree,int x) //recursive
{
    if(!tree || tree->key == x)
        return tree;
    return find(x > tree->key ? tree->right : tree->left,x);
}
----------------------- Zadanie3 -------------------------
3. Napisz procedurę void insert(node*& tree,int x) (dodaje do drzewa tree klucz x)

Odp:
void insert(node*& tree,int x) //recursive
{
    if(!tree)
        tree = new node(x,nullptr,nullptr);
    else
        insert(x > tree->key ? tree->right : tree->left,x);
}
void insert_iterative(node*& tree,int x)
{
    node** nd = &tree;
    while(*nd)
        nd = x > (*nd)->key ? &(*nd)->right : &(*nd)->left;
    *nd = new node(x,nullptr,nullptr);
}
----------------------- Zadanie4 -------------------------
4. Drzewo BST o różnych kluczach można odtworzyć z listy par klucz_węzła:klucz_jca
    a) Narysuj drzewo BST reprezentowane przez listę par: 1:2, 2:4, 3:2, 4:5, 6:7, 7:9, 8:7, 9:5
    b) Wypisz jego klucze w porządku inorder
    c) Wypisz jego klucze w porządku preorder
    d) Wypisz jego klucze w porządku postorder

Odp:

----------------------- Zadanie5 -------------------------
5. Napisz procedurę void wypisz(node* tree,int order=0), która wypisuje klucze drzewa tree w porządku inorder gdy order = 0, preorder gdy order=1, postorder gdy order=2

Odp:
void wypisz(node* tree,int order=0)
{
    if(tree)
    {
        switch(order)
        {
            case 0:
                wypisz(tree->left,order);
                std::cout << tree->key << " ";
                wypisz(tree->right,order);
                break;
            case 1:
                std::cout << tree->key << " ";
                wypisz(tree->left,order);
                wypisz(tree->right,order);
                break;
            case 2:
                wypisz(tree->left,order);
                wypisz(tree->right,order);
                std::cout << tree->key << " ";
                break;
            default:
                break;
        }
    }
}
----------------------- Zadanie6 -------------------------
6. Jakie informacje przechowujemy w węźle drzewa czerwono-czarnego? Podaj definicję drzewa czerwono czarnego. Zadeklaruj strukturę RBnode tak, by dziedziczyła z node. Czy można dla niej użyć funkcji napisanych w zadaniach 2,3 i 5?

Odp: 
    1.Przechowujemy informacje jak w drzewie BST tylko jeszcze potrzebujemy przechowywać kolor węzła, w naszym przypadku jest to bool(może również być znak(char)).
    2. Drzewem czerwono czarnym nazywamy drzewo takie że:
        1. Każdy węzeł jest czerwony lub czarny
        2. Korzeń jest czarny.
        3. Wszystkie liścia(null pointery) są czarne
        4. Jeśli węzeł jest czerwony wtedy jego dzieci muszą być czarne
        5. Każda ścieżka z dowolnego węzła do liścia(nullptr) ma dokładnie taką samą ilość czarnych węzłów(czyli taką samą czarną głębokość)
    3.
        struct RBnode : public node
        {
            RBnode(int k,node* l=nullptr,node* r=nullptr,bool red=1) : node(k,l,r), m_red(red) {}
            bool m_red;
        };
    4.  2,5 - tak, 3 - nie.
*/
struct node
{
    node(int k,node* l,node* r) : key(k),left(l),right(r) {}

    int key;
    node* left;
    node* right;
};
struct RBnode : public node
{
    RBnode(int k,node* l=nullptr,node* r=nullptr,bool red=1) : node(k,l,r), m_red(red) {}
    bool m_red;
};
void wypisz(node* tree,int order=0)
{
    if(tree)
    {
        switch(order)
        {
            case 0:
                wypisz(tree->left,order);
                std::cout << tree->key << " ";
                wypisz(tree->right,order);
                break;
            case 1:
                std::cout << tree->key << " ";
                wypisz(tree->left,order);
                wypisz(tree->right,order);
                break;
            case 2:
                wypisz(tree->left,order);
                wypisz(tree->right,order);
                std::cout << tree->key << " ";
                break;
            default:
                break;
        }
    }
}
void insert(node*& tree,int x)
{
    if(!tree)
        tree = new node(x,nullptr,nullptr);
    else
        insert(x > tree->key ? tree->right : tree->left,x);
}
void insert_iterative(node*& tree,int x) 
{
    node** nd = &tree;
    while(*nd)
        nd = x > (*nd)->key ? &(*nd)->right : &(*nd)->left;
    *nd = new node(x,nullptr,nullptr);
}
node* find(node* tree,int x)
{
    if(!tree || tree->key == x)
        return tree;
    return find(x > tree->key ? tree->right : tree->left,x);
}
void inorder(node* tree)
{
    if(tree)
    {
        inorder(tree->left);
        std::cout << tree->key << " ";
        inorder(tree->right);
    }
}

int main()
{
    node* tree = nullptr;
    RBnode test(5);
    wypisz(&test);
    std::cout << std::endl;
    insert_iterative(tree,3);
    insert_iterative(tree,4);
    insert_iterative(tree,5);
    insert_iterative(tree,1);
    wypisz(tree);
    std::cout << std::endl;
    wypisz(tree,1);
    std::cout << std::endl;
    wypisz(tree,2);
    std::cout << std::endl;
}
