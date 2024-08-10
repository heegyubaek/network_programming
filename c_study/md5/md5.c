#include <stdio.h>
#include <openssl/md5.h>

void print_md5(unsigned char *hash) {
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    const char *data = "Hello, World!";
    unsigned char hash[MD5_DIGEST_LENGTH];

    MD5((unsigned char*)data, strlen(data), hash);

    printf("MD5 hash: ");
    print_md5(hash);

    return 0;
}
