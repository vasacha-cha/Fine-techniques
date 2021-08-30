#ifndef STATE_H
#define STATE_H
struct state
{
	int A; 
	int B; 
	int C; 
	
	// implementation field
	int fn_index;
	
};
typedef struct state state_t;
struct node
{
	state_t st;
	struct node* prev;
	struct node* next;
};

typedef struct node node_t;
struct list
{
	node_t* head;
	node_t* tail;
};
typedef struct list list_t;


void set_state(state_t* ptr_state, int A, int B, int C);
void disp_state(const state_t* ptr_state);

void moveAB(const state_t* src, state_t* dst, int A, int B, int C);
void moveAC(const state_t* src, state_t* dst, int A, int B, int C);
void moveBA(const state_t* src, state_t* dst, int A, int B, int C);
void moveBC(const state_t* src, state_t* dst, int A, int B, int C);
void moveCA(const state_t* src, state_t* dst, int A, int B, int C);
void moveCB(const state_t* src, state_t* dst, int A, int B, int C);

int are_same(const state_t* lhs, const state_t* rhs);



void init_list(list_t *ptr_list);
void add_at_end(list_t *ptr_list, const state_t *ptr_state);
void remove_at_end(list_t *ptr_list);
void disp_list(const list_t *ptr_list);
int is_repeated(const list_t *ptr_list, const state_t *ptr_state);

#endif
