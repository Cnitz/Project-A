//
//  query.c
//  
//
//  Created by Christian Nitz on 3/19/14.
//
//

#include "q_defs.h"

void print_data();
int num_cons();
void(*f)(void*) = print_data;
void testing();
int find_space();
int find_conn();
int grammar_checker();
Tree* build_tree();
char* str_at();
char **columns;
char* types;
int cc;


Tree *q_parse(char *query_text, char **column_names, char *column_types,  int num_columns){

    columns = malloc(sizeof(char*)*num_columns);
    columns = column_names;
    cc = num_columns;
    types = column_types;
    
    Tree* ret = build_tree(query_text);
    //TODO: insert build_tree
    

    return ret;
}


void q_free(Tree *query){
    if(t_left(query) != NULL)
    q_free(t_left(query));
    if(t_right(query) != NULL)
    q_free(t_right(query));
    
    if(query != NULL)
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
    for(int i = 0; i < cc; i++){
    if(strcmp(query_data, columns[i]) == 0)
        return i;
    }
    return -1;
}


double q_get_double(void *query_data){
    int* err = malloc(sizeof(int));
    double r = rd_parse_number(query_data, 0, strlen(query_data), err);
    free(err);
    return r;
}


char *q_get_str(void *query_data){ return (char*)query_data; }

void print_data(void* v){
    if(v == NULL) return;
    int* err = calloc(1, sizeof(int));
    rd_parse_number(v, 0, strlen(v), err);
    if(*err == 0)
    printf("%.2f\n", rd_parse_number(v, 0, strlen(v), err));
    else if (*err == 1){
        if (strcmp(v, "&&") == 0) printf("AND\n");
        else if(strcmp(v, "||") == 0) printf("OR\n");
        else printf("%s\n",  (char *)v);
    }
    free(err);
}

int num_cons(char* text){
    int count = 0;
    for(int i = 0; i < strlen(text); i++){
        if(*(text+i) == '&')
            if(*(text+i+1) == '&') count++;
        if(*(text+i) == '|')
            if(*(text+i+1) == '|') count++;
    }
    return count;
}

int find_space(char* p, int start){
    for(int i = start; i < strlen(p); i++){
        if( p[i] == ' ')
            if( p[i+1] != ' ')
                return i;
    }
    return 0;
}

// returns index of the connective
int find_conn(char* p, int n){
    int index = 0, cc = 0;
    for(int i = 0; i < strlen(p); i++){
        if(cc == n) return index;
        if(p[i] == '&' && p[i+1] == '&'){
            index = i;
            cc++;
        }
        if(p[i] == '|' && p[i+1] == '|'){
            index = i;
            cc++;
        }
        
    }
    return 0;
}



Tree* build_tree(char* query){
    int conc = num_cons(query);
    int loc_conn = 0;
    
        loc_conn = find_conn(query, conc/2+1);
    Tree* t = t_make();
    
    if(conc == 0) {
        t_set_data(t, str_at(query, 0));
    }
    if(query[loc_conn] == '&'){
        t_set_data(t, "&&");
    }
    if(query[loc_conn] == '|'){
        t_set_data(t, "||");
    }
    if(conc != 0){
        
    //left subtree
    char* left = calloc(loc_conn, sizeof(char));
    strncpy(left, query, loc_conn);
    left[loc_conn] = '\0';
        
    //right subtree
    char* right = calloc(((strlen(query)/2)+1),sizeof(char));
    strcpy(right, query+loc_conn+2);
        
        t_set_left(t, build_tree(left));
        t_set_right(t, build_tree(right));
        
  
        
    free(left);
    free(right);
    }
    return t;
}

char* str_at(char* p, int n){
    int end = 0, in = 0;
    for(int i = n; i < strlen(p); i++){
        if(in == 0 && p[i] != ' ') n = i;
        if(p[i] != ' '){
            in = 1;
        }
 
        if(p[i] == ' ' && in == 1){
            end = i;
            break;
        }
         end = (i+1);
        if(p[i] == '\0') {
            
            break;
        }
       
    }
    char* ret = malloc(sizeof(char)*(end-n+1));
    strncpy(ret, p+n, end-n);
    ret[end-n] = '\0';
    return ret;
}

int grammar_checker(char* text){
    int in = 0, con = 0, in2 = 0, cc = 0;
    //checks conditional statements.
    for(int i = 0; i < strlen(text); i++){
        if(text[i] == ' ') {}
        if((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
            if(con == 0)
                in = 1;
        if(text[i] == '<' || text[i] == '=' || text[i] == '>'){
            con++;
            if(con > 2) return 0;
            
        }
        if(in == 1 && con > 0)
            if ((text[i] != ' ' && text[i] != '&') && (text[i] != '|' && text[i] != '=')
                && (text[i] != '>' && text[i] != '<'))
                in2 = 1;
        if (text[i] == ' ' && in == 1 && in2 == 1 && con > 0){
            in = 0;
            in2 = 0;
            con = 0;
            cc = 0;
            continue;
        }
        else if (text[i] == ' ' && (in == 1 || in2 == 1 || con > 0))
            return 0;

        if (text[i] == '&' && in == 1 && in2 == 1 && con >  0){
            in = 0;
            in2 = 0;
            con = 0;
            cc = 0;
                    }
        
        if (text[i] == '|' && in == 1 && in2 == 1 && con > 0){
            in = 0;
            in2 = 0;
            con = 0;
            cc = 0;
           
        }
       
        if((text[i] == '&' && text[i+1] == '&') || (text[i] == '|' && text[i+1] == '|')) cc++;
        if((text[i] == '&' && text[i+1] != '&') || (text[i] == '|' && text[i+1] != '|')){
            cc++;
            if(cc == 2) continue;
                return 0;
            }
        
        
        
        
    }
 
    return 1;
}

void testing(){
    for(int i = 0; i < cc; i++){
     printf("%s\n", columns[i]);
    }
}
