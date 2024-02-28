#include <iostream>
#include <vector>
#include <random>
#include <complex>

template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    size_t rows;
    size_t cols;

public:
    Matrix(size_t rows, size_t cols, T value) : rows(rows), cols(cols) {
        data.resize(rows, std::vector<T>(cols, value));
    }

    Matrix(size_t rows, size_t cols, T lower, T upper) : rows(rows), cols(cols) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<T> dis(lower, upper);

        data.resize(rows, std::vector<T>(cols));
        for (size_t i = 0; i < rows; ++i) {
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

    Matrix<T> operator/(T scalar) {
        if (scalar == 0) {
            std::cerr << "Error: Division by zero" << std::endl;
            return *this;
        }

        Matrix<T> result(rows, cols, 0);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] / scalar;
            }
        }
        return result;
    }

    T trace() {
        if (rows != cols) {
            std::cerr << "Error: Trace is only defined for square matrices" << std::endl;
            return T();
        }

        T sum = T();
        for (size_t i = 0; i < rows; ++i) {
            sum += data[i][i];
        }
        return sum;
    }

    
};
