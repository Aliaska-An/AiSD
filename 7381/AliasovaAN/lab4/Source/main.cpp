#include <iostream>
#include <string>
#include <fstream>
#include "Btree.h"
#include "BinTree.cpp"

using namespace std;
using namespace binTree_modul;

ifstream fin("input.txt");
ofstream fout("output.txt");

binTree to_create(string LPK, string LKP);
void printKLP(binTree b);
int find_symb(string LPK, char word);
void print_tree(binTree elem, int l);
void if_error(string LPK, string LKP);

int main() {
	binTree b;
	string LPK, LKP;
		cout << "Enter LPK:";
		fout << "Enter LPK:";
		cin >> LPK;
		fout << LPK << endl;
		cout << "Enter LKP:";
		fout << "Enter LKP:";
		cin >> LKP;
		fout << LKP << endl;
		if_error(LPK, LKP);//проверка на ошибку входных данных
		cout << endl;
		cout << "-------------Intermediate data-------------" << endl;
		fout << "-------------Intermediate data-------------" << endl;
		b = to_create(LPK, LKP);//анализ и создание бд
		cout << "-------------------------------------------" << endl;
		cout << "Full tree:" << endl;
		fout << "-------------------------------------------" << endl;
		fout << "Full tree:" << endl;
		print_tree(b, 0);//печать бд
		cout << "KLP: ";
		fout << "KLP: ";
		printKLP(b);//печать клп-обхода полученного дерева
		cout << endl;
		fout << endl;
		destroy(b);//разрушение бд
	return 0;
}

binTree to_create(string LPK, string LKP) {
	if (LKP.length()==1 && LPK.length() == 1) {//если длина строк равна 1
		if (LPK[0] == LKP[0]) { //и элементы равны
			cout << "The knot [" << LKP[0] << "] is processed." << endl;
			fout << "The knot [" << LKP[0] << "] is processed." << endl;
			return new node(LKP[0]);//создаем узел
		}
		else {//иначе выводим ошибку
			cout << "Error!" << endl;
			fout << "Error!" << endl;
		}
		
	}
	binTree elem = new node('\0');//пустое бд
	binTree sup;//вспомогательное бд(для перестановки указателей)
	int symb;//расстояние от одного символа до другого
	for (size_t i = 0; LKP.length() > i; i++) {
		if (LPK[i] == LKP[i]) {//если равны текущие элементы
			if (elem->info != '\0') { //если уже есть левый узел
				sup = elem;
				elem = to_create(LPK.substr(i, 1), LKP.substr(i, 1));//создаем новое дерево
				elem->lt = sup;//присоединяем слева предыдущее дерево
				cout << "Current subtree:" << endl;
				fout << "Current subtree:" << endl;
				print_tree(elem, 0);
			}
			else {//если нет
				elem->info = LKP[i];//устанавливаем корень
				cout << "The knot [" << LKP[i] << "] is processed." << endl;
				cout << "Current subtree:" << endl;
				fout << "The knot [" << LKP[i] << "] is processed." << endl;
				fout << "Current subtree:" << endl;
				print_tree(elem, 0);
			}
		}
		if (LPK[i] != LKP[i]) {//если это вершина
			if (elem->info != '\0') {//если уже есть правое поддерево
				sup = elem;
				elem = new node(LKP[i]);//создаем новое дерево
				elem->lt = sup;//присоединяем слева текущее дерево
				cout << "The knot [" << LKP[i] << "] is processed." << endl;
				cout << "Current subtree:" << endl;
				fout << "The knot [" << LKP[i] << "] is processed." << endl;
				fout << "Current subtree:" << endl;
				print_tree(elem, 0);
			}
			else { 
				elem->info = LKP[i];//если нет
				cout << "The knot [" << LKP[i] << "] is processed." << endl;
				cout << "Current subtree:" << endl;
				fout << "The knot [" << LKP[i] << "] is processed." << endl;
				fout << "Current subtree:" << endl;
				print_tree(elem, 0);
			}
			symb = find_symb(LPK.substr(i,LPK.length()), LKP[i]);//находим текущую ветку в ЛПК-обходе
			elem->rt = to_create(LPK.substr(i, symb), LKP.substr(i + 1, symb));//строим правое поддерево
			cout << "Current(united) subtree:" << endl;
			fout << "Current(united) subtree:" << endl;
			print_tree(elem, 0);
			i += symb;
		}
	}
	return elem;
 }

void printKLP(binTree b)//печать КЛП
{
	if (!isNull(b)) {//если не пусто
		cout << RootBT(b);//печатаем корень
		fout << RootBT(b);
		if (b == NULL) { cerr << "Error: Left(null) \n"; exit(1); }
		else printKLP(b->lt);//переходим к левому поддереву

		if (b == NULL) { cerr << "Error: Right(null) \n"; exit(1); }
		else printKLP(b->rt);//переходим к правому поддереву
	}
}
void if_error(string LPK, string LKP) {
	if (LPK.length() != LKP.length()) {//если разные длины строк
		cout << "Error.LPK and LKP have different sizes" << endl;
		fout << "Error.LPK and LKP have different sizes" << endl;
	}

	//проверка на разные символы
	for (size_t i = 0; i < LPK.length(); i++) {
		for (size_t j = 0; j < LKP.length(); j++) {
			if (LPK[i] != LKP[j] && j == LKP.length() - 1) {
				cout << "Error.LPK and LKP have different symbols" << endl;
				fout << "Error.LPK and LKP have different symbols" << endl;
			}
			else if (LPK[i] == LKP[j]) break;
		}
	}
}

void print_tree(binTree elem, int l) {//печать дерева
	if (elem != 0) {//если дерево не пусто
		print_tree(elem->rt, l + 1);//переходим к правому поддереву
		for (int i = l; i > 0; i--) { cout << "  "; fout << "  ";}//печатаем отступ соответствующий уровню
		cout << elem->info << '\n';//печатаем вершину
		fout << elem->info << '\n';
		print_tree(elem->lt, l + 1);//переходим к правому поддереву
	}
}

//нахождение вхождения символа в строке LPK
int find_symb(string LPK, char word) {
	int i = 0;
	while (LPK[i] != word) {//пока символ не найден
		i++;
		if (i == LPK.length()) {//если не найден выдать ошибку
			cout << "Error!" << endl;
			fout << "Error!" << endl;
		}
	}
	return i;
}
