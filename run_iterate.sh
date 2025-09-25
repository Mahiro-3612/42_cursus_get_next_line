#!/bin/bash

TEST_FILE="empty.txt"

for i in $(seq 0 100)
do
    echo "------------------------------------------"
    echo "BUFFER_SIZE = $i でテスト中..."
    echo "------------------------------------------"

    rm -f a.out
    cc -Wall -Wextra -Werror -D BUFFER_SIZE=$i get_next_line.c get_next_line_utils.c get_next_line.h main_iterate.c

    if [ -f "a.out" ]; then
        ./a.out "$TEST_FILE"
    else
        echo "コンパイルエラー: BUFFER_SIZE = $i"
    fi
done

echo "全てのテストが完了しました。"