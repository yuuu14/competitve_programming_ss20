#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cstring>
#include <fstream>
#include <numeric>
#include <chrono>
#define OR -1
#define AND -2
#define INPUT cin

using namespace std;

template<class T> inline void destroy(T*& p) { delete p; p = 0; }
struct Node {
    int key;
    bool isroot;
    Node* lc;
    Node* rc;
};
class Parser {
    Node* ast;
public:
    Parser() { ast = new Node; ast->isroot = true; }
    ~Parser() { delete_node(ast); }

    void simplify(string s) {
        parsing(ast, s);
    }

    void parsing(Node* root, string str) {
        if (is_num(str)) {
            //cout << str << endl;
            root->key = stoi(str);
            root->isroot = false;
            return;
        }

        string andor = str.substr(0, 1);
        root->key = andor == "*" ? AND : OR;
        //cout << "original str: " << str << endl;
        str = str.substr(2, str.size()-3); // remove andor '(' ')'
       
        //cout << "remove andor '(' ')': " << str << endl;
        
        long sub = 0, comma = 0; // sub = #'(' - #')' ;comma = #1st_level_','
        // if left subtree is AND0/OR1, no need to parse right subtree
        // if right subtree is AND0/OR1, delete left subtree
        // if one of the subtree is AND1/OR0, delete this and ...
        auto cptr = str.begin();
        for (; cptr != str.end() && comma == 0; ++cptr) {
            if (*cptr == '(') sub++;
            else if (*cptr == ')') sub--;
            else if (*cptr == ',' && sub == 0) comma++;
        }
        //cout << "#comma: " << comma << endl;
        if (comma == 0) {
            root->isroot = true;
            parsing(root, str);
            return;
        }
        root->lc = new Node;
        root->lc->isroot = true;
        //cout << "left subtree: " << string(str.begin(), cptr-1) << endl;
        parsing(root->lc, string(str.begin(), cptr-1));
        
        if ((root->key == AND && root->lc->key == 0) || (root->key == OR && root->lc->key == 1)) {
            root->key = root->lc->key;
            root->isroot = false;
            delete_node(root->lc);
            return;
        }
        root->rc = new Node;
        
        str = andor + "(" + string(cptr, str.end()) + ")";
        root->rc->key = root->key;
        root->rc->isroot = false;
        parsing(root->rc, str);
        if ((root->key == AND && root->rc->key == 0) || (root->key == OR && root->rc->key == 1)) {
            root->key = root->rc->key;
            root->isroot = false;
            delete_node(root->lc);
            delete_node(root->rc);
            return;
        }
        if ((root->key == AND && root->lc->key == 1) || (root->key == OR && root->lc->key == 0)) {
            root->key = root->rc->key;
            delete_node(root->lc);
            root->lc = root->rc->lc;
            Node* tmp = root->rc->rc;
            root->rc->lc = nullptr;
            root->rc->rc = nullptr;
            delete_node(root->rc);
            root->rc = tmp;
        }
        else if ((root->key == AND && root->rc->key == 1) || (root->key == OR && root->rc->key == 0)) {
            root->key = root->lc->key;
            delete_node(root->rc);
            root->rc = root->lc->rc;
            Node* tmp = root->lc->lc;
            root->lc->lc = nullptr;
            root->rc->rc = nullptr;
            delete_node(root->lc);
            root->lc = tmp;
        }
    }

    void print_ast() { printing(ast); }

    void printing(Node* node) {
        if (node->key >= 0) { cout << node->key; return; }
        if (node->isroot) cout << (node->key == AND ? "*(" : "+(");
        printing(node->lc);
        cout << ',';
        printing(node->rc);
        if (node->isroot) cout << ')';
        return;
    }

    void delete_node(Node*& stree) {
        if (stree->lc) delete_node(stree->lc);
        if (stree->rc) delete_node(stree->rc);
        destroy<Node>(stree);
        return;
    }
    
    bool is_num(string s) {
        for (unsigned int i = 0; i < s.size(); ++i)
            if (!isdigit(s[i])) return false;
        return true;
    }
};

int main() {
    fstream file("1.in");

    string s;
    getline(INPUT, s);
    Parser parser;
    parser.simplify(s);
    parser.print_ast();

    return 0;
    
}

