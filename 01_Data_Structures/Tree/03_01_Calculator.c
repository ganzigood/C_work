/*
스택을 활용한 계산기 

두가지 알고리즘이 필요하다.
1. 중위 표기법을 후위 표기법으로 변환
2. 후위 표기법의 데이터를 계산

+, -, *, / 만 사용가능, 괄호'()' 사용 불가.
1~9 까지의 정수만 사용 가능...

스택을 연습하기 위한 코드임..
*/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define True 1
#define False 0

#define Max_Len 100

typedef struct __node
{
    char data;
    struct __node* down;
}Node;

typedef struct __stack {
    Node* Top;
    int NumOfData;
}Stack;

void InitStack(Stack* myStack) {
    myStack->Top=NULL;
    myStack->NumOfData=0;
}

void Push(Stack* myStack, char tokken) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = tokken;

    newNode->down = myStack->Top;
    myStack->Top = newNode;
    (myStack->NumOfData)++;
}

char Peek(Stack* myStack) {
    if(myStack->Top == NULL) {
        return False;
    }
    return myStack->Top->data;
}

char Pop(Stack* myStack) {
    if(myStack->Top == NULL) {
        return False;
    }
    char data = myStack->Top->data;
    Node* delNode = myStack->Top;
    myStack->Top = myStack->Top->down;
    free(delNode);
    (myStack->NumOfData)--;
    return data;
}

int DataCount(Stack* myStack) {
    return myStack->NumOfData;
}

//수식변환 중위 연산자 -> 후위 연산자
int formula_change(Stack* mystack, char* origin_formula, char** changed_formula) {
    int j = 0;
    int i;
    char change_formula[Max_Len];

    for(i=0; i<(int)sizeof(origin_formula) ; i++ ){
        char tokken = origin_formula[i];
        switch(tokken)  {
            case'+':
                if(Peek(mystack)==False){
                    Push(mystack,tokken);
                } else if(Peek(mystack) =='-'){
                    Push(mystack,tokken);
                } else if(Peek(mystack)=='*' || Peek(mystack)=='/'){
                    change_formula[j]=Pop(mystack);
                    j++;
                    Push(mystack,tokken);
                }
                break;
            case '-':
                if(Peek(mystack)==False){
                    Push(mystack,tokken);
                } else if(Peek(mystack) =='+'){
                    Push(mystack,tokken);
                } else if(Peek(mystack)=='*' || Peek(mystack)=='/'){
                    change_formula[j]=Pop(mystack);
                    j++;
                    Push(mystack,tokken);
                }
                break;
            case '*':
                if(Peek(mystack)==False){
                    Push(mystack,tokken);
                } else if(Peek(mystack)=='+' || Peek(mystack)=='-'){
                    Push(mystack,tokken);
                }
                break;
            case '/':
                if(Peek(mystack)==False){
                    Push(mystack,tokken);
                } else if(Peek(mystack)=='+' || Peek(mystack)=='-'){
                    Push(mystack,tokken);
                }
                break;
            case '(':
                break;
            case ')':
                break;
            default:
                change_formula[j] = tokken;
                j++;
                if(DataCount(mystack) == 2) {
                    change_formula[j] = Pop(mystack);
                    j++;
                    change_formula[j] = Pop(mystack);
                    j++;
                }
                break;
        }
    }
    for(i=j-1; i<(int)sizeof(origin_formula); i++){
        change_formula[i] = Pop(mystack);
    }
    change_formula[i] = '\0';
    *changed_formula = change_formula;
    return True;
}

int calculate(Stack* myStack, char* formula){
    int result;
    /*
    매개변수로 받은 변환된 수식 데이터를 정적 변수에 담아야 된다. char* 형에 옮기는경우 
    코드의 진행중 Push()를 만나서 힙 영역에 새롭게 데이터를 쓰게 되면서 메모리 정렬을 새롭게 하면서 데이터의 위치가 변경될 수 있다.
    이것 때문에 하루종일 헤맸다..... 아.. 
    */
    char tokken[Max_Len];       
    int i, num1, num2;
    
    strcpy(tokken, formula);

    for(i=0; i<(int)sizeof(formula)-1 ; i++ ){
       
        char to = tokken[i];

        switch(to)  {
            case'+':
                num1 = Pop(myStack)-'0';
                num2 = Pop(myStack)-'0';
                result = num1+num2;
                Push(myStack, result+'0');
                break;
            case'-':
                num1 = Pop(myStack)-'0';
                num2 = Pop(myStack)-'0';
                result = num2-num1;
                Push(myStack, result+'0');
                break;
            case'*':
                num1 = Pop(myStack)-'0';
                num2 = Pop(myStack)-'0';
                result = num1*num2;
                Push(myStack, result+'0');
                break;
            case'/':
                num1 = Pop(myStack)-'0';
                num2 = Pop(myStack)-'0';
                result = num2/num1;
                Push(myStack, (char)result);
                break;
            default:
                Push(myStack, to);
                break;
        }
    }
    return result;
}
