/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 09:07:15 by codespace         #+#    #+#             */
/*   Updated: 2025/09/20 09:07:52 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int main(void)
{
    int     fd1;
    int     fd2;
    int     fd3;
    char    *line;

    // 3つの異なるファイルを開く
    fd1 = open("test1.txt", O_RDONLY);
    fd2 = open("test2.txt", O_RDONLY);
    fd3 = open("test3.txt", O_RDONLY);

    // ファイルが開けたかチェック
    if (fd1 == -1 || fd2 == -1 || fd3 == -1)
    {
        printf("Error: ファイルを開けませんでした。\n");
        return (1);
    }
    printf("fd1=%d, fd2=%d, fd3=%d\n", fd1, fd2, fd3);
    printf("--- 読み込み開始 ---\n");

    // 全てのファイルが終端に達するまでループを続ける
    while (1)
    {
        int lines_read_this_cycle = 0;

        // fd1から1行読み込む
        line = get_next_line(fd1);
        if (line)
        {
            printf("[fd1]: %s", line);
            free(line);
            lines_read_this_cycle++;
        }

        // fd2から1行読み込む
        line = get_next_line(fd2);
        if (line)
        {
            printf("[fd2]: %s", line);
            free(line);
            lines_read_this_cycle++;
        }

        // fd3から1行読み込む
        line = get_next_line(fd3);
        if (line)
        {
            printf("[fd3]: %s", line);
            free(line);
            lines_read_this_cycle++;
        }

        // この周回でどのファイルからも1行も読み込めなかったら、全て読み終わったと判断
        if (lines_read_this_cycle == 0)
            break;
    }
    printf("--- 読み込み終了 ---\n");

    // 開いたファイルを全て閉じる
    close(fd1);
    close(fd2);
    close(fd3);

    return (0);
}