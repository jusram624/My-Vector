
/**
 * You don't have to modify this source file, but can if you want.
 * This will not be used for grading, so you can use it to debug your
 * vector class.
 * This is the program that runs with "make run"
 */

///	Your welcome
#include <iostream>
#include "MyVector.hpp"

///	Your welcome
using std::cout, std::endl;

//
int main()
{
	//
	//cout << "Hello! Maybe use this source file for debugging?" << endl;
	
	MyVector<int> vector;

	for (size_t i = 0; i <= 1090; i++)
	{
		cout << vector.push_back(i) <<" ";
	}
//TEST .insert()
	for (size_t i = 0; i <= 408; i++)
	{
		cout << vector.pop_back() <<" ";
	}
/*	
//test .capacity()
	cout << "Capcity: " << vector.capacity() << endl;
//TEST .size()
	cout << "Size: " << vector.size() << endl;
//TEST.empty()
	if(vector.empty() == true)
		cout << "Is Empty" << endl;
	else
		cout << "Not Empty" << endl;
//TEST .insert()
	cout << vector.at(0) << " " << vector.at(1) << " " << vector.at(2) << endl;
	cout << "New size: " << vector.erase(1)<< endl;
*/

//vector.pop_back();//
//vector.clear();
cout <<endl;
for (size_t i = 0; i < vector.size(); i++)
{
	cout << vector.at(i) << " " ;
}
cout << endl;
cout << "Size: " << vector.size() << endl;
cout << "Capacity: " << vector.capacity() << endl;
//cout << vector.at(9);
	return 0;
}

