#ifndef HAMMING_NETWORK
#define HAMMING_NETWORK

#include <vector>
#include <iostream>
#include "print_matr.h"
#include "norm.h"
#include <iterator>
#include <fstream>

namespace hamming
{
	class network
	{
	private:
		using int_matrix = int**;
		using double_matrix = double**;
		using  double_vector = double*;
		using  int_vector = int*;

		int_matrix x_;		//������� ��������� �������
		double_matrix w_;	//������� ����� ������� ���� 
		double_matrix eps_;	//�������� �������� ������� ���� 
		double_vector s1;
		double_vector s2;
		double_vector y1;
		double_vector y2;

		double eMax_;	//�������� ������������
		double T;			//����� ������������� �������
		double eps;		// �������� ���� ������������� ������� (0;1/K)
		int K;
		int M;
		int sh;
		
	
	public:
		void work();


		network();
		//������������� �������
		double f(double s) const;

		//������ ������ �� ����� 
		std::string read_view(std::string path);

		void print_view(const std::string&, int) const;
	};

	
}

#endif
