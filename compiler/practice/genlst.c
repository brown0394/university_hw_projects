#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node;
typedef struct Node Node;
typedef struct Node *List;

struct Data;
typedef struct Data Data;

typedef enum {INT, CHR, LST} TAG;

struct Node {
    Data *val;
    List  nxt;
};

struct Data {
    TAG tag;
    union {
        int  intval;
        char chrval;
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
    int first = 1;

    if (!level) {
        if (strlen(str)) flushstr(str, strlen(str));
        str[0] = '(';
    }

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
                case LST : {
                    strcat(str, "(");
                    ++level;
                    ltos(cur->val->lstval);
                    --level;
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

void append(List ls, Data *n) {
    List newnode = (List)malloc(sizeof *newnode);
    newnode->nxt = NULL;
    newnode->val = n;
    ls->nxt = newnode;
}

int main() {
    char str[200];
    char number[100];
    int numbidx = 0;
    int parencnt = 0;

    char input;

    List head[100];
    List last[100];
    int i;
    for (i = 0; i < 100; ++i) {
        head[i] = NULL;
        last[i] = NULL;
    }
    Data* data = NULL;

    
    int height = 0;
    int width = 0;
    int mheight = 0;
    while (1) {
        scanf("%c", &input);

        if (input == ')') {
            if (parencnt == 1)
                break;
            data = mklst(head[parencnt-1]);
            head[parencnt-1] = NULL;
            last[parencnt-1] = NULL;
            --parencnt;
            --height;
        }
        else if ('(' == input) {
            ++height;
            if(height > mheight){
                mheight = height;
            }
            ++parencnt;
            continue;
        }
        else if (' ' == input) {
            if (numbidx > 0) {
                number[numbidx] = '\0';
                data = mkint(atoi(number));
                numbidx = 0;
            }
            else
                continue;
        }
        else if (input >= '0' && input <= '9')
            number[numbidx++] = input;
        else
            data = mkchr(input);

        if (!numbidx) {
            if (head[parencnt-1] == NULL) {
                head[parencnt-1] = cons(data, NULL);
                last[parencnt-1] = head[parencnt-1];
            }
            else {
                append(last[parencnt-1], data);
                last[parencnt-1] = last[parencnt-1]->nxt;
            }
            if (parencnt == 1)
                ++width;
        }

    }
    printf("%d\n", mheight * width);
    printf("%s\n", ltos(head[0]));
    printf("%s\n", ltos(head[0]));
    printf("%s\n", ltos(head[0]));
    return 0;
}