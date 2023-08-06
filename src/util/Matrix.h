//
// Created by Nicholas Weiss on 7/31/23.
//

#ifndef PHYSICS_ENGINE_MATRIX_H
#define PHYSICS_ENGINE_MATRIX_H

#include <vector>


class Matrix {
    public vector<vector<float>> matrix;
    public int numRows;
    public int numColumns;
    Matrix(vector<vector<float>>);
    ~Matrix();

    private void swapRows(int row1, int row2);
    private void scaleRow(int rowIndex, float scalar);

    public void rref();
};


#endif //PHYSICS_ENGINE_MATRIX_H
