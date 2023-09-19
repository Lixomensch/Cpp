#include <iostream>
#include <vector>
#define INT_MAX 0x7fffffff

using namespace std;
struct HashNode {
    int key;
    int value;
    HashNode(int k, int v) : key(k), value(v) {}
};

class HashMap {
private:
    vector<HashNode*> table;
    int TABLE_SIZE;

    int Function1(int key) {
        return (key & INT_MAX) % TABLE_SIZE;
    }

    int Function2(int key) {
        return 1 + (key % (TABLE_SIZE - 1));
    }

public:
    HashMap() {
        TABLE_SIZE = 10;
        table.resize(TABLE_SIZE, nullptr);
    }

    void insert(int key, int value) {
        int index = Function1(key);
        int step = Function2(key);

        while (table[index] != nullptr) {
            index = (index + step) % TABLE_SIZE;
        }

        table[index] = new HashNode(key, value);
    }

    int get(int key) {
        int index = Function1(key);
        int step = Function2(key);

        while (table[index] != nullptr) {
            if (table[index]->key == key) {
                return table[index]->value;
            }
            index = (index + step) % TABLE_SIZE;
        }

        return -1;
    }

    void remove(int key) {
        int index = Function1(key);
        int step = Function2(key);

        while (table[index] != nullptr) {
            if (table[index]->key == key) {
                delete table[index];
                table[index] = nullptr;
                return;
            }
            index = (index + step) % TABLE_SIZE;
        }
    }

    ~HashMap() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i] != nullptr) {
                delete table[i];
            }
        }
    }
};
