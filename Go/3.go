package main

import (
	"fmt"
	"math"
)

func printMatrix(matrix [][]float64) {
	n := len(matrix)
	for i := 0; i < n; i++ {
		fmt.Print("[")
		for j := 0; j < n; j++ {
			fmt.Printf("%12.6f", matrix[i][j])
		}
		fmt.Printf(" | %12.6f ]\n", matrix[i][n])
	}
	fmt.Println()
}

func gaussElimination(matrix [][]float64) {
	n := len(matrix)
	for k := 0; k < n-1; k++ {
		pivotRow := k
		maxVal := math.Abs(matrix[k][k])
		for i := k + 1; i < n; i++ {
			val := math.Abs(matrix[i][k])
			if val > maxVal {
				maxVal = val
				pivotRow = i
			}
		}
		if pivotRow != k {
			matrix[k], matrix[pivotRow] = matrix[pivotRow], matrix[k]
			fmt.Printf("Обмен строк %d и %d\n", k+1, pivotRow+1)
		}

		for i := k + 1; i < n; i++ {
			if math.Abs(matrix[k][k]) < 1e-10 {
				fmt.Println("Матрица вырожденная или плохо обусловленная!")
				return
			}
			factor := matrix[i][k] / matrix[k][k]
			for j := k; j <= n; j++ {
				matrix[i][j] -= factor * matrix[k][j]
			}
		}
		fmt.Printf("Шаг %d:\n", k+1)
		printMatrix(matrix)
	}
}

func backSubstitution(matrix [][]float64) []float64 {
	n := len(matrix)
	x := make([]float64, n)
	for i := n - 1; i >= 0; i-- {
		if math.Abs(matrix[i][i]) < 1e-10 {
			fmt.Println("Нулевой диагональный элемент! Система может не иметь единственного решения.")
			return x
		}
		sum := matrix[i][n]
		for j := i + 1; j < n; j++ {
			sum -= matrix[i][j] * x[j]
		}
		x[i] = sum / matrix[i][i]
	}
	return x
}

func gauss() {
	matrix := [][]float64{
		{0.89, -0.04, 0.21, -18.00, -1.24},
		{0.25, -1.23, 0.08, -0.09, -1.21},
		{-0.21, 0.08, 0.80, -0.13, 2.56},
		{0.15, -1.31, 0.06, -1.21, 0.89},
	}

	fmt.Println("Исходная расширенная матрица [A | b]:")
	printMatrix(matrix)

	gaussElimination(matrix)

	solution := backSubstitution(matrix)
	fmt.Println("Решение системы:")
	for i, val := range solution {
		fmt.Printf("x[%d] = %.10f\n", i+1, val)
	}
	fmt.Println()
}

func checkDiagonalDominance(matrix [][]float64) bool {
	size := len(matrix)
	for i := 0; i < size; i++ {
		sum := 0.0
		for j := 0; j < size; j++ {
			if j != i {
				sum += math.Abs(matrix[i][j])
			}
		}
		if math.Abs(matrix[i][i]) <= sum {
			fmt.Printf("Нет диагонального преобладания в строке %d\n", i+1)
			return false
		}
	}
	return true
}

func solveSeidel() {
	epsilon := 1e-3
	maxIterations := 5

	matrixA := [][]float64{
		{0.89, -0.04, 0.21, -18.00},
		{0.25, -1.23, 0.08, -0.09},
		{-0.21, 0.08, 0.80, -0.13},
		{0.15, -1.31, 0.06, -1.21},
	}
	vectorB := []float64{-1.24, -1.21, 2.56, 0.89}

	if !checkDiagonalDominance(matrixA) {
		fmt.Println("Метод Зейделя может не сойтись из-за отсутствия диагонального преобладания")
	}

	size := len(matrixA)
	solution := make([]float64, size)
	iterations := 0
	var error float64

	for {
		error = 0.0
		oldSolution := make([]float64, size)
		copy(oldSolution, solution)

		for i := 0; i < size; i++ {
			sum := 0.0
			for j := 0; j < size; j++ {
				if j != i {
					sum += matrixA[i][j] * solution[j]
				}
			}
			newValue := (vectorB[i] - sum) / matrixA[i][i]
			if diff := math.Abs(newValue - solution[i]); diff > error {
				error = diff
			}
			solution[i] = newValue
		}

		iterations++
		if error <= epsilon || iterations >= maxIterations {
			break
		}
	}

	fmt.Println("Решение системы методом Зейделя:")
	fmt.Printf("Количество итераций: %d\n", iterations)
	fmt.Printf("x1 = %.6f\n", solution[0])
	fmt.Printf("x2 = %.6f\n", solution[1])
	fmt.Printf("x3 = %.6f\n", solution[2])
	fmt.Printf("x4 = %.6f\n", solution[3])
}
