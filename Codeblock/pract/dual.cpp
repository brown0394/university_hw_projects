#include <iostream>

class Node
{
    friend class doubleList;
private:
    int _data;
    Node* _next;
    Node* _prev;
};

class doubleList
{
    friend class Iterator;
public:
    doubleList()
    {
        _head = new Node;
        _head->_data = 0;
        _head->_next = _head;
        _head->_prev = _head;
    }
    doubleList(const doubleList& other)
    {
        _head = other._head;
    }
    void InsertNode(int data, Node* prev);
    void Stack(int data);
    void Sort();
    int Val();
    ~doubleList();
    void DeleteNode(Node* del);
    void PrintAll();

    class Iterator {
        Node *curr;
    public:
        Iterator(Node *np=nullptr): curr(np) {}
        Iterator& operator =(const Iterator &p) {
            curr = p.curr;
            return *this;
        }
        bool operator !=(const Iterator &p) {
            return this->curr != p.curr;
        }
        bool operator ==(const Iterator &p){
            return this->curr == p.curr;
        }
        int operator *() {
            return curr->_data;
        }
        Node* operator ++() {
            return (curr = curr->_next);
        }
        Node* Cur()
        {
            return curr;
        }
    };

    Iterator begin() {
        return _head->_next;
    }
    Iterator end() {
        return _head;
    }

private:
  Node* _head;

};

void doubleList::InsertNode(int data, Node* prev)
{
    Node* newone = new Node;
    newone->_data = data;
    if(_head->_prev == _head)
    {
        _head->_prev = newone;
        newone->_next = _head->_next;
        newone->_prev = _head;
        _head->_next = newone;
    }
    else
    {
        newone->_next = prev->_next;
        prev->_next = newone;
        newone->_prev = prev;
    }
}

void doubleList::Stack(int data)
{
    Node* newone = new Node;
    newone->_data = data;
    if(_head->_prev == _head)
    {
        _head->_prev = newone;
        newone->_next = _head;
    }
    else
    {
        newone->_next = _head->_next;
        newone->_next->_prev = newone;
    }

    newone->_prev = _head;
    _head->_next = newone;
}

doubleList::~doubleList()
{
    Node* temp = _head->_prev;
    Node* curr;
    if(temp != _head)
    {
        while(temp != _head)
        {
            curr = temp;
            temp = temp->_prev;
            delete curr;
        }
    }
    delete _head;
}

void doubleList::DeleteNode(Node* del)
{
    if(_head->_next != _head)
    {
        del->_prev->_next = del->_next;
        del->_next->_prev = del->_prev;
        delete del;
    }
}

void doubleList::Sort()
{
    if(_head->_next != _head)
    {
        doubleList sorted(*this);
        Iterator p = sorted.begin();
        int big = *p;
        Node* bn = p.Cur();
        ++p;
        _head = new Node;
        _head->_prev = _head;
        _head->_next = _head;
        while(1)
        {
            if(p == sorted.end())
            {
                p = sorted.begin();
                if(p == sorted.end())
                {
                    break;
                }
                else
                {
                    Stack(big);
                    if(*p == big)
                    {
                        ++p;
                    }
                    sorted.DeleteNode(bn);
                    big = *p;
                    bn = p.Cur();
                }
            }
            if(big < *p)
            {
                big = *p;
                bn = p.Cur();
            }
            ++p;
        }
    }

}

void doubleList::PrintAll()
{
    Iterator p;
    bool first = true;
    for(p = begin(); p != end(); ++p)
    {
        if(!first)
        {
            std::cout<< ' ';
        }
        else first = false;
        std::cout << *p;
    }
    std::cout << std::endl;
}

int main()
{
    int num = 0;
    doubleList list;
    std::cin >> num;
    int numbers = 0;
    for(int i = 0; i < num; ++i)
    {
        std::cin >> numbers;
        list.Stack(numbers);
    }
    list.Sort();
    list.PrintAll();
    return 0;
}
