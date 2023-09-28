template<class trem>
class node {
public:
    trem dado;
    node<trem>* next;
    static node* montaNode(trem x) {
        node<trem>* p = new node<trem>;
        if (p) {
            p->dado = x;
            p->next = 0;
        }
        return p;
    }
};

template<class trem>
class stack {
private:
    node<trem>* top;
    int n;

public:
    stack() {
        top = 0;
        n = 0;
    }

    ~stack() {
        while (top) {
            node<trem>* p = top;
            top = top->next;
            delete p;
        }
    }

    bool empty() {
        return !n;
    }

    int size() {
        return n;
    }

    bool push(trem x) {
        node<trem>* p = node<trem>::montaNode(x);
        if (!p)return false;
        p->next = top;
        top = p;
        n++;
        return true;
    }

    bool pop() {
        if (!n) {
            return false;
        }
        node<trem>* p = top;
        top = top->next;
        delete p;
        n--;
        return true;
    }

    trem returnTop() {
        trem p;
        if (!n) {
            p = top->dado;
        }
        return p;
    }

    void clean() {
        while (top) {
            node<trem>* p = top;
            top = top->next;
            delete p;
        }
    }
};