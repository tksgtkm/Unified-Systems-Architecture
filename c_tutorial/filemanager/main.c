#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "utils.h"

void usage(char *prog_name, char *filename) { 
   printf("使用方法： %s <%sに追加するデータ>\n", prog_name, filename); 
   exit(0);
}

void write_method(int userid, int fd, char *buffer, char *datafile) {

    buffer = (char *)ec_malloc(100);
    datafile = (char *)ec_malloc(20);
    strcpy(datafile, "/var/notes");

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

int read_method(int fd, int uid, char *searchstring) {
    int note_length;
    char byte = 0, note_buffer[100];


}

int main(int argc, char *argv[]) {
    int userid, fd;

    userid = getuid();

    // if (argc < 2)
    //     usage(argv[0], datafile);

    if (argv[1] == '-w') {
        char *buffer, *datafile;
        strcpy(buffer, argv[2]);
        write_method(userid, fd, buffer, datafile);
    } else if (argv[1] == '-r') {
        char searchstring[100];
        strcpy(searchstring, argv[2]);

    }
}