#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _list{
    char *key;
    void *data; 
    struct _list *next;
} list_t;


void list_initialize(list_t *head) {

    if (!head) {
        return;
    }

    head->next = NULL;
}

int list_add(list_t *head, const char *key, void *data) {

    if (!head) {
        return -1;
    }

    list_t *tmp = (list_t *)malloc(sizeof(list_t));

    if (!tmp) {
        return -1;
    }

    tmp->key = strdup(key);

    if (!(tmp->key)) {
        return -1;
    }

    tmp->data = data;
  
    tmp->next = head->next;
    head->next = tmp;

    return 0;
}

int list_del(list_t *head, const char *key) {

    list_t *tmp, *priv;

    if (!head || !key) {
        return -1;
    }

    priv = head;
    tmp = priv->next;

    while (tmp != NULL) {

        if (strcmp(tmp->key, key) == 0) {
           priv->next = tmp->next; 
           free(tmp->key);
           free(tmp);
           tmp = NULL;
           break;
        }

        priv = tmp;
        tmp = tmp->next;
    }

    return 0;
}

void* list_find(list_t *head, const char *key) {

    list_t *tmp = NULL;

    if (!head || !key) {
        return NULL;
    }

    tmp =head->next; 

    while (tmp != NULL) {

        if (strcmp(key, tmp->key) == 0) {
            return tmp->data;
        }
        
        tmp = tmp->next;
    }

    return 0;

}

int list_destroy(list_t *head) {

    list_t *del, *tmp;

    if (!head) {
        return -1;
    }

    tmp = head->next;

    while (!tmp) {
        del = tmp;
        tmp = tmp->next;
        free(del->key);
        free(del);
    }

    head->next = NULL;

    return 0;
}

int main(void) {

    list_t head;

    list_initialize(&head);

    if (list_add(&head, "test1", (void *)"test1") != 0 ||
        list_add(&head, "test2", (void *)"test2") != 0 ||
        list_add(&head, "test3", (void *)"test3") != 0) {
        return -1;
    }

    printf("%s\n", (char *)list_find(&head, "test1"));
    printf("%s\n", (char *)list_find(&head, "test2"));

    list_del(&head, "test1");

    if (!list_find(&head, "test1")) {
        printf("delete success\n");
    }

    list_destroy(&head);

    return 0;
}
