#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int check_digit(char *arg)
{
        int i, len;

        len=strlen(arg);
        for(i = 0; i < len; i++)
        {
                if ( !isdigit((int)arg[i]) && (int)arg[i] != (int)'.')
                {
                        printf("There is non-digit input %c\n", arg[i]);
                        return 0;
                }
        }
        return 1;
}

int main(int argc, char *argv[])
{
        int i;
        double val, nn[3];

        if (argc == 1 || argc > 4)
        {
                printf("Usage : %s start_number end_number ratio [optional:default=2]\n", argv[0]);
                printf("All numbers must be positive and ratio must not be one.\n");
                return 1;
        }
        for (i=1; i < argc; i++)
        {
                if ( !check_digit(argv[i]) )
                {
                        printf("Usage : %s start_number end_number ratio [optional:default=2]\n", argv[0]);
                        printf("All numbers must be positive and ratio must not be one.\n");
                        return 1;
                }
        }

        for (i=2; i <= argc; i++)
                nn[i-2] = strtod(argv[i-1],NULL);
        if (argc == 3)
                nn[2] = 2.0;

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
                        printf("%G ", val);
        else
                for (val=nn[0]; val >= nn[1]; val*=nn[2])
                        printf("%G ", val);
        printf("\n");

        return 0;
}
