#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<chrono>
#include<vector>
#include<cmath>
#include<iomanip>

using namespace std;

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::time_point<std::chrono::system_clock> Clock_val;

struct data
{
	int id;
	int size;
	vector<int> numbers;	
};

struct sort
{
	int id;
	string type;
	string time;
};

void mergeSort(data, vector<sort> &);
void quickSort(data, vector<sort> &);
void bucketSort(data, vector<sort> &);
void bubbleSort(data, vector<sort> &);
void insertSort(data, vector<sort> &);
void setData(vector<data> &);
void setSort(vector<sort> &);
void show(vector<data> &, vector<sort> &);
void showData(vector<data> &, int);
void showSort(vector<sort> &, int, int);
void generateData();
int convertStringToInt(string);
void addData(vector<data> &);
void sortData(vector<data> &, vector<sort> &);
void error();

int main()
{
	vector<data> dataBase;
	vector<sort> sortBase;
	
	int option;	
	while(true)
	{
		setData(dataBase);
		setSort(sortBase);
		system("CLS");
		cout<<"=============================="<<endl
			<<"Witaj w kalkulatorze sortowan!"<<endl
			<<"=============================="<<endl
			<<"Opcje:"<<endl
			<<"1. Wyswietl zestaw"<<endl
			<<"2. Dodaj zestaw"<<endl
			<<"3. Sortuj zestaw"<<endl
			<<"4. Wyswietl ranking sortowan"<<endl
			<<"0. Zakoncz"<<endl
			<<"-> "; cin>>option;
		switch(option)
		{
			case 0:
				system("CLS");
				cout<<"======="<<endl
					<<"Koniec!"<<endl
					<<"=======";
				return 0;
			case 1:
				show(dataBase, sortBase);
				break;
			case 2:
				addData(dataBase);
				break;
			case 3:
				sortData(dataBase, sortBase);
				break;
			case 4:
				
				break;
			default:
				system("CLS");
				cout<<"===================="<<endl
					<<"\aNie ma takiej opcji!"<<endl
					<<"===================="<<endl;
				system("pause");
				continue;
		}
	}
	
	return 0;
}

void setData(vector<data> &dataBase)
{
	dataBase.clear();
	ifstream file;
	file.open("data.txt");
	
	if(!file.good())
	{
		file.close();
			
		system("CLS");
		cout<<"============"<<endl
			<<"Brak danych!"<<endl
			<<"============"<<endl;
		sleep(2);
		
		system("CLS");
		cout<<"================"<<endl
			<<"Generuje dane..."<<endl
			<<"================"<<endl;
		
		generateData();
		sleep(2);
		
		system("CLS");
		cout<<"============================"<<endl
			<<"Pomyslnie wygenerowano dane"<<endl
			<<"============================"<<endl;
		sleep(2);
		
		file.open("data.txt");
	}
	
	string line;

	while(!file.eof())
	{
		int id = 0;
		getline(file, line);
		if(line == "")
		{
			continue;
		}
		if(line == "{");
		{
			data newData; 
			newData.id = id++;
			int size = 0;
			getline(file, line);
			while(line != "}")
			{	
				size++;
				newData.numbers.push_back(convertStringToInt(line));
				getline(file, line);
			}
			newData.size = size;
			dataBase.push_back(newData);
		}
	}
	
	file.close();
}

void setSort(vector<sort> &sortBase)
{
	sortBase.clear();
	string line;
	ifstream file;
	file.open("sort.txt");
	
	while(!file.eof())
	{
		getline(file, line);
		if(line == "")
		{
			continue;
		}
		if(line == "{")
		{
			sort newSort;
			getline(file, line);
			newSort.id = convertStringToInt(line);
			getline(file, line);
			newSort.type = line;
			getline(file, line);
			newSort.time = line;
			sortBase.push_back(newSort);
		}
	}
	
	file.close();
}

