#include <stdio.h>
#include<stdlib.h>
#include "A3_header_PES1201801799.h"

//assign values to structure variables
void set_state(state_t* ptr_state, int A, int B, int C)
{
	ptr_state->A = A;
	ptr_state->B = B;
	ptr_state->C = C;
	
	ptr_state->fn_index = 0;
}

//display structure variables
void disp_state(const state_t* ptr_state)
{
		printf(" %d %d %d\n", 
		ptr_state->A, ptr_state->B, ptr_state->C);
}

//transferring water from A to B
void moveAB(const state_t* src, state_t *dst, int A, int B, int C)
{	
	dst->A = src->A;
	dst->B = src->B;
	dst->C = src->C;
	
	if( (B - src->B) >= src->A)
	{
		dst->A = 0;
		dst->B = src->A + src->B;
	}
	else
	{
		dst->B = B;
		dst->A = src->A - (B - src-> B);
	}
	
	dst->fn_index = 0; 
}

//transferring water from A to C
void moveAC(const state_t* src, state_t *dst, int A, int B, int C)
{	
	dst->A = src->A;
	dst->B = src->B;
	dst->C = src->C;
	
	if( (C - src->C) >= src->A)
	{
		dst->A = 0;
		dst->C = src->A + src->C;
	}
	else
	{
		dst->C = C;
		dst->A = src->A - (C - src-> C);
	}

	dst->fn_index = 0; 
}

//transferring water from B to A
void moveBA(const state_t* src, state_t *dst, int A, int B, int C)
{	
	dst->A = src->A;
	dst->B = src->B;
	dst->C = src->C;

	if( (A - src->A) >= src->B)
	{
		dst->B = 0;
		dst->A = src->B + src->A;
	}
	else
	{
		dst->A = A;
		dst->B = src->B - (A - src->A);
	}

	dst->fn_index = 0; 
}

//transferring water from B to C
void moveBC(const state_t* src, state_t *dst, int A, int B, int C)
{	
	dst->A = src->A;
	dst->B = src->B;
	dst->C = src->C;

	if( (C - src->C) >= src->B)
	{
		dst->B = 0;
		dst->C = src->B + src->C;
	}
	else
	{
		dst->C = C;
		dst->B = src->B - (C - src->C);
	}

	dst->fn_index = 0; 
}

//transferring water from C to A
void moveCA(const state_t* src, state_t *dst, int A, int B, int C)
{	
	dst->A = src->A;
	dst->B = src->B;
	dst->C = src->C;

	if( (A - src->A) >= src->C)
	{
		dst->C = 0;
		dst->A = src->C + src->A;
	}
	else
	{
		dst->A = A;
		dst->C = src->C - ( A - src->A);
	}


	dst->fn_index = 0; 
}

//transferring water from C to B
void moveCB(const state_t* src, state_t *dst, int A, int B, int C)
{	
	dst->A = src->A;
	dst->B = src->B;
	dst->C = src->C;

	if( (B - src->B) >= src->C)
	{
		dst->C = 0;
		dst->B = src->C + src->B;
	}
	else
	{
		dst->B = B;
		dst->C = src->C - (B - src->B);
	}

	dst->fn_index = 0;
}

//for checking if state rached is the final state
int are_same(const state_t* lhs, const state_t* rhs)
{
	return lhs->A == rhs->A && lhs->B == rhs->B 
		&& lhs->C == rhs->C;
}


//list related functions

void init_list(list_t *ptr_list)
{
	ptr_list->head = NULL;
	ptr_list->tail = NULL;
}

void add_at_end(list_t *ptr_list, const state_t *ptr_state)
{
	node_t* temp = (node_t*)malloc(sizeof(node_t));
	temp->st = *ptr_state;
	// empty list
	if(ptr_list->head == NULL)
	{
		temp->next = NULL;
		temp->prev = ptr_list->tail;
		ptr_list->head = temp;
		ptr_list->tail = temp;
	}
	// non-empty list
	else
	{
		temp->next = NULL;
		temp->prev = ptr_list->tail;
		ptr_list->tail->next = temp;
		ptr_list->tail = temp;
	}
}

void remove_at_end(list_t *ptr_list)
{
	// for an empty list
	if(ptr_list->head == NULL)
	{
		printf("empty list\n");
	}
	
	// for list with one node
	else if(ptr_list->head == ptr_list->tail)
	{
		node_t* temp = ptr_list->tail;
		ptr_list->tail = temp->prev;
		ptr_list->head = NULL;
		free(temp);
	}

	// for list with multiple nodes
	else
	{
		node_t* temp = ptr_list->tail;
		ptr_list->tail = temp->prev;
		ptr_list->tail->next = NULL;
		free(temp);
	}
}

void disp_list(const list_t *ptr_list)
{
	node_t* temp = ptr_list->head;
	while(temp)
	{	
		disp_state(&temp->st);
		temp = temp->next;
	}
}

//to check if the state has already occured in the list
int is_repeated(const list_t *ptr_list, const state_t *ptr_state)
{
	node_t* temp = ptr_list->head;
	while(temp)
	{	
		if (are_same(&temp->st, ptr_state))
			return 1;
		temp = temp->next;
	}
	return 0;
}