#include <stdio.h>
#include <openssl/sha.h>

void print_sha256(unsigned char *hash) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    const char *data = "Hello, World!";
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256((unsigned char*)data, strlen(data), hash);

    printf("SHA-256 hash: ");
    print_sha256(hash);

    return 0;
}
