//simple insertion and binary search implementation in C
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct node{
    int d;
    struct node *left,*right;
    
}node;
node *getn(int d){
    node *newn=malloc(sizeof(node));
    newn->d=d;
    newn->left=newn->right=NULL;
    return newn;
}
node *insert(node *root,int d){
    if (root==NULL){
        root=getn(d);
    }
    else if(d<root->d){
        root->left=insert(root->left,d);
    }
    else 
    root->right=insert(root->right,d);
    return root;
}
bool search(node *root,int d){
    if(root==NULL)
    return 0;
    else if(d==root->d) return 1;
    else if(d<root->d) return search(root->left,d);
    else return search(root->right,d);
}
int main(){
    node *root=NULL;
    root=insert(root,50);
    root=insert(root,45);
    root=insert(root,58);
    root=insert(root,33);
    root=insert(root,99);
    if(search(root,100))
    printf("got");
    else 
    printf("no");
}