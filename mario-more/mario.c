#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0 || 8 < height);
    // main loop
    for (int i = 1; i <= height; i++)
    {

        // first spaces
        for (int j = height - i; j >= 1; j--)
        {
            printf(" ");
        }

        // first pyramide
        for (int k = i; k >= 1; k--)
        {
            printf("#");
        }

        // gap between pyramids
        printf("  ");
        
        // second pyramide
        for (int l = i; l >= 1; l--)
        {
            printf("#");
        }
        printf("\n");
    }
}