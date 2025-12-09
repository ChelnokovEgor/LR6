package main

import "fmt"

func main() {
	var choice int
	fmt.Scanln(&choice)

	switch choice {
	case 1:
		number11()
	case 2:
		number12()
	case 3:
		number13()
	case 4:
		AESOFB()
	case 5:
		gauss()
		solveSeidel()
	case 6:
		path()
	default:
		fmt.Println("Неизвестный выбор")
	}
}
