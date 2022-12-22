// program to clear console screen in C using clrscr() function.
#include <conio.h>
#include <stdio.h>

// driver code
int main()
{
    int number1, number2, addition;
    // clear screen
    clrscr();
    // input number1 and number2
    printf("Enter No 1 and No 2\n");
    scanf("%d%d", &number1, &number2);
    addition = number1 + number2;
    printf("Sum Of Two Number is =%d", addition);
}