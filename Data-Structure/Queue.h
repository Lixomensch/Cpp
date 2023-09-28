template<class trem>
class node {
public:
    trem dado;
    node<trem>* next;

    static node<trem>* montaNode(trem x) {
        node<trem>* p = new node<trem>;
        if (p) {
            p->dado = x;
            p->next = nullptr;  // Usando nullptr em vez de 0
        }
        return p;
    }

    static void desmontaNode(node<trem>* p) {
        delete p;
    }
};

template<class trem>
class queue {
private:
    node<trem>* head;
    node<trem>* tail;
    int n;

public:
    queue() {
        head = tail = nullptr;  // Usando nullptr em vez de 0
        n = 0;
    }

    ~queue() {
        while (head) {
            node<trem>* p = head;
            head = head->next;
            node<trem>::desmontaNode(p);
        }
    }

    int size() {
        return n;
    }

    bool empty() {
        return n == 0;
    }

    bool push(trem x) {
        node<trem>* p = node<trem>::montaNode(x);
        if (!p) return false;
        if (!head) {
            head = tail = p;
        }
        else {
            tail->next = p;
            tail = p;
        }
        n++;
        return true;
    }

    void pop() {
        if (head) {
            node<trem>* p = head;
            head = head->next;
            node<trem>::desmontaNode(p);
            n--;
            if (!head) tail = nullptr;  // Usando nullptr em vez de 0
        }
    }

    trem front() {
        return head->dado;
    }

    void clean() {
        while (head) {
            node<trem>* p = head;
            head = head->next;
            node<trem>::desmontaNode(p);
        }
        tail = nullptr;
        n = 0;
    }
};

