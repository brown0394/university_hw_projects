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
Data *car(List ls);
List cdr(List ls);
List cons(Data* n, List ls);
char *ctos(char c);
char *itos(int n);
char* ltos(List ls);
Data *mkint(int n);
Data *mkchr(char c);
Data *mklst(List l);
Data *mkstr(char* s);
void append(List ls, Data *n);
