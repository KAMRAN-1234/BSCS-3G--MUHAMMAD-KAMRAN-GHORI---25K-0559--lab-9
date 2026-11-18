#include<bits/stdc++.h>
using namespace std;

struct Node {
    int v, h=1;
    Node*l=0,*r=0;
    Node(int x):v(x) {}
};

int height(Node*t) {

        return t?t->h:0;
}

int getBalance(Node*t) {

    return t?height(t->l)-height(t->r):0;
}

void update(Node*t) {

    t->h=1+max(height(t->l), height(t->r));
}

Node*rightRotate(Node*y) {
    Node*x=y->l;
    y->l=x->r;
    
    x->r=y;
    update(y);
    
update(x);

    return x;
}

Node*leftRotate(Node*x) {
    Node*y=x->r;
    x->r=y->l;
    
    y->l=x;
        update(x);
    update(y);
    
    return y;
}

Node*insert(Node*t, int x) {
    if (!t) return new Node(x);
    
    if (x<t->v) t->l=insert(t->l, x);
    
     else if (x>t->v) t->r=insert(t->r, x);
    
    else return t;
    update(t);
     int b=getBalance(t);
    
     if (b>1&&x<t->l->v) {
        cout<<"Left-Left case at "<<t->v<<", right rotation"<<endl;
         return rightRotate(t);
    }

    if (b<-1&&x>t->r->v) {
        cout<<"Right-Right case at "<<t->v<<", left rotation"<<endl;
                return leftRotate(t);
    }

    return t;
}

void preorder(Node*t) {
    if (!t) return;
 cout<<t->v<<" ";
     preorder(t->l);
    
     preorder(t->r);
}

void test(vector<int>a) {
    Node*root=0;
    for (int x:a) root=insert(root, x);

         cout<<"Root: "<<root->v<<endl<<"Preorder: ";

    preorder(root);
    
    cout<<endl<<endl;
}

int main() {
    test({30, 35, 45});
    test({13, 10, 5});
}