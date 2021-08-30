#include <stdlib.h>
#include <stdio.h>

typedef struct book{
    unsigned mem;                       //Holds the amount of free/allocated memory bytes
    char free;                          //To check if the memory is free(1) or not(0)
    struct book *link;                  //Pointer to point to the next book structure
}book;

book *bk;                               //Global book structure variable

char *p;                                //Theoritical memory array pointer
int size;                               //Global size

int book_size = sizeof(book);           //Holds the size of the book structure for calculation

void allocate(int n){           
    p = (char*)malloc(sizeof(char)*n);  //Allocating memory to the char pointer
    bk = (book*)p;                      //Explicit type cnvertion to book structure
    bk->mem = n - book_size;            
    bk->link = NULL;
    bk->free = 1;
} //function to allocate memory for the global array p, n number of bytes long.

void* mymalloc(int size){
    book *temp = bk;
    book *maxTemp = NULL;
    unsigned max = book_size;           //Used to calculate the largest free space available
    
    while(temp != NULL){                //finding maximum free space 
        if((max <= (temp->mem)) && ((temp->free) == 1)){
            maxTemp = temp;             //maxTemp holds the address of the book with highest free space available
            max = temp->mem;
        }
        temp = temp->link;
    }                                 
    
    
    if(size <= maxTemp->mem)            //Proceed only if the given size is less than or equal to the available free space
    {if(maxTemp != NULL  && (max > (book_size + size))){//Allocate the given size
        temp = (book*)((char*)maxTemp +book_size + size);
        temp->mem = maxTemp->mem - book_size - size;
        temp->free = 1;
        maxTemp->free = 0;
        temp->link = maxTemp->link;     
        maxTemp->link = temp;
        maxTemp->mem = size;
    }else if(maxTemp != NULL){          //If the size is not fesiable for a new book structure with atleast one block free
        maxTemp->free = 0;              //allocate the remaining blocks to the previous(here the current) one
    }else return NULL;                  //return NULL if memory can't be allocated

    return (void*)((char*)maxTemp + book_size); //Since maxTemp holds the address of the book structure we return
                                                //the free space following that
    }
} //function to allocate a block of size "size" from p

void myfree(void *b){
    if(b == NULL){                      //return NULL if a NULL pointer is passed
        return;
    }
    b = (void*)((char*)b - book_size);  //Address of book structure is b - book_size, since b is the address of the free memory
    book* prev = NULL;
    book* pres = bk;

    while(pres != NULL && b != pres){   //Loop to find the memory book that needs to free the allocated blocks
        prev = pres;
        pres = pres->link;
    }

    if(b == bk && bk->free == 0){       //If the memory to be freed is the starting memory itself
        if(pres->link != NULL && pres->link->free == 1){      //If next memory is also free merge it with the present one
            pres->mem += pres->link->mem + book_size;
            pres->link = pres->link->link;
            pres->free = 1;
        }else{
            pres->free = 1;
        }
        return;
    }

    if(prev != NULL){                   
        if(prev->free == 1){            //If previous memory is also free merge it with the present one 
            if(pres->link != NULL && pres->link->free == 1){//If the next memory is also free merge previous, present and next memories
                prev->mem += pres->link->mem + book_size + pres->mem + book_size;
                prev->link = pres->link->link;
            }else{                      //Else only merge the present with the previous memory
                prev->mem += pres->mem + book_size;
                prev->link = pres->link;
            }
        }else if(pres->link != NULL && pres->link->free == 1){//If next memory is also free merge it with the present one 
                if(prev->free == 1){//If the previous memory is also free merge previous, present and next memories
                    prev->mem += pres->link->mem + book_size + pres->mem + book_size;
                    prev->link = pres->link->link;
                }else{                  //Else only merge the present with the next memory
                    pres->mem += pres->link->mem + book_size;
                    pres->link = pres->link->link;
                    pres->free = 1;
                } 
        }else{
            pres->free = 1;             //Else free the current memory
        }
    }
} //free the block pointed to by the parameter

void print_book(){
    printf("%u",book_size);
} // prints bytes used by the bookkeeping structure

void display_mem_map(){
    book *temp = bk;
    printf("start_addr\tblock_in_bytes\tstatus\n");
    while(temp != NULL){

        printf("%d\t\t%u\t\t%s\n",(int)((char*)temp - p),book_size,"book");
        printf("%d\t\t%u\t\t%s\n",(int)((char*)temp - p + book_size),temp->mem,(temp->free==1)?"free":"allocated");
        temp = temp->link;
    }
} // prints the memory map
