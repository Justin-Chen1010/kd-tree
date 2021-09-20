/* parse.c
*
* Create by Yan-Ting Justin Chen (yantingjc@student.unimelb.edu.au) on 20th September 2020.
* This has the operations that are required to read->format->insert into linked list-> insert into k-d tree ->print out search results
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "func.h"


/*******************************************************************************************************/
/* This function iterates through the entire list in the k-d tree and will print 
	out the relavent information in the format required.*/
void
print_key(list_t *list, FILE *out_file){

	node_t *curr_node; 
	curr_node = list->head;

	while(curr_node!=NULL){
	/* Print the coordinates first and then put it in the same format as the example */
		fprintf(out_file, "%s %s -->", curr_node->data->x_coord, curr_node->data->y_coord); 
		fprintf(out_file, " Census year: %s ||", curr_node->data->year);
		fprintf(out_file, " Block ID: %s ||", curr_node->data->block_id);
		fprintf(out_file, " Property ID: %s ||", curr_node->data->property_id);
		fprintf(out_file, " Base property ID: %s ||", curr_node->data->base_property_id);
		fprintf(out_file, " CLUE small area: %s ||", curr_node->data->clue_small_area);
		fprintf(out_file, " Trading Name: %s ||", curr_node->data->trading_name);
		fprintf(out_file, " Industry (ANZSIC4) code: %s ||", curr_node->data->industry_code);
		fprintf(out_file, " Industry (ANZSIC4) description: %s ||", curr_node->data->industry_description);
		fprintf(out_file, " x coordinate: %s ||", curr_node->data->x_coord);
		fprintf(out_file, " y coordinate: %s ||", curr_node->data->y_coord);
		fprintf(out_file, " Location: %s || \n", curr_node->data->location);
		/* Print the node */
		curr_node = curr_node->next;
	}
}

/*******************************************************************************************************/
/* This function extracts information from the file fp, then reformats the string so that it can be
   put into the correct nodes then inserted into a linked list. It also calls the bst_insert function
   which puts the list and node into a k-d tree structure.*/
   
