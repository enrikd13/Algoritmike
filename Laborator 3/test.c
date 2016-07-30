#include <stdio.h>
#include <stdlib.h>

int length =0;

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
} node;

node* create_node(int data){
    node *new_node = (node*)malloc(sizeof(node));
    if(new_node == NULL){
        fprintf (stderr, "Out of memory!!! (create_node)\n");
        exit(1);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void buildHeap(int E[]){
}


