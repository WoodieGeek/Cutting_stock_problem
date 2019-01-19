#ifndef MATRIX_H
#define MATRIX_H
#include <bits/stdc++.h>

class MatrixException : public std::exception {
 public:
    MatrixException(const std::string msg) : Msg(msg) { }
    const char* what() const noexcept override {
        return Msg.c_str();
    }
    ~MatrixException() {}
private:
    std::string Msg;
};

template <typename T>
class Matrix
{
public:
    Matrix();
    ~Matrix() = default;
    Matrix(const Matrix& rhs);
    Matrix(Matrix&& rhs);
    Matrix(size_t rows, size_t columns);
    std::vector<std::vector<T>>& GetData();
    size_t GetRows() const;
    size_t GetColumns() const;
    void Transpose();
    std::vector<T>& operator [] (size_t index);
    void AppendRow(std::vector<T>& row);
    void AppendColumn(std::vector<T>& column);
private:
    std::vector<std::vector<T>> Data;
    size_t Rows;
    size_t Columns;
};

template <typename T>
Matrix<T>::Matrix() { }

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns)
    : Columns(columns)
    , Rows(rows) {
    Data.resize(Rows);
    for (auto& row : Data)
        row.resize(Columns);
}

template <typename T>
Matrix<T>::Matrix(const Matrix& obj)
    : Data(obj.GetData())
    , Rows(obj.GetRows())
    , Columns(obj.GetColumns()) { }

template <typename T>
Matrix<T>::Matrix(Matrix&& rhs)
    : Data(std::move(rhs.GetData()))
    , Columns(rhs.GetColumns())
    , Rows(rhs.GetRows()) { }

template <typename T>
std::vector<std::vector<T>>& Matrix<T>::GetData() {
    return Data;
}

template <typename T>
size_t Matrix<T>::GetColumns() const {
    return Columns;
}

template <typename T>
size_t Matrix<T>::GetRows() const{
    return Rows;
}

template <typename T>
void Matrix<T>::Transpose() {
    size_t square = std::min(Rows, Columns);
    for (size_t i = 0; i < square; i++)
        for (size_t j = i + 1; j < square; j++)
            std::swap(Data[i][j], Data[j][i]);
    if (Columns > Rows) {
        Data.resize(Columns);
        for (size_t i = 0; i < Rows; i++) {
            for (size_t j = square + 1; j < Columns; j++)
                Data[j].push_back(Data[i][j]);
            Data[i].resize(Rows);
        }
    }
    else if (Rows > Columns) {
        for (size_t i = square + 1; i < Rows; i++)
            for (size_t j = 0; j < Columns; j++)
                Data[j].push_back(Data[i][j]);
        Data.resize(Columns);
    }
    std::swap(Rows, Columns);
}

template <typename T>
std::vector<T>& Matrix<T>::operator[](size_t index) {
    return Data[index];
}

template <typename T>
void Matrix<T>::AppendRow(std::vector<T>& row) {
    if (row.size() != Columns)
        throw MatrixException("Size of matrix is not equal size of row");
    Data.push_back(row);
    Rows++;
}

template <typename T>
void Matrix<T>::AppendColumn(std::vector<T>& column) {
    if (column.size() != Rows)
        throw MatrixException("Size of matrix is not equal size of column");
    for (size_t i = 0; i < Rows; i++)
        Data[i].push_back(column[i]);
    Columns++;
}

#endif // MATRIX_H
