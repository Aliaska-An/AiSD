#include <iostream> 
#include <fstream> 
#include <cstdlib> 
#include <locale.h> 
#include "Queue.cpp"

using namespace std;
void menu()//меню
{
	cout << "============================================" << endl;
	cout << "Davkaeva Valentina 7382 lab3 variant 5v" << endl;
	cout << "====================MENU====================" << endl;
	cout << "============================================" << endl;
	cout << "1.Read the string from file." << endl;
	cout << "2.End the program." << endl;
	cout << "============================================" << endl;
	cout << "Your choice:";
}
void call_error(Queue & Q3, int num) // функция,показывающая место ошибки 
{
	switch (num)
	{
	case 1:
	{	cout << "------------------------------------Error-----------------------------------------" << endl;
	cout << "The last read element doesn't satisfy the definition of the text.Expected symbol or curcle close bracket." << endl;
	break;
	}
	case 2:
	{	cout << "------------------------------------Error-----------------------------------------" << endl;
	cout << "The last read element doesn't satisfy the definition of the text.Expected symbol or square close bracket." << endl;
	break;
	}
	case 3:
	{
		cout << "------------------------------------Error-----------------------------------------" << endl;
		cout << "The last read element doesn't satisfy the definition of the text.Expected symbol or figure close bracket." << endl;
		break;
	}
	case 4:
	{
		cout << "------------------------------------Error-----------------------------------------" << endl;
		cout << "The last read element doesn't satisfy the definition of the text.Expected symbol or open bracket of any tipe." << endl;
		break;
	}
	case 5:
	{
		cout << "------------------------------------Error-----------------------------------------" << endl;
		cout << "Not enough for the text.Expected symbol or circle close bracket." << endl;
		break;
	}
	case 6:
	{
		cout << "------------------------------------Error-----------------------------------------" << endl;
		cout << "Not enough for the text.Expected symbol or figure close bracket." << endl;
		break;
	}
	case 7:
	{
		cout << "------------------------------------Error-----------------------------------------" << endl;
		cout << "Not enough for the text.Expected symbol or square close bracket." << endl;
		break;
	}
	}
	cout << "This isn't a text!" << endl;
	cout << "Part of the string, which can be completed to the text: ";//Часть строки, которая является формулой и может быть завершена. 
	while (Q3.can_pop())//если элемент можно взять
		cout << Q3.pop() << " ";//печать посимвольно элементов очереди
	cout << "\nEnd of analyzing! " << endl;//Программа будет завершена. 
	system("pause");
	exit(1);
}
bool cur_brckt_o(char symb) // проверка круглой открытой скобки 
{
	if (symb == '(')
		return true;
	else
		return false;
}
bool cur_brckt_c(char symb) // проверка круглой закрытой скобки 
{
	if (symb == ')')
		return true;
	else
		return false;
}
bool sq_brckt_o(char symb) // проверка квадратной открытой скобки 
{
	if (symb == '[')
		return true;
	else
		return false;
}
bool sq_brckt_c(char symb) // проверка квадратной закрытой скобки
{
	if (symb == ']')
		return true;
	else
		return false;
}
bool fig_brckt_o(char symb) // проверка фигурной открытой скобки 
{
	if (symb == '{')
		return true;
	else
		return false;
}
bool fig_brckt_c(char symb) // проверка фигурной закрытой скобки
{
	if (symb == '}')
		return true;
	else
		return false;
}

