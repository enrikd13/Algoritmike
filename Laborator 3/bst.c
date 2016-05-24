#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
} node;

node* krijo_node(int data){
    node *new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

node* shto_node(node *root, int data){
    if(root == NULL){
        root = krijo_node(data);
    }
    else{
        int majte  = 0;
        node* leviz = root;
        node* prind   = NULL;
 
        while(leviz != NULL){
            prind = leviz;
            if(data < leviz->data){
                majte = 1;
                leviz = leviz->left;
            }
            else if(data > leviz->data){
                majte = 0;
                leviz = leviz->right;
            }
        }
        if(majte)
            prind->left = krijo_node(data);
        else
            prind->right = krijo_node(data);
    }
    return root;
}

void printoInorder(struct node* node){
	if (node == NULL)
		return;

	printoInorder(node->left);

	printf("%d ", node->data); 

	printoInorder(node->right);
}

node* pred(int n, node *root) {
    node * n1, * n2 ;
    n1=root ;
    while(n1!=NULL){
    	if (n1->data == n ) break;
        if(n < n1->data) { 
            printf("Zhvendosje Majtas\n"); 
            if (n1->left != NULL) n1 = n1->left;
            else break ; //
            }
        
        if(n > n1->data ){
            printf("Zhvendosje djathtas\n");
            n2 = n1; //Meqe do kalojme djathtas fillimisht ruajme vleren e prindit , pasi ai mund te jete pred .
            if (n1->right != NULL) n1=n1->right;
            else break ;
        }
        
    }
    if(n1->data<=n) return n1 ;
    else return n2;
}


int main(){
    node * root = krijo_node(25);
    shto_node(root, 10);
    shto_node(root, 60);
    shto_node(root, 5);
    shto_node(root, 20);
    shto_node(root, 15);
    shto_node(root, 35);
    shto_node(root, 65);
    shto_node(root, 45);
    printf("Pema e printuar ne InOrder eshte :\n");
    printoInorder(root);
    int n; 
    printf("\nJepni numrin te cilit doni ti gjeni paraardhesin :");
    scanf("%d", &n);
    node * test = pred(n, root);
    printf("%d", test->data);
}

