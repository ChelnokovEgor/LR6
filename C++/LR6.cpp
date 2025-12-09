#include <iostream>
#include "1.h"
#include "2.h"
#include "3.h"
#include "4.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");

	int k;
	cin >> k;

	switch (k)
	{
	case 1:
	{
		number11();
		number12();
		number13();
		break;
	}
	case 2:
	{
		AESOFB();
		break;
	}
	case 3:
	{
		gauss();
		solveSeidel();
		break;
	}
	case 4:
	{
		path();
		break;
	}
	default:
		break;
	}

}