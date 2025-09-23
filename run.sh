#!/bin/bash

rm -f a.out
# clear
cc -Wall -Wextra -Werror -D BUFFER_SIZE=$1 get_next_line.c get_next_line_utils.c get_next_line.h main.c
# cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c get_next_line.h main.c
./a.out $2