kdTree_t *
parse_string(kdTree_t *parent, FILE *fp, FILE *out_file){
	
	int temp_len;
    char temp[MAX_CHAR];
	char processed[MAX_CHAR]; 
	data_t *curr;
	
	
	/*Consume the first line */
	fgets(temp, MAX_CHAR, fp);
	
	
    while(fgets(temp, MAX_CHAR, fp)){
		curr = (data_t *)calloc(1, sizeof(data_t));
		assert(curr!=NULL);
        int i, j;
        int is_quote=0;
        temp_len = strlen(temp);
        char x;
		
		/*Removes carriage returns and new lines at the end of the file*/
		if(temp[temp_len-2] == '\r'){
			temp[temp_len-2] = '\0';
		}
		else if(temp[temp_len-1] == '\n'){
			temp[temp_len-1] = '\0';
		}
		
		/*Reads the data into a temporary array and then formats it*/
        for(i=0; temp[i]!= '\0'; i++){
            int quote_changed = 0;
            x = temp[i]; 
            if(temp[i] == '"' && is_quote==1 && quote_changed == 0){
                is_quote = 0;
                quote_changed = 1;
            }
            if(temp[i] == '"' && is_quote==0 && quote_changed == 0){
                is_quote = 1;
                quote_changed = 1;
            }
            
            if(x == '"' && temp[i] =='"'){
                for(j=i; j<temp_len; j++){
                    temp[j] = temp[j+1];
                }
            }
            if(temp[i] == ',' && is_quote==0){
                temp[i] = '\n';
            }
        }

		
		/*Copies the formatted array into a temporary buffer*/
		for(i=0; i<temp_len; i++){
			processed[i] = temp[i];
		}
		
		/*Puts all of the data into the data_t type and then insert it into the list 
		  Doing all of this as it is being read line by line to ensure consistentcy*/
		
		/* Calloc all 11 */
		curr->year = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->year != NULL);
		
		curr->block_id = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->block_id != NULL);
		
		curr->property_id = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->property_id !=NULL);
		
		curr->base_property_id = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->base_property_id !=NULL);
		
		curr->clue_small_area = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->clue_small_area != NULL);
		
		curr->trading_name = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->trading_name != NULL);
		
		curr->industry_code = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->industry_code != NULL);
		
		curr->industry_description = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->industry_description != NULL);
		
		curr->x_coord = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->x_coord != NULL);
		
		curr->y_coord = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->y_coord != NULL);
		
		curr->location = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->location != NULL);
		
		
		int z = 0;
		i = 0;
		/*Read into the respective arrays then realloc with a +1 because we need the nullbyte at the end to do the comparison*/
		while(processed[i] != '\n'){
			curr->year[z] = processed[i];
			i++;
			z++;
		} 
		curr->year = (char *)realloc(curr->year, strlen(curr->year)+1);
		assert(curr->year != NULL);
		i++;
		z=0;	
		/*Need to iterate i to skip over the new line that let it exit the first loop, then reset z.
		  The reason why we are checking for new line is because I put a new line in the processed 
		  buffer every single time I had to remove a comma. This way we split the attributes up correctly.*/

		while(processed[i] != '\n'){
			curr->block_id[z] = processed[i];
			i++;
			z++;
		} 
		curr->block_id = (char *)realloc(curr->block_id, strlen(curr->block_id)+1);
		assert(curr->block_id != NULL);
		i++;
		z=0;
		
		while(processed[i] != '\n'){
			curr->property_id[z] = processed[i];
			i++;
			z++;
		} 
		curr->property_id = (char *)realloc(curr->property_id, strlen(curr->property_id)+1);
		assert(curr->property_id !=NULL);
		i++;
		z=0;

		while(processed[i] != '\n'){
			curr->base_property_id[z] = processed[i];
			i++;
			z++;
		}
		curr->base_property_id = (char *)realloc(curr->base_property_id, strlen(curr->base_property_id)+1);
		assert(curr->base_property_id !=NULL);
		i++;
		z=0;
		
		while(processed[i] != '\n'){
			curr->clue_small_area[z] = processed[i];
			i++;
			z++;
		} 
		curr->clue_small_area = (char *)realloc(curr->clue_small_area, strlen(curr->clue_small_area)+1);
		assert(curr->clue_small_area != NULL);
		i++;
		z=0;
		while(processed[i] != '\n'){
			curr->trading_name[z] = processed[i];
			i++;
			z++;
		} 
		curr->trading_name = (char *)realloc(curr->trading_name, strlen(curr->trading_name)+1);
		assert(curr->trading_name != NULL);
		i++;
		z=0;
		while(processed[i] != '\n'){
			curr->industry_code[z] = processed[i];
			i++;
			z++;
		} 
		curr->industry_code = (char *)realloc(curr->industry_code, strlen(curr->industry_code)+1);
		assert(curr->industry_code != NULL);
		i++;
		z=0;
		
		while(processed[i] != '\n'){
			curr->industry_description[z] = processed[i];
			i++;
			z++;
		} 
		curr->industry_description = (char *)realloc(curr->industry_description, strlen(curr->industry_description)+1);
		assert(curr->industry_description != NULL);
		i++;
		z=0;
		
		while(processed[i] != '\n'){
			curr->x_coord[z] = processed[i];
			i++;
			z++;
		} 
		curr->x_coord = (char *)realloc(curr->x_coord, strlen(curr->x_coord)+1);
		assert(curr->x_coord != NULL);
		i++;
		z=0;
		
		while(processed[i] != '\n'){
			curr->y_coord[z] = processed[i];
			i++;
			z++;
		}
		curr->y_coord = (char *)realloc(curr->y_coord, strlen(curr->y_coord)+1);
		assert(curr->y_coord != NULL);
		i++;
		z=0;
		while(processed[i] != '\0'){
			curr->location[z] = processed[i];
			i++;
			z++;
		} 
		curr->location = (char *)realloc(curr->location, strlen(curr->location)+1);
		assert(curr->location != NULL);
		/* After the insertion of the data into the respective arrays inside the data_t structure,
		   plug it into the insert function which will create a list and a new node and insert the
		   data into the node then finally into the k-d tree at the end.*/
		parent = bstInsert(parent, curr, 0);
	}
	return parent;
}
/***************************************************************************************/
