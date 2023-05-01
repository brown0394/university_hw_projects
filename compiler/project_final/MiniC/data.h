    struct Data;
    typedef struct Data Data;

    struct Node;
    typedef struct Node Node;
    typedef struct Node *List;

    typedef enum {UNARY, BINARY, INTVAL, IDNUM, EMPTY, JMP} NKind;

    struct Node {
       NKind kind;
       Data *val;
       List son;
       List bro;
       int gen;
    };

    struct Data {
       union {
       int intval;
       char opval;
       char *sval;
       };
    };

   struct TableNode;
   typedef struct TableNode TableNode;
   typedef struct TableNode *TableList;

   struct TableHead;
   typedef struct TableHead TableHead;

   struct TableNode {
      Data *id;
      int sploc;
      TableList nxt;
   };

   struct TableHead {
      TableList nxt;
      TableList last;
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
void generateTf(FILE* fp, List head, TableHead** symtable);
void freeTree(List head);

void addNxt(TableList me, TableList nxt);
Data *mkstr(char *s);
int tbidxCheck(char a);
void putInTable(TableHead** symtable, Data *id, int *loc);
TableList checkTable(TableHead** symtable, char *id);

int getIdLoc(TableHead** symtable, char *id);
TableList tcons(Data *n, TableList ls);