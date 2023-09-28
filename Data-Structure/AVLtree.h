#include <iostream>
using namespace std;


template <class trem>
class nodeT {
public:
    trem d; //item do node
    nodeT<trem>* right; //direita
    nodeT<trem>* left; //esquerda
    int fb; //fator de balanceamento

    static trem desmontanodeT(nodeT<trem>* x)
    {
        trem aux;
        if (x)
        {
            aux = x->d;
            delete x;
        }
        return aux;
    }

    static nodeT* montanodeT(trem x)
    {
        nodeT<trem>* p = new nodeT;
        if (p)
        {
            p->d = x; //node criado recebe o item
        }
        p->right = p->left = 0; //direita e esquerda sempre null
        return p;
    }
};

template <class trem>
class AvlTree {
private:
    nodeT<trem>* root;
    int n;

    nodeT<trem>* RMin(nodeT<trem>* R) {//busca minimo

        if (!R)
        {
            return 0;
        }
        if (!(R->left))
        {
            return R;
        }
        return RMin(R->left);
    }

    nodeT<trem>* Rsearch(nodeT<trem>* R, trem x) { //busca um item e caso encontre retorna o node

        if (!R)
        {
            return 0;
        }

        if (x < R->d) {//é menor vai para a esquerda
            return Rsearch(R->left, x);
        }
        if (x > R->d) {//é maior vai para a direita
            return Rsearch(R->right, x);
        }
        //achou!
        return R;
    }

    void RSD(nodeT<trem>** R) //rotação simples a direita
    {
        nodeT<trem>* a = *R;
        nodeT<trem>* b = a->left;
        //trocas
        a->left = b->right;
        b->right = a;
        *R = b;
        //arrumar fator de balanceamento
        if (b->fb == -1)
        {
            a->fb = b->fb = 0;
        }
        else // b->fb == 0
        {
            a->fb = -1;
            b->fb = +1;
        }
    }

    void RSE(nodeT<trem>** R) {//rotação simples a esquerda

        nodeT<trem>* a = *R;
        nodeT<trem>* b = a->right;
        //trocas
        a->right = b->left;
        b->left = a;
        *R = b;
        //arrumar fator de balanceamento
        if (b->fb == +1)
        {
            a->fb = b->fb = 0;
        }
        else // b->fb == 0
        {
            a->fb = +1;
            b->fb = -1;
        }
    }

    void RDD(nodeT<trem>** R) {//rotação dupla a direita
        nodeT<trem>* a = *R;
        nodeT<trem>* b = a->left;
        nodeT<trem>* c = b->right;
        //troca
        b->right = c->left;
        a->left = c->right;
        c->right = a;
        c->left = b;
        *R = c;
        if (c->fb == -1)
        {
            c->fb = b->fb = 0;
            a->fb = +1;
        }
        else
        {
            if (c->fb == +1)
            {
                c->fb = a->fb = 0;
                b->fb = -1;
            }
            else
            {//c->fb ==0
                a->fb = b->fb = c->fb = 0;
            }
        }
    }

    void RDE(nodeT<trem>** R) {//rotação dupla a esquerda

        nodeT<trem>* a = *R;
        nodeT<trem>* b = a->right;
        nodeT<trem>* c = b->left;
        //troca
        b->left = c->right;
        a->right = c->left;
        c->left = a;
        c->right = b;
        *R = c;
        if (c->fb == +1)
        {
            c->fb = b->fb = 0;
            a->fb = -1;
        }
        else
        {
            if (c->fb == -1)
            {
                c->fb = a->fb = 0;
                b->fb = +1;
            }
            else
            {//c->fb ==0
                a->fb = b->fb = c->fb = 0;
            }
        }
    }

