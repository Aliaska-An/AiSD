#pragma once
#include <string>

using namespace std;
namespace binTree_modul
{
	typedef char base;

	struct node {
		base info;//узел
		node *lt;//указатель на левого сына
		node *rt;//указатель на правого сына
		// constructor
		node(base elem) { info = elem; lt = NULL; rt = NULL; }
	};

	typedef node *binTree; // "представитель" бинарного дерева
	void menu();
	bool isNull(binTree);
	base RootBT(binTree); //для непустого бинарного дерева
	void destroy(binTree&);
}
