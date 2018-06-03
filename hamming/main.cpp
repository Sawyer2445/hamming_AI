#include <iostream>
#include "hamming_network.h"
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace hamming;

int main()
{
	/*std::cout << "Enter path: ";
	std::string path;
	std::getline(std::cin, path);
	path.erase(0, 1);
	path.erase(path.size()-1, 1);
	std::ifstream file(path);
	std::string view = "";
	while(file)
	{
		std::string str;
		std::getline(file, str);
		view += str;
		std::cout << str <<  '\n';
	}
	std::cout << view;*/
	auto n1 = new network();
	n1->work();

	system("pause");
	return 0;
}