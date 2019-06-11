#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int getRows() {
	int  rows;
	cout << "Введите количество строк: ";
	cin >> rows;
	cout << endl;
	return rows;
}


int*  getCols(int rows) {
	int *cols = new int[rows];
	for (int i = 0; i < rows; i++) {
		
		cout << "введите количество столбцов (длину строки) "<<i << " строки: ";
		cin >> cols[i];
		
	}
	return cols;
}

void printToEkr(double** dunamicmassive, int rows, int cols[]) { // вывод на экран
	cout << "Наши данные: " << endl;
	//int rows = sizeof(*dunamicmassive) / sizeof(*dunamicmassive[1]); // общий размер массива делим на размер строки 
	//int cols = sizeof(dunamicmassive[1]) / sizeof(*dunamicmassive[1][1]); // размер одной строки делим на размер одного эллемента 
	for (int i = 0; i < rows; i++) {//нужно передать размеры массива
		for (int j = 0; j < cols[i]; j++) {
			cout << dunamicmassive[i][j] << "\t";
		}
		cout << "\n";
	}
}
void enterToFile(double** dunamicmassive, int rows, int cols[]) {
	string cup;
	//cout << "Введите имя файла, в который будут вписаны данные ";
	//cin >> cup;
	//cup += ".txt";
	fstream inFile; // inFile - переменная-объект, которая принимает файл
	inFile.open("22.txt", ios::out);

	if (!inFile) {
		cout << " Ошибка открытия файла ";
		exit(1); // terminate with error
	}

	for (int i = 0; i < rows; i++) {

		for (int j = 0; j < cols[i]; j++)  // через j отсчитываем размер массива
		{
			inFile << dunamicmassive[i][j] << "\t";
		}
		inFile << "\n";

	}

	inFile.close(); // закрываем файл	
}
void vivodExs(double** dunamicmassive, int rows, int cols[]) {

	fstream f;
	f.open("1.xls", ios::out);

	for (int i = 0; i < rows; i++) {//нужно передать размеры массива
		for (int j = 0; j < cols[i]; j++) {
			f << dunamicmassive[i][j] << "\t";
		}
		f << "\n";
	}

	f.close();

}
void cleaner(double** dunamicmassive, int rows) {
	//int rows = sizeof(dunamicmassive) / sizeof(dunamicmassive[1]);
	for (int i = 0; i < rows; i++) { // чистим память 
		delete[] dunamicmassive[i];
	}
	delete[] dunamicmassive;
}

void history2(double** dunamicmassive, int rows, int cols[]) {
	int perekluchatel;
	cout << "как бы вы хотели организовать вывод?" << endl;
	cout << "если вы хотите организовать вывод в консоль - нажмите 1" << endl;
	cout << "если вы хотите записать данные в файл - нажмите 2" << endl;
	cout << "если вы хотите записать данные в таблицу excel - нажмите 3" << endl;
	cout << "Ваш выбор: ";
	cin >> perekluchatel;

	switch (perekluchatel)
	{
	case 1:
		printToEkr(dunamicmassive, rows, cols);
		break;

	case 2:

		enterToFile(dunamicmassive, rows, cols);
		break;

	case 3:
		vivodExs(dunamicmassive, rows, cols);
		break;

	default: cout << endl << " Неверный ввод! " << endl;

	}
	cleaner(dunamicmassive, rows);
}


