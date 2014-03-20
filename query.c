//
//  query.c
//  
//
//  Created by Christian Nitz on 3/19/14.
//
//

#include "q_defs.h"
#include "defs_itf.h"
void print_data();
void(*f)(void*) = print_data;


Tree *q_parse(char *query_text, char **column_names, char *column_types,  int num_columns){
    //TODO: Write this
    
    return NULL;
}


void q_free(Tree *query){
    if(query->left != NULL)
    q_free(query->left);
    if(query->right != NULL)
    q_free(query->right);
    free(query);
}


void q_print(Tree *data){
    if(data == NULL) return;
    int space = 0;
    t_print(data, space, f);
}


int q_get_type(void *query_data){
    
    if(strcmp("||", query_data) == 0) return 0;
    else if (strcmp("&&", query_data) == 0) return 1;
    else if (strcmp("=", query_data) == 0) return 2;
    else if (strcmp("<", query_data) == 0) return 3;
    else if (strcmp(">", query_data) == 0) return 4;
    else if (strcmp("<=", query_data) == 0) return 5;
    else if (strcmp(">=", query_data) == 0) return 6;
    else return -1;
}


int q_get_col_index(void *query_data){
    
    //TODO: Write this
    
    return 0;
}


double q_get_double(void *query_data){
    int* err = malloc(sizeof(int));
    double r = rd_parse_number(query_data, 0, strlen(query_data), err);
    free(err);
    return r;
}


char *q_get_str(void *query_data){
    
    
    return (char*)query_data;
}

void print_data(void* v){
    if(v == NULL) return;
    int* err = calloc(1, sizeof(int));
    rd_parse_number(v, 0, strlen(v), err);
    if(*err == 0)
    printf("%.2f\n", rd_parse_number(v, 0, strlen(v), err));
    else if (*err == 1){
        if (strcmp(v, "&&") == 0) printf("AND\n");
        else if(strcmp(v, "||") == 0) printf("OR\n");
        else printf("%s\n",  v);
    }
    free(err);
}

