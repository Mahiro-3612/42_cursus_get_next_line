#!/bin/bash
rm -f a.out
# rm -f gnl
clear
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c get_next_line.h main.c
./a.out main.c
