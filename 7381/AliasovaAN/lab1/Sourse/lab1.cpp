#include <iostream>
#include <string>
#include <string.h>

using namespace std;

int find_way(int deep, int first, int second, bool **matr, int city_count) { //функция для нахождения пути
	for(int i = 0; i < deep; i++)
		cout << "\t";
	cout << "->rec with " << first << " " << second << endl;
	if(matr[first-1][second-1] || first == second) {
		for(int i = 0; i < deep; i++)
			cout << "\t";
			return 1;
	}
	for(int i = 0; i < city_count; i++) {
		if(matr[first-1][i-1]) {
			matr[first-1][i-1] = false;
			if(find_way(deep+1, i, second, matr, city_count)) {
				for(int i = 0; i < deep; i++)
					cout << "\t";
				cout << "<-rec" << endl;
				return 1;
			}
		}
	}
	for(int i = 0; i < deep; i++)
		cout << "\t";
	cout << "<-rec" << endl;

	return 0;
}

void proverka(int &a, char* stroka){ //проверка на дурака
	bool test = true;
	do {
		cout << stroka << endl;
		cin >> a;
		if ( !(test = cin.good()) )
			cout << "Вы ввели не число!" << endl;
		cin.clear() ;
		cin.ignore(1) ;
	} while(!test);
return;
}

int main(){

	int city_count;					//ввод кол-ва городов
	char str[] = "Введите количество городов:";
	proverka(city_count, str);

	if (city_count == 0){				//проверка на пустоту списка
                cout << "Пустой список";
                 return 0;
	}

	bool **matr = new bool *[city_count]; 		//динамическое выделение памяти
	for (int i = 0; i < city_count; i++)
		matr[i] = new bool [city_count];

	int road_count;
							//ввод кол-ва дорог
	char str1[] = "Введите количество дорог: ";
	proverka(road_count, str1);

	cout << "Введите дороги:\n";			//ввод самих дорог
	for (int k = 0; k < road_count; k++) {
		int i, j;
		cin >> i >> j;

		try {
			if (i > city_count || i < 1 || j > city_count || j < 1)
				throw "Не существует указаного города.";
		}
		catch (const char * string){
			cout << string << endl << "Повторите ввод: ";
			k--;
			continue;
		}
			matr[i-1][j-1] = true;		//создание матрицы смежности
			matr[j-1][i-1] = true;
	}

	cout << "Введите начальный и конечный города: " << endl;//ввод начального и конечного города
	int start, finish;
	cin >> start >> finish;

	if (find_way(0, start, finish, matr, city_count))
		cout << "YES" << endl;
	else
		cout << "NO" << endl;

	for(int i = 0 ; i < city_count; i++)		//очищение памяти
		free(matr[i]);
	free(matr);
	return 0;
}
