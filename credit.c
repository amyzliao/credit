#include <cs50.h>
#include <stdio.h>

//numdigits: long -> int
//counts the number of digits in an integer
int numdigits(long num)
{
    int digits = 0;
    do
    {
        num = num / 10;
        digits++;
    }
    while (num > 0);
    return digits;
}

//firsttwo: long -> int
//returns the first two digits of the number
int firsttwo(long num)
{
    int numdiv = numdigits(num) - 2;
    for (int i = 0; i < numdiv; i++)
    {
        num = num / 10;
    }
    return num;
}

//firstone: long -> int
//returns the first digit of the number
int firstone(long num)
{
    int numdiv = numdigits(num) - 1;
    for (int i = 0; i < numdiv; i++)
    {
        num = num / 10;
    }
    return num;
}

//sumdigs: int -> int
//returns the sum of the digits of the integer
int sumdigs(int num)
{
    int accum = 0;
    while (num > 0)
    {
        accum += num % 10;
        num = num / 10;
    }
    return accum;
}

//valid1: long -> int
//returns the result of step 1 of Luhn's validity test
int valid1(long num)
{
    int accum = 0;
    while (num > 0)
    {
        num = num / 10;
        int dig = num % 10;
        accum += sumdigs(dig * 2);
        num = num / 10;
    }
    return accum;
}

//valid2: long -> int
//returns the result of step 2 of Luhn's validity test
int valid2(long num)
{
    int accum = 0;
    while (num > 0)
    {
        accum += num % 10;
        num = num / 10;
        num = num / 10;
    }
    return accum;
}

//validtest: int, int -> boolean
//determines whether the number is syntactically valid
bool validtest(int step1, int step2)
{
    int finalval = step1 + step2;
    if (finalval % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}




int main(void)
{
    long cardnum = get_long("Number: ");

    //info for company categorization
    int carddigits = numdigits(cardnum);
    int first2 = firsttwo(cardnum);
    int first1 = firstone(cardnum);

    //info for validity
    int step1r = valid1(cardnum);
    int step2r = valid2(cardnum);

    //check for validity
    if (validtest(step1r, step2r))
    {
        //check for amex: 15 digits, start with 34 or 37
        if (carddigits == 15 && (first2 == 34 || first2 == 37))
        {
            printf("AMEX\n");
        }
        //check for mastercard: 16 digits, start with 51, 52, 53, 54, or 55
        else if (carddigits == 16 && (first2 == 51 || first2 == 52 || first2 == 53 || first2 == 54 || first2 == 55))
        {
            printf("MASTERCARD\n");
        }
        //check for visa: 13 or 16 digits, start with 4
        else if ((carddigits == 13 || carddigits == 16) && first1 == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }



}