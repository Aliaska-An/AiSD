#include <iostream>
#include <string>
#include <cstdlib>
#include "Btree.h"
using namespace std;

namespace binTree_modul
{	
	//-------------------------------------
	bool isNull(binTree b)//проверка на пустое дерево
	{
		return (b == NULL);
	}
	//-------------------------------------
	base RootBT(binTree b)			// для непустого бинарного дерева
	{
		if (b == NULL) { cerr << "Error: RootBT(null) \n"; exit(1); }
		else return b->info;
	}

	//-------------------------------------			
	void destroy(binTree &b)//разрушение бинарного дерева
	{
		if (b != NULL) {
			destroy(b->lt);
			destroy(b->rt);
			delete b;
			b = NULL;
		}
	}

} 
