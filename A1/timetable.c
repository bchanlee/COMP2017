#include "timetable.h"

int main(int argc, char *argv[]) {
    int ret; // return value of sscanf
    int suitable_train = 0; // check if there is a suitable train
    int timetable_found = 0; // check if timetable data is supplied
    char line[MAX_LEN]; // a line from timetable data
    // earliest time for departure (cross-day)
    int max_hr = INT_MAX;
    int max_min = INT_MAX;
    int max_sec = INT_MAX;
    // earliest time for departure (no cross-day)
    int cur_hr = INT_MAX;
    int cur_min = INT_MAX;
    int cur_sec = INT_MAX;
    int max_diff = INT_MAX; // closest time difference (in seconds)
    int diff; // current time difference (in seconds)
    // user data (from cmd line args)
    char *usr_source = NULL;
    char *usr_dest = NULL;
    int usr_hr;
    int usr_min;
    int usr_sec;
    // timetable data (from stdin)
    char data_source[MAX_LEN];
    char data_dest[MAX_LEN];
    int data_hr;
    int data_min;
    int data_sec;

    // not enough arguments
    if (argc != 4) {
        print_err("Please provide <source> <destination> <time> as command "
                    "line arguments");
        return 1;
    }

    // read from cmd line
    usr_source = argv[1];
    usr_dest = argv[2];
    ret = sscanf(argv[3], "%d:%d:%d", &usr_hr, &usr_min, &usr_sec);
    // error checking user arguments
    if (ret != 3) {
        print_err("Invalid time format");
        return 1;
    }
    if (usr_hr >= 24 || usr_min >= 60 || usr_sec >= 60) {
        print_err("Invalid time format");
        return 1;
    }

    // read from file
    while (fgets(line, MAX_LEN, stdin) != NULL) {
        // timetable data supplied
        timetable_found = 1;
        // parse line into appropriate format
        ret = sscanf(line, "%[^::]::%[^::]::%d:%d:%d", data_source,
                     data_dest, &data_hr, &data_min, &data_sec);

        // line longer than maximum limit
        if (str_len(data_source) > MAX_LEN - 14 ||
            str_len(data_dest) > MAX_LEN - 14) {
             continue;
        }
        // invalid entry
        if (ret != 5) {
            print_err("Invalid entry");
            // return 1; // skip line instead
            continue;
        }

        // invalid time format
        if (data_hr >= 24 || data_min >= 60 || data_sec >= 60) {
            print_err("Invalid time format");
            // return 1; // skip line instead
            continue;
        }

        // check that source and dest is the same for usr and data
        if (str_cmp(usr_source, data_source, str_len(usr_source))) {
            if (str_cmp(usr_dest, data_dest, str_len(usr_dest))) {
                // suitable train found
                suitable_train = 1;
                // find the closest time (no cross-day)
                diff = 3600*(data_hr - usr_hr) + 60*(data_min - usr_min)
                        + (data_sec - usr_sec);
                if (diff >= 0) {
                    if (diff < max_diff) {
                        max_diff = diff;
                        cur_hr = data_hr;
                        cur_min = data_min;
                        cur_sec = data_sec;
                    }
                }

                // find the earliest time for cross-day times
                if (data_hr <= max_hr) {
                    max_hr = data_hr;
                    max_min = data_min;
                    max_sec = data_sec;
                    continue;
                    if (data_min <= max_min) {
                        max_hr = data_hr;
                        max_min = data_min;
                        max_sec = data_sec;
                        continue;
                        if (data_sec <= max_sec) {
                            max_hr = data_hr;
                            max_min = data_min;
                            max_sec = data_sec;
                        }
                    }
                }

            }
        }
    }

    // print output
    if (suitable_train) {
        // if suitable train is found
        printf("The next train to %s from %s departs at ",
                usr_dest, usr_source);
        // print cross-day time
        if (max_diff == INT_MAX) {
            printf("%02d:%02d:%02d\n", max_hr, max_min, max_sec);
        }
        // print on-day time
        else {
            printf("%02d:%02d:%02d\n", cur_hr, cur_min, cur_sec);
        }
    }
    else {
        // if suitable train is not found or timetable data is not supplied
        if (timetable_found) {
            print_err("No suitable trains can be found");
        }
        else {
            print_err("No timetable to process");
        }
        return 1;
    }

    return 0;
}

// compares two strings
int str_cmp(const char *w1, const char *w2, unsigned int len) {
    int result = 1;
    // traverse each char of each string
    for (int i = 0; i < len; i++) {
        // check if char matches
        if (w1[i] != w2[i]) {
            result = 0;
            break;
        }
    }

    return result;
}

// returns length of string
int str_len(const char *w) {
    int result = 0;
    // traverse the string
    while (w[result] != '\0') {
        result += 1;
    }

    return result;
}

// prints error message
void print_err(const char *error_msg) {
    fprintf(stderr, "%s\n", error_msg);
}