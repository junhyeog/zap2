#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <utmp.h>
#include <limits.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define UTMP_ARR_SIZE 1024

char path[PATH_MAX];
char lastlog_path[PATH_MAX];

struct utmp *utmp_arr[UTMP_ARR_SIZE];
size_t sz;

bool flag_A; /* delete all by account*/
bool flag_R; /* replace by account */
bool flag_a; /* by account */
bool flag_t; /* by tty name */
bool flag_d; /* by date (mmddyy) */

char user[UT_NAMESIZE];
char user_r[UT_NAMESIZE];
char line[UT_LINESIZE];
char line_r[UT_LINESIZE];
struct tm date;
struct tm date_r;

int compare(const void *a, const void *b);
void sort_utmp_arr();
bool chk(struct utmp utmp_ent);
void build_utmp_arr();
void write_utmp_arr();
void clear_utmp_arr();
void write_lastlog();

void zap2();
