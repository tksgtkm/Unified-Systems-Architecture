void fatal(char *message) {
    char error_message[100];

    strcpy(error_message, "[!!] 致命的なエラー：");
    strncat(error_message, message, 79);
    perror(error_message);
    exit(-1);
}

void *ec_malloc(unsigned int size) {
    void *ptr;
    ptr = malloc(size);
    if (ptr == NULL)
        fatal("ec_malloc()内のメモリ割当てでエラーが発生しました。");
    return ptr;
}