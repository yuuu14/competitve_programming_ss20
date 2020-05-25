#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cstring>
#include <fstream>
#include <numeric>
#include <chrono>
//#include <boost/algorithm/string/join.hpp>

#define INPUT file
#define ADD -1
#define MUL -2
#define ADD_ '+'
#define MUL_ '*'

using namespace std;

bool contain_0or1(string);
string simplify_(string);
bool is_num(string);

struct Node {
    short key;
    vector<Node *> child;
};

class Parser {
public:
    Node *ast = new Node;
    ~Parser() {
        free_node(ast);
    }
    /* create new node from subtree */
    Node* create_node(string subtree) {
        Node* tmp = new Node;
        parsing(subtree, tmp);
        return tmp;
    }

    void sizeof_tree() {
        cout << "size of ast: " << sizeof(ast) << endl;
    }

    void buill_ast(string to_parse) {
        parsing(to_parse, ast);
    }

    void print_ast() {
        printing(ast);
        cout << endl;
    }
    void printing(Node* node) {
        if (node->child.size() == 0) {
            cout << node->key;
            return;
        }
        if (node->key == ADD) cout << "+(";
        else cout << "*(";
        for (auto it = node->child.begin(); it+1 != node->child.end(); ++it) {
            printing(*it);
            cout << ","; //cout << "Result: ";
        }
        printing(node->child.back());
        
        cout << ")";
    }

    /* build ast tree, return and/or value or direct value of number */
    void parsing(string tree, Node* parent) {
        if (is_num(tree)) {
            parent->key = (long)stoi(tree);
        }
        switch (tree[0]) {
            case '+': parent->key = ADD; break;
            case '*': parent->key = MUL; break; 
        }
        long lpn = 0, rpn = 0; // num of left/right parenthesis
        string stree("");
        for (unsigned int i = 1; i < tree.size(); ++i) {
            if (tree[i] == '(') {
                lpn++;
                if (lpn-rpn != 1) stree += '(';
            }
            else if (tree[i] == ')') {
                rpn++;
                if (lpn-rpn <= 1) {
                    stree = lpn-rpn == 0? stree: stree + ')';
                    if (lpn-rpn == 0 && stree.empty()) break;
                    
                    parent->child.push_back(create_node(stree));
                    stree.erase();
                }
                else stree += ')';
            }
            else if (tree[i] == ',' && (lpn-rpn == 1)) {
                if (stree.empty()) continue;
                
                parent->child.push_back(create_node(stree));
                stree.erase();
            }
            else stree += tree[i];
        }
    }

    void free_node(Node* node) {
        /*while(node->child.size()) {
            free_node(node->child[0]);
        }*/
        vector<int> idx_delete;
        for (unsigned int i = 0; i < node->child.size(); ++i) idx_delete.push_back(i);
        for (auto it = idx_delete.rbegin(); it != idx_delete.rend(); ++it) {
            free_node(node->child[*it]);
            node->child.erase(node->child.begin() + *it);
        }
        delete node;
        return;
    }
    void free_child_by_index(Node* parent, vector<int> idx_delete) {
        for (auto it = idx_delete.rbegin(); it != idx_delete.rend(); ++it) {
            free_node(parent->child[*it]);
            parent->child.erase(parent->child.begin() + *it);
        }
    }

    void simplify() {
        simp(ast);
    }

    void simp(Node* node) {
        if (node->child.size() == 0) return;

        for (auto it = node->child.begin(); it != node->child.end(); ++it)
            simp(*it);

        if (node->child.size() >= 2) {
            unsigned int idx = 0;
            vector<int> idx_delete;
            for (; idx < node->child.size(); ++idx) {
                if ((node->key == ADD && node->child[idx]->key == 1) || (node->key == MUL && node->child[idx]->key == 0)) {
                    node->key = node->child[idx]->key;
                    //while (node->child.size()) free_node(node->child[0]);
                    vector<int> idx_delete_;
                    for (unsigned int i = 0; i < node->child.size(); ++i) idx_delete_.push_back(i);
                    free_child_by_index(node, idx_delete_);
                    //node->child.clear();
                    break;
                }
                if ((node->key == ADD && node->child[idx]->key == 0) || (node->key == MUL && node->child[idx]->key == 1))
                    if (node->child.size()-idx_delete.size() > 2) // keep at least 2 children nodes
                        idx_delete.push_back(idx);
            }
            // remove 0/1 by idx_delete
            free_child_by_index(node, idx_delete);
        }

        /* *or+(1or0, s) */
        if (node->child.size() >= 2) {
            int not0and1 = -1;
            if ((node->key == ADD && node->child[0]->key == 0) || (node->key == MUL && node->child[0]->key == 1)) 
                not0and1 = 1;
            else if ((node->key == ADD && node->child[1]->key == 0) || (node->key == MUL && node->child[1]->key == 1))
                not0and1 = 0;
            if (not0and1 != -1) {
                //while (node->child.size()) free_node(node->child[0]);
                //for (auto it = node->child.rbegin(); it != node->child.rend(); ++it) free_node(*it);
                //free_child(node);
                node->key = node->child[not0and1]->key;
                for (auto it = node->child[not0and1]->child.begin(); it != node->child[not0and1]->child.end(); ++it) {
                    node->child.push_back(*it);
                }
                vector<int> idx_delete = {0, 1};
                free_child_by_index(node, idx_delete);
            } 
        }   
    }    