void show(vector<data> &dataBase, vector<sort> &sortBase)
{
	int index, option;
	bool end = false;
	system("CLS");
	cout<<"===================="<<endl
		<<"Wyswietlanie zestawu"<<endl
		<<"===================="<<endl;
	cout<<"Wybierz zestaw:"<<endl;
	for(int i = 1; i <= dataBase.size(); i++)
	{
		cout<<"Nr "<<i<<"."<<endl;
	}
	cout<<"-> "; cin>>index;
	
	while(!end)
	{
		system("CLS");
		cout<<"===================="<<endl
			<<"Wyswietlanie zestawu"<<endl
			<<"===================="<<endl;
		cout<<"Zestaw nr "<<index<<", wyswietl: "<<endl
			<<"1. Dane"<<endl
			<<"2. Wyniki sortowan"<<endl
			<<"0. Powrot do menu"<<endl;
		cout<<"-> "; cin>>option;
		
		switch(option)
		{
			case 0:
				end = true;
				break;
			case 1:
				showData(dataBase, index);
				break;	
			case 2:
				showSort(sortBase, index, dataBase[index].id);
				break;
			default:
				error();
				continue;
		}
	}
}

void showData(vector<data> &dataBase, int index)
{
	system("CLS");
	cout<<"===================="<<endl
		<<"Wyswietlanie zestawu"<<endl
		<<"===================="<<endl;
	cout<<"Zestaw nr "<<index<<", dane: "<<endl;
	for(int i = 0; i < dataBase[index].numbers.size(); i++)
	{
		cout<<dataBase[index].numbers[i]<<endl;
	}
	system("pause");
}

void showSort(vector<sort> &sortBase, int index, int id)
{
	int n = 0;
	system("CLS");
	cout<<"===================="<<endl
		<<"Wyswietlanie zestawu"<<endl
		<<"===================="<<endl;
	cout<<"Zestaw nr "<<index<<", wyniki sortowan: "<<endl;
	for(int i = 0; i < sortBase.size(); i++)
	{
		if(id == sortBase[i].id)
		{
			cout<<"Typ sortowania: "<<sortBase[i].type<<", czas sortowania: "<<sortBase[i].time<<endl;
			n++;
		}
	}
	if(n == 0)
		cout<<"Brak sortowan"<<endl;
	system("pause");
}

void generateData()
{
	ofstream file;
	file.open("data.txt");
	srand(time(NULL));
	
	for(int i = 1; i <= 5; i++)
	{
		file<<"{"<<endl;
		int size = rand()%100+901;
		for(int index = 0; index < size; index++)
		{
			file<<rand()%101<<endl;
		}
		file<<"}"<<endl;
	}
	
	file.close();
	
	file.open("sort.txt");
	file.close(); 
}

int convertStringToInt(string text)
{
	int length = text.length();
	int result = 0;
	int power = 0;
	
	for(int i = length-1; i >= 0; i--)
	{
		result += (int(text[i]) - 48) * pow(10, power);
		power++;
	}
	
	return result;
}

void addData(vector<data> &dataBase)
{
	int n;
	data newData;
	ofstream file;
	file.open("data.txt", ios::app);
	
	system("CLS");
	cout<<"========================"<<endl
		<<"Dodawanie zestawu danych"<<endl
		<<"========================"<<endl;
	cout<<"Wprowadz liczby\n(znak konczy wprowadzanie):"<<endl;
	while(cin>>n)
	{
		newData.numbers.push_back(n);
	}
	cin.clear();
	while(cin.get() != '\n')
		continue;
	dataBase.push_back(newData);
	
	file<<"{"<<endl;
	for(int index = 0; index < newData.numbers.size(); index++)
	{
		file<<newData.numbers[index]<<endl;
	}
	file<<"}"<<endl;
		
	system("CLS");
	cout<<"============================"<<endl
		<<"Pomyslnie dodano nowy zestaw"<<endl
		<<"============================"<<endl;
	sleep(2);
	
	file.close();
}

