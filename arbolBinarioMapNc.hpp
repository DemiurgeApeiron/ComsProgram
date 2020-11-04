#ifndef _BST_HPP
#define _BST_HPP
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class BTreeNode {
   protected:
    map<string, int> val;
    BTreeNode *left;
    BTreeNode *right;

   public:
    ~BTreeNode(){};
    BTreeNode() = default;
    BTreeNode(map<string, int> _val) {
        this->val = _val;
        this->left = NULL;
        this->right = NULL;
    };
    BTreeNode(map<string, int> _val, BTreeNode *_left, BTreeNode *_right) {
        this->val = _val;
        this->left = _left;
        this->right = _right;
    };

    map<string, int> get_val() { return val; };
    BTreeNode *get_left() { return left; };
    BTreeNode *get_right() { return right; };
    void set_val(map<string, int> _val) { this->val = _val; };
    void set_left(BTreeNode *node) { left = node; };
    void set_right(BTreeNode *node) { right = node; };
};

class BinarySearchTree {
   protected:
    BTreeNode *root;

   public:
    ~BinarySearchTree() {}
    BinarySearchTree() { root = NULL; }

    BTreeNode *find(map<string, int> val) {
        BTreeNode *ptr = root;
        while (ptr != NULL) {
            if (ptr->get_val().begin()->first == val.begin()->first) {
                return ptr;
            }
            ptr = ptr->get_val().begin()->second > val.begin()->second ? ptr->get_left() : ptr->get_right();
        }
        return NULL;
    }

    bool insertNode(map<string, int> val) {
        BTreeNode *ptr = root;
        BTreeNode *pre = NULL;

        while (ptr != NULL) {
            if (ptr->get_val() == val) {
                return false;
            }
            pre = ptr;
            ptr = ptr->get_val() > val ? ptr->get_left() : ptr->get_right();
        }
        BTreeNode *newNode = new BTreeNode(val);
        if (pre == NULL) {
            root = newNode;
        } else {
            ptr->get_val() < val ? pre->set_right(newNode) : pre->set_left(newNode);
        }
        return true;
    }

    BTreeNode *insertNodeR(BTreeNode *node, map<string, int> val) {
        if (node == NULL) {
            return new BTreeNode(val);
        }
        if (val.begin()->second < node->get_val().begin()->second) {
            node->set_left(insertNodeR(node->get_left(), val));
        } else {
            node->set_right(insertNodeR(node->get_right(), val));
        }
        return node;
    }
    bool insertNodeRecursive(map<string, int> val) {
        root = insertNodeR(root, val);
        return true;
    };

    BTreeNode *sucessor(BTreeNode *node) {
        BTreeNode *ptr = node->get_right();
        while (ptr->get_left() != NULL) {
            ptr = ptr->get_left();
        }
        return ptr;
    };

    BTreeNode *delete_node(BTreeNode *node, int key) {
        // caso base
        if (node == NULL) return node;

        // si el valor a eliminar es menor que el valor del nodo
        // entonces está en el subarbol izquierdo
        if (key < node->get_val().begin()->second)
            node->set_left(delete_node(node->get_left(), key));

        // si el valor a eliminar es mayor que el valor del nodo
        // entonces está en el subarbol derecho
        else if (key > node->get_val().begin()->second)
            node->set_right(delete_node(node->get_right(), key));

        // si el valor a eliminar es igual que el valor del nodo
        // entonces este es el elemento que queremos eliminar
        else {
            // nodos con solo un hijo o sin hijos
            if (node->get_left() == NULL) {
                BTreeNode *temp = node->get_right();
                delete node;
                return temp;
            } else if (node->get_right() == NULL) {
                BTreeNode *temp = node->get_left();
                delete node;
                return temp;
            }

            // nodo con dos hijos, entonces obtener el sucesor
            BTreeNode *temp = sucessor(node);

            // copiar el valor del sucesor al nodo que contiene el elemento a borrar
            node->set_val(temp->get_val());

            // borrar el sucesor
            node->set_right(delete_node(node->get_right(), temp->get_val().begin()->second));
        }
        return node;
    };

    void delete_node(map<string, int> val) {
        root = delete_node(root, val.begin()->second);
    };

    void print_preorder(BTreeNode *node) {
        if (node != NULL) {
            cout << node->get_val().begin()->first << ", ";
            print_preorder(node->get_left());
            print_preorder(node->get_right());
        }
    };

