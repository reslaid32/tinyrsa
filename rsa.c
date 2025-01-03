#include "rsa.h"

int64_t rsa_gcd(int64_t a, int64_t b) {
    while (b != 0) {
        int64_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}


int64_t rsa_mod_exp(int64_t base, int64_t exp, int64_t mod) {
    int64_t result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int64_t rsa_mod_inverse(int64_t a, int64_t m) {
    int64_t m0 = m, t, q;
    int64_t x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

int64_t rsa_generate_prime(int64_t min, int64_t max) {
    int64_t prime;
    int is_prime = 0;

    while (!is_prime) {
        prime = rand() % (max - min + 1) + min;
        is_prime = 1;
        for (int64_t i = 2; i <= sqrt(prime); i++) {
            if (prime % i == 0) {
                is_prime = 0;
                break;
            }
        }
    }

    return prime;
}

void rsa_generate_keys(int64_t p, int64_t q, int64_t *e, int64_t *d, int64_t *n) {
    *n = p * q;
    int64_t phi = (p - 1) * (q - 1);

    *e = 3;
    while (__gcd(*e, phi) != 1) {
        (*e)++;
    }

    *d = rsa_mod_inverse(*e, phi);
}

int64_t rsa_encrypt(int64_t original, int64_t e, int64_t n) {
    return rsa_mod_exp(original, e, n);
}

int64_t rsa_decrypt(int64_t original, int64_t d, int64_t n) {
    return rsa_mod_exp(original, d, n);
}
