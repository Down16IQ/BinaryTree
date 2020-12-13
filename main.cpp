#include <iostream>
//#include "BinaryTree.h"
#include "Node.h"
#include <set>

#define BINARYTREE


// std::set<int>::reverse_iterator rit;
// std::set<int>::iterator it;

int main()
{
#ifndef BINARYTREE
	//std::set<double> obj{ 10, 15, 5, 2, 7, 8, 6, 5.5, 6.5 };	
	std::set<double> obj{ 5,2,1,3,10,7,15,8,11,20,18,25,17,23 };
	auto it = obj.begin();
	it++;
	it++;
	it++;
	std::cout << "Element to delete " << *it << std::endl;
	obj.erase(it);
	auto it2 = obj.begin();
	/*for (it = obj.rbegin(); it != obj.rend(); ++it)
	{
		std::cout << *it << std::endl;
	}*/
#endif // !BINARYTREE
#ifdef BINARYTREE
	Node<double> obj;
	obj.insert(10);
	obj.insert(15);
	obj.insert(5);
	obj.insert(2);
	obj.insert(7);
	obj.insert(6);
	obj.insert(8);
	obj.insert(5.5);
	obj.insert(6.5);
	obj.insert(9);
	obj.insert(9.5);
	auto it = obj.begin();
	it += 5;
	std::cout << *it << " will be deleted\n";
	obj.erase(it);

	for (auto&& it : obj)
	{
		std::cout << it << std::endl;
	}
 	obj.clear();

#endif // !BINARYTREE
	return 0; 
}