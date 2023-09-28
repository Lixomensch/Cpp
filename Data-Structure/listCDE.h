template<class trem>
class Node {
public:
    trem Dados;
    Node<trem>* Next;
    Node<trem>* Prev;

    static Node<trem>* MontaNode(trem T) {
        Node<trem>* P = new Node<trem>;
        if (P) {
            P->Dados = T;
            P->Next = nullptr;
            P->Prev = nullptr;
        }
        return P;
    };
};



template <class trem>
class ListCDE {
private:
    Node<trem>* Head;
    Node<trem>* It;
    int N;

public:
    ListCDE() {
        Head = It = nullptr;
        N = 0;
    }

    bool InsertNext(trem T) {
        Node<trem>* P = Node<trem>::MontaNode(T);
        if (!P) {
            return false;
        }
        if (!It) {
            P->Prev = P->Next = Head = It = P;
        }
        else {
            P->Next = It->Next;
            P->Prev = It;
            It->Next = (P->Next)->Prev = P;
            It = P;
        }
        N++;
        return true;
    }

    bool InsertPrev(trem T) {
        Node<trem>* P = Node<trem>::MontaNode(T);
        if (!P) {
            return false;
        }
        if (!It) {
            P->Prev = P->Next = Head = It = P;
        }
        else {
            P->Prev = It->Prev;
            P->Next = It;
            It->Prev = (P->Prev)->Next = P;
            It = P;
            if (Head == P->Next) {
                Head = P;
            }
        }
        N++;
        return true;
    }

    void Erase() {
        if (It) {
            Node<trem>* P = It;
            if (It->Next == It) {
                Head = It = nullptr;
            }
            else {
                (It->Next)->Prev = It->Prev;
                (It->Prev)->Next = It->Next;
                It = It->Next;
                if (Head == P) {
                    Head = P->Next;
                }
            }
            delete P;
            N--;
        }
    }

    bool Itpp() {
        if (It) {
            It = It->Next;
            return true;
        }
        return false;
    }

    bool Itmm() {
        if (It) {
            It = It->Prev;
            return true;
        }
        return false;
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

    void End() {
        if (Head) {
            It = Head->Prev;
        }
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

    ~ListCDE() {
        while (Head) {
            Node<trem>* P = Head;
            Head = Head->Next;
            delete P;
        }
    }
};

