#include <iostream>

using namespace std;

class SparseMat
{
public:
    SparseMat(): _row(0), _col(0), _val(0), _idx(0), _numbers(0){}
    SparseMat(const SparseMat& other)
    {
         _idx = other._idx;
         _row = other._row;
         _col = other._col;
        _smatlist = new SparseMat[_idx];
        for(int i = 0; i < other._idx; ++i)
        {
            _smatlist[i]._row = other._smatlist[i]._row;
            _smatlist[i]._col = other._smatlist[i]._col;
            _smatlist[i]._val = other._smatlist[i]._val;
        }
    }
    ~SparseMat()
    {
        delete [] _smatlist;
    }
    void SetMat(int idx)
    {
        _idx = idx;
        _smatlist = new SparseMat[idx];
    }
    void ColRow(int row, int col)
    {
        _row = row;
        _col = col;
    }

    void AddElement(int row, int col, int val, int idx)
    {
        _smatlist[idx]._row = row;
        _smatlist[idx]._col = col;
        _smatlist[idx]._val = val;
        ++_numbers;
    }
    void Transpose(const SparseMat& other)
    {
        _idx = other._idx;
        _row = other._col;
        _col = other._row;
        _smatlist = new SparseMat[_idx];
        int index[_row] = {0};
        int rindex[_row] = {0};
        for(int i = 0; i < other._idx; ++i)
        {
            index[other._smatlist[i]._col] += 1;

        }
        for(int i = 1; i < _row; ++i)
        {
            rindex[i] = rindex[i-1] + index[i-1];
        }
        for(int i = 0; i < other._idx; ++i)
        {
            _smatlist[rindex[other._smatlist[i]._col]]._row = other._smatlist[i]._col;
            _smatlist[rindex[other._smatlist[i]._col]]._col = other._smatlist[i]._row;
            _smatlist[rindex[other._smatlist[i]._col]++]._val = other._smatlist[i]._val;
        }
    }

    const SparseMat operator *(const SparseMat& other)
    {
        SparseMat result;
        result.SetMat(_row * _row);
        int sum = 0;
        int lastrow = _smatlist[0]._row;
        int colidx = 0;

        int resultrow = 0;
        int resultcol = 0;
        int listidx = 0;
        int lastidx = 0;
        int colcont = 0;

        result.ColRow(_row, _row);

        for(int i = 0; i < _idx+1; ++i)
        {
            if(lastrow != _smatlist[i]._row || i == _idx)
            {
                ++colidx;
                if(sum != 0)
                {
                    result.AddElement(resultrow, resultcol, sum,listidx++);
                    sum = 0;

                }
                ++resultcol;
                if(resultcol >= _row)
                {
                    resultcol = 0;
                    ++resultrow;
                }

                if(colidx >= other._col)
                {
                    colidx = 0;
                    lastrow = _smatlist[i]._row;
                    lastidx = i;
                    ++colcont;
                }
                else
                {
                    i = lastidx;
                }
            }

            for(int j = 0; j < other._idx; ++j)
            {
                if((_smatlist[i]._row - colcont + colidx == other._smatlist[j]._col) && (_smatlist[i]._col == other._smatlist[j]._row))
                {
                    sum += _smatlist[i]._val * other._smatlist[j]._val;
                }
            }
        }
        return result;

    }

    void PrintMat(int idx)
    {
        cout << _smatlist[idx]._row << ' ' << _smatlist[idx]._col << ' ' << _smatlist[idx]._val << endl;
    }
    int Row()
    {
        return _row;
    }
    int Col()
    {
        return _col;
    }
    int Num()
    {
        return _numbers;
    }
    int MatCol(int idx)
    {
        return _smatlist[idx]._col;
    }
    int MatRow(int idx)
    {
        return _smatlist[idx]._row;
    }
    int MatVal(int idx)
    {
        return _smatlist[idx]._val;
    }





private:
    SparseMat* _smatlist;
    int _row;
    int _col;
    int _val;
    int _idx;
    int _numbers;
};

ostream& operator << (ostream& out, SparseMat& n)
{
    for(int i = 0; i < n.Row() * n.Col(); ++i)
    {
        if(n.MatVal(i) != 0)
            out << '(' << n.MatRow(i) << ',' << n.MatCol(i) << ',' << n.MatVal(i) << ')' << endl;
    }

}

//ostream& operator << (ostream& out, SparseMat& n)
//{
//    return
//}

int main(void)
{
    int row = 0;
    int col = 0;
    int idxcount = 0;
    int rowcount = 0;
    int colcount = 0;
    SparseMat smat;
    SparseMat tmat;
    std::cin >> row >> col;
    int matrix[row][col] = {0};

    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            std::cin >> matrix[i][j];
            if(0 != matrix[i][j])
            {
                ++idxcount;

            }
        }
    }


    smat.SetMat(idxcount);

    idxcount = 0;

    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            if(0 != matrix[i][j])
            {
                smat.AddElement(i, j, matrix[i][j], idxcount++);
                rowcount = i;
                if(j > colcount)
                    colcount = j;
            }
        }
    }
    smat.ColRow(rowcount+1, colcount+1);
    tmat.Transpose(smat);

    SparseMat rmat = (smat * tmat);


    cout << rmat.Row() << ' ' << rmat.Col() << ' ' << rmat.Num() << endl;
    cout << rmat << endl;

    return 0;
}
