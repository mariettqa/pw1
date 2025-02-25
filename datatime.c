#include <stdlib.h>
#include "datatime.h"
#include <stdio.h>

#define SECONDS_IN_MINUTE 60
#define SECONDS_IN_HOUR 3600
#define SECONDS_IN_DAY 86400
const int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

datatime *construct(int day, int month, int year, int hour, int minute){ // Конструктор
    datatime * dt = (datatime*)malloc(sizeof(datatime));

    dt -> day = day;
    dt -> month = month;
    dt -> year = year;
    dt -> hour = hour;
    dt -> minute = minute;

    return dt;
}

datatime * construct_default(){ // По умолчанию конструктор
    return construct(1,1,1970,0,0);
}

datatime * construct_copy(datatime dt){ // Копирующий конструктор
    datatime * dt1 = (datatime*)malloc(sizeof(datatime));

    dt1 -> day = dt.day;
    dt1 -> month = dt.month;
    dt1 -> year = dt.year;
    dt1 -> hour = dt.hour;
    dt1 -> minute = dt.minute;

    return dt1;
}

void destroy(datatime* dt){ // Деструктор
    free(dt);
}

int is_leap_year(int year) { // Проверка на високосность
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

long get_timestamp(datatime dt) { // Таймстамп
    long seconds = 0;

    for (int y = 1970; y < dt.year; y++) {
        seconds += (is_leap_year(y) ? 366 : 365) * SECONDS_IN_DAY;
    }

    for (int m = 0; m < dt.month - 1; m++) {
        seconds += days_in_month[m] * SECONDS_IN_DAY;
        if (m == 1 && is_leap_year(dt.year)) {
            seconds += SECONDS_IN_DAY;
        }
    }

    seconds += (dt.day - 1) * SECONDS_IN_DAY;
    seconds += dt.hour * SECONDS_IN_HOUR;
    seconds += dt.minute * SECONDS_IN_MINUTE;

    return seconds;
}

datatime * create_datatime_from_timestamp(long timestamp){ // Создание структуры из таймстампа для дальнейшего сравнения
    datatime * dt = construct(1,0,1970,0,0);

    while(timestamp > 365 * SECONDS_IN_DAY){
        timestamp -= (is_leap_year(dt->year) ? 366 : 365) * SECONDS_IN_DAY;

        dt->year++;
    }

    while (timestamp >= days_in_month[dt->month] * SECONDS_IN_DAY) {
        if (dt->month == 1 && is_leap_year(dt->year)) {
            if (timestamp < 29 * SECONDS_IN_DAY) break;
            timestamp -= 29 * SECONDS_IN_DAY;
        } else {
            timestamp -= days_in_month[dt->month] * SECONDS_IN_DAY;
        }
        dt->month++;
    }
    dt->month++;
    dt->day = timestamp / SECONDS_IN_DAY + (timestamp % SECONDS_IN_DAY != 0 ? 1 : 0);
    timestamp %= SECONDS_IN_DAY;

    dt->hour = timestamp / SECONDS_IN_HOUR;
    timestamp %= SECONDS_IN_HOUR;

    dt->minute = timestamp / SECONDS_IN_MINUTE;
    
    return dt;
}

#pragma region Вывод
void print_day(datatime dt){
    printf("%d\n", dt.day);
}

void print_hour(datatime dt){
    printf("%d\n", dt.hour);
}

void print_year(datatime dt){
    printf("%d\n", dt.year);
}

void print_month(datatime dt){
    printf("%d\n", dt.month);
}

void print_minute(datatime dt){
    printf("%d\n", dt.minute);
}

void fprint_date(datatime dt){
    printf("%02d:%02d %02d.%02d.%04d\n", dt.hour, dt.minute, dt.day, dt.month, dt.year);
}

void print_date(datatime dt){
    printf("%d:%d %d.%d.%d\n", dt.hour, dt.minute, dt.day, dt.month, dt.year);
}
#pragma endregion
#pragma region Сеттеры
void set_day(datatime * dt, int day){
    dt->day = day;
}

void set_month(datatime * dt, int month){
    dt->month = month;
}

void set_minute(datatime * dt, int minute){
    dt->minute = minute;
}

void set_hour(datatime * dt, int hour){
    dt->hour = hour;
}

void set_year(datatime * dt, int year){
    dt->year = year;
}
#pragma endregion
#pragma region Ввод
void enter_date(datatime * dt){
    int day, month, year, hour, minute;

    printf("Введите дату в формате: ЧАС МИН ДЕНЬ МЕСЯЦ ГОД\n");
    scanf("%d %d %d %d %d", &hour, &minute, &day, &month, &year);

    dt -> day = day;
    dt -> month = month;
    dt -> year = year;
    dt -> hour = hour;
    dt -> minute = minute;
}

void fenter_date(datatime * dt){
    int day, month, year, hour, minute;

    printf("Введите дату в формате: HH:MM DD.MM.YY\n");
    scanf("%02d:%02d %02d.%02d.%04d", &hour, &minute, &day, &month, &year);

    dt -> day = day;
    dt -> month = month;
    dt -> year = year;
    dt -> hour = hour;
    dt -> minute = minute;
}
#pragma endregion
#pragma region Сравнения


int greater(datatime dt1, datatime dt2){
    return get_timestamp(dt1) > get_timestamp(dt2);
}

int less(datatime dt1, datatime dt2){
    return get_timestamp(dt1) < get_timestamp(dt2);
}

int greater_loosely(datatime dt1, datatime dt2){
    return get_timestamp(dt1) >= get_timestamp(dt2);
}

int less_loosely(datatime dt1, datatime dt2){
    return get_timestamp(dt1) <= get_timestamp(dt2);
}
int equals(datatime dt1, datatime dt2){
    return dt1.day == dt2.day && dt1.hour == dt2.hour && dt1.minute == dt2.minute && dt1.year == dt2.year && dt1.month == dt2.month;
}

int not_equals(datatime dt1, datatime dt2){
    return !equals(dt1, dt2);
}
#pragma endregion
#pragma region Временые промежутки
datatime * get_time_difference(datatime dt1, datatime dt2){
    datatime *dt = create_datatime_from_timestamp(abs(get_timestamp(dt1) - get_timestamp(dt2)));
    dt->year -= 1970;
    return dt;
}

int get_time_difference_minutes(datatime  dt1, datatime  dt2){
    return abs(get_timestamp(dt1) - get_timestamp(dt2)) / SECONDS_IN_MINUTE;
}

int get_time_difference_hours(datatime  dt1, datatime  dt2){
    return abs(get_timestamp(dt1) - get_timestamp(dt2)) / SECONDS_IN_HOUR;
}

int get_time_difference_days(datatime  dt1, datatime  dt2){
    return abs(get_timestamp(dt1) - get_timestamp(dt2)) / (SECONDS_IN_HOUR * 24);
}

int get_time_difference_years(datatime  dt1, datatime  dt2){
    return get_time_difference(dt1,dt2)->year;
}

int get_time_difference_months(datatime  dt1, datatime  dt2){
    return get_time_difference(dt1,dt2)->month + 12 * get_time_difference(dt1,dt2)->year;
}

#pragma endregion