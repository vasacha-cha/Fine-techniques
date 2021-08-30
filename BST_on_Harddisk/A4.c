//implementation file
#include<stdio.h>
#include <stdlib.h>
#include"assignment_4.h"

FILE* init_tree(const char* filename)
{
    FILE* fp = fopen(filename, "r+");
    tree_t t;
    if(fp == NULL)//check if there's a pre-existing file with the same name.
    {
		fp = fopen(filename, "w");
		t.free_head = 0;
		t.root = -1;
		fwrite(&t, sizeof(tree_t), 1, fp);
		fclose(fp);
		fp = fopen(filename, "r+");
    }
    return fp;//return an opened file pointer. 
}

//calls fclose() on file ponter
void close_tree(FILE *fp)
{
	fclose(fp);
}


void insert_key(int key, FILE *fp)
{
    node_t t_node, p_node, u_node;
    tree_t t;
    int temp;
    int tempo;
    t_node.key = key;
    t_node.left_offset = -1;
    t_node.right_offset = -1;
     
    fseek(fp,0,SEEK_SET); 
    fread(&t, sizeof(tree_t), 1, fp);
   
    //find offset in file
   
    //check for deleted nodes
    if(t.free_head == 0) //no deleted nodes
    {
        fseek(fp, 0, SEEK_END);
        temp = ftell(fp);
    }

    //deleted nodes present
    else
    {
        temp = t.free_head;
        fseek(fp, temp, SEEK_SET);
        fread(&p_node, sizeof(node_t), 1, fp); 
        t.free_head = p_node.left_offset;
    }

    //inserting into tree

    int u;
    //Empty tree
    if(t.root == -1)
    {  
        t.root = temp;
        fseek(fp,temp,SEEK_SET);				
        fwrite(&t_node, sizeof(node_t), 1, fp);
    }

    //Non empty tree
	//find position first and then write into file
	//update tree structure after inserting
    else
    {  
        tempo = t.root;
        u = 0;
		fseek(fp, tempo, SEEK_SET); 
		fread(&p_node, sizeof(node_t), 1, fp);
        while(tempo != -1 && p_node.key!=key)
        {  
			fseek(fp, tempo, SEEK_SET); 
			fread(&p_node, sizeof(node_t), 1, fp);
            u = tempo; 
            if(key < p_node.key)
            {  
                tempo = p_node.left_offset;    
            }
            else
            {  
                tempo = p_node.right_offset;
            }
           
        }
		
		if(key == p_node.key) return;
       
        
        if(key < p_node.key)
        {  
            p_node.left_offset = temp;
        }
        else
        {  
            p_node.right_offset = temp;
        }
       
    fseek(fp,u,SEEK_SET);
    fwrite(&p_node,sizeof(node_t),1,fp);
   
    }
    fseek(fp, temp, SEEK_SET);
    fwrite(&t_node, sizeof(node_t), 1, fp);
   
    fseek(fp,0,SEEK_SET);
    fwrite(&t,sizeof(tree_t),1,fp);  
	
}

//takes node and file pointer as parameters
//Recursively calls itself to display tree in inorder
void inorder(node_t *t_node, FILE *fp)
{	
	
	int key = t_node->key;
	int l = t_node->left_offset;
    int r = t_node->right_offset;

    if(l!=-1)
    {
     fseek(fp, l, SEEK_SET);
     fread(t_node, sizeof(node_t), 1, fp);
	 inorder(t_node, fp);
    }

    printf("%d ", key);

    if(r!=-1)
    {
     fseek(fp, r, SEEK_SET);
     fread(t_node, sizeof(node_t), 1, fp);
	 inorder(t_node, fp);
    } 
}

//calls inorder() after reading tree and root
void display_inorder(FILE *fp)
{  
	printf("\n");
    tree_t t;
    node_t t_node;
   
    
    fseek(fp, 0, SEEK_SET);
    fread(&t, sizeof(tree_t), 1, fp);    
    if(t.root == -1) return;
       
    fseek(fp,t.root,SEEK_SET);        
    fread(&t_node, sizeof(node_t), 1, fp);
   
	inorder(&t_node, fp);
	printf("\n");
}

//takes node and file pointer as parameters
//Recursively calls itself to display tree in preorder 
void preorder(node_t *t_node, FILE *fp)
{
	int l = t_node->left_offset;
    int r = t_node->right_offset;

	printf("%d ", t_node->key); 

    if(l!=-1)
    {
     fseek(fp, l, SEEK_SET);
     fread(t_node, sizeof(node_t), 1, fp);
	 preorder(t_node, fp);
    }

    if(r!=-1)
    {
     fseek(fp, r, SEEK_SET);
     fread(t_node, sizeof(node_t), 1, fp);
	 preorder(t_node, fp);
    } 
}

//calls preorder() after reading tree and root
void display_preorder(FILE *fp)
{	
	printf("\n");	
    tree_t t;
    node_t t_node;
   
    
    fseek(fp, 0, SEEK_SET);
    fread(&t, sizeof(tree_t), 1, fp);    
    if(t.root == -1) return;
       
    fseek(fp,t.root,SEEK_SET);        
    fread(&t_node, sizeof(node_t), 1, fp);
   
	preorder(&t_node, fp);
	printf("\n");
   
}

