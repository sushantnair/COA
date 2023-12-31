#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
void binint(int *b, int len, int max);
void binfrac(int *b, int len);
int d_to_b(int num, int *b, int bits);
void ieee();
int seperate(char val[], int *int_part, float *frac_part);
int frac_conv(float *frac_binarr, int *frac_bin, int frac_max);
int normal(int int_max, int int_len, int *int_bin, int frac_max, int frac_len, int *frac_bin);
void mantissa(int int_max, int *int_bin, int frac_len, int *frac_bin, int norexp);
int main()
{
    ieee();
    return 0;
}
void ieee()
{
    char in_num[20] = {'0'};
    int int_part = 0;
    float frac_part = 0;
    int frac_max = 20;
    int int_max = 10;
    int int_len = 0; 
    int frac_len = 0;
    int int_bin[10] = {0}, frac_bin[20] = {0};
    float frac_binarr[21] = {0};
    int norexp = 0;
    int biexp = 0, biexpsingle[9] = {0}, biexpdoub[11] = {0}, biexpsingle_len = 0, biexpdoub_len = 0;
    int signBit = 0;
    int i, j, temp = 0;
    printf("\nIEEE\t754\tFLOATING\tPOINT\tREPRESENTATION");
    printf("\nEnter the number whose IEEE 754 equivalent you wish to get: ");
    scanf("%s", in_num);
    signBit = seperate(in_num, &int_part, &frac_part);
    int_len = d_to_b(int_part, &int_bin[0], int_max);
    if(int_len == 0)
        int_len = 1;
    printf("\nThe integer in binary is %d.", int_part);
    binint(&int_bin[0], int_len, int_max);
    frac_binarr[0] = frac_part;
    frac_len = frac_conv(&frac_binarr[0], &frac_bin[0], frac_max);
    printf("\nThe fraction in binary is %.5f.", frac_part);
    binfrac(&frac_bin[0], frac_len);
    printf("\nNormalization: ");
    binint(&int_bin[0], int_len, int_max);
    printf(".");
    binfrac(&frac_bin[0], frac_len);
    norexp = normal(int_max, int_len, &int_bin[0], frac_max, frac_len, &frac_bin[0]);
    printf("\n1.");
    mantissa(int_max, &int_bin[0], frac_len, &frac_bin[0], norexp);
    printf(" × 2 ^ %d.", norexp);
    printf("\nThe normalized exponent is %d.", norexp);
    printf("\nBiasing: ");
    biexp = 127 + norexp;
    biexpsingle_len = d_to_b(biexp, &biexpsingle[0], 9);
    printf("\nSingle Precision: ");
    printf("\n%d = E - 127", norexp);
    printf("\nE = %d = ", biexp);
    binint(&biexpsingle[0], biexpsingle_len, 9);
    biexp = 1023 + norexp;
    biexpdoub_len = d_to_b(biexp, &biexpdoub[0], 11);
    printf("\nDouble Precision: ");
    printf("\n%d = E - 1023", norexp);
    printf("\nE = %d = ", biexp);
    binint(&biexpdoub[0], biexpdoub_len, 11);
    printf("\nDisplay: ");
    printf("\nSign Bit\tBiased Exponent\t\tMantissa\n");
    printf("\t%d\t | \t", signBit);
    binint(&biexpsingle[0], biexpsingle_len, 9);
    printf("\t | ");
    mantissa(int_max, &int_bin[0], frac_len, &frac_bin[0], norexp);
    printf("\n");
    printf("\t%d\t | \t", signBit);
    binint(&biexpdoub[0], biexpdoub_len, 11);
    printf("\t | ");
    mantissa(int_max, &int_bin[0], frac_len, &frac_bin[0], norexp);
    printf("\n");
}
int d_to_b(int num, int *b, int bits)
{
    int i = bits - 1, len = 0, rem = 0;
    while(num >= 1)
    {
        rem = num % 2;
        *(b + (i--)) = rem;
        num = num / 2;
        len++;
    }
    return len;
}
void binint(int *b, int len, int max)
{
    int i, temp = max - len;
    for(i = temp; i < max; i++)
    {
        printf("%d", *(b+i));
    }
}
void binfrac(int *b, int len)
{
    int i;
    for(i = 0; i < len; i++)
    {
        printf("%d", *(b+i));
    }
}
int seperate(char val[], int *int_part, float *frac_part)
{
    int i = 0, flag = 0, sign = 0, dot_pos;
    float frac_place_val = 0.1;
    int int_place_val = 1, digit;
    *frac_part = 0.0;
    *int_part = 0;
    if(val[0]=='-')
        sign = 1;
    else
        sign = 0;
    while(i < strlen(val) && flag == 0)
    {
        if(val[i] == '.')
        {
            dot_pos = i;
            flag = 1;
        }
        i++;
    }
    for(i = dot_pos - 1; i >= sign; i--)
    {
        digit = val[i] - '0';
        *int_part = (*int_part) + digit*int_place_val;
        int_place_val = int_place_val*10;
    }
    for(i = dot_pos + 1; i < strlen(val); i++)
    {
        digit = val[i] - '0';
        *frac_part = (*frac_part) + digit*frac_place_val;
        frac_place_val = frac_place_val/10;
    }
    return sign;
}
int frac_conv(float *frac_binarr, int *frac_bin, int frac_max)
{
    int i = 1, j, len = 0, flag = 0, temp;
    char frac_string[10] = {'0'};
    while(flag == 0 && i <= frac_max)
    {
        frac_binarr[i] = frac_binarr[i - 1]*2.00;
        if(frac_binarr[i] > 1.00)
        {
            frac_bin[i - 1] = 1;
            gcvt(frac_binarr[i], 6, frac_string);
            seperate(frac_string, &temp, &frac_binarr[i]);
        }
        else if(frac_binarr[i] == 1.00)
        {
            frac_bin[i - 1] = 1;
        }
        else
        {
            frac_bin[i - 1] = 0;
        }
        len++;
        if(frac_binarr[i] == 0.00 || frac_binarr[i] == 1.00)
        {
            flag = 1;
        }
        else
        {
            j = 0;
            {
                if(frac_binarr[i] == frac_binarr[j])
                {
                    flag = 1;
                }
                j++;
            }
        }
        i++;
    }
    return len;
}
int normal(int int_max, int int_len, int *int_bin, int frac_max, int frac_len, int *frac_bin)
{
    int i, temp_len = 0, temp = 0, flag = 0, norexp = 0;
    temp_len = int_max - int_len;
    temp = int_len;
    flag = 0;
    for(i = temp_len; i < int_max; i++)
    {
        if(int_bin[i] == 1)
        {
            flag = 1;
            temp--;
            break;
        }
        else temp--;
    }
    if(flag == 1)
    {
        norexp = temp;
    }
    else
    {
        temp = 1;
        for(i = 0; i < frac_len; i++)
        {
            if(frac_bin[i] == 1)
            {
                break;
            }
            else temp++;
        }
        norexp=-temp;
    }
    return norexp;
}
void mantissa(int int_max, int *int_bin, int frac_len, int *frac_bin, int norexp)
{
    int i;
    if(norexp > 0)
    {
        binint(&int_bin[0], norexp, int_max);
        if((norexp+frac_len) > 23)
            frac_len = 23 - norexp;
        binfrac(&frac_bin[0], frac_len);
    }
    else
    {
        for(i = abs(norexp); i < frac_len; i++)
        {
            printf("%d", frac_bin[i]);
        }
        if(abs(norexp) == frac_len)
        {
            printf("0");
        }
    }
}	
