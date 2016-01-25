#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "brightness.h"

int main(int argc, char *argv[])
{
        int cmd_opt;
        struct option long_option[] =
        {
                { "current", 0, NULL, 'c'},
                { "percentage", 1, NULL, 'p'},
                { "value", 1, NULL, 'v'},
                { NULL, 0, NULL, 0}
        };

        if(argc == 1)
                printf("%u\n", get_brightness_percentage());

        for(; ; )
        {
                if((cmd_opt = getopt_long(argc, argv, "cp:v:", long_option, NULL)) == -1)
                        break;

                switch(cmd_opt)
                {
                case 'c':
                        printf("%u\n", get_brightness());
                        break;
                case 'p':
                        set_brightness_percentage((unsigned)atoi(optarg));
                        break;
                case 'v':
                        set_brightness((unsigned)atoi(optarg));
                        break;
                default:
                        break;
                }
        }

        return 0;
}
