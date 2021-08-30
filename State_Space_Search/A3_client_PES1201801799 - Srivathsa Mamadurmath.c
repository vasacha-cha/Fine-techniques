#include <stdio.h>
#include "A3_header_PES1201801799.h"

int main()
{	
	int D, E, F;
	int P, Q, R;
	int X, Y, Z;
	scanf("%d %d %d",&D, &E, &F);
	scanf("%d %d %d",&P, &Q, &R);
	scanf("%d %d %d",&X, &Y, &Z);
	state_t start;
	state_t goal;
	
	void (*move[])(const state_t*, state_t*, int, int ,int ) = {
		moveAB,
		moveAC,
		moveBA,
		moveBC,
		moveCA,
		moveCB
	};
	
	set_state(&start, P, Q, R);
	set_state(&goal, X, Y, Z);
	list_t mylist;
	init_list(&mylist);
	add_at_end(&mylist, &start);
	int is_soln = 0;
	state_t temp;
	int fn_index;
	int count=0;//for number of solutions
	//start from P Q R
	//check if solution
	//if not, add to list
	//continue till solution is found
	//if all transitions are done, backtrack
	//display list if solution found
	while(mylist.tail)//for all solutions, backtrack till non repeated state (branch). Continue till initial state is removed from list.
	{	count++;
		is_soln=0;
		while(! is_soln && mylist.tail)
		{
			fn_index = mylist.tail->st.fn_index;
			
			move[fn_index](&mylist.tail->st, &temp, D, E, F);
			if(! is_repeated(&mylist, &temp))
			{
				add_at_end(&mylist, &temp);
				is_soln = are_same(&temp, &goal);
			}
			else
			{
				while( mylist.tail && ++mylist.tail->st.fn_index == 6)
				{
					remove_at_end(&mylist);
				}
			}
		}
		
		disp_list(&mylist);
		printf("\n\n");
	}
	
	printf("Number of solutions: %d \n",--count);
}