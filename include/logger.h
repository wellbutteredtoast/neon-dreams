#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>


static char* get_current_time() {
    // HH:MM:SS + \0
    static char time_string[9];
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    snprintf(time_string, sizeof(time_string), "%02d:%02d:%02d",
        tm_info->tm_hour,
        tm_info->tm_min,
        tm_info->tm_sec);

    return time_string;
}

static char* get_current_date() {
    // YYYY-MM-DD + \0
    static char date_str[11];
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    snprintf(date_str, sizeof(date_str), "%04d-%02d-%02d",
             tm_info->tm_year + 1900,
             tm_info->tm_mon + 1,
             tm_info->tm_mday);

    return date_str;
}

static void write_to_file(FILE* file) {

}

void nd_system(const char* content[]) {
    // ...
}

#endif // logger.h