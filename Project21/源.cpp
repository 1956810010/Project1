#include <stdlib.h>
#include"stdio.h"
#include"math.h"

#define    maxsize    1024
typedef int datatype;
char e[maxsize];

typedef struct
{
    datatype data[maxsize];
    int Top;
}Stack;

void Init_Stack(Stack* S)
{
    S->Top = -1;
}

int isfull(Stack* S)
{
    if (S->Top == maxsize - 1)
        return (1);
    else
        return (0);
}

int isempty(Stack* S)
{
    if (S->Top >= 0)
        return (0);
    else
        return (1);
}

void push(Stack* S, datatype x)
{
    if (S->Top == maxsize - 1)
    {
        printf("堆栈已满\n");
    }
    else
    {
        S->Top++;
        S->data[S->Top] = x;
    }

}

datatype pop(Stack* S)
{
    datatype temp;
    if (isempty(S))
    {
        printf("堆栈为空\n");
        return (NULL);
    }
    else
    {
        S->Top--;
        temp = S->data[S->Top + 1];
    }
    return (temp);
}

int  zhuanhuan(int num, int n)
{
    Stack K;
    Init_Stack(&K);
    while (num)
    {

        push(&K, num % 10);
        num = num / 10;
    }

    while (!isempty(&K))
    {
        num = pow((float)n, K.Top) * pop(&K) + num;
    }
    printf("十进制数%d", num);
    return num;
}

void conversion(int n, int B)
{
    Stack S;
    Init_Stack(&S);
    int r, m;
    char i;
    r = n;
    while (r)
    {
        m = r % B;
        if (isfull(&S))
            printf("数据过大\n");
        else
        {
            push(&S, e[m]);
        }

        r = r / B;
    }
    printf("\n转换后的数为");
    while (!isempty(&S))
    {
        i = pop(&S);
        if (i >= 65 && i <= 122)
            printf("%c", i);
        else if (i >= 0 && i < 10)
            printf("%d", i);
        printf("\n");
    }
    printf("\n\n");
}

int main()
{
    int num, m, n;
    for (int i = 0; i < 10; i++)
        e[i] = i;
    for (int i = 10; i < 20; i++)
        e[i] = i + 55;
    while (1)
    {
        printf("请输入需要转换为其他进制的任意进制数据\n");
        scanf_s("%d %d %d", &num, &m, &n);
        if (num == 0) break;
        num = zhuanhuan(num, m);
        conversion(num, n);
    }
}