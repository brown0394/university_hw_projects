#include<stdio.h>
#include<stdlib.h>
#include<string.h>


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

void flushstr(char* str, int length) {
    int i;
    for (i = 0; i < length; ++i) {str[i] = '\0';}
}

char* ltos(List ls) {
    static char str[200];
    static int level = 0;
    if (!level) {
        if (strlen(str) > 0) flushstr(str, strlen(str));
	str[0] = '(';
    } 
    int first = 1;
    if (NULL != ls) {
        List  cur = ls;
        while (NULL != cur) {
            if (first)
                first = 0;
            else
                strcat(str, " ");
            switch(car(cur)->tag){
                case INT : {
                    strcat(str, itos(car(cur)->intval));
                    break;
                }
                case CHR : {
                    strcat(str, ctos(car(cur)->chrval));
                    break;
                }
	        case STR : {
		    strcat(str, car(cur)->sval);
		    break;
		}
                case LST : {
                    strcat(str, "(");
		    ++level;
                    ltos(cur->val->lstval);
		    --level;
                }
                default : break;
            }
            cur = cdr(cur);
        }
        strcat(str, ")");
        return str;
    }
    return NULL; 
}

void addnxt(List ls, Data *n) {
    List newnode = (List)malloc(sizeof *newnode);
    newnode->nxt = NULL;
    newnode->val = n;
    ls->nxt = newnode;
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

char* prdata(Data* root) {
    switch (root->tag) {
       case INT : { return itos(root->intval); }
       case CHR : { return ctos(root->chrval); }
       case STR : { return root->sval; }
       case LST : { return ltos(root->lstval); }
    }
    return "error\n";
}

void getHeight(List ls, int *height, int *mxheight) {
    List cur = ls;
    if(*height > *mxheight) *mxheight = *height;
    while (cur != NULL) {
        if (cur->val->tag == LST) { ++(*height); getHeight(car(cur)->lstval, height, mxheight);}
	cur = cdr(cur);
    }
    --(*height);
}

void getWidth(List ls, int *width) {
    List cur = ls;
    while (cur != NULL) {
        ++(*width);
	cur = cdr(cur);
    }
    --(*width);
}

int getArea(Data* root) {
    int width = 1;
    int height = 1;
    int mxheight = 0;
    if (root->tag == LST) {
       getWidth(root->lstval, &width);
       getHeight(root->lstval, &height, &mxheight);
    }
    else mxheight = 1;
    
    return width * mxheight;
}
