#include <iostream>
#include "llist.h"
#include <exception>
#include <stdexcept>
#include <fstream>


using namespace std;

void dump(const LList& l)
{
	if (l.size() == 0)
		cout << "Empty" << endl;
	for (size_t i = 0; i < l.size(); i++)
	{
		cout << l[i] << " ";
	}
}

int main()
{
	LList l;
	l.push_back(3);
	l.push_front(0);
	l.push_back(2);	
	l.push_back(4);
	l.push_front(7);
	l.push_back(8);

	cout << "Stage 1: ";
	dump(l);
	cout << endl;

	l.erase_at(2);
	cout << "Stage 2: ";
        dump(l);
        cout << endl;

	l.insert_at(2, 10);
	cout << "Stage 3: ";
	dump(l);
	cout << endl;

	l.erase_at(2);
	cout <<  "Stage 4: ";
        dump(l);
        cout << endl;
	
	l.reverse();
	cout << "Stage 5: ";
	dump(l);
	cout << endl;

	for (size_t i = 0; i < 20000; ++i)
		l.push_back(i+1);

	LList c = l; //по графику, построенному с помощью valgrind, установлено, что объем памяти равен 1.374 мБ
	LList k = move(c); //468.9 кБ
	

	cout << "size is " << k.size() << endl;

	return 0;
}
