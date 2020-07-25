#include <stdio.h>
#include <stdlib.h>
#include <D:/3rdCSE/Me/Stsck/types.h>
#include <stdbool.h>
typedef struct stack
{
    uint32_t top;
    uint32_t stack_size;
    ptochar_t s_array;

}Stack;

Stack* stack_creator (uint32_t stack_size)
{
 Stack* s = (Stack*)malloc(sizeof(Stack));
 s->top = -1;
 s->stack_size = stack_size;
 s->s_array = (ptochar_t)malloc(s->stack_size * sizeof(uint8_t));
 return s;
}

bool is_Full (Stack* s)
{
    if (s->top == s->stack_size-1)
        return 1;
    return 0;
}

bool is_Empty (Stack* s)
{
    if (s->top == -1)
        return 1;
    return 0;
}

void push (Stack* s,uint8_t element)
{
    if (is_Full(s))
    {
        printf("stack is full \n");
        return;
    }
    s->top ++;
    s->s_array[s->top] = element;
}

uint8_t pull (Stack* s)
{
    uint8_t x;
    if (is_Empty(s))
        printf("stack is empty\n");
    else
    {
        x= s->s_array[s->top];
        s->top --;
        return x;
    }
}

void is_balanced (uint32_t e_size , ptochar_t expression)
{
    uint32_t open_size = 0;
    for (uint32_t i =0;i<=e_size;i++)
    {
        if(expression[i] == '{'||expression[i] == '('||expression[i] == '[')
        open_size ++;
    }
    Stack* balance_check  = stack_creator(open_size);
    for (uint32_t i =0;i<=e_size;i++)
    {
        if(expression[i] == '{'||expression[i] == '('||expression[i] == '[')
            push(balance_check,expression[i]);
        else if (expression[i] == '}'||expression[i] == ')'||expression[i] == ']')
        {
            if (expression[i] == '}' && balance_check->s_array[balance_check->top]== '{')
               pull(balance_check);
            else if (expression[i] == ')' && balance_check->s_array[balance_check->top]== '(')
               pull(balance_check);
            else if (expression[i] == ']' && balance_check->s_array[balance_check->top]== '[')
               pull(balance_check);
            else
               break;
        }
    }
    if (is_Empty(balance_check))
        printf("Balanced\n");
    else
        printf("Not balanced\n");
    //free(expression);

}

int main()
{

    uint8_t again = 'y';
    while (again == 'y')
    {
        uint32_t count=0;
        uint32_t Block_size = 5;
        uint32_t max_e_size = Block_size-1;
        ptochar_t expression = (ptochar_t)malloc(Block_size*sizeof(uint8_t));
        printf("enter expression\n");
        for (uint32_t i =0;;++i)
        {
            if (i>max_e_size)
            {
                expression=realloc(expression,(max_e_size+1+Block_size)*sizeof(uint8_t));
                max_e_size+=Block_size;
            }
            scanf("%c",&expression[i]);
            if (expression[i]==10)
             break;
            else
             count++;
        }
        is_balanced(count,expression);
        printf("Do you want to enter another expression ? (y/n) \n");
        scanf("%c%*c",&again);
    }
    return 0;
}