    bool is_num(string s) {
        for (unsigned int i = 0; i < s.size(); ++i)
            if (!isdigit(s[i])) return false;
        return true;
    }
};

int main() {
    Parser myParser;
    ifstream file("3.in");

    string s;
    getline(INPUT, s);
    auto start = chrono::high_resolution_clock::now();
    cout << simplify_(s) << endl;

    //myParser.buill_ast(s);
    //myParser.simplify();
    //myParser.print_ast();
    //myParser.sizeof_tree();
    
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
    cout << "Time taken: " << duration.count() << " microseconds" << endl;
    
    
    return 0; 
}

bool contain_0or1(string s) {
     for (unsigned int i = 1; i < s.size()-1; ++i) {
         if ((s[i] == '0' || s[i] == '1') && !isdigit(s[i-1]) && !isdigit(s[i+1]))
            return true;
     }
     return false;
}

/* return string removed first level of 1 and 0*/
string simplify_(string tree) {
    //cout << "cur_tree:" << tree << endl;
    if (is_num(tree)) {return tree;}
    long lpn = 0, rpn = 0;
    vector<string> strees;
    string stree("");
    for (auto c = tree.begin()+1; c != tree.end(); ++c) {
        if (*c == '(') {
            lpn++;
            if (lpn-rpn != 1) stree += *c;
        }
        else if (*c == ')') {
            rpn++;
            if (lpn-rpn <= 1) {
                stree = lpn-rpn == 0 ? stree : stree + ')';
                if (lpn-rpn == 0 && stree.empty()) break;
                string stree_simplified = simplify_(stree);
                //cout << "stree_simplified: "<< stree_simplified << endl;
                strees.push_back(stree_simplified);
                stree.erase();
            }
            else stree += ')';
        }
        else if (*c == ',' && (lpn-rpn == 1)) {
            if (stree.empty()) continue; // important!!! if having multiple subtree
            string stree_simplified = simplify_(stree);
            //cout << "stree_simplified: "<< stree_simplified << endl;
            strees.push_back(stree_simplified);
            stree.erase();
        }
        else stree += *c;
    }
    /*for (auto stree : strees) {
        for (auto ele : stree) cout << ele;
        cout << endl;
    }*/

    // tree[0] - andor
    char andor = tree[0];
    for (auto it = strees.begin(); it != strees.end();) {
        if (is_num(*it)) {
            if ((andor == MUL_ && *it == "0") || (andor == ADD_ && *it == "1")) {
                //cout << "*0/+1:" <<(*it == "0" ? "0" : "1") << endl; 
                return *it == "0" ? "0" : "1";
            }
            else if (*it == "0" || *it == "1") {
                it = strees.erase(it);
                if (strees.size() == 1) {
                    //cout<< "res1: " <<strees[0] <<endl;
                    return strees[0];}
                
            }
            else ++it;
        }
        else ++it;
    }
    //cout << boost::algorithm::join(strees, ",") << endl;
    
    string res = andor == MUL_ ? "*(" : "+(";
    //cout << res << endl;
    for (unsigned i = 0; i < strees.size()-1; ++i) res += strees[i] + ",";
    res += strees[strees.size()-1] + ")";
    //cout << "res2: " << res << endl;
    return res;
}

bool is_num(string s) {
    for (unsigned int i = 0; i < s.size(); ++i)
        if (!isdigit(s[i])) return false;
    return true;
}

