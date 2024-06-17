/* GENERIC IMPLEMENATION OF LIST - (SINGLY LINKED LIST) */
#ifndef GENLIST_H_
#define GENLIST_H_

#include <stdio.h>
#include <errno.h>    // For errno
#include <string.h>   
#include <stddef.h>

#define HANDLE_ERR(desc, msg)                                                   \
do {                                                                            \
    fprintf(stderr, "%s :%d: %s: ", __FILE__, __LINE__, __FUNCTION__);          \
    fprintf(stderr, "%s : %s\n", desc, msg);                                    \
    exit(EXIT_FAILURE);                                                         \
} while (0)                                                                     \

/* Provides more verbosity with perror codes */
#define HANDLE_ERR_V(desc, ...)                                                 \
do {                                                                            \
    fprintf(stderr, "%s :%d: %s: ", __FILE__, __LINE__, __func__);              \
    fprintf(stderr, "%s : ", desc);                                             \
    if (errno != 0) {                                                           \
        fprintf(stderr, "%s (errno %d: %s)\n", strerror(errno), errno,          \
                strerror(errno));                                               \
    } else {                                                                    \
        fprintf(stderr, __VA_ARGS__);                                           \
        fprintf(stderr, "\n");                                                  \
    }                                                                           \
    exit(EXIT_FAILURE);                                                         \
} while (0)                                                                     \


#include <stddef.h>

typedef struct node 
{
    void *data;                 
    struct node *next;
    // struct node *prev;       // (future implementation)
} node;

typedef struct 
{
    node *head;                 /* pointer to the head of list */
    // node *tail;              /* pointer to the last node of list (future implementation) */
    size_t stride;              /* size of each element in list */
    size_t len;                 /* length or count of elements in list */
} list;

/* Functions */

#define list_init(type) _list_init(sizeof(type))
#define ARRAY_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

list *_list_init(size_t stride);
node *create_node(void *data);
int is_list_empty(list *l);
void list_append(list *l, void *data);
void list_prepend(list *l, void *data);
void list_insert(list *l, size_t idx, void *key);
void *list_search(list *l, void *key);
void list_print(list *l, void (*print_item)(void *));
void list_destroy(list *l);
void list_remove(list *l, size_t idx);
void list_pop(list *l);
void *list_get(list *l, size_t idx);

/* TODO: 
    - take care of void * safety
    - implement the insert and search function 
    - also implement delete, insert and search by key functions
*/

#define list_map_items(l, items) {                      \
    for (int i = 0; i < ARRAY_LEN(items); ++i)          \
        list_append(l, items[i]);                       \
}                                                       \

#endif /* GENLIST_H_ */


