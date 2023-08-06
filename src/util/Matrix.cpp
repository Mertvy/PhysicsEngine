//
// Created by Nicholas Weiss on 7/31/23.
//

#include "Matrix.h"

Matrix::Matrix(vector<vector<float>> nums) {
    this->matrix = nums;
    this->numRows = nums.size();
    this->numColumns = nums.at(0).size();
}

void Matrix::swapRows(int row1, int row2) {
    vector<float> tmp = this->matrix.at(row2);
    this->matrix.at(row2) = this->matrix.at(row1);
    this->matrix.at(row1) = tmp;
}

void Matrix::scaleRow(int rowIndex, float scalar) {
    for (int i = 0; i < this->matrix.get(rowIndex).size(); i++) {
        this->matrix.get(rowIndex).at(i) *= scalar;
    }
}

void Matrix::rref() {
    int i = 0, j = 0;
    while (i < this->numRows && j < this->numColumns) {
        int max = 0, maxRow = i;
        for (int a = i; a < this->numRows; a++) {
            if (this->matrix->at(a)->at(j) > max) {
                max = this->matrix->at(a)->at(j);
                maxRow = a;
            }
        }
        if (max == 0) j++;
        else {
            swapRows(i, maxRow);

        }
    }
}