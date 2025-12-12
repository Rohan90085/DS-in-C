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
    int val, choice;
    
    while(1){
        printf("1. Insert  2. Search  3. Inorder  4. Preorder  5. Postorder  6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice){
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                root = insert(root, val);
                break;
            case 2:
                printf("Enter value to search: ");
                scanf("%d", &val);
                printf(search(root, val) ? "Found\n" : "Not Found\n");
                break;
            case 3:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;
            case 4:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;
            case 5:
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;
            case 6:
                return 0;
        }
    }
    return 0;
}