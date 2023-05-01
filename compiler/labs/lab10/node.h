    struct Data;
    typedef struct Data Data;

    struct Node;
    typedef struct Node Node;
    typedef struct Node *List;

    typedef enum {INT, OP, LST} TAG;
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

    List cons(Data *n, List ls);
    void addSon(List parent, List son);
    void addBro(List me, List bro);

    Data *mkint(int n);
    Data *mkchr(char c);

    List negate(List p, List son);
    List positiv(List p, List son);
