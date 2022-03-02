#include <iostream>


class Heap
{
private:
    int *_heap;
    int _size;
    int _cur;
public:
    Heap(int size):_cur(0)
    {
        _size = size + 1;
        _heap = new int[_size];
        initialize();
    }
    ~Heap()
    {
        delete _heap;
    }
    void insertData(int data);
    int deleteData();
    void swap(int *one, int *two);
    void initialize();
};



void Heap::initialize()
{
    for(int i = 0; i < _size; ++i)
    {
        _heap[i] = 0;
    }
}

void Heap::insertData(int data)
{
    ++_cur;
    int i = _cur;
    _heap[_cur] = data;
    while(i > 1)
    {
        if(_heap[i/2] < data)
        {
            swap(&_heap[i/2], &_heap[i]);
        }
        i /= 2;
    }
}

void Heap::swap(int *one, int *two)
{
    int temp = *one;
    *one = *two;
    *two = temp;
}

int Heap::deleteData()
{
    int i = 1;
    int data = _heap[i];
    if(_size > 0)
    {
        _heap[i] = 0;
        swap(&_heap[i], &_heap[_cur--]);
        while(true)
        {
            if((i * 2) + 1 <= _cur)
            {
                if(_heap[i*2] >= _heap[(i*2)+1] && _heap[i*2] > _heap[i])
                {
                    swap(&_heap[i], &_heap[i*2]);
                    i = i * 2;
                }
                else if(_heap[i*2] < _heap[(i*2)+1] && _heap[(i*2)+1] > _heap[i])
                {
                    swap(&_heap[i], &_heap[(i*2)+1]);
                    i = (i * 2) + 1;
                }
                else
                {
                    break;
                }

            }
            else
                break;
        }
        --_size;
    }
    return data;
}

void print(int size, Heap& heap)
{
    bool first = true;
    for(int i = 0; i < size; ++i)
    {
        if(first)
        {
            first = false;
        }
        else
        {
            std::cout << ' ';
        }
        std::cout << heap.deleteData();
    }
    std::cout << std::endl;
}

int main()
{
    int size, num;
    std::cin >> size;
    Heap heap(size);

    for(int i = 0; i < size; ++i)
    {
        std::cin >> num;
        heap.insertData(num);
    }

    print(size, heap);

    return 0;
}
