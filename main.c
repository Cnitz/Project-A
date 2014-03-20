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
void print_num();

int main(){
    int* err = calloc(1, sizeof(int));
    Tree* t = malloc(sizeof(Tree));
    Tree* l = malloc(sizeof(Tree));
    Tree* r = malloc(sizeof(Tree));
    t->data = "902";
    l->data = "hello";
    r->data = "104";
    t->left = l;
    t->right = r;
    q_print(t);
    printf("~~%d\n", q_get_type("pp"));
}