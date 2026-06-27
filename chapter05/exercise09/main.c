#include <stdio.h>

#define PASS "PASS"
#define FAIL "FAIL"

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int is_leap_year(int year);
int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

void check_day_of_year(int year, int month, int day, int expected);
void check_month_day(int year, int yearday, int expected_month, int expected_day);

int main(void)
{
    check_day_of_year(1988, 2, 29, 60);
    check_day_of_year(1989, 3, 1, 60);
    check_day_of_year(2000, 12, 31, 366);
    check_day_of_year(1900, 12, 31, 365);

    check_day_of_year(1988, 0, 10, -1);
    check_day_of_year(1988, 13, 10, -1);
    check_day_of_year(1988, 2, 30, -1);
    check_day_of_year(1989, 2, 29, -1);
    check_day_of_year(0, 1, 1, -1);

    check_month_day(1988, 60, 2, 29);
    check_month_day(1989, 60, 3, 1);
    check_month_day(2000, 366, 12, 31);
    check_month_day(1900, 365, 12, 31);

    check_month_day(1988, 0, -1, -1);
    check_month_day(1988, 367, -1, -1);
    check_month_day(1989, 366, -1, -1);
    check_month_day(0, 1, -1, -1);

    return 0;
}

int is_leap_year(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int day_of_year(int year, int month, int day)
{
    int leap;
    char *p;
    char *monthp;

    if (year < 1) {
        return -1;
    }

    if (month < 1 || month > 12) {
        return -1;
    }

    leap = is_leap_year(year);
    p = *(daytab + leap);
    monthp = p + month;

    if (day < 1 || day > *monthp) {
        return -1;
    }

    while (--month > 0) {
        day += *++p;
    }

    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int leap;
    int year_days;
    char *p;
    char *start;

    if (year < 1) {
        *pmonth = -1;
        *pday = -1;
        return;
    }

    leap = is_leap_year(year);
    year_days = leap ? 366 : 365;

    if (yearday < 1 || yearday > year_days) {
        *pmonth = -1;
        *pday = -1;
        return;
    }

    start = *(daytab + leap);
    p = start;

    while (yearday > *++p) {
        yearday -= *p;
    }

    *pmonth = p - start;
    *pday = yearday;
}

void check_day_of_year(int year, int month, int day, int expected)
{
    int actual = day_of_year(year, month, day);

    printf("day_of_year(%d, %d, %d) = %d: %s\n",
           year, month, day, actual, actual == expected ? PASS : FAIL);
}

void check_month_day(int year, int yearday, int expected_month, int expected_day)
{
    int month;
    int day;

    month_day(year, yearday, &month, &day);

    printf("month_day(%d, %d) = %d/%d: %s\n",
           year, yearday, month, day,
           month == expected_month && day == expected_day ? PASS : FAIL);
}
