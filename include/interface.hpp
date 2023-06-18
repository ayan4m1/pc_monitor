#pragma once
#include <stdint.h>
// the packet to receive
typedef struct read_status {
    // the command id
    constexpr static const int command = 1;
    char top_title[4];
    char top_unit1;
    int top1_hue1;
    int top1_hue2;
    int top_value1;
    int top_value1_max;
    int top_value1_div;
    char top_unit2;
    int top2_hue1;
    int top2_hue2;
    int top_value2;
    int top_value2_max;
    int top_value2_div;
    char bottom_title[4];
    char bottom_unit1;
    int bottom1_hue1;
    int bottom1_hue2;
    int bottom_value1;
    int bottom_value1_max;
    int bottom_value_1_div;
    char bottom_unit2;
    int bottom2_hue1;
    int bottom2_hue2;
    int bottom_value2;
    int bottom_value2_max;
    int bottom_value2_div;
} read_status_t;