#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "rsa.h"

int enc_main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <prime_p> <prime_q> <original>\n", argv[0]);
        return 1;
    }

    int64_t prime_p = atoll(argv[1]);
    int64_t prime_q = atoll(argv[2]);
    int64_t original = atoll(argv[3]);

    srand(time(NULL));

    int64_t e, d, n;
    rsa_generate_keys(prime_p, prime_q, &e, &d, &n);

    if (original >= n) {
        fprintf(stderr, "error: Original message must be smaller than n (%" PRId64 ")\n", n);
        return 1;
    }

    int64_t encrypted = rsa_encrypt(original, e, n);

    printf("%" PRId64, encrypted);

    return 0;
}

int dec_main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <prime_p> <prime_q> <encrypted>\n", argv[0]);
        return 1;
    }

    int64_t prime_p = atoll(argv[1]);
    int64_t prime_q = atoll(argv[2]);
    int64_t encrypted = atoll(argv[3]);

    srand(time(NULL));

    int64_t e, d, n;
    rsa_generate_keys(prime_p, prime_q, &e, &d, &n);

    int64_t decrypted = rsa_decrypt(encrypted, d, n);

    printf("%" PRId64, decrypted);

    return 0;
}

int main(int argc, char *argv[]) {
    #if defined(RSA_ENCRYPT_MAIN)
    return enc_main(argc, argv);
    #elif defined(RSA_DECRYPT_MAIN)
    return dec_main(argc, argv);
    #else
    fprintf(stderr, "error: Please define either RSA_ENCRYPT_MAIN or RSA_DECRYPT_MAIN\n");
    return -1;
    #endif
}
