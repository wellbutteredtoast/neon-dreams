#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// NOTE: This is not very efficient, these can probably be
//       improved on later, but it's late and this just works.

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

// Verbose and debugging messages.
// Usually for debug builds or crash dumps.
void nd_system(const char* content[]) {
    printf("[%d - %d] [SYSTEM] ", get_current_date(), get_current_time());
    for (int i = 0; content[i] != NULL; i++) {
        printf("%s", content[i]);
    }
    printf("\n");
}

// Information and general messages.
// The standard for logging things.
void nd_info(const char* content[]) {
    printf("[%s %s] [INFO] ", get_current_date(), get_current_time());
    for (int i = 0; content[i] != NULL; i++) {
        printf("%s", content[i]);
    }
    printf("\n");
}

// Things are not very stable.
// But there's nothing stopping execution yet.
void nd_warning(const char* content[]) {
    printf("[%s %s] [WARNING] ", get_current_date(), get_current_time());
    for (int i = 0; content[i] != NULL; i++) {
        printf("%s", content[i]);
    }
    printf("\n");
}

// Something has happened, and execution almost stopped.
// But errors are usually handled with grace.
void nd_error(const char* content[]) {
    printf("[%s %s] [ERROR] ", get_current_date(), get_current_time());
    for (int i = 0; content[i] != NULL; i++) {
        printf("%s", content[i]);
    }
    printf("\n");
}

// An error that cannot be recovered from happened!
// Only use when logging a crash state situation.
void nd_critical(const char* content[]) {
    printf("[%s %s] [CRITICAL] ", get_current_date(), get_current_time());
    for (int i = 0; content[i] != NULL; i++) {
        printf("%s", content[i]);
    }
    printf("\n");
}

#endif // logger.h