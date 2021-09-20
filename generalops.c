/* generalops.c
*
* Create by Yan-Ting Justin Chen (yantingjc@student.unimelb.edu.au) on 20th September 2020.
* This has the basic list operations that are needed to create a linked list, calculate the distance
* between the query and the current leaf, as well as all the freeing functions (tree, list, node, data_t etc.)
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "func.h"


/***************************************************************************************/
/* This function is provided by Alistar Moffat from taken from listops.c
   it makes an empty list. It is modified with calloc for the purpose of this assignment.
   Link to listops.c: https://people.eng.unimelb.edu.au/ammoffat/ppsaa/c/listops.c */
list_t
*make_empty_list(void) {
    list_t *list;
    list = (list_t*)calloc(1, sizeof(list_t));
    assert(list!=NULL);
	list->head = list->foot = NULL;
    return list;
}

/***************************************************************************************/
/* This is a function that I made to free the calloc'd grids inside data_t inside my node 
   structure, it is called by my free_list function which is then called recursively in my
   freeTree function*/
void free_data(data_t *curr){
		free(curr->year);		
		free(curr->block_id);		
		free(curr->property_id);		
		free(curr->base_property_id);		
		free(curr->clue_small_area);		
		free(curr->trading_name);		
		free(curr->industry_code);
		free(curr->industry_description);
		free(curr->x_coord);
		free(curr->y_coord);
		free(curr->location);
		free(curr);
}


/***************************************************************************************/
/* This function is provided by the Alistair Moffat taken from listops.c it 
   loops through and frees the calloc'd list, it is modified to free the nodes 
   specific categories for the purpose of this assignment 
   link to listops.c: https://people.eng.unimelb.edu.au/ammoffat/ppsaa/c/listops.c */

void
free_list(list_t *list) {
    node_t *curr, *prev;
    assert(list!=NULL);
    curr = list->head;
    while (curr) {
        prev = curr;
        curr = curr->next;
		free_data(prev->data);
        free(prev);
    }
    free(list);
}


/***************************************************************************************/
/* This function is provided by Alistair Moffat taken from listops.c
   This is the only function we need to insert data_t values into a node 
   into the list. It is modifed to meet the needs of the assignment
   Link: https://people.eng.unimelb.edu.au/ammoffat/ppsaa/c/listops.c */
list_t
*insert_at_foot(list_t *list, data_t *value) {
    node_t *new;
    new = (node_t*)calloc(1, sizeof(node_t));
    assert(new!=NULL);
    new->data = value;
    if (list->foot==NULL) {
        /* this is the first insertion into the list */
        list->head = list->foot = new;
    } else {
        list->foot->next = new;
        list->foot = new;
    }
    return list;
}

/***************************************************************************************/
/* This is a function that I wrote which will recursively call the function left and right
   calling my free_list function which calls a free_data function that can free all the 
   calloc'd gris inside the node_t's data_t parameter. Then finally freeing the kd itself*/
void freeTree(kdTree_t *parent){
    if(! parent){
        return;
    }
    freeTree(parent->left);
    freeTree(parent->right);
	free_list(parent->list);
    free(parent);
}

/***************************************************************************************/
/* This is a function I wrote that calculates the distance and returns it 
   since we only care about which ones bigger there is no point in square rooting it.*/
double dist_calc (coord_t *query, node_t *curr_node){
	double distance = 0;
	double x = atof(curr_node->data->x_coord) - query->x_coord;
	double squared_x_diff = x*x;
	double y = atof(curr_node->data->y_coord) - query->y_coord;
	double squared_y_diff = y*y;
	double sum = squared_x_diff + squared_y_diff;
	distance = sum;
	return distance;
}
/***************************************************************************************/
/* This function can calculate the difference between the coordinates in the backward call 
   of the tree function, it will take the level that it's on as parameter to determine which
   formula to use and which function*/
double coord_diff (coord_t *query, node_t *curr_node, int level){
	
	double diff;
	if (level%2 == 0){
		double squared_x_diff = (atof(curr_node->data->x_coord) - query->x_coord) * 
								(atof(curr_node->data->x_coord) - query->x_coord);
		diff = squared_x_diff;
	}
	else if (level%2 == 1){
		double squared_y_diff = (atof(curr_node->data->y_coord) - query->y_coord) * 
								(atof(curr_node->data->y_coord) - query->y_coord);
		diff = squared_y_diff;
	}
	return diff;
}
/***************************************************************************************/