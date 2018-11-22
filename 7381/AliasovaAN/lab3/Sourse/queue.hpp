template <class T>// исп для описания класса queue как шаблона, чтобы хранит в нем данные любого типа; T-параметр шабона класса
class Queue{ //создание класса
public:
	Queue(unsigned int); //конструктор
	unsigned int get_size();//функция для получения длины очереди
	void push(T); //добавление элемента в очередь
	void resize(unsigned int); //увеличение размера массива(вектора)
	bool isEmpty();//проверка на пустоту очереди
	T pop(); //удаление элемента из очереди
	~Queue(); //деструктор
private:
	unsigned int vsize; //размер вектора
	unsigned int qsize; //размер очереди
	T* vstart; //указатель на начало вектора
	T* qstart; //указатель на начало очереди
	T* qend; // указатель на конец очереди
};

template <class T>
Queue<T>::Queue(unsigned int size) : vsize(size), qsize(0) { //конструктор
	vstart = new T[size];
	qstart = vstart;
	qend = vstart;
}

template <class T>
	unsigned int Queue<T>::get_size(){ //получение размера очереди
	return qsize;
}

template <class T>
	void Queue<T>::push(T value) { //value = symbol
	if(qend != qstart || (qsize == 0 && vsize != 0))
		*qend = value;
	else {
		resize(vsize*2);
		*qend = value;
	}
	if(qend < (vstart + vsize - 1))
		++qend;
	else
		qend = vstart;
	++qsize;
}

template <class T>
void Queue<T>::resize(unsigned int new_size) { // увеличение вектора,создается новый массив и в негокопируется старый массив
	T* new_vect = new T[new_size];
	int i;
	for(i=0; i<(vsize-(qstart-vstart)); ++i)
		new_vect[i] = qstart[i];
	for(int j=0; i < vsize; ++i, ++j)
		new_vect[i] = vstart[j];
	qstart = new_vect;
	qend = new_vect + qsize;
	delete vstart;
	vstart = new_vect;
	vsize = new_size;
}

template <class T> //проверка на пустоту очереди
bool Queue<T>::isEmpty() {
	return qsize == 0;
}

template <class T>
T Queue<T>::pop() { //функция возвращает первый элемент и сдвигает очередь вправо 
	T ret = *qstart;
	if(qstart != (vstart + vsize - 1))
		++qstart;
	else
		qstart = vstart;
	--qsize;
	return ret;
}

template <class T>
Queue<T>::~Queue() { //деструктор
	delete vstart;
}
