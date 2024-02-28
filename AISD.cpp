#include "Matrix.h"

int main() {
    setlocale(LC_ALL, "Rus");
    // Создаем квадратную матрицу A
    Matrix<double> A(3, 3, 1.0); // Создание матрицы 3x3 с заполнением значениями 1.0

    std::cout << "Исходная матрица A:" << std::endl;
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            std::cout << A(i, j) << " ";
        }
        std::cout << std::endl;
    }

    // Приводим матрицу A к нижнетреугольному виду
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = i + 1; j < 3; ++j) {
            if (A(i, i) != 0) {
                double coeff = A(j, i) / A(i, i);
                for (size_t k = 0; k < 3; ++k) {
                    A(j, k) -= coeff * A(i, k);
                }
            }
            else {
                // Обработка деления на ноль или других ошибочных условий
                std::cerr << "Ошибка: Деление на ноль или другое ошибочное условие." << std::endl;
            }
        }
    }

    std::cout << "Матрица A в нижнетреугольном виде:" << std::endl;
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            if (j >= i) {
                std::cout << A(i, j) << " ";
            }
            else {
                std::cout << "0 ";
            }
        }
        std::cout << std::endl;
    }

    return 0;
}

