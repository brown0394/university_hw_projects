#include <iostream>
#include <algorithm>
#include <iterator>

typedef int DataType;


class Node
{
    friend class Stack;
public:
    Node():next(NULL), data(0){}
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
    Stack(): top(NULL){}
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
    if (top == NULL)
    {
        std::cout << "empty list" << std::endl;
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
    if(top != NULL)
    {
        if(top->next != NULL)
        {
            Node* temp = top;
            while(top->next != NULL)
            {
                top = top->next;
                delete temp;
                temp = top;
            }
            delete top;
        }
    }

}


int rangecheck(int num, int* numseq, Stack &stack1)
{
    int numidx = 0;
    int numarray[num];
    int seqidx = 0;
    int seqcnt = 0;

    for(int i = 1; i <= num; ++i)
    {
        stack1.push(i);
        if(*(numseq + seqidx) == i)
        {
            while(*(numseq + seqidx) == i - seqcnt && numidx < num)
            {
               numarray[numidx++] = stack1.pop();
                ++seqidx;
                ++seqcnt;
            }
            seqcnt = 0;
        }
    }

    for(int i = numidx; i < num; ++i)
    {
        numarray[i] = stack1.pop();
    }
    for(int i = numidx; i < num; ++i)
    {

        if(numarray[i] != *(numseq + i))
        {
            return 0;
        }
    }
    return 1;
}







int main(void)
{
    Stack stack1;

    int input = 0;
    int check = 0;
    std::cin >> input;
    int numseq[input];
    for(int i = 0; i < input; ++i)
    {
        std::cin >> numseq[i];
    }

    check = rangecheck(input, numseq, stack1);
    std::cout << check;


    return 0;
}
