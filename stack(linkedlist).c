//use ll when u dont know the size of satck
//begining is called top
//for push and pop(delete) node inserted at begining bcz time complexity is 0(1) so 
//if we take last time complexity is 0(n)
//stack overflow occurs when there is no space left to allocate memory
//stack underflow when top=NULL 

#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int data;
    struct node *link;
}node;
node *top=NULL;
void push(int d){
    node *newnode=malloc(sizeof(node));
    if(newnode==NULL){
        printf("stack overflow");
        exit(1);
    }
    newnode->data=d;
    newnode->link=top;
    top=newnode;
}
int pop(){
    node *temp=top;
    if(top==NULL){
        printf("stack is empty\n");
        exit(1);
    }
    int data;
    data=temp->data;
    top=temp->link;
    free(temp);
    temp=NULL;
    return data;
}
int peek(){
    if(top==NULL){
        printf("the stack is underflow");
        exit(1);
    }
    int d=top->data;
    return d;
}
void view(){
    if(top==NULL){
        printf("stack is underflow\n");
        return;
    }
    node *temp=top;
    while(temp!=NULL){
        printf("%d\t",temp->data);
        temp=temp->link;
    }
    printf("\n");
}
int main(){
    int c,d;
    printf("1:push\n2:pop\n3:peek\n4:view\n5:exit\n");
    while(1){
        printf("eneter u r choice>>");
        scanf("%d",&c);
        switch(c)
        {
            case 1:
                    printf("enter the element>>");
                    scanf("%d",&d);
                    push(d);
                    break;
            case 2:
                    printf("the popped element>>%d\n",pop());
                    break;
            case 3:
                 printf("the top element>>%d\n",peek());
                  break;
            case 4:
                   view();
                   break;
            case 5:
                   exit(1);
            default:
                   printf("invalid choice");
            
        }
    }
}
