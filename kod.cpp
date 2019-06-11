#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int getRows() {
	int  rows;
	cout << "������� ���������� �����: ";
	cin >> rows;
	cout << endl;
	return rows;
}


int*  getCols(int rows) {
	int *cols = new int[rows];
	for (int i = 0; i < rows; i++) {
		
		cout << "������� ���������� �������� (����� ������) "<<i << " ������: ";
		cin >> cols[i];
		
	}
	return cols;
}

void printToEkr(double** dunamicmassive, int rows, int cols[]) { // ����� �� �����
	cout << "���� ������: " << endl;
	//int rows = sizeof(*dunamicmassive) / sizeof(*dunamicmassive[1]); // ����� ������ ������� ����� �� ������ ������ 
	//int cols = sizeof(dunamicmassive[1]) / sizeof(*dunamicmassive[1][1]); // ������ ����� ������ ����� �� ������ ������ ��������� 
	for (int i = 0; i < rows; i++) {//����� �������� ������� �������
		for (int j = 0; j < cols[i]; j++) {
			cout << dunamicmassive[i][j] << "\t";
		}
		cout << "\n";
	}
}
void enterToFile(double** dunamicmassive, int rows, int cols[]) {
	string cup;
	//cout << "������� ��� �����, � ������� ����� ������� ������ ";
	//cin >> cup;
	//cup += ".txt";
	fstream inFile; // inFile - ����������-������, ������� ��������� ����
	inFile.open("22.txt", ios::out);

	if (!inFile) {
		cout << " ������ �������� ����� ";
		exit(1); // terminate with error
	}

	for (int i = 0; i < rows; i++) {

		for (int j = 0; j < cols[i]; j++)  // ����� j ����������� ������ �������
		{
			inFile << dunamicmassive[i][j] << "\t";
		}
		inFile << "\n";

	}

	inFile.close(); // ��������� ����	
}
void vivodExs(double** dunamicmassive, int rows, int cols[]) {

	fstream f;
	f.open("1.xls", ios::out);

	for (int i = 0; i < rows; i++) {//����� �������� ������� �������
		for (int j = 0; j < cols[i]; j++) {
			f << dunamicmassive[i][j] << "\t";
		}
		f << "\n";
	}

	f.close();

}
void cleaner(double** dunamicmassive, int rows) {
	//int rows = sizeof(dunamicmassive) / sizeof(dunamicmassive[1]);
	for (int i = 0; i < rows; i++) { // ������ ������ 
		delete[] dunamicmassive[i];
	}
	delete[] dunamicmassive;
}

void history2(double** dunamicmassive, int rows, int cols[]) {
	int perekluchatel;
	cout << "��� �� �� ������ ������������ �����?" << endl;
	cout << "���� �� ������ ������������ ����� � ������� - ������� 1" << endl;
	cout << "���� �� ������ �������� ������ � ���� - ������� 2" << endl;
	cout << "���� �� ������ �������� ������ � ������� excel - ������� 3" << endl;
	cout << "��� �����: ";
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

	default: cout << endl << " �������� ����! " << endl;

	}
	cleaner(dunamicmassive, rows);
}


double** Vklava(int rows, int cols[]) {
	

	double **massiv = new double* [rows];

	
	for (int i = 0; i < rows; i++)  // ���� �� �������
	{
		massiv[i] = new double[cols[i]];
		for (int j = 0; j < cols[i]; j++)  // ���� �� ��������
		{
			printf("a[%d][%d] = ", i, j);
			cin >> massiv[i][j];
		}
	}
	return massiv;
}




 
void outputFromFile() {

	ifstream inFile; // inFile - ����������-������, ������� ��������� ����
	inFile.open("22.txt");

	if (!inFile) {
		cout << " ������ �������� ����� ";
		exit(1); // terminate with error
	}
	string line="";
	int sizeOfFile = 0;
	while (getline(inFile, line)) { //����� �� ����� �����, ����� ����� ���-�� �����
		sizeOfFile++;
	}

	inFile.close(); // ��������� ����	
	inFile.open("22.txt");

	if (!inFile) {
		cout << " ������ �������� ����� ";
		exit(1); // terminate with error
	}

	double** arr = new double* [sizeOfFile];
	int* cols = new int[sizeOfFile];

	int kot=0; 
	while (getline(inFile, line)) { //����� �� ������ �������, ����� ����� ���-�� ���������� � ���
		int elementOfLine = 0;
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] == 9) { //
				elementOfLine++;
			}
		}
		cols[kot] = elementOfLine ; // ������ � ���� ����� � ����� � elementOfLine ���������
		arr[kot] = new double[elementOfLine];
		kot++;
	}
	inFile.close(); // ��������� ����	

	inFile.open("22.txt");

	if (!inFile) {
		cout << " ������ �������� ����� ";
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
				index++; //��� ���� ��� �� ��������� ������ �� ������� (j ����� �� �������) 
			}
			else {
				tmp += line[j];
			}
		}
		i++; // ����� �� �������� ���������� �������
		
	}

	history2(arr, sizeOfFile, cols);
	inFile.close(); // ��������� ����	
}





	void seeker(double** dunamicmassive, int rows, int cols)	// ����� ������ �������� �������
	{

		
		double symbol;
		cout << " ������� ������� ����� " << endl;
		cout << "���������  �����: ";
		cin >> symbol;

		int  keeper = 0;

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
			if (dunamicmassive[i][j] == symbol) {
				keeper++;
				cout << "������� ����� ��������� ��(�) " << j + 1 << " �������(�������)  " << i + 1 << " ������ " << endl;
			}
				}
			}
		
		cout << endl << "������� " << keeper << " ��������!" << endl;
	}

	double** ydalenieElementa(double** dunamicmassive, int rows, int cols[]) {
		int vrows;
		int vcols;
		cout << "�������� �������, �� ������� ����� ������ �������� " << endl;
		cout << "������: ";
		cin >> vrows;
		vrows--; //����� ���������� ������������ � ���������
		cout << "�������: ";
		cin >> vcols;
		vcols--;//����� ���������� ������������ � ���������
		cols[vrows] --; // ������ ��� � ���������� ������� ������� ��������� ����� ������
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
		cout << "�������� �������, � ������� ����� �������� �������� " << endl;
		cout << "������: ";
		cin >> vrows;
		vrows--;
		cout << "�������: ";
		cin >> vcols;
		vcols--;
		cout << "������� �����: ";
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

	double** Vrand(int rows, int cols[]){ // ������������
		//��������� rows cols
	

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
	cout << "��� �� �� ������ ������������ ����?" << endl;
	cout << "���� �� ������ ������ ������� - ������� 1" << endl;
	cout << "���� � ��� ��� ���� ��������� ������ � �����, �� ������� 2" << endl;
	cout << "���� �� �� ������ ������������ ��������� ��������� �����, �� ������� 3" << endl;
	cout << "��� �����: ";
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
		default: cout << endl << " �������� ����! " << endl;
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