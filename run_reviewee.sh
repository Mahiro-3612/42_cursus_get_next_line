#!/bin/bash
rm -f a.out
# rm -f gnl
clear
cc -Wall -Wextra -Werror -D BUFFER_SIZE=24 get_next_line.c get_next_line_utils.c get_next_line.h main_reviewee.c
./a.out main_reviewee.c
