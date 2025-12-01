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
int isEmpty(){
    return(top==-1);
}
int pop(){
      if(isEmpty())
        {
            printf("the stack is empty\n");
            return 0;
         }
    int data=arr[top];
    top--;
    return data;
}
int main(){
    int n,c;
    printf("1:push  2:exit 3:pop ");
    while(1)
    {
        printf("choice>>");
        scanf("%d",&c);
        switch(c){
            
        case 1:
              {
                 if(isFull()){
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
            exit(0);   
             }
        case 3:{
          printf("%d\n",pop());  
          break;
        }
    }}
    printf("the stack elements are>>");
for(int i=top;i>=0;i--){
    printf("%d\t",arr[i]);
}
    
}
