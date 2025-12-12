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
void inorder(node *root){
    if(root==NULL) return ;
    inorder(root->left);
    printf("%d\t",root->d);
    inorder(root->right);
}
void postorder(node *root){
    if(root==NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d\t",root->d);
    
}
void preorder(node *root){
    if(root==NULL) return;
    printf("%d\t",root->d);
    preorder(root->left);
    preorder(root->right);
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
    printf("\n");
    inorder(root);
    printf("\n");
    preorder(root);
    printf("\n");
    postorder(root);
}