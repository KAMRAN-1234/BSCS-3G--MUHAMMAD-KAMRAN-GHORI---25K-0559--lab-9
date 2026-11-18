#include<bits/stdc++.h>
using namespace std;

struct Node {
    int v;
    Node*l=0,*r=0;

    Node(int x):v(x) {}
};

struct ListNode {
    int v;

    ListNode*next=0;

    ListNode(int x):v(x) {}
};

Node*insertBST(Node*t, int x) {
    if (!t) return new Node(x);
    
    if (x<t->v) t->l=insertBST(t->l, x);
        else t->r=insertBST(t->r, x);

    return t;
}

void toList(Node*t, ListNode*&head, ListNode*&tail, int&n) {
    if (!t) return;
    
    toList(t->l, head, tail, n);
        ListNode*x=new ListNode(t->v);

    if (!head) head=tail=x;
    else {

        tail->next=x;
            tail=x;
    }
    n++;

        toList(t->r, head, tail, n);
}

Node*buildBalancedTree(ListNode*&head, int n) {
    if (n<=0) return 0;
    Node*left=buildBalancedTree(head, n/2);

     Node*root=new Node(head->v);


    head=head->next;

    root->l=left;
        root->r=buildBalancedTree(head, n-n/2-1);

    return root;
}

Node*balanceExistingBST(Node*root) {
    ListNode*head=0,*tail=0;
    int n=0;
         toList(root, head, tail, n);
    
return buildBalancedTree(head, n);
}

int height(Node*t) {

    return t?1+max(height(t->l), height(t->r)):-1;
}

void inorder(Node*t) {
    if (!t) return;
    inorder(t->l);

    cout<<t->v<<" ";
         inorder(t->r);
}

int main() {
    
    int a[]={10, 20, 30, 40, 50, 60, 70, 80, 90};
    Node*root=0;
    
    for (int x:a) root=insertBST(root, x);
    
    
    cout<<"Height before: "<<height(root)<<endl;
    cout<<"Inorder before: ";
    
    inorder(root);
      cout<<endl;
   
    root=balanceExistingBST(root);
     cout<<"Height after: "<<height(root)<<endl;
     cout<<"Inorder after: ";
inorder(root);

cout<<endl<<"Root after: "<<root->v<<endl;
}