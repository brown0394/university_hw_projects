//#include <iostream>
#include <algorithm>
#include <iterator>

typedef int DataType;


class Node
{
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


class Stack
{
private:
    Node *top;
public:
    Stack(): top(nullptr){}
    ~Stack();
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

Stack::~Stack()
{
    if(top != nullptr)
    {
        if(top->next != nullptr)
        {
            Node* temp = top;
            while(top->next != nullptr)
            {
                top = top->next;
                delete temp;
                temp = top;
            }
            delete top;
        }
    }

}



int main(void)
{
    Stack stack;

    stack.push(5);
    stack.push(4);
    stack.push(3);
    stack.push(2);

    for(int i = 0; i < 4; ++i)
    {
        std::cout << stack.pop();

    }

    return 0;
}