//find position of node to be deleted
//delete if found
//return if not found
//while deletion: check if node is root node and delete accordingly
//update tree structure
void delete_key(int key, FILE *fp)
{
    int tempo;
    int u = -2;
    int rep, prep, cprep;
    int found;
    node_t t_node, p_node, rep_node, prep_node, cprep_node, root_node;
    tree_t t;
    
    
    fseek(fp, 0, SEEK_SET);
    fread(&t, sizeof(tree_t), 1, fp);
    
    fseek(fp, t.root, SEEK_SET);
    fread(&root_node, sizeof(root_node), 1, fp);
    
    tempo = t.root;
    fseek(fp, t.root, SEEK_SET);
    
	//finding position of node to be deleted
    while (tempo != -1)
    {   
        fread(&t_node, sizeof(node_t), 1, fp);
        fseek(fp, tempo, SEEK_SET);
        
        if(key == t_node.key)
        {
            found = ftell(fp);
            break;
        }

        else
        {
            u = tempo;
            if(key < t_node.key)
            {
               tempo = t_node.left_offset;
            }
            else if(key > t_node.key)
            {
                tempo = t_node.right_offset;
            }
            
            fseek(fp, tempo, SEEK_SET);
        }
        
    }

	//didn't find key, return
    if(tempo == -1) return;	

    //deletion part
    fseek(fp, found, SEEK_SET);
    fread(&p_node, sizeof(node_t), 1, fp);

    if(u != -2)
    {   
        fseek(fp, u, SEEK_SET);
        fread(&t_node, sizeof(node_t), 1, fp);
    }
    
	// no subtrees
    if((p_node.left_offset == -1) && (p_node.right_offset == -1))
    {
        if(key == root_node.key)
        {
            t.root = -1;
        }
        
        else
        {
        
            if(t_node.left_offset == tempo)
            {
                t_node.left_offset = -1;
            }
            else
            {
                t_node.right_offset = -1;
            }
			fseek(fp,u,SEEK_SET);
			fwrite(&t_node,sizeof(node_t),1,fp);
        }

        p_node.left_offset = p_node.right_offset = t.free_head;
        t.free_head = found;
	}
	
	//right subtree present
    else if((p_node.left_offset == -1) && (p_node.right_offset != -1))
    {
        rep = p_node.right_offset;
        
		if(key == root_node.key)
        {
            t.root = p_node.right_offset;
        }
        else
        {
		    if(t_node.left_offset == tempo)
		    {
		        t_node.left_offset = rep;
		    }
		    else
		    {
		        t_node.right_offset = rep;
		    }
			fseek(fp,u,SEEK_SET);
			fwrite(&t_node,sizeof(node_t),1,fp);
		}

        
        p_node.left_offset = p_node.right_offset = t.free_head;
        t.free_head = found;
    
    }

	//left subtree present
     else if((p_node.left_offset != -1) && (p_node.right_offset == -1))
    {
        rep = p_node.left_offset;

        if(key == root_node.key)
        {
            t.root = p_node.left_offset;
        }
        else
        {
		    if(t_node.left_offset == tempo)
		    {
		        t_node.left_offset = rep;
		    }
		    else
		    {
		        t_node.right_offset = rep;
		    }
			fseek(fp,u,SEEK_SET);
			fwrite(&t_node,sizeof(node_t),1,fp);
		}

        p_node.left_offset = p_node.right_offset = t.free_head;
        t.free_head = found;
    }  

	//use inorder succesor to replace node to be deleted
    else// if((p_node.left_offset != -1) && (p_node.right_offset != -1))
    {
    	prep = -1;
    	
        rep = p_node.right_offset;
        
        fseek(fp , rep, SEEK_SET);
        fread(&rep_node, sizeof(node_t), 1, fp);

		//find inorder succesor 
        while(rep_node.left_offset != -1)
        {
            prep = rep;
            rep = rep_node.left_offset;
            
            fseek(fp, prep, SEEK_SET);
            fread(&prep_node, sizeof(node_t), 1, fp);
            
            fseek(fp, rep, SEEK_SET);
            fread(&rep_node, sizeof(node_t), 1, fp);
        }
        
        cprep = rep_node.right_offset;
        
		if(prep == -1)
		{
			p_node.right_offset = cprep;
		}
		else
		{        
        	prep_node.left_offset = cprep;
        	fseek(fp,prep,SEEK_SET);
        	fwrite(&prep_node,sizeof(node_t),1,fp);
        }
        
        p_node.key = rep_node.key;
        
        rep_node.left_offset = t.free_head;
        rep_node.right_offset = t.free_head;
        t.free_head = rep;
        
        fseek(fp,rep,SEEK_SET);
        fwrite(&rep_node,sizeof(node_t),1,fp);
    }
    
    fseek(fp,0,SEEK_SET);
    fwrite(&t,sizeof(tree_t),1,fp);
    
    fseek(fp,found,SEEK_SET);
    fwrite(&p_node,sizeof(node_t),1,fp);
        
}