bool symb_f(char symb) //является ли элемент именем 
{
	if (symb == '(' || symb == '{' || symb == '[' || symb == ')' || symb == '}' || symb == ']')
		return false;
	else
		return true;
}
void is_it_txt(Stack Q1, Queue & Q3) //анализирующая функция
{
	char symb;
	Stack pos;//стек,служащий для хранения позиции и типа скобки
	bool bracket_c_cur, bracket_c_sq, bracket_c_fig;
	int n;
	bracket_c_cur = bracket_c_sq = bracket_c_fig = false;//вначале не ожидается закрытая скобка любого типа 
	while (Q1.can_pop())//пока стек не пуст
	{
		symb = Q1.pop();//взятие элемента
		cout << "   From the stack, the element is extracted [" << symb << "] ";//Из стека извлечен элемент [ 
		if (symb_f(symb))// если символ
		{
			cout << ",which is the symbol " << endl;//который является элементом.
			if (pos.can_pop()) {//если уже есть открытая скобка любого типа
				n = pos.pop();//узнаем,какого типа
				if (n == 1) {//круглая скобка
					bracket_c_cur = true;//тогда ожидается закрывающая-ся  круглая скобка
					bracket_c_sq = bracket_c_fig = false;//остальные типы закрывающихся скобок запрещены
				}
				if (n == 2) {//фигурная скобка
					bracket_c_fig = true;//тогда ожидается закрывающая-ся фигурная скобка
					bracket_c_sq = bracket_c_cur = false;//остальные типы закрывающихся скобок запрещены

				}
				if (n == 3) {//квадратная скобка
					bracket_c_sq = true;//тогда ожидается закрывающаяся  квадратная скобка
					bracket_c_cur = bracket_c_fig = false;//остальные типы закрывающихся скобок запрещены
				}
				pos.push(n);//возвращаем проверенный элемент в стек

			}
			else bracket_c_cur = bracket_c_sq = bracket_c_fig = false;//если нет,то запрещаем закрывающиеся
			Q3.push(symb);//заносим в очередь удовлетворяющий элемент
		}

		if (cur_brckt_o(symb))//круглая открывающая скобка
		{
			cout << ",which is a curcle open bracket " << endl;
			bracket_c_cur = true;//тогда ожидается закрывающаяся  круглая скобка
			bracket_c_sq = bracket_c_fig = false;//остальные типы закрывающихся ско-бок запрещены
			pos.push(1);//заносим в стек номер скобки,которая на следующих шагах должна быть закрыта
			Q3.push(symb);//заносим в очередь удовлетворяющий элемент
		}
		if (cur_brckt_c(symb))//круглая закрывающая скобка
		{
			cout << ",which is a curcle close bracket" << endl;
			if (!bracket_c_cur&&bracket_c_fig) call_error(Q3, 3);//если на данном шаге не должна стоять закрывающаяся круглая скобка,а должна стоять фигурная,то выдаем соот-ветсвующую ошибку
			if (!bracket_c_cur&&bracket_c_sq) call_error(Q3, 2);//если на данном шаге не должна стоять закрывающаяся круглая скобка,а должна стоять квадратная,то выдаем соот-ветсвующую ошибку
			if (pos.can_pop()) {//если уже есть открытая скобка любого типа
				n = pos.pop();//узнаем,какого типа
				if (n == 1) {//если это круглая
					if (pos.can_pop()) {//проверяем,если еще открытые скобки
						n = pos.pop();//узнаем какого типа ранее идущая скобка
						if (n == 1) {//круглая скобка
							bracket_c_cur = true;//тогда ожидается за-крывающаяся  круглая скобка
							bracket_c_sq = bracket_c_fig = false;//остальные типы закрывающихся скобок запрещены
						}
						if (n == 2) {//фигурная скобка
							bracket_c_fig = true;//тогда ожидается за-крывающаяся фигурная скобка
							bracket_c_sq = bracket_c_cur = false;//остальные типы закрывающихся скобок запрещены

						}
						if (n == 3) {//квадратная скобка
							bracket_c_sq = true;//тогда ожидается за-крывающаяся  квадратная скобка
							bracket_c_cur = bracket_c_fig = false;//остальные типы закрывающихся скобок запрещены
						}
						pos.push(n);//возвращаем проверенный элемент в стек
						Q3.push(symb);//заносим в очередь удовлетворяющий элемент
					}
					else Q3.push(symb);//заносим в очередь удовлетворяющий элемент
				}
			}
			else call_error(Q3, 4);//если нет,то вызываем соответствующую ошибку

		}
		if (fig_brckt_o(symb))//фигурная открывающая скобка
		{
			cout << ",which is a figure open bracket " << endl;
			bracket_c_fig = true;//тогда ожидается закрывающаяся фигурная скобка
			bracket_c_sq = bracket_c_cur = false;//остальные типы закрывающихся ско-бок запрещены
			pos.push(2);//заносим в стек номер скобки,которая на следующих шагах должна быть закрыта
			Q3.push(symb);//заносим в очередь удовлетворяющий элемент
		}
		if (fig_brckt_c(symb))//фигурная закрывающая скобка
		{
			cout << ",which is a figure close bracket" << endl;
			if (!bracket_c_fig&&bracket_c_cur) call_error(Q3, 1);//если на данном шаге не должна стоять закрывающаяся фигурная скобка,а должна стоять круглая,то выдаем соот-ветсвующую ошибку
			if (!bracket_c_fig&&bracket_c_sq) call_error(Q3, 2);//если на данном шаге не должна стоять закрывающаяся фигурная скобка,а должна стоять квадратная,то выдаем со-ответсвующую ошибк
			if (pos.can_pop()) {//если уже есть открытая скобка любого типа
				n = pos.pop();//узнаем,какого типа
				if (n == 2) {//если фигурная
					if (pos.can_pop()) {//проверяем,если еще открытые скобки
						n = pos.pop();//узнаем какого типа ранее идущая скобка
						if (n == 1) {//круглая скобка
							bracket_c_cur = true;//тогда ожидается за-крывающаяся  круглая скобка
							bracket_c_sq = bracket_c_fig = false;//остальные типы закрывающихся скобок запрещены
						}
						if (n == 2) {//фигурная скобка
							bracket_c_fig = true;//тогда ожидается за-крывающаяся фигурная скобка
							bracket_c_sq = bracket_c_cur = false;//остальные типы закрывающихся скобок запрещены
						}
						if (n == 3) {//квадратная скобка
							bracket_c_sq = true;//тогда ожидается за-крывающаяся  квадратная скобка
							bracket_c_cur = bracket_c_fig = false;//остальные типы закрывающихся скобок запрещены
						}
						pos.push(n);//возвращаем проверенный элемент в стек
						Q3.push(symb);//заносим в очередь удовлетворяющий элемент
					}
					else Q3.push(symb);//заносим в очередь удовлетворяющий элемент
				}
			}
			else call_error(Q3, 4);//если нет,то вызываем соответствующую ошибку

		}
		if (sq_brckt_o(symb))//квадратная открывающая скобка
		{
			cout << ",which is a square open bracket " << endl;
			bracket_c_sq = true;//тогда ожидается закрывающаяся  квадратная скобка
			bracket_c_cur = bracket_c_fig = false;//остальные типы закрывающихся скобок запрещены
			pos.push(3);//заносим в стек номер скобки,которая на следующих шагах должна быть закрыта
			Q3.push(symb);//заносим в очередь удовлетворяющий элемент
		}
		if (sq_brckt_c(symb))//квадратная закрывающая скобка
		{
			cout << ",which is a square close bracket" << endl;
			if (!bracket_c_sq&&bracket_c_fig) call_error(Q3, 3);//если на данном шаге не должна стоять закрывающаяся квадратная скобка,а должна стоять фигурная,то выдаем со-ответсвующую ошибку
			if (!bracket_c_sq&&bracket_c_cur) call_error(Q3, 1);//если на данном шаге не должна стоять закрывающаяся квадратная скобка,а должна стоять круглая,то выдаем соот-ветсвующую ошибк
			if (pos.can_pop()) {//если уже есть открытая скобка любого типа
				n = pos.pop();//узнаем,какого типа
				if (n == 3) {//если квадратная
					if (pos.can_pop()) {//проверяем,если еще открытые скобки
						n = pos.pop();//узнаем какого типа ранее идущая скобка
						if (n == 1) {//круглая скобка
							bracket_c_cur = true;//тогда ожидается за-крывающаяся  круглая скобка
							bracket_c_sq = bracket_c_fig = false;//остальные типы закрывающихся скобок запрещены
						}
						if (n == 2) {//фигурная скобка
							bracket_c_fig = true;//тогда ожидается за-крывающаяся фигурная скобка
							bracket_c_sq = bracket_c_cur = false;//остальные типы закрывающихся скобок запрещены
						}
						if (n == 3) {//квадратная скобка
							bracket_c_sq = true;//тогда ожидается за-крывающаяся  квадратная скобка
							bracket_c_cur = bracket_c_fig = false;//остальные типы закрывающихся скобок запрещены
						}
						pos.push(n);//возвращаем проверенный элемент в стек
						Q3.push(symb);//заносим в очередь удовлетворяющий элемент
					}
					else Q3.push(symb);//заносим в очередь удовлетворяющий элемент
				}
			}
			else call_error(Q3, 4);//если нет,то вызываем соответствующую ошибку

		}
	}
	if (pos.can_pop()) {//если есть еще открывающиеся скобки
		n = pos.pop();//достаем элемент
		if (n == 1) call_error(Q3, 5);//если круглая,то выводим соответствующую ошибку
		if (n == 2) call_error(Q3, 6);//если фигурная,то выводим соответствующую ошибку
		if (n == 3) call_error(Q3, 7);//если квадратная,то выводим соответствующую ошибку
	}

}

