#include <stdio.h>
#include <stdlib.h>

typedef enum {INT, CHR} TAG;

typedef struct Atom {
    TAG tag;
    union {
        int intval;
        char charval;
    };
} Atom;

typedef struct Node {
    Atom *val;
    struct Node *nxt;
} *List;

typedef struct Head {
    int amount;
    List next;
    List last;
} Head;

int val(List ls) {
    if (ls != NULL) {
        if (ls->val->tag == INT) {
            return ls->val->intval;
        }
        else {
            return ls->val->charval;
        }
    }
    return -1;
}

List nxt(List ls) {
    if(ls != NULL){
        return ls->nxt;
    }
    return NULL;
}

List cons(Atom* n, List ls) {
    List newnode = (List)malloc(sizeof *newnode);
    newnode->nxt = ls;
    newnode->val = n;
    return newnode;
}

void append(List ls, Atom *n) {
    List newnode = (List)malloc(sizeof *newnode);
    newnode->nxt = NULL;
    newnode->val = n;
    ls->nxt = newnode;
}

void print(List ls, const char *sep, const char *end) {
    List cur = ls;
    while (cur != NULL) {
        if (nxt(cur) != NULL) {
            if (cur->val->tag == CHR)
                printf("'%c'%s", val(cur), sep);
            else
                printf("%d%s", val(cur), sep);
        }
        else {
            if (cur->val->tag == CHR)
                printf("%c", val(cur));
            else
                printf("%d", val(cur));
        } 
        cur = nxt(cur);
    }
    printf("%s", end);
}

Atom* mkint(int number){
    Atom* newnode = (Atom*)malloc(sizeof *newnode);
    newnode->tag = INT;
    newnode->intval = number;
    return newnode;
}
Atom* mkchar(char chr){
    Atom* newnode = (Atom*)malloc(sizeof *newnode);
    newnode->tag = CHR;
    newnode->charval = chr;
    return newnode;
}

int main(){
    Head head;
    head.amount = 0;
    head.last = NULL;
    head.next = NULL;
    char str[100];
    char number[100];
    int numcnt = 0;
    int num = 0;
    int n = 0;
    int min = 0;
    gets(str);
    for(int i = 0; str[i] != '\0'; ++i){
        if(str[i] == ' '){
            if(numcnt > 0){
                number[numcnt] = '\0';
                n = atoi(number);
                if(min){
                    min = 0;
                    n = n * -1;
                }
                numcnt = 0;
                num = 1;
            }
            else{
                continue;
            }
        }
        else if(str[i] == '-'){
            min = 1;
            continue;
        }
        else if(str[i] >= '0' && str[i] <= '9'){
            number[numcnt++] = str[i];
            continue;
        }
        Atom* newnode = NULL;
        if(num){
            num = 0;
            newnode = mkint(n);
            n = 0;
        }
        else{
            newnode = mkchar(str[i]);
        }
        if(head.next == NULL){
            head.next = cons(newnode, NULL);
            head.last = head.next;
            ++head.amount;
        }
        else{
            append(head.last, newnode);
            head.last = nxt(head.last);
            ++head.amount;
        }
    }

    if(numcnt > 0){
        number[numcnt] = '\0';
        n = atoi(number);
        if(min){
            min = 0;
            n = n * -1;
        }
        Atom* newnode = mkint(n);
        if(head.next == NULL){
            head.next = cons(newnode, NULL);
            head.last = head.next;
            ++head.amount;
        }
        else{
            append(head.last, newnode);
            head.last = nxt(head.last);
            ++head.amount;
        }
    }
    scanf("%d", &num);
    if(num >= head.amount || num < 0){
        printf("#nil\n");
    }
    else{
        int i = 0;
        List cur = head.next;
        for(; i < num; ++i){
            cur = nxt(cur);
        }
        if(cur->val->tag == INT){
            int a = val(cur);
            if(a < 0){
                printf("#nil\n");
            }
            else{
                ++a;
                printf("%d\n", a);
            }
        }
        else{
            char a = (char)val(cur);
            if((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z')){
                if(a == 'z'){
                    a = 'a';
                }
                else if(a == 'Z'){
                    a = 'A';
                }
                else{
                    a = a+1;
                }
                printf("%c\n", a);
            }
            else{
                printf("#nil\n");
            }
        }
    }

    return 0;
}