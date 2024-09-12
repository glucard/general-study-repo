// Como compilar:
// gcc libbsd_queue.c -o libbsd_queue
// Como executar:
// ./libbsd_queue

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <bsd/sys/queue.h>

typedef struct _Cat {
        //struct _Cat *next;
        LIST_ENTRY(_Cat) pointers;
        char name[255];
        int color;
        char can_climb;
} Cat;

Cat *create_cat(char *name, int color, char can_climb);

Cat *create_cat(char *name, int color, char can_climb) {
        Cat *cat = (Cat *)malloc(sizeof(Cat));
        strcpy(cat->name, name);
        cat->color = color;
        cat->can_climb = can_climb;
        return cat;
}



LIST_HEAD(cat_list, _Cat) cats;

int main()
{
        printf("\n--------------EXAMPLE------------------\n");
        Cat *cat1 = create_cat("Cat1", 2, 0);
        Cat *cat2 = create_cat("Cat2", 3, 1);
        Cat *cat3 = create_cat("Cat3", 4, 0);
        Cat *cat4 = create_cat("Cat4", 2, 0);
        
        LIST_INIT(&cats);
        
        LIST_INSERT_HEAD(&cats, cat1, pointers);
        LIST_INSERT_HEAD(&cats, cat2, pointers);
        LIST_INSERT_HEAD(&cats, cat3, pointers);
        LIST_INSERT_HEAD(&cats, cat4, pointers);
        
        LIST_REMOVE(cat4, pointers);
        
        Cat *cat;
        LIST_FOREACH(cat, &cats, pointers) {
                printf("Memory address: %p\n", cat);
                printf("Cat color ID: %d\n", cat->color);
        }
        printf("\n");
        
        printf("\n");
}