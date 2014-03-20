//
//  query.c
//  
//
//  Created by Christian Nitz on 3/19/14.
//
//

#include "q_defs.h"
#include "defs_itf.h"
void print_num();
void print_str();
void(*p)(void*) = print_str;
void(*f)(void*) = print_num;


Tree *q_parse(char *query_text, char **column_names, char *column_types,  int num_columns){
    //TODO: Write this
    
    return NULL;
}


void q_free(Tree *query){
    
    
}


void q_print(Tree *data){
    if(data == NULL) return;
    int space = 0;
    int* err = malloc(sizeof(int));
    rd_parse_number(data->data, 0, strlen(data->data), err);
    if(*err == 1)
        t_print(data, space, p);
    else if(*err == 0){
        t_print(data, space, f);
    }
    free(err);
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
    
    //TODO: Write this
    
    return 0.0;
}


char *q_get_str(void *query_data){
    
    //TODO: Write this
    
    return NULL;
}

void print_num(void* v){
    if(v == NULL) return;
    int* err = calloc(1, sizeof(int));
    printf("%.2f\n", rd_parse_number(v, 0, strlen(v), err));
    free(err);
}

void print_str(void* v){
    if (v == NULL) return;
    printf("%s\n",  v);
}