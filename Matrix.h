#include <iostream>
#include <random>
#include <complex>

template <typename T>
class Matrix {
private:
    T** data;
    size_t rows;
    size_t cols;

public:
    Matrix(size_t rows, size_t cols, T value) : rows(rows), cols(cols) {
        data = new T * [rows];
        for (size_t i = 0; i < rows; ++i) {
            data[i] = new T[cols];
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] = value;
            }
        }
    }

    Matrix(size_t rows, size_t cols, T lower, T upper) : rows(rows), cols(cols) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<T> dis(lower, upper);

        data = new T * [rows];
        for (size_t i = 0; i < rows; ++i) {
            data[i] = new T[cols];
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] = dis(gen);
            }
        }
    }

    T& operator()(size_t i, size_t j) {
        return data[i][j];
    }

    const T& operator()(size_t i, size_t j) const {
        return data[i][j];
    }

    Matrix<T> operator+(const Matrix<T>& other) {
        Matrix<T> result(rows, cols, 0);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] + other(i, j);
            }
        }
        return result;
    }

    Matrix<T> operator*(const Matrix<T>& other) {
        Matrix<T> result(rows, other.cols, 0);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                for (size_t k = 0; k < cols; ++k) {
                    result(i, j) += data[i][k] * other(k, j);
                }
            }
        }
        return result;
    }

    Matrix<T> operator*(T scalar) {
        Matrix<T> result(rows, cols, 0);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] * scalar;
            }
        }
        return result;
    }

    bool operator==(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols)
            return false;

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (data[i][j] != other(i, j))
                    return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix<T>& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix) {
        for (size_t i = 0; i < matrix.rows; ++i) {
            for (size_t j = 0; j < matrix.cols; ++j) {
                out << matrix(i, j) << " ";
            }
            out << std::endl;
        }
        return out;
    }

    ~Matrix() {
        if (data != nullptr) {
            for (size_t i = 0; i < rows; ++i) {
                delete[] data[i];
            }
            delete[] data;
        }
    }
};
