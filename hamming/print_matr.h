#ifndef PRINT_MATR
#define PRINT_MATR

#include <iostream>

template <class T>
void print_matrix(const int i, const int j, T** matr)
{
	for (auto i_ = 0; i_ < i; i_++)
	{
		for (auto j_ = 0; j_ < j; j_++)
		{
			std::cout << matr[i_][j_] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << "------------\n";
}
#endif
