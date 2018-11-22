#include <iostream>
#include <fstream>
#include <string>
#include "queue.hpp"

void rewrite(std::istream &fin, std::ostream &fout){//функция для вывода процесса работы программы
	Queue<unsigned char> numbers(4), other(10); //устанавливаем размеры элементов
	std::string input; 
	while(!fin.eof()){ //пока fin()
		getline(fin, input);
		int count = 1;
		for(auto i : input){ //Ключевое слово auto указывает компилятору использовать выражение инициализации объявленной переменной, или параметр лямбда-выражения, чтобы вывести ее тип.
						
			if(i > '9' || i < '0'){
				other.push(i); //push in other
				std::cout<<"push elem №" << count <<" in other's array"<<" : "<< i << std::endl;
			}
			else{
				numbers.push(i); //push in numbers
				std::cout<<"push elem №" << count << " in number's array" <<" : "<< i << std::endl;
			}
			count++;
			unsigned char c;
			std::cout << "numbers: " << std::endl;
			for(int j=0; j<numbers.get_size(); ++j){ //вывод содержимого numbers
				c = numbers.pop();
				//std::cout << "	pop element №"<< j <<" : "<< c << std::endl;
				std::cout << c;
				numbers.push(c);
			}
			std::cout << std::endl;
			std::cout << "other: "<< std::endl;
			for(int j=0; j<other.get_size(); j++){ //вывод содержимого other
				c = other.pop();
				//std::cout << "	pop element №"<< j <<" : "<< c << std::endl;
				std::cout << c;
				other.push(c);
			}
			std::cout << std::endl << std::endl;
		}
		while(!other.isEmpty())
			fout << other.pop();//запись вначале всех символов
		while(!numbers.isEmpty())
			fout << numbers.pop();//запись всех цифр
		fout << std::endl;
	}
}


int main(){
	std::filebuf in_file, out_file; //filebuf - Этот тип является синонимом класса шаблона basic_filebuf, специализированного для элементов типа char с признаками символа по умолчанию.
	std::string in_filename, out_filename; //string - это STL’евский класс основанный на шаблонах(аналогичен char*)
	while(true){
		std::cout << "Enter input file name or nothing to exit: "; //ввод названия входного файла
		getline(std::cin, in_filename);
		if(in_filename == "") //если не нужно больше читать содержимое файла
			break;
		if(!in_file.open(in_filename, std::ios::in)){//если нельзя открыть файл для чтения; //std::ios::in - открыть файл для чтения
			std::cout << "Incorrect file, try again" << std::endl;
			in_file.close();
			continue;
		}
		std::cout << "Enter output file name: ";//ввод имени выходного файла
		getline(std::cin, out_filename);
		if(!out_file.open(out_filename, std::ios::out)){ //если нельзя открыть файл для записи
			std::cout << "Incorrect file, try again" << std::endl;
			in_file.close();
			out_file.close();
			continue;
		}
		std::istream fin(&in_file);//считывание посимвольно
		std::ostream fout(&out_file);
		rewrite(fin, fout);
		in_file.close();
		out_file.close();
	}
	return 0;
}







