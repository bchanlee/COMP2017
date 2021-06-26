#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_LEN (4096)

// compares two strings
int str_cmp(const char *w1, const char *w2, unsigned int len);
// returns length of string
int str_len(const char *w);
// prints error message
void print_err(const char *error_msg);

#endif
