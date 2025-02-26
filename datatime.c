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
    handle_data_overload(dt);
}

void handle_data_overload(datatime * dt){
    datatime * dt1 = create_datatime_from_timestamp(get_timestamp(*dt));

    dt->day = dt1->day;
    dt->minute = dt1->minute;
    dt->month = dt1->month;
    dt->hour = dt1->hour;
    dt->year = dt1->year;
}

void set_month(datatime * dt, int month){
    dt->month = month;
    handle_data_overload(dt);
}

void set_minute(datatime * dt, int minute){
    dt->minute = minute;
    handle_data_overload(dt);
}

void set_hour(datatime * dt, int hour){
    dt->hour = hour;
    handle_data_overload(dt);
}

void set_year(datatime * dt, int year){
    dt->year = year;
    handle_data_overload(dt);
}

void increment_minute(datatime * dt, int minute){
    dt->minute += minute;
    handle_data_overload(dt);
}

void decrement_minute(datatime * dt, int minute){
    dt->minute -= minute;
    handle_data_overload(dt);
}

void increment_hour(datatime * dt, int hour){
    dt->hour += hour;
    handle_data_overload(dt);
}

void decrement_hour(datatime * dt, int hour){
    dt->hour -= hour;
    handle_data_overload(dt);
}

void increment_day(datatime * dt, int day){
    dt->day += day;
    handle_data_overload(dt);
}

void decrement_day(datatime * dt, int day){
    dt->day -= day;
    handle_data_overload(dt);
}

void increment_month(datatime * dt, int month){
    dt->month += month;
    handle_data_overload(dt);
}

void decrement_month(datatime * dt, int month){
    dt->month -= month;
    handle_data_overload(dt);
}

void increment_year(datatime * dt, int year){
    dt->year += year;
    handle_data_overload(dt);
}

void decrement_year(datatime * dt, int year){
    dt->year -= year;
    handle_data_overload(dt);
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

    printf("Введите дату в формате: HH:MM DD.MM.YYYY\n");
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

datatime * get_time_difference(datatime dt1, datatime dt2){
    datatime *dt = create_datatime_from_timestamp(abs(get_timestamp(dt1) - get_timestamp(dt2)));
    dt->year -= 1970;
    return dt;
}