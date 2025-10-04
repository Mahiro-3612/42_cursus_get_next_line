#!/bin/bash

SRC_FILES="get_next_line_bonus.c get_next_line_utils_bonus.c"
MAIN_FILE="main_bonus.c"
HEADER="get_next_line_bonus.h"
EXEC_NAME="gnl_bonus_tester"
TEST_FILE1="test1.txt"
TEST_FILE2="test2.txt"
EXPECTED_OUTPUT="expected_output.txt"
ACTUAL_OUTPUT="actual_output.txt"


rm -f ${EXEC_NAME} ${ACTUAL_OUTPUT}

cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 ${SRC_FILES} ${MAIN_FILE} -o ${EXEC_NAME}
if [ $? -ne 0 ]; then
    echo "❌ Compilation failed."
    exit 1
fi

./${EXEC_NAME} ${TEST_FILE1} ${TEST_FILE2} > ${ACTUAL_OUTPUT}

diff -y --suppress-common-lines ${EXPECTED_OUTPUT} ${ACTUAL_OUTPUT}

if [ $? -eq 0 ]; then
    echo "✅ SUCCESS: The bonus output is correct!"
else
    echo "❌ FAILURE: The bonus output does not match the expected result."
fi

rm -f ${EXEC_NAME} ${ACTUAL_OUTPUT}
