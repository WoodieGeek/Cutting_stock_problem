#ifndef MATRIX_H
#define MATRIX_H
#include <bits/stdc++.h>

class MatrixException;


template <typename T>
class Matrix
{
public:
    Matrix();
    ~Matrix() = default;
    Matrix(const Matrix& rhs);
    Matrix(Matrix&& rhs);
    Matrix(size_t rows, size_t columns);
    const std::vector<std::vector<T>>& GetData() const;
    size_t GetRows() const;
    size_t GetColumns() const;
    void Transpose();
    std::vector<T>& operator [] (size_t index);
    Matrix<T>& operator = (const Matrix& rhs);
    friend std::ostream& operator << (std::ostream& s, const Matrix<T>& rhs);
    template <typename V>
    void AppendRow(const std::vector<V>& row);
    template <typename V>
    void AppendColumn(const std::vector<V>& column);
    template <typename V>
    void SetColumn(size_t index, const std::vector<V>& column);
    template <typename V>
    void SetRow(size_t index, const std::vector<V>& row);
    void SwapRows(size_t a, size_t b);
    void SwapColumns(size_t a, size_t b);
    std::vector<T> GetColumn(size_t index);
private:
    std::vector<std::vector<T>> Data;
    size_t Rows;
    size_t Columns;
};

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
std::ostream& operator << (std::ostream& s, const Matrix<T>& rhs) {
    for (const auto& row : rhs.GetData()) {
        for (const auto& elem : row)
            s << elem << " ";
        s << std::endl;
    }
    return s;
};

template <typename T>
Matrix<T>::Matrix() {
    Rows = Columns = 0;
}

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
const std::vector<std::vector<T>>& Matrix<T>::GetData() const {
    return Data;
}

template <typename T>
size_t Matrix<T>::GetColumns() const {
    return Columns;
}

template <typename T>
size_t Matrix<T>::GetRows() const {
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
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {
    Rows = rhs.GetRows();
    Columns = rhs.GetColumns();
    Data = rhs.GetData();
    return *this;
}


template <typename T>
template <typename V>
void Matrix<T>::AppendRow(const std::vector<V>& row) {
    if (row.size() != Columns && Columns)
        throw MatrixException("Size of matrix is not equal size of row");
    Rows++;
    Data.resize(Rows);
    std::transform(row.begin(), row.end(), std::back_inserter(Data[Rows - 1]), [](const V& x) {
        return static_cast<T>(x);
    });
}

template <typename T>
template <typename V>
void Matrix<T>::AppendColumn(const std::vector<V>& column) {
    if (Rows == 0) {
        Data.resize(column.size());
        Rows = Data.size();
    }
    if (column.size() != Rows)
        throw MatrixException("Size of matrix is not equal size of column");
    for (size_t i = 0; i < Rows; i++)
        Data[i].push_back(static_cast<T>(column[i]));
    Columns++;
}

template <typename T>
template <typename V>
void Matrix<T>::SetRow(size_t index, const std::vector<V>& row) {
    if (row.size() != Columns)
        throw MatrixException("Size of matrix is not equal size of row");
    std::transform(row.begin(), row.end(), Data[index].begin(), [](const V& x) {
        return static_cast<T>(x);
    });
}

template <typename T>
template <typename V>
void Matrix<T>::SetColumn(size_t index, const std::vector<V>& column) {
    if (column.size() != Rows)
        throw MatrixException("Size of matrix is not equal size of column");
    for (size_t i = 0; i < Rows; i++)
        Data[i][index] = static_cast<V>(column[i]);
}

template <typename T>
void Matrix<T>::SwapRows(size_t a, size_t b) {
    for (size_t i = 0; i < Columns; i++)
        std::swap(Data[a][i], Data[b][i]);
}

template <typename T>
void Matrix<T>::SwapColumns(size_t a, size_t b) {
    for (size_t i = 0; i < Rows; i++)
        std::swap(Data[i][a], Data[i][b]);
}

template <typename T>
std::vector<T> Matrix<T>::GetColumn(size_t index) {
    if (index >= Columns)
        throw MatrixException("Column's index is out of range");
    std::vector<T> column(Rows);
    for (size_t i = 0; i < Rows; i++)
        column[i] = Data[i][index];
    return column;
}
#endif // MATRIX_H
