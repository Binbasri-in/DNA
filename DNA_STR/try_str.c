#include<stdio.h>
#include <string.h>
#include <math.h>

#define stacksize 50



void push(int  item,int *top,int s[])
{
    if(*top==stacksize-1)
    {
        printf("overflow");
        return;
    }
    *top=*top+1;
    s[*top]=item;
}

int pop(int *top,int s[])
{
    int  item;
    if(*top==-1)
    {
        return -1;
    }
    
    item=s[*top];
    *top=*top-1;
    return item;
}

int evaluate(char suffix[])
{
    int i,op1,op2,op,s[stacksize],res,n,top;
    char symbol;
    top=-1;
    n=strlen(suffix);
    for(i=0;i<n;i++)
    {
        symbol=suffix[i];
        switch(symbol)
        {
            case'+': op2=pop(&top,s);
                     op1=pop(&top,s);
                     res=op2+op1;
                     push(res,&top,s);
                     break;
            case'-': op2=pop(&top,s);
                     op1=pop(&top,s);
                     res=op1-op2;
                     push(res,&top,s);
                     break;
                     
             case'*': op2=pop(&top,s);
                     op1=pop(&top,s);
                     res=op2*op1;
                     push(res,&top,s);
                     break;
                     
             case'/': op2=pop(&top,s);
                     op1=pop(&top,s);
                     res=op2/op1;
                     push(res,&top,s);
                     break;
            case'%': op2=pop(&top,s);
                     op1=pop(&top,s);
                     res=op2%op1;
                     push(res,&top,s);
                     break;
            case '$':         
             case'^': op2=pop(&top,s);
                     op1=pop(&top,s);
                     res=(int)pow((double)op1,(double)op2);
                     push(res,&top,s);
                     break;
                     
            default: push(symbol-'0',&top,s);
        }
    }
    return(pop(&top,s));
}

void main()
{
    int res;
    char suffix[70];
    printf("enter the suffix expression");
    scanf("%s",suffix);
    res=evaluate(suffix);
    printf("the value of the suffix exp is %d",res);
}