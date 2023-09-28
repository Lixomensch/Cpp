template <class trem>
class Node {
public:
    trem Dados;
    Node<trem>* Next;

    static Node<trem>* MontaNode(trem T) {
        Node<trem>* P = new Node<trem>;
        if (P) {
            P->Dados = T;
            P->Next = nullptr;
        }
        return P;
    }

    static void DesmontaNode(Node<trem>* p) {
        delete p;
    }
};

template <class trem>
class ListSE {
private:
    Node<trem>* Head;
    Node<trem>* It;
    int N;

public:
    ListSE() {
        Head = It = nullptr;
        N = 0;
    }

    bool InsertNext(trem T) {
        Node<trem>* P = Node<trem>::MontaNode(T);
        if (!P) {
            return false;
        }
        if (!Head) {
            Head = It = P;
        }
        else {
            P->Next = It->Next;
            It->Next = P;
            It = P;
        }
        N++;
        return true;
    }

    void Erase() {
        if (It) {
            if (It == Head) {
                Head = Head->Next;
            }
            else {
                Node<trem>* P = Head;
                while (P->Next != It) {
                    P = P->Next;
                }
                P->Next = It->Next;
            }
            Node<trem>::DesmontaNode(It);
            It = nullptr;
            N--;
        }
    }

    trem ItRet() {
        trem T;
        if (It)T = It->D;;
        return T;
    };

    int Size() {
        return N;
    }

    bool Empty() {
        return N == 0;
    }

    void Begin() {
        It = Head;
    }

    bool busca(trem x) {
        Begin();
        if (It->D == x) {
            return true;
        }
        It = It->Next;
        while (It != Head && It->D != x) {
            It = It->Next;
        }
        if (It != Head) {
            return true;
        }
        return false;
    }

    void Clear() {
        while (Head) {
            Node<trem>* P = Head;
            Head = Head->Next;
            delete P;
        }
        N = 0;
        It = nullptr;
    }


    ~ListSE() {
        while (Head) {
            Node<trem>* P = Head;
            Head = Head->Next;
            delete P;
        }
    }
};
