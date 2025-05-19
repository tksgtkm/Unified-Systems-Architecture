#include <stdio.h>
#include <fcntl.h>

void binary_print(unsigned int value) {
    // 最上位バイトを取得するマスクを作成しておく
    unsigned int mask = 0xff000000;
    // 最上位バイトを取得するシフト係数を作成しておく
    unsigned int shift = 256*256*256;
    unsigned int byte, byte_iterator, bit_iterator;

    for (byte_iterator=0; byte_iterator < 4; byte_iterator++) {
        // 必要なバイトを切り出す
        byte = (value & mask) / shift;
        printf(" ");
        // 該当バイトのビットを表示する
        for(byte_iterator=0; byte_iterator < 8; byte_iterator++) {
            // 該当バイトの最上位ビットが0出ない場合
            if (byte & 0x80)
                printf("1");
            else
                printf("0");
            // すべてのビットを左に1つだけ移動する
            byte *= 2;
        }
        // マスクのビットを右に8つ移動させる
        mask /= 256;
        // シフト係数のビットを右に8つ移動させる
        shift /= 256;
    }
}

void display_flags(char *label, unsigned int value) {
    printf("%s\t: %d\t:", label, value);
    binary_print(value);
    printf("\n");
}

int main(int argc, char *argv[]) {
   display_flags("O_RDONLY\t\t", O_RDONLY); 
   display_flags("O_WRONLY\t\t", O_WRONLY); 
   display_flags("O_RDWR\t\t\t", O_RDWR);
   printf("\n"); 
   display_flags("O_APPEND\t\t", O_APPEND);
   display_flags("O_TRUNC\t\t\t", O_TRUNC); 
   display_flags("O_CREAT\t\t\t", O_CREAT);

   printf("\n"); 
   display_flags("O_WRONLY|O_APPEND|O_CREAT", O_WRONLY|O_APPEND|O_CREAT);
}
