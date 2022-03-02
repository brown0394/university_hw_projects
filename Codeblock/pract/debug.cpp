#include <iostream>
#include <string>

typedef std::string element;

class BST
{
    element data;
    BST *ltree, *rtree;
    bool _isfirst;
    BST *root;
    int _level;
    int _depth;
    int _curloc;
public:
    BST(): data(NULL), ltree(NULL), rtree(NULL), _level(0), _isfirst(true), _depth(0),
    _curloc(0){}
    BST(element d, BST *l=NULL, BST *r=NULL): data(d), ltree(l), rtree(r), _level(0), _isfirst(true), _depth(0),
    _curloc(0)
    {
        root = new BST;
    }
    void insert(element d)
    {
        root = root->insert(root, d);
    }
    BST* insert(BST *tree, element d);
    void SetDepth(int deth);
    std::ostream& print(int level, std::ostream &out=std::cout)
    {
        if(level < 2)
        {
            out << root->data;
            return out;
        }
        return root->print(root, level, out);
    }
    std::ostream& print(BST *tree, int level, std::ostream &out)
    {
        if(level < 2)
            level = 1;
        ++_level;
        if(tree)
        {
            if(_level == level)
            {
                if(_isfirst)
                    _isfirst = false;
                else
                    out << ' ';
                out << tree->data;
            }
            else
            {
                if(level > _depth)
                {
                    if(tree->ltree == NULL && tree->rtree == NULL)
                    {
                        if(_isfirst)
                            _isfirst = false;
                        else
                            out << ' ';
                        out << tree->data;
                    }
                }
                print(tree->ltree, level, out);
                print(tree->rtree, level, out);
            }
        }
        --_level;
        return out;
    }

};

BST* BST::insert(BST *tree, element d)
{
    ++_curloc;
    if(tree == NULL)
    {
        if(_depth < _curloc)
        {
            _depth = _curloc;
        }
        --_curloc;
        return new BST(d);
    }
    if(d > tree->data)
    {
        tree->rtree = insert(tree->rtree, d);
    }
    else
    {
        tree->ltree = insert(tree->ltree, d);
    }
    --_curloc;
    return tree;
}

int main(void)
{
    int num, level;
    BST tree;
    std::cin >> num;
    element* input = new element[num];
    for(int i = 0; i < num; ++i)
    {
        std::cin >> input[i];
        tree.insert(input[i]);
    }
    std::cin >> level;
    tree.print(level);

    delete[] input;
    return 0;
}