    int heightR(int h, BTreeNode *node) {
        h += 1;
        if (node == NULL) {
            return h;
        } else {
            int hIzquierda = heightR(h, node->get_left());
            int hDerecha = heightR(h, node->get_right());
            return hIzquierda > hDerecha ? hIzquierda : hDerecha;
        }
    }

    int getHeight() {
        int h = 0;
        h = heightR(h, root);
        return h;
    }

    int getSHeight(BTreeNode *node) {
        int h = 0;
        h = heightR(h, node);
        return h;
    }

    int getProfundidad(map<string, int> val) {
        BTreeNode *ptr = find(val);
        int prof = getSHeight(root) - getSHeight(ptr);
        return prof;
    }

    void yellowPath(BTreeNode *node) {
        cout << node->get_val().begin()->first << ", ";
        int left;
        int right;
        if (node->get_left() != NULL) {
            left = getSHeight(node->get_left());
        } else {
            left = 0;
        }
        if (node->get_right() != NULL) {
            right = getSHeight(node->get_right());
        } else {
            right = 0;
        }
        if (node->get_left() != NULL || node->get_right() != NULL) {
            getSHeight(node->get_left()) > getSHeight(node->get_right()) ? yellowPath(node->get_left()) : yellowPath(node->get_right());
        }
        /*if (getSHeight(node->get_left()) > getSHeight(node->get_right())) {
            yellowPath(node->get_left())
        } else {
            
        }*/
    }
    void myChildren(BTreeNode *node) {
        if (node->get_left() != NULL) {
            cout << node->get_left()->get_val().begin()->first << ", ";
            myChildren(node->get_left());
        }
        if (node->get_right() != NULL) {
            cout << node->get_right()->get_val().begin()->first << ", ";
            myChildren(node->get_right());
        }
    }

    int getLevel(map<string, int> val) {
        return getProfundidad(val);
    }

    void getAllDecendats(map<string, int> val) {
        BTreeNode *ptr = find(val);
        myChildren(ptr);
    }

    void longPath() {
        yellowPath(root);
    }
    void print_preorder() {
        print_preorder(root);
        cout << endl;
    };

    void printSpacesV1() {
        for (size_t i = 0; i < 3; i++) {
            cout << " ";
        }
    }
    void printLines() {
        cout << "--";
    }

    void V1Print(int h, BTreeNode *node) {
        if (node != NULL && node->get_left() != NULL) {
            int hMe = h - getSHeight(node);
            for (size_t i = 0; i < hMe + 1; i++) {
                printSpacesV1();
                if (i < hMe) {
                    cout << "|";
                }
            }
            cout << "├";
            printLines();
            cout << node->get_left()->get_val().begin()->first << endl;
            V1Print(h, node->get_left());
            if (node->get_right() != NULL) {
                for (size_t i = 0; i <= hMe; i++) {
                    //cout << i << " " << hMe;
                    printSpacesV1();
                    if (i < hMe && hMe != 0) {
                        cout << "|";
                    } else if (i == hMe - 1) {
                        cout << " ";
                    }
                }
                cout << "└--" << node->get_right()->get_val().begin()->first << endl;
            } else {
                //cout << endl;
            }

            V1Print(h, node->get_right());

        } else if (node != NULL && node->get_right() != NULL) {
            int hMe = h - getSHeight(node);
            if (node->get_right() != NULL) {
                for (size_t i = 0; i <= hMe; i++) {
                    //cout << i << " " << hMe;
                    printSpacesV1();
                    if (i < hMe && hMe != 0) {
                        cout << "|";
                    } else if (i == hMe - 1) {
                        cout << " ";
                    }
                }
                cout << "└--" << node->get_right()->get_val().begin()->first << endl;
            } else {
                //cout << endl;
            }

            V1Print(h, node->get_right());
        }
    }

    void printV1() {
        int h = getHeight();
        cout << "└";
        cout << "-";
        cout << "-";
        cout << root->get_val().begin()->first << endl;

        V1Print(h, root);
    }

    void printSpacesV2(int factor) {
        for (size_t i = 0; i < factor; i++) {
            cout << " ";
        }
    }
    void printLinesV2(int factor) {
        for (size_t i = 0; i < factor; i++) {
            cout << "-";
        }
    }

