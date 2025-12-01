// stack is linear data sructure which follows lifo principle where every new element at one end called top and removed from there



#include<stdio.h>
#include<stdlib.h>
#define max 3
int arr[max];
int top=-1;
int isFull(){
    return(top==max-1);
}
void push(int data){
    if(isFull()){
        printf("\nstack overfull");
        return;
    }
    top++;
    arr[top]=data;

}
int main(){
    int n,c;
    printf("1:push  2:exit");
    while(1){
        printf("choice>>");
        scanf("%d",&c);
        if(c==2){
        break;
    }
    printf("eneter the eelement");
    scanf("%d",&n);
    push(n);
    }
    
for(int i=top;i>=0;i--){
    printf("%d",arr[i]);
}
    
}
