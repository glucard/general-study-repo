// Como compilar:
// gcc libbsd_queue.c -o libbsd_queue
// Como executar:
// ./libbsd_queue

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <bsd/sys/queue.h>

typedef struct _HashListNode {
        //struct _Cat *next;
        LIST_ENTRY(_HashListNode) pointers;
        int key;
        int value;
} HashListNode;

HashListNode *create_hln(int key, int value);

HashListNode *create_hln(int key, int value) {
        HashListNode *hln = (HashListNode *)malloc(sizeof(HashListNode));
        hln->key = key;
        hln->value = value;
        return hln;
}

typedef struct hash_list {
        struct _HashListNode *lh_first;
} HashList;

#define N 10

void insert_hash_table(HashList** hash_table, int value, int (*hash_func)(int, int)) {
        int key = hash_func(value, N);
        HashListNode* hln = create_hln(key, value);
        LIST_INSERT_HEAD(hash_table[key], hln, pointers);
}

int mod(int x, int n) {
        return x % n;
}

int main() {
        HashList** hash_table = (HashList**)malloc(N * sizeof(HashList*));
        for(int i = 0; i < N; i++){
                hash_table[i] = (struct hash_list*)malloc(sizeof(struct hash_list));
                LIST_INIT(hash_table[i]);
        }

        for(int i = 0; i < 50; i++) {
                insert_hash_table(hash_table, rand(), mod);
        }

        printf("\n--------------PROMPT------------------\n");
        
        HashListNode *hln;
        
        for(int i = 0; i < N; i++){
                printf("i:%d, Memory address: %p:\n", i, hash_table[i]);
                LIST_FOREACH(hln, hash_table[i], pointers) {
                        printf(" - Memory address: %p - ", hln);
                        printf("Key: %d - ", hln->key);
                        printf("Value: %d\n", hln->value);
                }
                printf("\n");
        }
        printf("\n");
        
        printf("\n");
}