double** Vklava(int rows, int cols[]) {
	

	double **massiv = new double* [rows];

	
	for (int i = 0; i < rows; i++)  // цикл по строкам
	{
		massiv[i] = new double[cols[i]];
		for (int j = 0; j < cols[i]; j++)  // цикл по столбцам
		{
			printf("a[%d][%d] = ", i, j);
			cin >> massiv[i][j];
		}
	}
	return massiv;
}




 
void outputFromFile() {

	ifstream inFile; // inFile - переменная-объект, которая принимает файл
	inFile.open("22.txt");

	if (!inFile) {
		cout << " Ошибка открытия файла ";
		exit(1); // terminate with error
	}
	string line="";
	int sizeOfFile = 0;
	while (getline(inFile, line)) { //ходим по всему файлу, чтобы найти кол-во строк
		sizeOfFile++;
	}

	inFile.close(); // закрываем файл	
	inFile.open("22.txt");

	if (!inFile) {
		cout << " Ошибка открытия файла ";
		exit(1); // terminate with error
	}

	double** arr = new double* [sizeOfFile];
	int* cols = new int[sizeOfFile];

	int kot=0; 
	while (getline(inFile, line)) { //ходим по каждой строчке, чтобы найти кол-во эллементов в ней
		int elementOfLine = 0;
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] == 9) { //
				elementOfLine++;
			}
		}
		cols[kot] = elementOfLine ; // хранит в себе номер с троки с elementOfLine элементов
		arr[kot] = new double[elementOfLine];
		kot++;
	}
	inFile.close(); // закрываем файл	

	inFile.open("22.txt");

	if (!inFile) {
		cout << " Ошибка открытия файла ";
		exit(1); // terminate with error
	}


	
	int i = 0;
	string tmp = "";
	while (getline(inFile, line)) { 
		int index = 0;
		
		for (int j = 0; j < line.size(); j++)
		{
			if (line[j] == 9) {

				arr[i][index] = atof(tmp.c_str());
				tmp =  "" ;
				index++; //для того что бы правильно ходить по массиву (j ходит по строчке) 
			}
			else {
				tmp += line[j];
			}
		}
		i++; // ходит по строчкам двумерного массива
		
	}

	history2(arr, sizeOfFile, cols);
	inFile.close(); // закрываем файл	
}





	void seeker(double** dunamicmassive, int rows, int cols)	// метод поиска элемента массива
	{

		
		double symbol;
		cout << " Введите искомое число " << endl;
		cout << "Введенное  число: ";
		cin >> symbol;

		int  keeper = 0;

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
			if (dunamicmassive[i][j] == symbol) {
				keeper++;
				cout << "Искомое число находится на(в) " << j + 1 << " позиции(колонке)  " << i + 1 << " строки " << endl;
			}
				}
			}
		
		cout << endl << "Найдено " << keeper << " символов!" << endl;
	}

	double** ydalenieElementa(double** dunamicmassive, int rows, int cols[]) {
		int vrows;
		int vcols;
		cout << "Ввведите позицию, из которой будет удален эллемент " << endl;
		cout << "строка: ";
		cin >> vrows;
		vrows--; //чтобы установить соответствие с индексами
		cout << "столбец: ";
		cin >> vcols;
		vcols--;//чтобы установить соответствие с индексами
		cols[vrows] --; // потому что мі собираемся удалить элемент уменьшаем длину строки
		double* tmp = new double[cols[vrows]];
	
		

		for (int i = 0; i < cols[i] - 1; i++) {
			
			if (i < vcols) {
				tmp[i] = dunamicmassive[vrows][i];
			}

			if (i > vcols) {
				tmp[i-1] = dunamicmassive[vrows][i];
			}
			if (i == vcols) {
				tmp[i] = dunamicmassive[vrows][i+1];
			}
		}
		dunamicmassive[vrows ] = tmp;
		return dunamicmassive;
	}

	double** dobavlenieElementa(double** dunamicmassive, int rows, int cols[]) {
		int vrows;
		int vcols;
		double num;
		cout << "Ввведите позицию, в которую будет добавлен эллемент " << endl;
		cout << "строка: ";
		cin >> vrows;
		vrows--;
		cout << "столбец: ";
		cin >> vcols;
		vcols--;
		cout << "введите число: ";
		cin >> num;
		cols[vrows]++; // edt
		double* tmp = new double[cols[vrows]];
		
		
		for (int i = 0; i < cols[i]; i++) {
			if (i == vcols ) {
				tmp[i] = num;
			}
			else if(i < vcols) {
				tmp[i] = dunamicmassive[vrows][i];
			}else
			{
				tmp[i] = dunamicmassive[vrows][i - 1];
			}
		}
		dunamicmassive[vrows] = tmp;
		return dunamicmassive;
	}

	double** Vrand(int rows, int cols[]){ // Рандомизатор
		//получаешь rows cols
	

	double** dunamicmassive = new double* [rows];
	
	srand(time(0));
	for (int i = 0; i < rows; i++) { 
		dunamicmassive[i] = new double[cols[i]];
		for (int j = 0; j < cols[i]; j++) {

			dunamicmassive[i][j] = rand() % 20 + 1;
		
		}
	}
	//vivodExs(dunamicmassive, rows, cols[]);
	return dunamicmassive;	
}









void history() {
	int perekluchatel;
	int rows = 0;
	int *cols = new int[0];
	cout << "Как бы вы хотели организовать ввод?" << endl;
	cout << "Если вы хотите ввести вручную - введите 1" << endl;
	cout << "Если у вас уже есть некоторые данные в файле, то введите 2" << endl;
	cout << "Если же вы хотите использовать генератор случайных чисел, то введите 3" << endl;
	cout << "Ваш выбор: ";
	cin >> perekluchatel;

	double** dunamicmassive= new double* [0];
	switch (perekluchatel)
	{
		case 1: 
			rows = getRows();
			cols = getCols(rows);
			dunamicmassive = Vklava(rows,cols);
			
			history2(dunamicmassive, rows, cols);
			break;
		
		case 2: 
			outputFromFile();
			break;
		
		case 3:
			rows = getRows();
			cols = getCols(rows);
			dunamicmassive = Vrand(rows, cols);
			history2(dunamicmassive, rows, cols);
			break;
		default: cout << endl << " Неверный ввод! " << endl;
	}

	
}





int main() {
	setlocale(LC_ALL, "ru");
	while (true) {
		history();
	}
	
	//cleaner();
	system("pause");
	return 0;
}