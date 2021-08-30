#include <stdio.h>
#include <stdlib.h>
#include "assignment_2.h"

//structure defined for the list containing the greatest element followed by the other elements in te required format
typedef struct node{
	int data;
	struct node* link;
}node;

//creates a node for the list elements
static node* get_node(int a){
	node* temp = malloc(sizeof(node));
	temp->data = a;
	temp->link = NULL;
	return temp;
}

//deletion of link list which is not required
static void delete(node* p){
	node* temp = NULL;
	while(p){
		temp = p->link;
		free(p);
		p = temp;	
	}
}

//prints the linked list with header p
static void print(node* p){
	while(p){
		printf("%d ",p->data);
		p = p->link;
	}
}

//compares both the lists and deletes the unrequired list
static node* compare_list(node* a,node* b){
	print(a);
	printf("x ");
	print(b);
	printf("= ");
	if(a->data >= b->data){
		delete(b->link);
		b->link = a->link;
		a->link = b;
		return a;
	}
	else{
		delete(a->link);
		a->link = b->link;
		b->link = a;
		return b;
	}
}

static node* compare(int* a,int start,int end,int n){
	//start:starting index of the array to be compared
	//end:ending index of the array to be compared
	//n:size of array -1

	 
	if(start == n) return get_node(a[start]);
	//Send element back if array has only one element
	//occurs only at the end of the array
	
	//compare first 2 elements of the array
	printf("%d x %d = ",a[start],a[start+1]);
	node* x = get_node(a[start]);
	node* y = get_node(a[start+1]);
	
	if(x->data >= y->data) x->link = y;
	else {
		y->link = x;
		x = y;
	}
	print(x);
	printf("\n");	
	//c;count number of elements compared before
	//s,r;start and end of next comparisions
	int c = 2;
	int s = start+2;
	int r = c+s;
	
	//comparing elements using decrease and conquer
	while(s<end && s<=n){
		y = compare(a,s,r,n);
		x = compare_list(x,y);
		//merging the two required lists
		print(x);
		printf("\n");

	//change s,r,c to next comparision values
		s = r;
		c += c;
		r = s+c;
	}
	return x;
// returning the reqiured list 
}
	

void find_second_greatest(int *numbers, int length){
	node* res = compare(numbers,0, length, length-1);
	node* t = res->link;
	
	//second largest element
	int second = t->data;
	t = t->link;
	while(t){
		if(t->data > second) second = t->data;
		t = t->link;
	}
	printf("\n%d\n",second);	
}
