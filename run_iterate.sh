#!/bin/bash

MIN_BUFFER=1
MAX_BUFFER=100

CC="cc"
CFLAGS="-Wall -Wextra -Werror -g -fsanitize=address,undefined"
SRC_FILES="get_next_line.c get_next_line_utils.c main.c"
EXEC_NAME="a.out"
TEST_FILE="giant_line.txt"
OUTPUT_FILE="result.txt"

for (( bs=${MIN_BUFFER}; bs<=${MAX_BUFFER}; bs++ ))
do
    rm -f ${EXEC_NAME} ${OUTPUT_FILE}
    ${CC} ${CFLAGS} -D BUFFER_SIZE=${bs} ${SRC_FILES} -o ${EXEC_NAME}
    if [ $? -ne 0 ]; then
        echo "❌ Compilation failed for BUFFER_SIZE = ${bs}."
        exit 1
    fi
    ./${EXEC_NAME} ${TEST_FILE} > ${OUTPUT_FILE}
    diff -q ${TEST_FILE} ${OUTPUT_FILE} > /dev/null

    if [ $? -eq 0 ]; then
        echo "✅ SUCCESS for BUFFER_SIZE = ${bs}."
    else
        echo "❌ FAILURE: Output does not match for BUFFER_SIZE = ${bs}."
        echo "See the difference below:"
        diff -y --suppress-common-lines ${TEST_FILE} ${OUTPUT_FILE}
        exit 1
    fi
done

rm -f ${EXEC_NAME} ${OUTPUT_FILE}

echo ""
echo "🎉 All tests passed for BUFFER_SIZE from ${MIN_BUFFER} to ${MAX_BUFFER}!"
