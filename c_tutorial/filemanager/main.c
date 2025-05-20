#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "utils.h"

#define FILENAME "/var/notes"

void usage(char *prog_name, char *filename) { 
   printf("使用方法： %s <%sに追加するデータ>\n", prog_name, filename); 
   exit(0);
}

void write_method(int userid, char *note) {
    int fd;
    char *buffer = (char *)ec_malloc(100);
    char *datafile = (char *)ec_malloc(20);
    strcpy(datafile, FILENAME);
    strcpy(buffer, note);

    printf("[DEBUG] buffer @ %p: \'%s\'\n", buffer, buffer);
    printf("[DEBUG] datafile @ %p: \'%s\'\n", datafile, datafile);

    fd = open(datafile, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd == -1)
        fatal("main()関数内、ファイルのオープン中にエラーが発生しました。");
    printf("[DEBUG] ファイル記述子：%d\n", fd);

    if (write(fd, &userid, 4) == -1)
        fatal("main()関数内、ファイルへのユーザーIDの書き込みでエラーが発生しました。");
    write(fd, "\n", 1);

    if (write(fd, buffer, strlen(buffer)) == -1)
        fatal("main()関数内、ファイルへのバッファの書き込みでエラーが発生しました。");
    write(fd, "\n", 1);
    
    if (close(fd) == -1)
        fatal("main()関数内、ファイルのクローズ中にエラーが発生しました。");

    printf("メモが保存されました。\n");
    free(buffer);
    free(datafile);
}

int find_user_note(int fd, int user_uid) {
    int note_uid = -1;
    unsigned char byte;
    int length;

    while (note_uid != user_uid) {
        if (read(fd, &note_uid, 4) != 4)
            return -1;
        if ((read(fd, &byte, 1) != 1))
            return -1;

        byte = length = 0;
        while (byte != '\n') {
            if (read(fd, &byte, 1) != 1)
                return -1;
            length++;
        }
    }

    lseek(fd, length * -1L, SEEK_CUR);

    printf("[DEBUG] uid %dの%dバイトのメモを見つけました。\n", note_uid, length);
    return length;
}

int search_note(char *note, char *keyword) {
    int i, keyword_length, match=0;

    keyword_length = strlen(keyword);
    if (keyword_length == 0)
        return 1;

    for (i=0; i<strlen(note); i++) {
        if (note[i] == keyword[match]) {
            match++;
        } else {
            if (note[i] == keyword[0])
                match = 1;
            else
                match = 0;
        }
        if (match == keyword_length)
            return 1;
    }
    return 0;
}

int print_notes(int fd, int uid, char *searchstring) {
    int note_length;
    char byte=0, note_buffer[100];

    note_length = find_user_note(fd, uid);
    if (note_length == -1)
        return 0;

    read(fd, note_buffer, note_length);
    note_buffer[note_length] = 0;

    if (search_note(note_buffer, searchstring))
        printf("%s", note_buffer);

    return 1;
}

void read_method(int uid, char *searchstring) {
    int note_length, fd;
    int printing = 1;
    char byte = 0, note_buffer[100];

    fd = open(FILENAME, O_RDONLY);
    if (fd == -1)
        fatal("main()関数内、ファイルの読み込みオープンでエラーが発生しました。");

    while (printing)
        printing = print_notes(fd, uid, searchstring);

    printf("------[メモの終わり]------\n");

    close(fd);
}

int main(int argc, char *argv[]) {
    int userid, fd;
    char searchstring[100];

    userid = getuid();

    if (argc < 2)
        usage(argv[0], FILENAME);

    if (strcmp(argv[1], "-w") == 0) {
        write_method(userid, argv[2]);
    } else if (strcmp(argv[1], "-r") == 0) {
        if (argc > 2)
            strcpy(searchstring, argv[2]);
        else
            searchstring[0] = 0;

        read_method(userid, searchstring);
    }
}