#include <iostream>

typedef int element;


class Node
{
    friend class Queue;
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
    else
    {
        Node* temp = _head->_next;
        _head->_next = temp->_next;
        int tempdata = temp->_data;
        if(temp == _last)
            _last = _head;
        delete temp;
        return tempdata;
    }

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
    else
    {
        return _head->_next->_data;
    }

}

int main()
{
    int number = 0;
    Queue qA;
    Queue qB;
    Queue lane;
    int numa = 0;
    int numb = 0;
    int cnta = 0;
    int cntb = 0;

    std::cin >> number;
    cnta = number;
    cntb = number;
    for(int i = 0; i < number; ++i)
    {
        std::cin >> numa >> numb;
        qA.Enqueue(numa);
        qB.Enqueue(numb);
    }
    try
    {
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
            if(qA.ChkValue() >= qB.ChkValue())
            {
                lane.Enqueue(qA.Dequeue());
                --cnta;
            }
            else
            {
                lane.Enqueue(qB.Dequeue());
                --cntb;
            }
        }
        if(cntb > 0)
        {
            for(int i = 0; i < cntb; ++i)
            {
                numb = qB.Dequeue();
                lane.Enqueue(numb);
            }
        }
        else if(cnta > 0)
        {
             for(int i = 0; i < cnta; ++i)
            {
                numa = qA.Dequeue();
                lane.Enqueue(numa);
            }
        }

        number = number * 2;

        for(int i = 0; i < number; ++i)
        {
            std::cout << lane.Dequeue() << std::endl;
        }
    }

    catch(int _)
    {
        std::cerr << "No elements to return" << std::endl;
        return -1;
    }


}
