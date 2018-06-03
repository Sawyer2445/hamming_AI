#include "hamming_network.h"
#include <algorithm>

int hamming::network::work()
{
	std::string view = { "111111111" };
	double_vector oldY1 = new double[K];
	const int_vector xx = new int[this->M];
	for (int i = 0; i < M; i++)
	{
		xx[i] = view[i] == '1' ? 1 : -1;
	}

	for (auto i = 0; i < K; i++)
	{
		double sum = 0;
		for (auto j = 0; j < M; j++)
		{
			sum += w_[i][j] * xx[j];
		}
		s1[i] = sum + this->T;
		s2[i] = s1[i];	//делаетс€ один раз
		std::cout << s1[i] << ' ';
	}
	std::cout << '\n';	//8 2 3

	//выход нейронов первого сло€ 
	for (auto i = 0; i < K; i++)
	{
		y1[i] = f(s1[i]);

		y2[i] = y1[i];	//делаетс€ один раз
		std::cout << y2[i] << ' '; 
	}
	std::cout << '\n'; //4.5 2 3

	do
	{
		for (auto i = 0; i < K; i++)
		{
			double sum = 0;
			for (auto j = 0; j < K; j++)
			{
				sum += eps_[i][j] * y2[j] * 1.0;
			}
			oldY1[i] = y2[i];
			s2[i] = sum;
			y2[i] = f(s2[i]);
		}
	} while (vec_norm(y2, oldY1, K) > eMax_);


	//печатаем индекс класса 
	double max = y2[0];
	int indx = 0;
	for (auto i = 1; i < K; i++)
	{
		if (y2[i] > max)
		{
			max = y2[i];
			indx = i;
		}
	}
	std::cout << indx + 1;
	


	return  -1;

}

hamming::network::network()
{
	
	setlocale(LC_ALL, "RUS");
	std::cout << "¬ведите количество образов: ";
	int k;
	std::cin >> k;
	std::cout << "¬ведите размерность картинок\n";
	int x, y;
	std::cout << "X: "; std::cin >> x;
	std::cout << "Y: "; std::cin >> y;

	this->K = k;
	this->M = x * y;
	this->T = M / 2.0;
	this->eps = 1.0 / K;
	s1 = new double[K];
	s2 = new double[K];
	y1 = new double[K];
	y2 = new double[K];

	//чтение потом 

	std::string view1 = "101010101";
	std::string view2 = "010111010";
	std::string view3 = "111101111";

	x_ = new int *[K];
	for (int i = 0; i < K; i++)
	{
		x_[i] = new int[M];

	}

	//сделать лучше 
	for (int j = 0; j < M; j++)
	{
		x_[0][j] = view1[j] == '1' ? 1 : -1;
	}
	for (int j = 0; j < M; j++)
	{
		x_[1][j] = view2[j] == '1' ? 1 : -1;
	}
	for (int j = 0; j < M; j++)
	{
		x_[2][j] = view3[j] == '1' ? 1 : -1;
	}

	w_ = new double *[K];
	for (int i = 0; i < K; i++)
	{
		w_[i] = new double[M];
		for (int j = 0; j < M; j++)
		{
			w_[i][j] = x_[i][j] / 2.0;
		}
	}

	eps_ = new double*[K];
	for (int i = 0; i < K; i++)
	{
		eps_[i] = new double[K];
		for (int j = 0; j < K; j++)
		{
			eps_[i][j] = i == j ? 1 : -eps;
		}
	}

	eMax_ = 0.1;
	print_matrix(K, M, x_);
	print_matrix(K, M, w_);
	print_matrix(K, K, eps_);

	
}

double hamming::network::f(double s) const
{
	if (s <= 0)
		return 0;
	if (0 < s && s <= T)
		return s;
	if (s >= T)
		return T;
	return -1;
}