void sortData(vector<data> &dataBase, vector<sort> &sortBase)
{
	int index;
	int option;
	sort newSort;
	ofstream file;
	file.open("sort.txt", ios::app);
	
	system("CLS");
	cout<<"=============="<<endl
		<<"Panel sortowan"<<endl
		<<"=============="<<endl;
	cout<<"Wybierz zestaw:"<<endl;
	for(int i = 1; i <= dataBase.size(); i++)
	{
		cout<<"Nr "<<i<<"."<<endl;
	}
	cout<<"-> "; cin>>index;
	--index;
	
	newSort.id = index;
	
	system("CLS");
	cout<<"=============="<<endl
		<<"Panel sortowan"<<endl
		<<"=============="<<endl;
	cout<<"Wybierz rodzaj sortowania:"<<endl
		<<"1. mergeSort"<<endl
		<<"2. quickSort"<<endl
		<<"3. bucketSort"<<endl
		<<"4. bubbleSort"<<endl
		<<"5. insertSort"<<endl
		<<"-> "; cin>>option;
	
	Clock_val start, end;
	
	switch(option)
	{
		case 1:
		{
			newSort.type = "mergeSort";
			start = Clock::now();
			mergeSort(dataBase[index], sortBase);
			end = Clock::now();
			break;
		}
		case 2:
		{
			newSort.type = "quickSort";
			start = Clock::now();
			quickSort(dataBase[index], sortBase);
			end = Clock::now();
			break;
		}
		case 3:
		{
			newSort.type = "bucketSort";
			start = Clock::now();
			bucketSort(dataBase[index], sortBase);
			end = Clock::now();
			break;
		}
		case 4:
		{	
			newSort.type = "bubbleSort";
			start = Clock::now();
			bubbleSort(dataBase[index], sortBase);
			end = Clock::now();
			break;
		}
		case 5:
		{
			newSort.type = "insertSort";
			start = Clock::now();
			insertSort(dataBase[index], sortBase);
			end = Clock::now();
			break;
		}
		default:
			error();
	}
	
	system("CLS");
	cout<<"=============="<<endl
		<<"Panel sortowan"<<endl
		<<"=============="<<endl;

	auto miliseconds = (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count())*pow(10, -6);
	auto seconds = (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count())*pow(10, -9);
	if(seconds >= 1)
	{
		newSort.time = to_string(seconds);
		newSort.time += " sekund";
		cout<<"Czas sortowania "<<newSort.type<<": "<<seconds<<" sekund"<<endl;
	}
	else
	{
		newSort.time = to_string(miliseconds);
		newSort.time += " milisekund";
		cout<<"Czas sortowania "<<newSort.type<<": "<<miliseconds<<" milisekund"<<endl;
	}

	sortBase.push_back(newSort);
	
	file<<"{"<<endl
		<<newSort.id<<endl
		<<newSort.type<<endl
		<<newSort.time<<endl
		<<"}"<<endl;
		
	file.close();
	system("pause");
}

void mergeSort(data currentData, vector<sort> &sortBase)
{
	
}

void quickSort(data currentData, vector<sort> &sortBase)
{
	
}

void bucketSort(data currentData, vector<sort> &sortBase)
{
	
}

void bubbleSort(data currentData, vector<sort> &sortBase)
{
	for(int i = 0; i < currentData.size; i++)
	{
		for(int j = 0; j < currentData.size-i-1; j++)
		{
			if(currentData.numbers[j] > currentData.numbers[j+1])
			{
				int x = currentData.numbers[j+1];
				currentData.numbers[j+1] = currentData.numbers[j];
				currentData.numbers[j] = x;
			}
		}
	}
}

void insertSort(data currentData, vector<sort> &sortBase)
{
	
}

void error()
{
	system("CLS");
	cout<<"===================="<<endl
		<<"\aNie ma takiej opcji!"<<endl
		<<"===================="<<endl;
	system("pause");
}