    vector<vector<string>> getVals(BTreeNode *node, vector<vector<string>> &vals, string desicion) {
        if (node != NULL) {
            int h = getProfundidad(node->get_val());
            string left = "";
            string right = "";
            if (node->get_left() != NULL) {
                left = (node->get_left()->get_val().begin()->first);
            }
            if (node->get_right() != NULL) {
                right = (node->get_right()->get_val().begin()->first);
            }
            vector temp{desicion, to_string(h), left, right};
            vals.push_back(temp);
            getVals(node->get_left(), vals, "L");
            getVals(node->get_right(), vals, "R");
        }

        return (vals);
    }
    vector<vector<string>> detailedInfo() {
        vector<vector<string>> vals;
        return (getVals(root, vals, "L"));
    }
    void printArco(int factL, int factEsp, int numOfArcos) {
        if (numOfArcos == 1) {
            printSpacesV2(3);
        }
        for (size_t i = 0; i < numOfArcos; i++) {
            if (i == 0) {
                printSpacesV2(factEsp);
            }
            if (i % 2 != 0) {
                printSpacesV2(factEsp);
            }

            cout << "┌";
            printLinesV2(factL);
            cout << "┴";
            printLinesV2(factL);
            cout << "┐";
            printSpacesV2(getHeight());
        }
    }

    void printArcoVals(int factL, int factEsp, int numOfArcoVals, vector<vector<string>> vals, int h) {
        vector<vector<string>> ImportantVals;
        string searchingSide = "L";
        if (numOfArcoVals == 1) {
            printSpacesV2(3);
        }
        for (size_t i = 0; i < vals.size(); i++) {
            if (vals[i][1] == to_string(h)) {
                ImportantVals.push_back(vals[i]);
            }
        }
        for (size_t i = 0; i < numOfArcoVals; i++) {
            int index = 0;
            for (size_t j = 0; j < ImportantVals.size(); j++) {
                if (ImportantVals[j][0] == searchingSide) {
                    index = j;
                }
            }
            if (ImportantVals[index][0] == searchingSide) {
                printSpacesV2(factEsp);
                cout << ImportantVals[index][2];
                printSpacesV2(factEsp * 2);
                cout << ImportantVals[index][3];
            } else {
                printSpacesV2(factEsp);
                cout << "  ";
                printSpacesV2(factEsp * 2);
                cout << "  ";
            }
            if (i % 2 == 0) {
                printSpacesV2(numOfArcoVals + 3);
            }

            if (!ImportantVals.empty()) {
                ImportantVals.erase(ImportantVals.begin() + index);
            }
            if (searchingSide == "L") {
                searchingSide = "R";
            } else {
                searchingSide = "L";
            }
        }
    }

    void printV2() {
        int h = getSHeight(root);
        int deep = getProfundidad(root->get_val());
        int factorEsp = h * h;
        int factorLinea = h * h;
        vector<vector<string>> vals;

        if (h > 1) {
            cout << endl;
            printSpacesV2(factorEsp * 2 + 3);
            cout << root->get_val().begin()->first << endl;

            getVals(root, vals, "L");

            int factorDeCresimiento = 1;

            for (size_t i = 1; i < h; i++) {
                printArco(factorEsp, factorLinea, factorDeCresimiento);
                cout << endl;
                printArcoVals(factorEsp, factorLinea, factorDeCresimiento, vals, i - 1);
                cout << endl;
                factorEsp = (h - i) * (h - i);
                factorLinea = (h - i) * (h - i);
                factorDeCresimiento *= 2;
            }
        }
    }

    bool rTopNvalues(int num, BTreeNode *ptr, vector<string> &vect, bool &ret) {
        if (ret == false) {
            if (ptr != NULL) {
                if (ptr->get_right() != NULL) {
                    ptr = ptr->get_right();
                    rTopNvalues(num, ptr, vect, ret);
                }
            }
            ret = true;
        }
        if (ret == true) {
            if (vect.size() < num) {
                if (vect.back() != ptr->get_val().begin()->first) {
                    vect.push_back(ptr->get_val().begin()->first);
                }
                if (ptr != NULL && ptr->get_left() != NULL) {
                    ptr = ptr->get_left();
                    ret = false;
                    rTopNvalues(num, ptr, vect, ret);
                    if (std::find(vect.begin(), vect.end(), ptr->get_val().begin()->first) == vect.end()) {
                        vect.push_back(ptr->get_val().begin()->first);
                    }
                }
            }
        }
        return (ret);
    }

    void getTopNvalues(int num, vector<string> &vect) {
        bool ret;
        rTopNvalues(num, root, vect, ret);
    }
};

#endif