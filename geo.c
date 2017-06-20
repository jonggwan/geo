#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "gmp.h"

#define NONUMBER 0
#define INTEGER 1
#define FLOATING 2

int check_digit(char *arg)
{
        int i, len, isval=INTEGER;

        len=strlen(arg);
        for(i = 0; i < len; i++)
        {
                if ( !isdigit((int)arg[i]) )
                {
                        if ( (int)arg[i] == (int)'.' )
                                isval=FLOATING;
                        else
                        {
                                printf("There is non-digit input %c\n", arg[i]);
                                return NONUMBER;
                        }
                }
        }
        return isval;
}

int main(int argc, char *argv[])
{
        int i, isval[3];
        double val, nn[3];
        mpz_t num[3], nval, tt;

        if (argc == 1 || argc > 4)
        {
                printf("Usage : %s start_number end_number ratio [optional:default=2]\n", argv[0]);
                printf("All numbers must be positive and ratio must not be one.\n");
                return 1;
        }
        for (i=1; i < argc; i++)
        {
                isval[i-1] = check_digit(argv[i]);
                if ( !isval[i-1] )
                {
                        printf("Usage : %s start_number end_number ratio [optional:default=2]\n", argv[0]);
                        printf("All numbers must be positive and ratio must not be one.\n");
                        return 1;
                }
        }

        if (argc == 3)
        {
                isval[2] = INTEGER;
                nn[2] = 2.0;
        }

        if ( isval[0]*isval[1]*isval[2] == INTEGER )
        {
                mpz_inits(tt, nval, num[0], num[1], num[2], (mpz_ptr)NULL);
                for (i=2; i <= argc; i++)
                {
                        if (0 != mpz_set_str(num[i-2], argv[i-1], 10))
                        {
                                mpz_clears(tt, nval, num[0], num[1], num[2], (mpz_ptr)NULL);
                                printf("Error : There is non-integer\n");
                                return 1;
                        }
                }
                if (argc == 3)  mpz_set_si(num[2], 2L);

                if ( mpz_sgn(num[0]) <= 0 || mpz_sgn(num[1]) <= 0 || mpz_cmp_si(num[2], 1L) <= 0 )
                {
                        printf("All numbers must be positive and ratio must be larger than one.\n");
                        mpz_clears(tt, nval, num[0], num[1], num[2], (mpz_ptr)NULL);
                        return 1;
                }
                if ( mpz_cmp(num[0], num[1]) > 0 )
                {
                        printf("start_number must be smaller than end_number.\n");
                        mpz_clears(tt, nval, num[0], num[1], num[2], (mpz_ptr)NULL);
                        return 1;
                }

                if ( mpz_cmp(num[0], num[1]) == 0 )     gmp_printf("%Zd\n", num[0]);

                for ( mpz_set(nval,num[0]); mpz_cmp(nval,num[1]) <= 0; )
                {
                        gmp_printf("%Zd ", nval);
                        mpz_set(tt, nval);
                        mpz_mul(nval,tt,num[2]);
                }
                printf("\n");

                mpz_clears(tt, nval, num[0], num[1], num[2], (mpz_ptr)NULL);
        }
        else
        {
                for (i=2; i <= argc; i++)
                        nn[i-2] = strtod(argv[i-1],NULL);

                if (nn[0] == nn[1])
                {
                        printf("%G\n",nn[0]);
                        return 0;
                }

                if ( (nn[0] <= 0.0) || (nn[1] <= 0.0) || (nn[2] <= 0.0) || (nn[2] == 1.0) )
                {
                        printf("All numbers must be positive and ratio must not be one.\n");
                        return 1;
                }
                if ( (nn[2] > 1.0 && nn[0] > nn[1]) || (nn[2] < 1.0 && nn[0] < nn[1]) )
                {
                        printf("start_number must be larger/smaller than end_number if ratio is smaller/larger than one.\n");
                        return 1;
                }

                if ( nn[0] < nn [1] )
                        for (val=nn[0]; val <= nn[1]; val*=nn[2])
                                printf("%.17G ", val);
                else
                        for (val=nn[0]; val >= nn[1]; val*=nn[2])
                                printf("%.17G ", val);
                printf("\n");
        }

        return 0;
}
