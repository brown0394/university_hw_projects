# coding : utf-8
##m1 = []
##for i in range(3):
##    m1.append([])
##    for j in range(3):
##        m1[i].append(i+j)
##print(m1)
##
##
##m2 = [[i+j for j in range(3)] for i in range (3)] 

def rowvec(m, i):
    col = len(m[0])
    row_vec = [m[i][j] for j in range(col)]
    return row_vec

def colvec(m, j):
    row = len(m)
    col_vec = [m[i][j] for i in range(row)]
    return col_vec

def iproduct(v1, v2):
    p = 0
    assert len(v1) == len(v2)
    for i in range(len(v2)):
        p += v1[i] * v2[i]
    return p

def product(m1, m2):
    row1 = len(m1)
    col1 = len(m1[0])

    row2 = len(m2)
    col2 = len(m2[0])
    assert col1 == row2
    mat = [[0] * col2 for i in range(row1)]

    for i in range(row1):
        for j in range(col2):
            v1 = rowvec(m1, i)
            v2 = colvec(m2, j)
            mat[i][j] = iproduct(v1,v2)
    
##    for i in range(row1):
##        for j in range(col2):
##            mat[i][j] = 0
##            for k in range(col1):
##                mat[i][j] += m1[i][k] * m2[k][j]
    return mat

def filter_neg(mat):
    row = len(mat)
    col = len(mat[0])
    nmat = [[0]*col for i in range(row)]
    for i in range(row):
        for j in range(col):
            if mat[i][j] < 0:
                nmat[i][j] = 0
            else:
                nmat[i][j] = mat[i][j]
    return nmat

def transpose(mat):
    row = len(mat)
    col = len(mat[0])
    nmat = [[0]*row for i in range(col)]
    for i in range(row):
        for j in range(col):
            nmat[j][i] = mat[i][j]
    return nmat

def main():
    row = 2
    col = 3
    mat = [[0] * col for i in range(row)]
    print(mat)
    initlist = [1, 9, -12, 20, -5, 7]
    k = 0
    mat2 = [[initlist[(i*3)+j] for j in range(col)] for i in range(row)]
    print(mat2)
    for i in range(row):
        for j in range(col):
            mat[i][j] = initlist[k]
            k += 1
    print(mat)
    mmat = filter_neg(mat)
    print(mmat)
    mmmat = transpose(mat)
    print(mmmat)
    print(product(mat, mmmat))

if __name__ == "__main__":
    main()