    bool insert(nodeT<trem>** R, nodeT<trem>* aux)
    {
        if (!(*R))
        {//nao existe igual entao insere
            *R = aux;
            aux->fb = 0;
            n++;
            return true;
        }

        if ((*R)->d == aux->d)
        {//achou igual
            nodeT<trem>::desmontanodeT(aux);
            return false;
        }

        if (aux->d < ((*R)->d))
        {//insere esquerda
            if (insert(&((*R)->left), aux))
            {//aumentou esquerda
                if ((*R)->fb - 1 == -2)
                {//fb desbalanceou
                    if (((*R)->left)->fb == -1)
                    {//rotação simples direita
                        RSD(R);
                    }
                    else
                    {//rotação dupla direita
                        RDD(R);
                    }
                    return false; //na inserção apos o balanceamento sempre retorna false;
                }
                (*R)->fb += -1;
                return (*R)->fb; //caso seja 0, ou seja, +1 -> 0 deve retorna false e 0 -> -1 retorna true;

            }
            return false;
        }

        //vai para a direita
        if (insert(&((*R)->right), aux))
        {//aumentou direita
            if ((*R)->fb + 1 == 2)
            {//fb desbalanceou
                if (((*R)->right)->fb == 1)
                {//rotação simples esquerda
                    RSE(R);
                }
                else
                {//rotação dupla esquerda
                    RDE(R);
                }
                return false; //na inserção apos o balanceamento sempre retorna false;
            }
            (*R)->fb += 1;
            return (*R)->fb;//caso seja 0, ou seja, -1 -> 0 deve retorna false e 0 -> +1 retorna true;
        }
        return false;
    }

    void swap(trem* x, trem* y) {
        trem aux;
        aux = *x;
        *x = *y;
        *y = aux;
    }

    bool erase(nodeT<trem>** R, trem x, nodeT<trem>** aux) {
        if (!(*R))
        {
            return false;
        }

        if (x < ((*R)->d))
        {//vai para a esquerda
            if (erase(&((*R)->left), x, aux))
            {//exclui e reduz a esquerda
                if ((*R)->fb <= 0)
                {//nao desbalanceou
                    (*R)->fb += 1;
                    return !((*R)->fb); //seguindo a regra fb == -1 -> 0 retorna true ou fb == 0 -> +1 retorna false
                }
                //desbalanceou
                if (((*R)->right)->fb == 1)
                {
                    RSE(R);
                    return true;
                }
                //((*R)->right)->fb==-1
                RDE(R);
                return true;
            }
            //foi la excluiu a esquerda mas nao reduziu
            return false;
        }
        if (x > ((*R)->d))
        {//vai para a direita
            if (erase(&((*R)->right), x, aux))
            {//exclui e reduz a esquerda
                if ((*R)->fb >= 0)
                {//nao desbalanceou
                    (*R)->fb += -1;
                    return !((*R)->fb); //seguindo a regra fb == +1 -> 0 retorna true ou fb == 0 -> +1 retorna false
                }
                //desbalanceou
                if (((*R)->left)->fb == -1)
                {
                    RSD(R);
                    return true;
                }
                //((*R)->left)->fb==-1
                RDD(R);
                return true;
            }
            //foi la excluiu a direta mas nao reduziu
            return false;
        }
        if (!(*R)->left)
        {
            *aux = *R;
            *R = (*R)->right;
            return true;
        }

        if (!(*R)->right)
        {
            *aux = (*R);
            *R = (*R)->left;
            return true;
        }

        nodeT<trem>* m = RMin((*R)->right);
        swap(&(m->d), &((*R)->d));
        return erase(&(*R)->right, x, aux);
    }

   void preorder(nodeT<trem>* p, int cont, string& res)
    {

        if (p)
        {
            res += std::to_string(p->d) + ",";
            preorder(p->left, cont++, res);
            preorder(p->right, cont++, res);
        }
    }

public:

    int size()
    {
        return n;
    }

    bool empty()
    {
        return !n;
    }

    AvlTree()
    {
        n = 0;
        root = 0;
    }

    trem min() {//por padrão minimo da arvore
        trem x;
        nodeT<trem>* p = RMin(root);
        return (p ? p->d : x);
    }

    bool search(trem x)
    {
        return Rsearch(root, x) != nullptr;
    }


    bool insert(trem x)
    {
        nodeT<trem>* p = nodeT<trem>::montanodeT(x);
        int aux = n;
        insert(&root, p);
        if (!p)
        {
            return false;
        }
        return n - aux; // verifica se aumentou caso tenha inserido n vai ser maior que o aux (antigo n) sendo assim a subtração ficara 1 (true)
    }

    trem erase(trem x)
    {
        nodeT<trem>* p;
        erase(&root, x, &p);
        nodeT<trem> lixo = *p;

        if (p)
        {
            n--;
            return nodeT<trem>::desmontanodeT(p);
        }

        return lixo.d;
    }

    string preorder() {
        string res;
        preorder(root, 0, res);
        return res;
    }

};