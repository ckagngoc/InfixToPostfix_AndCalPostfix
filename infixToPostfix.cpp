#include <stdio.h>
#include <conio.h>
#include <string.h>
#define MAX 1000
typedef float DataType;

struct Node{
    DataType data;
    Node* next;
};
typedef Node* point;

void push(point* first,DataType value);
DataType pop(point* first);
DataType peek(point* first);
void output(point first);
int pre(char x);
void infixToPostfix(char infix[],char postfix[]);
float caculatePostfix(char postfix[]);
int Kiem_tra(char c[])
{
	int m = 0,n = 0,k = strlen(c);
	for(int i = 0; i < k; i++)
	{
		if(c[i] == 40) m++;
		if(c[i] == 41) n++;
		if(n>m) break;
		
	}
	if (m == n) return 1;
	else return 0;
}


int main(){
    FILE *f1,*f2;
    f1 = fopen("input.txt","r");
    f2 = fopen("output.txt","w");
    char a[MAX];
    char b[MAX];
    fprintf(f2,"\n_____________PHAM DUC MINH______________\n");
    fprintf(f2,"\n___________________________\n");
    while(fgets(a,MAX,f1) != NULL){
        fprintf(f2,"Infix: ");
        fputs(a,f2);
        if(Kiem_tra(a) == 1){
            fprintf(f2,"\nChuoi hop le \n");
            infixToPostfix(a,b);
            fprintf(f2,"\nPostfix: ");
            fputs(b,f2);
            fprintf(f2,"\nKet qua: ");
            fprintf(f2,"%f",caculatePostfix(b));
            fprintf(f2,"\n___________________________\n");
        } else{
            fprintf(f2,"\nChuoi khong hop le \n");
            fprintf(f2,"\n___________________________\n");
        }
    }
    fclose(f1);
    fclose(f2);
    return 0;
}

void push(point* first,DataType value){
    point t;
    t = new(Node);
    t->data = value;
    t->next = *first;
    *first = t;
}

DataType pop(point* first){
    DataType value;
    value = (*first)->data;
    *first = (*first)->next;
    return value;
}

DataType peek(point* first){
    return (*first)->data;
}

void output(point first){
    point t1 = first;
    printf("\ndata\tpoint");
    while(t1!=NULL){
        printf("\n%c\t%d",t1->data,t1->next);
        t1 = t1->next;
    }
}

int pre(char x){
    if(x=='$') return 0;
    if(x=='(') return 1;
    if(x=='+'||x=='-') return 2;
    if(x=='*'||x=='/') return 3;
    if(x==')') return 5;
    if('0'<=x and x<='9') return 6;
}

void infixToPostfix(char infix[],char postfix[]){
    char y = NULL;
    int j = 0;
    point stack;
    stack = new(Node);
    stack->data = '$';
    for(int i = 0;i<strlen(infix);i++){
        if(pre(infix[i]) == 6) postfix[j++] = infix[i];
        if(pre(infix[i]) == 1) push(&stack,infix[i]);
        if(pre(infix[i]) == 2 or pre(infix[i]) == 3){
            postfix[j++] = ' ';
            y = peek(&stack);
            while(pre(y) >= pre(infix[i])){
                postfix[j++] = ' ';
                postfix[j++] = pop(&stack);
                y = peek(&stack);
            }
            push(&stack,infix[i]);
        }
        if (infix[i] == ')'){
            y = pop(&stack);
            while(pre(y) == 2 or pre(y) == 3){
                postfix[j++] = ' ';
                postfix[j++] = y;
                y = pop(&stack);
            }
        }
    }
    while(stack->data != '$'){
        postfix[j++] = ' ';
        postfix[j++] = pop(&stack);
    } 
    postfix[j] = NULL;
}

float caculatePostfix(char postfix[]){
    point stack = NULL;
    stack = new(Node);
    float num1,num2;
    int i = 0;
    while(i<strlen(postfix)){
        if(postfix[i] == ' '){
            i++;
        } else{
            if(pre(postfix[i]) == 6){
                float num = 0;
                while('0' <= postfix[i] and postfix[i] <= '9'){
                    num = num * 10 + postfix[i] - '0';
                    i++;
                }
                push(&stack,num);
            } else{
                num2 = pop(&stack);
                num1 = pop(&stack);
                float ketqua;
                switch (postfix[i])
                {
                case '-':
                    /* code */
                    ketqua = num1-num2;
                    break;
                case '+':
                    ketqua = num1+num2;
                    break;
                case '*':
                    ketqua = num1*num2;
                    break;
                case '/':
                    ketqua = num1/num2;
                    break;
                }
                push(&stack,ketqua);
            }
            i++;
        }
    }
    return pop(&stack);
}
