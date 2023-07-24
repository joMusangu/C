#include <stdio.h>
int main(){
    int age=25;

    printf("%p", &age);
    int *ptr = &age;
    printf("\n%p",ptr);
    printf("\nValue: %d", *ptr);
    *ptr =31;
    printf("\nThe new value pointer is: %d",age);
    int var;



return 0;
}
