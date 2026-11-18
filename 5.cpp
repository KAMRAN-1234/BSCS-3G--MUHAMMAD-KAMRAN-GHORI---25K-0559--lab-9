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
   

    if (b>1&&x<t->l->v) return rightRotate(t);
   
            
        if (b<-1&&x>t->r->v) return leftRotate(t);
   
    if (b>1&&x>t->l->v) {
        t->l=leftRotate(t->l);

        return rightRotate(t);
    }
   
        if (b<-1&&x<t->r->v) {
        t->r=rightRotate(t->r);
        return leftRotate(t);
    }
    return t;
}

Node*minNode(Node*t) {
    while (t->l) t=t->l;
    return t;
}

Node*deleteNode(Node*root, int x) {
    if (!root) return root;
    if (x<root->v) root->l=deleteNode(root->l, x);
    else if (x>root->v) root->r=deleteNode(root->r, x);
    else {
        if (!root->l||!root->r) {
            Node*c=root->l?root->l:root->r;
            delete root;
            return c;
        }
        Node*s=minNode(root->r);
        root->v=s->v;
        root->r=deleteNode(root->r, s->v);
    }
    update(root);
    int b=getBalance(root);
    if (b>1&&getBalance(root->l)>=0) {
        cout<<"LL case at "<<root->v<<endl;
        return rightRotate(root);
    }
    if (b>1&&getBalance(root->l)<0) {
        cout<<"LR case at "<<root->v<<endl;
        root->l=leftRotate(root->l);
        return rightRotate(root);
    }
    if (b<-1&&getBalance(root->r)<=0) {
        cout<<"RR case at "<<root->v<<endl;
        return leftRotate(root);
    }
    if (b<-1&&getBalance(root->r)>0) {
        cout<<"RL case at "<<root->v<<endl;
        root->r=rightRotate(root->r);
        return leftRotate(root);
    }
    return root;
}

void preorder(Node*t) {
    if (!t) return;
    cout<<t->v<<" ";
    preorder(t->l);
    preorder(t->r);
}

void demo(vector<int>a, int x) {
    Node*root=0;
    for (int v:a) root=insert(root, v);
    cout<<"Before: ";
    preorder(root);
    cout<<endl<<"Delete "<<x<<endl;
    root=deleteNode(root, x);
    cout<<"After: ";
    preorder(root);
    cout<<endl<<endl;
}

int main() {
    demo({30, 20, 40, 10}, 40);
    demo({30, 10, 40, 20}, 40);
    demo({20, 10, 30, 40}, 10);
    demo({20, 10, 30, 25}, 10);
}