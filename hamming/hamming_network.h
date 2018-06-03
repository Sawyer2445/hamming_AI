#ifndef HAMMING_NETWORK
#define HAMMING_NETWORK

#include <vector>
#include <iostream>
#include "print_matr.h"
#include "norm.h"

namespace hamming
{
	class network
	{
	private:
		using int_matrix = int**;
		using double_matrix = double**;
		using  double_vector = double*;
		using  int_vector = int*;

		int_matrix x_;		//матрица эталонных образов
		double_matrix w_;	//матрица весов первого слоя 
		double_matrix eps_;	//значение синапсов второго слоя 
		double_vector s1;
		double_vector s2;
		double_vector y1;
		double_vector y2;

		double eMax_;	//критерия стабилизации
		double T;			//порог активационной функции
		double eps;		// значение веса ингибиторного синапса (0;1/K)
		int K;
		int M;
	
	public:
		int work();


		network();
		//активационная функция
		double f(double s) const;
	};

	
}

#endif
