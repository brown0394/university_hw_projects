#include <iostream>

using namespace std;

#define MaxElements 100

class MatrixElement {
public:
    int row,col;
    int value;
};

class SparseMatrix {
public:
    int nRows, nCols, nElements;
    MatrixElement smArray[MaxElements];
    SparseMatrix(int r, int c): nRows(r), nCols(c), nElements(0) { }
    void addElement(int r, int c, int v) {
        smArray[nElements].row = r;
        smArray[nElements].col = c;
        smArray[nElements].value = v;
        nElements++;
    }
    void print() {
        cout << "Sparse Matrix is:" << endl;
        for (int i = 0; i < nElements; i++)
            cout << "(" << smArray[i].row << ", " 
                        << smArray[i].col << ", "
                        << smArray[i].value << ")" << endl;
    }
};


int main () {
    int row = 4, col = 4;
    int a[row][col] = { {0, 0, 9, 0} , {5, 0, 8, 1} , {7, 0, 0, 2}, {0, 0, 0, 1} };
    SparseMatrix sm(row, col);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (a[i][j] != 0)
                sm.addElement(i, j, a[i][j]);

    cout << "The matrix is:" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) 
            cout << a[i][j] << (j == col-1? "\n":" ");
    }
    sm.print();
    return 0;
}