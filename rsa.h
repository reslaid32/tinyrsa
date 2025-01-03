#if !defined(TINY_RSA_H)
#define TINY_RSA_H

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <inttypes.h>

int64_t rsa_gcd(int64_t a, int64_t b);

int64_t rsa_mod_exp(int64_t base, int64_t exp, int64_t mod);

int64_t rsa_mod_inverse(int64_t a, int64_t m);

int64_t rsa_generate_prime(int64_t min, int64_t max);

void rsa_generate_keys(int64_t p, int64_t q, int64_t *e, int64_t *d, int64_t *n);

int64_t rsa_encrypt(int64_t original, int64_t e, int64_t n);

int64_t rsa_decrypt(int64_t original, int64_t d, int64_t n);

#endif // TINY_RSA_H
