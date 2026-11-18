#include<bits/stdc++.h>
using namespace std;

struct Node {
    int v, h=1;
    Node*l=0,*r=0;
    Node(int x):v(x) {}
};

struct QNode {
    Node*data;
    QNode*next=0;

    QNode(Node*x):data(x) {}
};

class Queue {
    QNode*front=0,*back=0;
    int size=0;
public:

    void push(Node*x) {
        QNode*n=new QNode(x);
        if (!back) front=back=n;
        
            else {
            back->next=n;

            back=n;
        }
        size++;
    }
    Node*pop() {
        QNode*n=front;
        Node*x=n->data;
            front=front->next;

        if (!front) back=0;
        delete n;

        size--;
    return x;
    }

    bool empty() {
        return size==0;
    }

    int count() {
        return size;
    }
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

Node*balance(Node*t) {
    update(t);
    int b=getBalance(t);
    if (b>1&&getBalance(t->l)>=0)   return rightRotate(t);
    
    if (b>1) {
        t->l=leftRotate(t->l);

         return rightRotate(t);
    }
   
    if (b<-1&&getBalance(t->r)<=0) return leftRotate(t);
   
    if (b<-1) {
        t->r=rightRotate(t->r);

        return leftRotate(t);
    }
    return t;
}

Node*insert(Node*t, int x) {
    if (!t) return new Node(x);
   
     if (x<t->v) t->l=insert(t->l, x);
   
    else if (x>t->v) t->r=insert(t->r, x);

    else return t;

        return balance(t);
}

Node*minNode(Node*t) {

    while (t->l) t=t->l;
    
        return t;
}

Node*deleteNode(Node*t, int x) {
    if (!t) return t;
   
    if (x<t->v) t->l=deleteNode(t->l, x);
   
    else if (x>t->v) t->r=deleteNode(t->r, x);
   
    else {
        if (!t->l||!t->r) {
            Node*c=t->l?t->l:t->r;
            delete t;
            return c;
        }
        Node*s=minNode(t->r);
        t->v=s->v;
        t->r=deleteNode(t->r, s->v);
    }
    
        return balance(t);
}

void printLevelOrder(Node*root) {
    if (!root) return;
    Queue q;
    q.push(root);
    int level=0;
        
        while (!q.empty()) {
        
            int n=q.count();
        cout<<"Level "<<level++<<":";
         while (n--) {
            Node*t=q.pop();
        
            cout<<" "<<t->v<<"(bf "<<getBalance(t)<<")";
        
            if (t->l) q.push(t->l);
                    if (t->r) q.push(t->r);
        }
        cout<<endl;
    }
}

bool isAVL(Node*t) {
    if (!t) return 1;
     int d=height(t->l)-height(t->r);
    
 return abs(d)<=1&&isAVL(t->l)&&isAVL(t->r);
}

int main() {
    int a[]={10, 20, 30, 40, 50};
        Node*root=0;
   
         for (int x:a) root=insert(root, x);
    
         cout<<"After 5 insertions"<<endl;
    
         printLevelOrder(root);
    
     root=deleteNode(root, 10);
    cout<<endl<<"After deleting 10"<<endl;

    printLevelOrder(root);
        root=deleteNode(root, 20);
    
            cout<<endl<<"After deleting 20"<<endl;
    printLevelOrder(root);
    
    cout<<endl<<"Height difference of every node is at most 1: "<<(isAVL(root)?"Yes":"No")<<endl;
}