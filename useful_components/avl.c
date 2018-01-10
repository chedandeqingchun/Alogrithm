#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

struct Node {
    int key;
    int height;
    struct Node *left, *right;
};

int max(int n1, int n2) {

    if (n1 < n2) {
        return n2;
    }

    return n1;
}


int getHeight(struct Node *node) {

    if (!node) {
        return 0;
    } 

    return node->height;
}


int getBalance(struct Node *node) {

    if (!node) {
        return 0;
    }

    return ((node->left->height) - (node->right->height));
}

struct Node* ll(struct Node *node) {

    if (!node) {
        return NULL;
    }

    struct Node *x = node->left;
    node->left = x->right;
    x->right = node; 
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    return x;
}

struct Node* rr(struct Node *node) {
   
    if (!node) {
        return NULL;
    }
    
    struct Node *x = node->right;
    node->right = x->left;
    x->left = node;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    return x;
}


struct Node* lr(struct Node *node) {

    if (!node) {
        return NULL;
    } 

    struct Node *x = node->left;
    node->left = rr(x); 
    return ll(node);
}

struct Node* rl(struct  Node *node) {

    if (!node) {
        return NULL;
    }

    struct  Node *x = node->right;
    node->right = ll(x);
    return rr(node);
}

struct Node* insert_real(int key, struct Node *node) {

    if (!node) {
        node = (struct Node *)malloc(sizeof(struct Node));
        if (!node) {
            return NULL;
        }

        node->left = NULL;
        node->right = NULL;
        node->height = 1;
        node->key = key;
        return node;
    } 

    if (key < node->key) {
        node->left = insert_real(key, node->left);
    } else if (key > node->key) {
        node->right = insert_real(key, node->right);
    } else {
        return node;
    }

    node->height = max(node->left->height, node->right->height) + 1;

    /* adjust node */
    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0) {//ll 
        node  = ll(node);
    }

    if (balance > 1 && getBalance(node->right) >= 0) {//lr
        node = rr(node);
    }

    if (balance < 1 && getBalance(node->left) > 0) {//rl
        node = rl(node);
    }

    if (balance < 1 && getBalance(node->right) < 0) {//rr
        node = rr(node);
    }

    return node;
}

struct Node* erase_real(struct Node *node, int key) {

    if (!node) {
        return NULL;
    }

    if (key < node->key) {
        node->left = erase_real(node->left, key); 
    } else if (key > node->key) {
        node->right = erase_real(node->right, key);
    } else {

        if (node->left != NULL && node->right != NULL) {
            struct Node *x = node->right;            

            while (!(x->left)) {
                x = x->left;
            }

            node->key = x->key;
            node->right = erase_real(x,  key);
        } else {//delte node
            struct Node *tmp = node;
            node = node->left?node->left:node->right;
            free(tmp), tmp = NULL;

            if (node == NULL) {
                return NULL;
            }    
        }

    }

    //adjust balance 
   
     node->height = max(node->left->height, node->right->height) + 1;

    /* adjust node */
    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0) {//ll 
        node  = ll(node);
    }

    if (balance > 1 && getBalance(node->right) >= 0) {//lr
        node = rr(node);
    }

    if (balance < 1 && getBalance(node->left) > 0) {//rl
        node = rl(node);
    }

    if (balance < 1 && getBalance(node->right) < 0) {//rr
        node = rr(node);
    }

    return node;
}


struct Node * findEle(struct Node *root, int key) {

    if (!root) {
        return NULL;
    }

    struct Node *tmp = root; 

    while (tmp) {
        if (tmp->key > key) {
            tmp = tmp->left;     
        } else if (tmp->key < key) {
            tmp = tmp->right;
        } else {
            return tmp;
        }
    }

    return tmp;
}


int main(void) {

    struct Node *root = NULL;

    insert_real(5, root); 
    insert_real(10, root);
    insert_real(1, root);
    insert_real(7, root);
    insert_real(6, root);

    struct Node *tmp = findEle(root, 1);
    printf("key is %d\n", tmp->key);


    return 0;
}
