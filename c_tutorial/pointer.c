#include <stdio.h>
#include <string.h>

int main() {
    // 20個の要素を持つ文字の配列
    char str_a[20];
    // 文字の配列を示すポインタ
    char *pointer;
    // 同じく文字列を指すポインタ
    char *pointer2;

    strcpy(str_a, "Hello World!\n");
    // 1つめのポインタが配列の先頭を指すように指定する
    pointer = str_a;
    // 1つめのポインタが指している文字列を表示する
    printf(pointer);

    // 2つめのポインタは2バイト先を指すように設定する
    pointer2 = pointer + 2;
    // 2つめのポインタが指している文字列を表示する
    printf(pointer2);
    // その場所に他の文字列をコピーする
    strcpy(pointer2, "y you guys!\n");
    // 1つめのポインタが指している文字列を表示する
    printf(pointer);
}

/*
(gdb) break 15
Breakpoint 1 at 0x11ab: file pointer.c, line 16.
(gdb) run

Breakpoint 1, main () at pointer.c:16
16	    printf(pointer);
(gdb) x/xw pointer
0x7fffffffdc30:	0x6c6c6548
(gdb) x/s pointer
0x7fffffffdc30:	"Hello World!\n"
(gdb) x/xw &pointer
0x7fffffffdc20:	0xffffdc30
(gdb) print &pointer
$1 = (char **) 0x7fffffffdc20
(gdb) print pointer
$2 = 0x7fffffffdc30 "Hello World!\n"

*/