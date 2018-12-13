#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>

using namespace std;

template <class T>
class HuffmanTree{
private:
    HuffmanTree* left;   // 0
    HuffmanTree* right;  // 1
    bool flag = false; //true if leaf
    T value;

public:
	HuffmanTree(ifstream& s);
	bool isLeaf(){		//возвращает true, если элемент является листом дерева
		return flag;
	}
	HuffmanTree *get_left() { //возвращает указатель на левый элемент
		return left;
	}
	HuffmanTree *get_right() { //возвращает указатель на првый элемент
		return right;
	}
	T val() { //возвращает кодируемый элемент
		cout << "символ декодрованного текста: " << value << endl;
		return value;
	}
	~HuffmanTree();
};

template <class T>
HuffmanTree<T>::HuffmanTree(ifstream& s){
	flag = false;
	left = NULL;
	right = NULL;
	char ch;
	if (s.peek() == '('){
		s >> ch; // remove '('
		cout << "скобка: " << ch << endl;
	}
	else
		return;
    if (s.peek() == '('){
	left = new HuffmanTree(s);
            if (s.peek() == ')'){
                s >> ch; // remove ')'
		cout << "скобка: " << ch << endl;
	}
        }
    else{
	flag = true;
	s >> value;
	cout << "элемент словаря: " << value << endl;
        return;
        }
    if (s.peek() == '('){
	cout << "скобка: " << ch << endl;
        right = new HuffmanTree(s);
        s >> ch; // remove ')'
	if(ch != ')')
		cout << "буква кода: " << ch << endl;
    }
    if (s.peek() == ')'){
        s >> ch; // remove ')'
	cout << "скобка: " << ch << endl;
	}
}

template <class T>
HuffmanTree<T>::~HuffmanTree(){//деструктор
	if (left)
		delete left;
	if (right)
		delete right;
}

int main(){
    int n, c;
    int *el;
    string str_i, str_o;//названия входного и выходного файлов
    while(true){
        cout << "Press 1 to decode a file\n" <<
                "Press 2 to exit." << endl;
        cin >> str_i;
        if (!isdigit(str_i[0])) //проверка 
            continue;
        c = stoi(str_i);
        str_i.clear();
        switch (c)
        {
            case 1:
                break;
            case 2:
                return 0;
            default:
                cout << "Something went wrong. Try again!" << endl;
                continue;
        }
        cout << "Enter input file name: ";
        cin >> str_i;
        cout << "Enter output file name: ";
        cin >> str_o;
        if (str_i == str_o){
            cout << "Input and output files can't be the same." << endl;
            continue;
        }
        ifstream f;
        ofstream o;
        char b;
        f.open(str_i);
        o.open(str_o);
        if (!f){//проверка на существование входного файла
            cout << "Unable to open the input file!" << endl;
            continue;
        }
        if (!o)//проверка на существование выходного файла
        {
            cout << "Unable to open the output file!" << endl;
            continue;
        }
        HuffmanTree<char> *Dictionary = new HuffmanTree<char>(f); //создание и выделение памяти под словарь
        HuffmanTree<char> *tmp = Dictionary;
        while (!f.eof()){//пока не достигнут конец файла
            b = f.get();//считываем символ из файла f и возвращаем его значение
		cout << "буква кода: " << b << endl;
            if (b == '\n')
                if (f.peek() == EOF)//если очередной символ является концом файла
                    break;
            for (char i = 7; i >= 0; i--)
            {
                if (tmp)
                    tmp = ((b & (1 << i)) == 0 ? tmp->get_left() : tmp->get_right());//в код символа добавляется 0 при спуске по левой ветви или 1 при спуске по правой ветви
                if (tmp && tmp->isLeaf())
                {
                    o << tmp->val();//запись раскодированного символа
                    tmp = Dictionary;
                }

            }
        }
        f.close();
        o.close();
        if (tmp)
            cout << str_i << " was decoded to " << str_o << " succesfully." << endl;
        else
            cout << str_i <<" is broken." << endl;
        delete Dictionary;
    }
}