void print_f(Queue & Q3) // вывести текст 
{
	while (Q3.can_pop())
	{
		cout << Q3.pop();
	}
}
void main_txt(istream &fin, Stack & Q2) // функция,в которой проверятся условие, является ли текстом введенные символы 
{
	Queue Q3;//очередь для выхода текста
	char symb;
	fin >> symb;

	while (!(fin.eof())) {//пока не достиг конец файла
		Q2.push(symb);//добавляем в стек
		Q3.push(symb);//добавляем в очередь
		fin >> symb;
	}
	Stack Q1;//промежуточный стек для вывода в нужном порядке
	cout << "Put the elements of the string on the stack:" << endl;//Заносим элементы строки в стек: 
	while (Q2.can_pop())//пока можно взять из стека
	{
		char a = Q2.pop();//берем элемент
		cout << "   An item is placed on the stack [" << a << "]." << endl;//В стек помещен элемент [" << a << "]. 
		Q1.push(a);//перезаписываем в другой стек

	}
	cout << "The string read from the file: ";//считанная из файла строка 
	print_f(Q3);//выводим строку
	cout << endl;
	is_it_txt(Q1, Q3);//проверяем на текст
	cout << "This is the text!" << endl;//Это текст
	cout << "Source text: ";//Ее вид 
	print_f(Q3);//выводим строку
}
int main()
{
	setlocale(0, "RUS");
	int answer;
	Stack Q2;
	menu();
	cin >> answer;
	switch (answer)
	{
	case 1:
	{
		char name[20];
		cout << "Enter the name of file" << endl;
		cin >> name;
		ifstream fin(name);
		system("cls");
		main_txt(fin, Q2);
		fin.close();
		break;
	}
	case 2:
	{
		system("cls");
		cout << "End of program!" << endl;
		system("pause");
		return 0;

	}

	default:
		system("cls");
		cout << "Incorrect input.Try again.";
		break;
	}
	cout << endl;
	system("pause");
}
