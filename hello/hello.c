#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("Typeun your name: ");
    printf("hello, %s\n", name);
}