#include <iostream>


typedef int DataType;


class Node
{
    friend class LinkedList;
    friend class Stack;
public:
    Node():next(nullptr), data(0){}
    Node(DataType p_data)
    {
        data = p_data;
    }
private:
    DataType data;
    Node *next;

};

class LinkedList
{
    friend class Stack;
private:
    Node *first;
public:
    LinkedList(): first(nullptr){}
    void insert(DataType data, Node *q);
    void deleteNode(Node *p, Node* q);
    Node *search();
};

class Stack
{
private:
    Node *top;
public:
    Stack(): top(nullptr){}
    void push(DataType data);
    DataType pop();
};

void Stack::push(DataType data)
{
    Node *newnode = new Node(data);
    newnode->next = top;
    top = newnode;
}

DataType Stack::pop()
{
    if (top == nullptr)
    {
        printf("empty list\n");
    }
    else
    {
        DataType temp = top->data;
        Node *removed = top;
        top = top->next;
        delete removed;
        return temp;
    }

}

void LinkedList::insert(DataType data, Node *q)
{
    Node *newNode = new Node;
    newNode->data = data;

    if (first == nullptr)
    {
        first = newNode;
        newNode->next = nullptr;
    }
    else
    {
        newNode->next = q->next;
        q->next = newNode;
    }

}

void LinkedList::deleteNode(Node *p, Node *q)
{
    if(p != nullptr)
        q->next = p->next;
        delete p;
}


int main(void)
{
    Stack stack;
    stack.push(8);
    stack.push(7);
    int a = stack.pop();
    a = stack.pop();
    a = stack.pop();


    return 0;
}
