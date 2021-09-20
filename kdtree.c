/* kdtree.c
*
* Create by Yan-Ting Justin Chen (yantingjc@student.unimelb.edu.au) on 20th September 2020.
* This has the kdTree operations that include a recursive insert as well as a recursive neighbor search
* This also has a search function that takes user input and searches through the tree and print the results 
* out in the specified format. 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "func.h"

/***************************************************************************************/
/*This function recursively inserts the kdtree, in the base case where the current node
  is NULL, it will calloc a new tree and create a new list putting the data in the tree
  the tree structure has been modified to take a list rather than a data/content parameter */
kdTree_t *bstInsert(kdTree_t *parent, data_t *data, int level){
	/* Base case, it checks if current node is NULL, then creates a new tree with the 
	   data inserted into a node into a list into the tree struct.*/
    if(parent == NULL){
        kdTree_t *child = (kdTree_t *)calloc(1, sizeof(kdTree_t));
		assert(child!=NULL);
        child->list = make_empty_list();
		child->list = insert_at_foot(child->list, data);
        return child;
    }
	
	/* Does modulo 2 to decide which coordinate to do on what level, in this case
	   check on the x level for the 5 possible cases, x is smaller or bigger. Then
	   for X is the same check whether its an exact match otherwise insert left or right*/
	if(level%2 == 0){

		if (atof(parent->list->head->data->x_coord) < atof(data->x_coord)){
			parent->right = bstInsert(parent->right, data, level+1);
		}
		else if(atof(parent->list->head->data->x_coord) > atof(data->x_coord)){
			parent->left = bstInsert(parent->left, data, level+1);
		}
		else{ /* If X is the same check for Y.*/
			if(atof(parent->list->head->data->y_coord) == atof(data->y_coord)){
				insert_at_foot(parent->list, data);
				return parent; 
				/* Adds to the list on exact match else move left or right depending on other parameter */
			}
			else if(atof(parent->list->head->data->y_coord) < atof(data->y_coord)){
				parent->right = bstInsert(parent->right, data, level+1);
			}
			else if(atof(parent->list->head->data->y_coord) > atof(data->y_coord)){
				parent->left = bstInsert(parent->left, data, level+1);
			}
		}
	}
	/* For comparison on the y level */
	else if(level%2 == 1) {
		if (atof(parent->list->head->data->y_coord) < atof(data->y_coord)){
			parent->right = bstInsert(parent->right, data, level+1);
		}
		else if(atof(parent->list->head->data->y_coord) > atof(data->y_coord)){
			parent->left = bstInsert(parent->left, data, level+1);
		}
		else{ /* If Y is the same then check for x*/
			if(atof(parent->list->head->data->x_coord) == atof(data->x_coord)){
				insert_at_foot(parent->list, data);
				return parent;
			}
			else if(atof(parent->list->head->data->x_coord) < atof(data->x_coord)){
				parent->right = bstInsert(parent->right, data, level+1);
			}
			else if(atof(parent->list->head->data->x_coord) >  atof(data->x_coord)){
				parent->left = bstInsert(parent->left, data, level+1);
			}
		}
	}
    return parent;  
}
/***************************************************************************************/

