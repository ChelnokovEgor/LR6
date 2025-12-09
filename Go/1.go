package main

import (
	"fmt"
	"math/rand"
	"time"
)


func countNeighbors(grid [][]int, i, j, rows, cols int) int {
	count := 0
	for di := -1; di <= 1; di++ {
		for dj := -1; dj <= 1; dj++ {
			if di == 0 && dj == 0 {
				continue
			}
			ni := (i + di + rows) % rows
			nj := (j + dj + cols) % cols
			count += grid[ni][nj]
		}
	}
	return count
}

func nextGen(grid [][]int, mode int) [][]int {
	rows := len(grid)
	cols := len(grid[0])
	next := make([][]int, rows)
	for i := range next {
		next[i] = make([]int, cols)
	}

	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			alive := grid[i][j]
			n := countNeighbors(grid, i, j, rows, cols)
			if mode == 0 {
				if alive == 1 {
					if n == 2 || n == 3 {
						next[i][j] = 1
					}
				} else {
					if n == 3 {
						next[i][j] = 1
					}
				}
			} else {
				if alive == 1 {
					if n == 1 || n == 3 || n == 5 {
						next[i][j] = 1
					}
				} else {
					if n == 2 || n == 4 {
						next[i][j] = 1
					}
				}
			}
		}
	}
	return next
}

func placeGlider(grid [][]int, r, c int) {
	rows := len(grid)
	cols := len(grid[0])
	grid[(r+0)%rows][(c+1)%cols] = 1
	grid[(r+1)%rows][(c+2)%cols] = 1
	grid[(r+2)%rows][(c+0)%cols] = 1
	grid[(r+2)%rows][(c+1)%cols] = 1
	grid[(r+2)%rows][(c+2)%cols] = 1
}

func randomInit(grid [][]int, density float64) {
	rows := len(grid)
	cols := len(grid[0])
	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			if rand.Float64() < density {
				grid[i][j] = 1
			} else {
				grid[i][j] = 0
			}
		}
	}
}

func number11() {
	rand.Seed(time.Now().UnixNano())
	var N int
	fmt.Print("Задача 1: \nВведите N: ")
	fmt.Scanln(&N)

	matrix := make([][]int, N)
	for i := range matrix {
		matrix[i] = make([]int, N)
		for j := range matrix[i] {
			matrix[i][j] = rand.Intn(201) - 100
		}
	}

	maxPosCount := -1
	bestRowIdx := -1
	for i := 0; i < N; i++ {
		posCount := 0
		for j := 0; j < N; j++ {
			if matrix[i][j] > 0 {
				posCount++
			}
		}
		if posCount > maxPosCount {
			maxPosCount = posCount
			bestRowIdx = i
		}
	}

	var resultRow []int
	if bestRowIdx != -1 {
		resultRow = make([]int, N)
		copy(resultRow, matrix[bestRowIdx])
	}

	fmt.Println("\nМатрица:")
	for _, row := range matrix {
		for _, val := range row {
			fmt.Printf("%4d ", val)
		}
		fmt.Println()
	}

	fmt.Printf("\nСтрока с наибольшим количеством положительных чисел (%d): ", maxPosCount)
	for _, x := range resultRow {
		fmt.Print(x, " ")
	}
	fmt.Println()
	fmt.Println()
}

func number12() {
	rand.Seed(time.Now().UnixNano())
	var M, N int
	fmt.Print("Задача 2\nВведите M и N: ")
	fmt.Scanln(&M, &N)

	matrix := make([][]int, M)
	freq := make(map[int]int)
	for i := range matrix {
		matrix[i] = make([]int, N)
		for j := range matrix[i] {
			matrix[i][j] = 100 + rand.Intn(51)
			freq[matrix[i][j]]++
		}
	}

	maxFreq := 0
	mostFreqNum := -1
	for num, cnt := range freq {
		if cnt > maxFreq {
			maxFreq = cnt
			mostFreqNum = num
		}
	}

	allUnique := true
	for _, cnt := range freq {
		if cnt > 1 {
			allUnique = false
			break
		}
	}

	fmt.Println("\nМатрица:")
	for _, row := range matrix {
		for _, val := range row {
			fmt.Print(val, " ")
		}
		fmt.Println()
	}

	if allUnique {
		fmt.Println("\nВсе числа уникальны — нет числа, встречающегося чаще других.")
	} else {
		fmt.Printf("\nНаиболее часто встречающееся число: %d (встречается %d раз(а))\n", mostFreqNum, maxFreq)
	}
}

func number13() {
	rand.Seed(time.Now().UnixNano())
	rows, cols := 20, 50
	mode := 0
	steps := 200

	fmt.Print("Задача 3:\n")
	fmt.Print("Выберите режим:\n0 — классические правила\n1 — альтернативные\n")
	fmt.Scanln(&mode)

	grid := make([][]int, rows)
	for i := range grid {
		grid[i] = make([]int, cols)
	}

	fmt.Print("Инициализация:\n1 — глайдер\n2 — случайная колония\n")
	var init int
	fmt.Scanln(&init)

	switch init {
	case 1:
		placeGlider(grid, rows/2-1, cols/2-2)
	case 2:
		randomInit(grid, 0.25)
	default:
		fmt.Println("Неверный выбор. Используется случайная инициализация (20%).")
		randomInit(grid, 0.2)
	}

	fmt.Println("Cимуляция")
	for gen := 0; gen < steps; gen++ {
		modeStr := "классический"
		if mode != 0 {
			modeStr = "альтернативный"
		}
		fmt.Printf("Поколение: %d | Режим: %s\n", gen, modeStr)
		for i := 0; i < rows; i++ {
			for j := 0; j < cols; j++ {
				if grid[i][j] == 1 {
					fmt.Print("0")
				} else {
					fmt.Print(" ")
				}
			}
			fmt.Println()
		}
		grid = nextGen(grid, mode)
	}
	fmt.Println("\nСимуляция завершена.")
}
