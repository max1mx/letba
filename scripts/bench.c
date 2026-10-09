#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <secp256k1.h>

#ifdef USE_THREADS
#include <pthread.h>
#include <unistd.h>
#endif

#define TOTAL_ITERS 1000000

static unsigned char g_privkey[32] = {
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
    0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
    0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
    0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f
};

static double now_sec(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}

static void run_single(secp256k1_context *ctx) {
    secp256k1_pubkey pubkey;
    for (int i = 0; i < TOTAL_ITERS; i++) {
        if (!secp256k1_ec_pubkey_create(ctx, &pubkey, g_privkey)) {
            fprintf(stderr, "pubkey_create failed\n");
            exit(1);
        }
    }
}

#ifdef USE_THREADS
static secp256k1_context *g_ctx;

static void *worker(void *arg) {
    (void)arg;
    secp256k1_pubkey pubkey;
    int per = TOTAL_ITERS / (int)sysconf(_SC_NPROCESSORS_ONLN);
    for (int i = 0; i < per; i++) {
        secp256k1_ec_pubkey_create(g_ctx, &pubkey, g_privkey);
    }
    return NULL;
}
#endif

int main(void) {
    secp256k1_context *ctx = secp256k1_context_create(SECP256K1_CONTEXT_NONE);
    if (!ctx) { fprintf(stderr, "ctx failed\n"); return 1; }

    double t0 = now_sec();

#ifdef USE_THREADS
    long n = sysconf(_SC_NPROCESSORS_ONLN);
    g_ctx = ctx;
    pthread_t *threads = calloc(n, sizeof(pthread_t));
    for (long i = 0; i < n; i++)
        pthread_create(&threads[i], NULL, worker, NULL);
    for (long i = 0; i < n; i++)
        pthread_join(threads[i], NULL);
    free(threads);
    printf("[MT] %ld threads, %d ops\n", n, TOTAL_ITERS);
#else
    run_single(ctx);
    printf("[ST] 1 thread, %d ops\n", TOTAL_ITERS);
#endif

    double t1 = now_sec();
    double elapsed = t1 - t0;
    double per_op_us = (elapsed * 1e6) / TOTAL_ITERS;

    printf("  elapsed:  %.3f s\n", elapsed);
    printf("  per op:   %.2f us\n", per_op_us);
    printf("  throughput: %.0f keys/s\n", TOTAL_ITERS / elapsed);

    secp256k1_context_destroy(ctx);
    return 0;
}
