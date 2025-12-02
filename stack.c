#include<stdio.h>
#include<stdlib.h>
#define max 3
int arr[max];
int top=-1;
int isFull(){
    return(top==max-1);
}
void push(int data){
    top++;
    arr[top]=data;
}
int isEmpty()
{
    return(top==-1);
}
int pop()
{
      if(isEmpty())
        {
            printf("the stack is empty\n");
            return 0;
         }
    int data=arr[top];
    top--;
    return data;
}
int peek(){
    if(isEmpty()){
        printf("the stack is underflow\n");
        exit(1);
    }
    return(arr[top]);
}
void print(){
     for(int i=top;i>=0;i--){
         printf("%d\t",arr[i]);
     }
     printf("\n");
}
int main()
{
    int n,c;
    printf("1:push\n2:see top element\n3:pop\n4:exit\n5:see all element\n");
    while(1)
    {
        printf("choice>>");
        scanf("%d",&c);
        switch(c){
            
        case 1:
              {
                  if(isFull(c)){
                 printf("stack overfull\n");
                 break;
                 }
                 else
                 {
                 printf("eneter the eelement>>");
                 scanf("%d",&n);
                 push(n);
                 }
        break;
           }
        case 2:{
             printf("the top element is>>%d\n",peek());
            break;
             }
        case 3:{
          printf("%d\n",pop());  
          break;
        }
        case 4:{
           exit(1);
           break;
        }
        case 5:{
         print();
         break;
        }
        default:
        printf("invalid choice\n");
        break;
    }
}
return 0;
}
