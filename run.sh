#!/bin/bash

CC="cc"
CFLAGS="-Wall -Wextra -Werror -g -fsanitize=address,undefined -D BUFFER_SIZE=1"
SRC_FILES="get_next_line.c get_next_line_utils.c main.c"
HEADER="get_next_line.h"
EXEC_NAME="a.out"
TEST_FILE="short.txt"
OUTPUT_FILE="result.txt"

rm -f ${EXEC_NAME} ${OUTPUT_FILE}

echo "Compiling..."
${CC} ${CFLAGS} ${SRC_FILES} -o ${EXEC_NAME}
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

./${EXEC_NAME} ${TEST_FILE} > ${OUTPUT_FILE}
diff -y --suppress-common-lines ${TEST_FILE} ${OUTPUT_FILE}
if [ $? -eq 0 ]; then
    echo "✅ SUCCESS: The output matches the original file."
else
    echo "❌ FAILURE: The output does not match the original file."
fi

rm -f ${EXEC_NAME} ${OUTPUT_FILE}
