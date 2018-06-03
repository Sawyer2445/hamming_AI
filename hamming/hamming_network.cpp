#include "hamming_network.h"
#include <algorithm>
#include <string>

void hamming::network::work()
{
	std::string path;
	std::cout << "Укажите путь образу для распознования: ";
	std::cin >> path;


	std::string view = read_view(path);
	print_view(view, sh);
	double_vector oldY1 = new double[K];
	const int_vector xx = new int[this->M];
	for (int i = 0; i < M; i++)
	{
		xx[i] = view[i] == '#' ? 1 : -1;
	}

	for (auto i = 0; i < K; i++)
	{
		double sum = 0;
		for (auto j = 0; j < M; j++)
		{
			sum += w_[i][j] * xx[j];
		}
		s1[i] = sum + this->T;
		s2[i] = s1[i];	//делается один раз
	}

	//выход нейронов первого слоя 
	for (auto i = 0; i < K; i++)
	{
		y1[i] = f(s1[i]);

		y2[i] = y1[i];	//делается один раз
	}

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
	std::cout << "Образ соответствует классу: " <<  indx + 1 << std::endl;
	
}

hamming::network::network()
{
	
	setlocale(LC_ALL, "RUS");
	std::cout << "Введите размерность картинок\n";
	int x, y;
	std::cout << "Ширина: "; std::cin >> x;
	std::cout << "Высота: "; std::cin >> y;
	std::cout << "Введите количество образов: ";
	int k;
	std::cin >> k;

	

	this->sh = x;
	this->K = k;
	this->M = x * y;
	this->T = M / 2.0;
	this->eps = 1.0 / K;
	s1 = new double[K];
	s2 = new double[K];
	y1 = new double[K];
	y2 = new double[K];

	//чтение образов и сохранение их в массив строк 
	std::vector<std::string> views;

	for (auto i = 0; i < k; i++)
	{
		std::string path;
		std::cout << "Путь к эталонному образу " << i + 1<< ": ";
		std::cin >> path;
		views.push_back(read_view(path));
		std::cout << "Класс № " << i + 1;
		print_view(views[i], x);
	}
	x_ = new int *[K];
	for (int i = 0; i < K; i++)
	{
		x_[i] = new int[M];

	}

	for (auto i = 0; i < K; i++)
	{
		for (auto j = 0; j < M; j++)
		{
			x_[i][j] = views[i][j] == '#' ? 1 : -1;
		}
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

std::string hamming::network::read_view(const std::string path)
{
	std::ifstream file(path);
	std::string view = "";
	while (file)
	{
		std::string str;
		std::getline(file, str);
		view += str;
	}
	file.close();
	return view;
}

void hamming::network::print_view(const std::string& view, int x) const
{
	for(auto i = 0; i < view.size(); i++)
	{
		if (!(i % x))
			std::cout << '\n';
		std::cout << view[i];
	}
	std::cout << "\n________________\n\n";
}
