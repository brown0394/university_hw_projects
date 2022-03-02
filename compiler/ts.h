//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>


struct Node;
typedef struct Node Node;
typedef struct Node *List;

struct Data;
typedef struct Data Data;

typedef enum {INT, CHR, LST, STR} TAG;

struct Node {
    Data *val;
    List  nxt;
};

struct Data {
    TAG tag;
    union {
        int  intval;
        char chrval;
	char *sval;
        List lstval;
    };
};

Data *car(List ls){
    if (NULL != ls)
        return ls->val;
    return NULL;
}

List cdr(List ls) {
    if (ls != NULL)
        return ls->nxt;
    return NULL;
}

List cons(Data* n, List ls) {
    List newnode = (List)malloc(sizeof *newnode);
    newnode->nxt = ls;
    newnode->val = n;
    return newnode;
}

char *ctos(char c) {
    static char str[10];
    sprintf(str, "'%c'\0", c);
    return str;
}

char *itos(int n) {
    static char str[10];
    sprintf(str, "%d\0", n);
    return str;
}

char* ltos(List ls) {
    static char str[200] = "(";
    int first = 1;
    if (NULL != ls) {
        List  cur = ls;
        while (NULL != cur) {
            if (first)
                first = 0;
            else
                strcat(str, " ");
            switch(cur->val->tag){
                case INT : {
                    strcat(str, itos(cur->val->intval));
                    break;
                }
                case CHR : {
                    strcat(str, ctos(cur->val->chrval));
                    break;
                }
	        case STR : {
		    strcat(str, cur->val->sval); break;
		}
                case LST : {
                    strcat(str, "(");
                    ltos(cur->val->lstval);
                }
                default : break;
            }
            cur = cur->nxt;
        }
        strcat(str, ")");
        return str;
    }
    return NULL; 
}

Data *mkint(int n) {
    Data* newdata = (Data *)malloc(sizeof *newdata);
    newdata->tag = INT;
    newdata->intval = n;
    return newdata;
}
Data *mkchr(char c) {
    Data* newdata = (Data *)malloc(sizeof *newdata);
    newdata->tag = CHR;
    newdata->chrval = c;
    return newdata;
}
Data *mklst(List l) {
    Data* newdata = (Data *)malloc(sizeof *newdata);
    newdata->tag = LST;
    newdata->lstval = l;
    return newdata;
}
Data *mkstr(char *s) {
    Data* newdata = (Data *)malloc(sizeof *newdata);
    newdata->tag = STR;
    newdata->sval = (char *)calloc(strlen(s)+1, 1);
    strcpy(newdata->sval, s);
    return newdata;
}


void append(List ls, Data *n) {
    List newnode = (List)malloc(sizeof *newnode);
    newnode->nxt = NULL;
    newnode->val = n;
    ls->nxt = newnode;
}

char* prdata(Data* root) {
    switch (root->tag) {
       case INT : { return itos(root->intval); }
       case CHR : { return ctos(root->chrval); }
       case STR : { return root->sval; }
       case LST : { return ltos(root->lstval); }
    }
    return "error\n";
}
