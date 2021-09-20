/* Assignment2.c
*
* Create by Yan-Ting Justin Chen (yantingjc@student.unimelb.edu.au) on 20th September 2020.
* This is the main function that includes the header file linking to my 2 other function files.
*
* To run the program type:
* ./dict results/temp_input results/temp_results < results/temp_stdin
* Made up of 5 files including this one
* -- Assignment2.c The main file that refers to the headerfile that refers to the two function files
* -- generalops.c includes the operations that do with lists, distance and freeing.
* -- parse.c includes the operations that are required to read->format->insert into linked list-> take input -> search key in dict
* -- func.h includes all the function prototypes as well as struct prototypes
* -- kdtree.c includes all the functions that have to do with the construction and searching of a kd tree.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "func.h"


int main (int argc, char **argv){
	
	FILE *out_file = fopen(argv[2], "w");
    FILE *fp = fopen (argv[1] , "r");
    if (fp == NULL){
        printf("File not found");
        return 0;
    }
	kdTree_t *kdTree = NULL;
	kdTree = parse_string(kdTree, fp, out_file);	

	search(kdTree, out_file);

	freeTree(kdTree);
	fclose(fp);
	fclose(out_file);
	return 0;
}
