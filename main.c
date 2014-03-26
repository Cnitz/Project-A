//
//  main.c
//  
//
//  Created by Christian Nitz on 3/19/14.
//
//

#include "q_defs.h"
#include "defs_itf.h"
void print_str();
void testing();
void print_num();
int num_cons();
int find_space();
int find_conn();
int grammar_checker();
char ** columns2;
char* str_at();
Tree*  build_tree();
int find_conditional();
//char* p1, p2, p3;
char *p1 = "hello";
char *p2 = "howdy";
char *p3 = "hoe";
char *sc = "SSDDS";


int main(){
    columns2 = malloc(sizeof(char*)*3);
    columns2[0] = p1;
    columns2[1] = p2;
    columns2[2] = p3;
  /*  int* err = calloc(1, sizeof(int));
    Tree* t = malloc(sizeof(Tree));
    Tree* l = malloc(sizeof(Tree));
    Tree* r = malloc(sizeof(Tree));
    t->data = "902";
    l->data = "hello";
    r->data = "||";
    t->left = l;
    t->right = r;
    q_print(t);
    printf("~~%d\n", q_get_type("pp"));
    q_free(t);
    printf("%s\n",q_get_str(t->data));
    q_parse("hello", columns2, sc, 3);
    //q_get_col_index(
    //testing();
    printf("%s\n", rd_parse_string("AMOUNT>=5000 && OPERATION=500", 0, 30));
    
    printf( "%d\n", find_conn("AMOUNT>=5000     && OPERATION=500 && || && ||", 3));
   // build_tree("AMOUNT>=5000     && OPERATION=500 && || && ||"); */
    //Tree* t2 = q_parse("AMOUNT>=50000 && ZIP=47906 && OCCUPATION=Prof || AMOUNT>100 && OCCUPATION=TA && tom=89 || georgia=fish", columns2, sc, 3);
 //   q_print(t2);
    //printf("%d\n",grammar_checker("    AMOUNT>=tom      &&     tom>you&&herny=kkk   "));
    //q_get_double("tom>=you");
    printf("%.2f\n", q_get_double("AMOUNT>=5000"));
    printf("%s\n", q_get_str("Amount>=tom"));
    /*
     OR
      AND
       AND
     
    
    */
}
