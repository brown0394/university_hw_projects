#include <iostream>

typedef int element;


class Node
{
    friend class Queue;
public:
    Node():_data(0), _next(NULL){}
private:
    element _data;
    Node* _next;

};

class Queue
{
public:

    Queue():_head(NULL), _last(NULL)
    {
        _head = new Node;
        _head->_data = 0;
        _head->_next = _head;
        _last = _head;
    }
    ~Queue();

    void Enqueue(element data);
    element Dequeue();
    void IsEmpty();
    int ChkValue();

private:
    Node* _head;
    Node* _last;
};

void Queue::Enqueue(element data)
{
    Node* newone = new Node;
    newone->_data = data;
    if(_head->_next == _head)
    {
        _head->_next = newone;
        _last = newone;
    }
    else
    {
        _last->_next = newone;
        _last = newone;
        _last ->_next = _head;
    }
}

Queue::~Queue()
{
    if(_head->_next != _head)
    {
        Node* temp = _head->_next;
        delete _head;
        while(temp->_next != _last)
        {
            _head = temp;
            temp = temp->_next;
            delete _head;
        }
        delete temp;
    }

}

element Queue::Dequeue()
{
    if(_head->_next == _head)
    {
        IsEmpty();
    }
    Node* temp = _head->_next;
    _head->_next = temp->_next;
    int tempdata = temp->_data;
    if(temp == _last)
        _last = _head;
    delete temp;
    return tempdata;

}

void Queue::IsEmpty()
{
    throw -1;

}

int Queue::ChkValue()
{
    if(_head->_next == _head)
    {
        IsEmpty();
    }
    return _head->_next->_data;

}

void printall(int num, Queue& p_lane)
{
    for(int i = 0; i < num; ++i)
    {
        std::cout << p_lane.Dequeue() << std::endl;
    }
}

void writeall(int p_num, Queue& p_a, Queue& p_b)
{
    int numa, numb;
    for(int i = 0; i < p_num; ++i)
    {
        std::cin >> numa >> numb;
        p_a.Enqueue(numa);
        p_b.Enqueue(numb);
    }
}

void writelane(int p_num, Queue& p_a, Queue& p_b, Queue& p_lane)
{
    int cnta = p_num;
    int cntb = p_num;
    while(1)
    {
        if(cnta == 0)
        {
            break;
        }
        if(cntb == 0)
        {
            break;
        }
        if(p_a.ChkValue() >= p_b.ChkValue())
        {
            p_lane.Enqueue(p_a.Dequeue());
            --cnta;
        }
        else
        {
            p_lane.Enqueue(p_b.Dequeue());
            --cntb;
        }
    }
    if(cntb > 0)
    {
        for(int i = 0; i < cntb; ++i)
        {
            p_lane.Enqueue(p_b.Dequeue());
        }
    }
    else
    {
        for(int i = 0; i < cnta; ++i)
        {
            p_lane.Enqueue(p_a.Dequeue());
        }
    }
}

int main()
{
    Queue qA, qB, lane;
    int number;

    std::cin >> number;
    writeall(number, qA, qB);
    try
    {
        writelane(number, qA, qB, lane);
        printall(number * 2, lane);
    }

    catch(int _)
    {
        std::cerr << "No elements to return" << std::endl;
        return -1;
    }


}
