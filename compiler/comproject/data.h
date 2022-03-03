   struct TableNode;
   typedef struct TableNode TableNode;
   typedef struct TableNode *TableList;

   struct TableHead;
   typedef struct TableHead TableHead;


   struct HeadTable;
   typedef struct HeadTable HeadTable;
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

   struct TableNode {
      char *id;
      char *val;
      TableList nxt;
   };

   struct TableHead {
      TableList nxt;
      TableList last;
   };

   struct HeadTable {
      TableHead headarr[27];
      HeadTable* up;
      HeadTable* down;
   };





TableList cons(char *id, char* value, TableList ls);
char *car(TableList ls);
TableList cdr(TableList ls);

void addNxt(TableList me, TableList nxt);
char *mkstr(char *s);
Data *mkData(char *s);

int tbidxCheck(char a);
void putInTable(TableHead** symtable, char *id);
void putInTableV(TableHead** symtable, char *id, char *value);
TableList checkTable(TableHead** symtable, char *id);
int fprintData(TableHead** symtable, FILE* fp, Data *data);

int updateTable(TableHead** symtable, Data *id, Data *value);
