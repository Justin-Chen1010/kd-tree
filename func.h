#define MAX_FIELD 128+1
#define MAX_CHAR 512+1
#define TOTAL_FIELDS 11
#include <stdio.h>

/* Struct Prototypes */
/*****************************************************************************/
typedef struct {
    char *year;
	char *block_id;
	char *property_id;
	char *base_property_id;
	char *clue_small_area;
	char *trading_name;
	char *industry_code;
	char *industry_description;
	char *x_coord;
	char *y_coord;
	char *location;
} grid_cell_t;
typedef grid_cell_t data_t;

/*****************************************************************************/
typedef struct node node_t;
struct node {
    data_t *data;
    node_t *next;
};
/*****************************************************************************/
typedef struct {
    node_t *head;
    node_t *foot;
} list_t;

/*****************************************************************************/
typedef struct {
    double x_coord;
	double y_coord;
} coord_t;
/*****************************************************************************/

typedef struct bst {
    list_t *list;
    struct bst *left;
    struct bst *right;
}kdTree_t;
/*****************************************************************************/
/* Function Prototypes */
list_t *make_empty_list(void);
list_t *insert_at_foot(list_t *list, data_t *value);

double dist_calc (coord_t *query, node_t *curr_node);
double coord_diff (coord_t *query, node_t *curr_node, int level);

void free_list(list_t *list);
void freeTree(kdTree_t *parent);
void print_key(list_t *list, FILE *out_file);
void search(kdTree_t *tree, FILE *out_file);

kdTree_t *bstInsert(kdTree_t *parent, data_t *data, int level);
kdTree_t *parse_string(kdTree_t *parent, FILE *fp, FILE *out_file);
kdTree_t *near_neigh(kdTree_t *parent, coord_t *query, int level, int *comparisons, kdTree_t *best_match);
/*****************************************************************************/








