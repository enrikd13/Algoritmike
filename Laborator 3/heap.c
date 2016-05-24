#include <stdio.h>
#include <stdlib.h>

#define NMAX 100 ; //Maksimumi i elementeve te vektorit
#define N 10 ;     //Nr i elementeve ne vektor

int rendi (int n);
void max_heap(int a[], int i);
void swap(int a[], int i, int j);
void buildHeap(int a[]);
int pred(int a[], int n, int i);

struct heap {
	int size;
	int length;
	int * data;
}heap ;

int main(){
    int i;
    heap.length=NMAX;
    heap.size=N ;
    int a[] = {0, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7}; //Vektori i elementeve (elementi me index 0 eshte mbushur per te lehtesuar punen)
    heap.data=a;
    buildHeap(heap.data);
    for(i=1; i<=heap.size; i++){
        printf("%d\t", heap.data[i]);
    }
    printf("\n\nJepni numrin per te cilin doni te gjeni paraardhesin : ");
    scanf("%d", &i);
    printf("\nParaardhesi i %d eshte %d", i, pred(heap.data, i, 1));
    
}

int pred(int a[], int n, int i){
    int l, r;
    if (i>10) return -1; 
    else{
        if (a[i]==n) return a[i] ;
        l=pred(a, n, 2*i) ; r = pred(a, n, 2*i+1) ;
        if ( a[i] <= n && a[i] > l && a[i] > r) return a[i];
        else if(l>r) return l ;
        else return r ;
    }
    
}
void max_heap1(int a[], int i){ //for(i=1; i<n/2; i++)
    if (i<1) return ;
    int max=i, y=0, r=0;
    if (a[2*i]>a[2*i+1]) max = 2*i ; else max = 2*i+1 ;
    if (a[i]<a[max]) {
        swap(a, i, max); 
        max_heap(a, i/2);
        if (a[i]<a[2*i] || a[i]< a[2*i+1])
            max_heap(a, max);
     }
}

void buildHeap(int a[]){
    int i ;
    for(i=5; i>=1; i--){
        max_heap(a, i);
    }
}

void max_heap(int a[], int i){
    int max=i;
    if (a[2*i]>a[i] && 2*i <=10) max = 2*i ; 
    if(a[2*i] < a[2*i+1] && a[2*i+1]>a[i] && 2*i+1<=10) max = 2*i+1 ;
    if (i!=max) {
        swap(a, i, max); 
        max_heap(a, max);
        
    }
}

void swap(int a[], int i, int j){
    int tmp ;
    printf("%d me %d\n", a[i], a[j]);
    tmp=a[i];
    a[i]=a[j];
    a[j]=tmp;
    
    for(i=1; i<=10; i++){
        printf("%d\t", a[i]);
    }
    printf("\n");
}

int rendi(int n){
    int i, x=2 ;
    for (i=1; n>x-1; i++)
        x*=2 ;
    return i;
}