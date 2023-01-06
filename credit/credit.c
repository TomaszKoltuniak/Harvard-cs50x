#include <cs50.h>
#include <stdio.h>

int value_index(string, int);
void invalid(void);

int main(void)
{
    long number = get_long("Number: ");

    // converting to string
    char str[16];
    sprintf(str, "%ld", number);

    // checking length
    int length;
    for (int i = 0; i < sizeof(str) && str[i]; i++)
    {
        length = i + 1;
    }

    // reversing string
    char n[16];

    int j = length - 1;
    for (int i = 0; i < length; i++)
    {
        n[i] = str[j];
        j--;
    }

    // Luhn's algorithm sum
    int sum = 0;
    for (int i = 0; i <= length - 1; i++)
    {
        if (i % 2)
        {
            switch (value_index(n, i))
            {
                case 5:
                    sum += 1;
                    break;
                case 6:
                    sum += 3;
                    break;
                case 7:
                    sum += 5;
                    break;
                case 8:
                    sum += 7;
                    break;
                case 9:
                    sum += 9;
                    break;
                default:
                    sum += value_index(n, i) * 2;
            }
        }
        else
        {
            sum += value_index(n, i);
        }
    }

    // sum validation
    if (sum % 10 == 0)
    {
        // per length
        switch (length)
        {
            case 15:
                if (value_index(n, length - 1) == 3 && ((value_index(n, length - 2) == 4) || (value_index(n, length - 2) == 7)))
                {
                    printf("AMEX\n");
                }
                else
                {
                    invalid();
                }
                break;
            case 13:
                if (value_index(n, length - 1) == 4)
                {
                    printf("VISA\n");
                }
                else
                {
                    invalid();
                }
                break;
            case 16:
                if (value_index(n, length - 1) == 4)
                {
                    printf("VISA\n");
                }
                else if (value_index(n, length - 1) == 5 && ((value_index(n, length - 2) == 1) || (value_index(n, length - 2) == 2)
                         || (value_index(n, length - 2) == 3) || (value_index(n, length - 2) == 4) || (value_index(n, length - 2) == 5)))
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    invalid();
                }
                break;
            default:
                invalid();
        }
    }
    else
    {
        // invalid sum
        invalid();
    }
}

int value_index(string str, int index)
{
    return ((int) str[index] - '0');
}
void invalid(void)
{
    printf("INVALID\n");
}