kdTree_t *near_neigh(kdTree_t *parent, coord_t *query, int level, int *comparisons, kdTree_t *best_match){
	/* If the current node is NULL hit the base case need to return */
	if(parent == NULL){ 
        return best_match;
    }
	
	*comparisons+=1;
	double curr_dist = dist_calc(query, parent->list->head); 
	double best_dist = dist_calc(query, best_match->list->head);
	
/* Check the distance against best_distance at every recursion assign if needed*/
	if (curr_dist < best_dist){ 
		best_match = parent;
	}
	
/* This part goes to the end of the tree, before returning from recursion */	
	if(level%2 == 0){ 
		
		if (query->x_coord > atof(parent->list->head->data->x_coord)){
			best_match = near_neigh(parent->right, query, level+1, comparisons, best_match);
		}
		else if(query->x_coord < atof(parent->list->head->data->x_coord)){
			best_match = near_neigh(parent->left, query, level+1, comparisons, best_match);
		}
		
		else{ /*If x is the same and y is bigger or equal then go right, otherwise left*/
			if(query->y_coord >= atof(parent->list->head->data->y_coord)){
				best_match = near_neigh(parent->right, query, level+1, comparisons, best_match);
			}
			else if(query->y_coord < atof(parent->list->head->data->y_coord)){
				best_match = near_neigh(parent->left, query, level+1, comparisons, best_match);
			}
		}
	}
		
	/* For comparison on the y level */
	else if(level%2 == 1) {
		
		if (query->y_coord > atof(parent->list->head->data->y_coord)){
			best_match = near_neigh(parent->right, query, level+1, comparisons, best_match);
		}
		else if(query->y_coord < atof(parent->list->head->data->y_coord)){
			best_match = near_neigh(parent->left, query, level+1, comparisons, best_match);
		}
		
		else{ /*If y is the same and x is bigger or equal then go right, otherwise left*/
			if(query->x_coord >= atof(parent->list->head->data->x_coord)){
				best_match = near_neigh(parent->right, query, level+1, comparisons, best_match);
			}
			else if(query->x_coord < atof(parent->list->head->data->x_coord)){
				best_match = near_neigh(parent->left, query, level+1, comparisons, best_match);
			}
		}
	}
	
/*Returning from recursion*/
	
	if(level%2 == 0){ 
		/* Check whether the x distance is smaller than the current best distance, to determine whether
		   it is necessary or not to traverse the other side.*/
		if(coord_diff(query, parent->list->head, level) < dist_calc(query, best_match->list->head)){
			
			if (query->x_coord > atof(parent->list->head->data->x_coord)){
				best_match = near_neigh(parent->left, query, level+1, comparisons, best_match);
			}
			else if(query->x_coord < atof(parent->list->head->data->x_coord)){
				best_match = near_neigh(parent->right, query, level+1, comparisons, best_match);
			}
		
			else{ /*If x is the same and y is bigger or equal then go right*/
				if(query->y_coord >= atof(parent->list->head->data->y_coord)){
					best_match = near_neigh(parent->left, query, level+1, comparisons, best_match);
				}
				else if(query->y_coord < atof(parent->list->head->data->y_coord)){
					best_match = near_neigh(parent->right, query, level+1, comparisons, best_match);
				}
			}
		}
	}
		
	/* For comparison on the y level */
	else if(level%2 == 1) {
		/* Check whether the y distance is smaller than the current best distance, to determine whether
		   it is necessary or not to traverse the other side.*/
		if(coord_diff(query, parent->list->head, level) < dist_calc(query, best_match->list->head)){
			if (query->y_coord > atof(parent->list->head->data->y_coord)){
				best_match = near_neigh(parent->left, query, level+1, comparisons, best_match);
			}
			else if(query->y_coord < atof(parent->list->head->data->y_coord)){
				best_match = near_neigh(parent->right, query, level+1, comparisons, best_match);
			}
			
			else{ /*If y is the same and x is bigger or equal then go right*/
				if(query->x_coord >= atof(parent->list->head->data->x_coord)){
					best_match = near_neigh(parent->left, query, level+1, comparisons, best_match);
				}
				else if(query->x_coord < atof(parent->list->head->data->x_coord)){
					best_match = near_neigh(parent->right, query, level+1, comparisons, best_match);
				}
			}
		}
	}
	return best_match;
}

/***************************************************************************************/
/* Takes the user input with scanf and store it into a coord_t consisting of x and y doubles,
   then the function calls the nearest neighbour function and returns the best match, which
   then calls the printing function that prints it in the required format then frees the query.*/
void search(kdTree_t *tree, FILE *out_file){
	coord_t *query = (coord_t *)calloc(1, sizeof(coord_t));
	assert(query!=NULL);
	int level = 0, comparisons = 0;
	kdTree_t *best_match = tree;
	while(scanf("%lf %lf", &query->x_coord, &query->y_coord) == 2){
		comparisons = 0;
		best_match = near_neigh(tree, query, level, &comparisons, best_match);
		print_key(best_match->list, out_file);
		printf("%s %s --> ", best_match->list->head->data->x_coord, best_match->list->head->data->y_coord); 
		printf("%d\n", comparisons);
	}
	free(query); 
}
/***************************************************************************************/