    struct Data;
    typedef struct Data Data;

    struct Node;
    typedef struct Node Node;
    typedef struct Node *List;

    typedef enum {INT, OP} TAG;
    typedef enum {UNARY, BINARY, INTVAL} NKind;

    struct Node {
       NKind kind;
       Data *val;
       List son;
       List bro;
    };

    struct Data {
       TAG tag;
       union {
       int intval;
       char opval;
       };
    };


List cons(Data* n, List ls);
Data *car(List ls);
List cdr(List ls);
Data *mkint(int n);
Data *mkchr(char c);
List unary(char c, List son);
void addSon(List parent, List son);
void addBro(List me, List bro);
List binary(char c, List son1, List son2);
void printStack(List head);
void printall(List head);
void printblank();
void generateTf(FILE* fp, List head);
