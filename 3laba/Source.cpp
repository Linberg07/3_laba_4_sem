#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

#include "list.h"

using namespace std;

class City {
public:
	string name;
	int cost;
	City(string nameP, int costP) : name(nameP), cost(costP) {};
};

class ProcessCity {
public:
	string name;
	int disatnce;
	bool isVisited;
	ProcessCity() {};
	ProcessCity(string nameP) : name(nameP) {};
};


bool isDouble(list<string>& arr, string str) {
	for (int i = 0; i < arr.getSize(); i++) {
		string a = arr[i];
		if (arr[i] == str)
			return true;
	}
	return false;
}


bool allVisited(ProcessCity* pCity, int count) {
	for (int i = 0; i < count; i++) {
		if (pCity[i].isVisited == false)
			return false;
	}
	return true;
}



int minDistance(ProcessCity* pCity, int count) {
	int index = -1;
	int min = INT_MAX;
	for (int i = 0; i < count; i++) {
		if (pCity[i].disatnce < min && pCity[i].isVisited == false) {
			min = pCity[i].disatnce;
			index = i;
		}
	}
	return index;
}

int getIndex(string* arr, string str) {
	for (int i = 0; i < arr->size(); i++) {
		if (arr[i] == str)
			return i;
	}
	return -1;
}


int isConnected(string* indices, list<City>** adjancencyList, int begin, int end) {
	for (int i = 0; i < adjancencyList[begin]->getSize(); i++)
		if (getIndex(indices, (*adjancencyList[begin])[i].name) == end)
			return (*adjancencyList[begin])[i].cost;
	return -1;
}



int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	fstream f;

	f.open("in.txt");
	int countString = 0;
	string bufString;
	while (!f.eof()) {
		getline(f, bufString);
		countString++;
	}
	f.close();

	f.open("in.txt");
	string** inputList = new string * [countString];
	for (int i = 0; i < countString; i++) {
		inputList[i] = new string[4];
		for (int j = 0; j < 3; j++) {
			getline(f, bufString, ';');
			if (bufString != "N/A")
				inputList[i][j] = bufString;
			else
				inputList[i][j] = "-1";
		}
		getline(f, bufString);
		if (bufString != "N/A")
			inputList[i][3] = bufString;
		else
			inputList[i][3] = "-1";
	}
	f.close();


	list<string> cities;
	for (int i = 0; i < countString; i++) {
		if (!isDouble(cities, inputList[i][0]))
			cities.push(inputList[i][0]);
		if (!isDouble(cities, inputList[i][1]))
			cities.push(inputList[i][1]);
	}

	list<City>** adjancencyList = new list<City> * [cities.getSize()];
	for (int i = 0; i < cities.getSize(); i++) {
		City* buf = new City(cities[i], 0);
		list<City>* buf2 = new list<City>;
		buf2->push(*buf);
		adjancencyList[i] = buf2;
	}


	for (int i = 0; i < countString; i++) {
		int j = 0;
		if (inputList[i][2] != "-1") {
			while (inputList[i][0] != (*adjancencyList[j])[0].name)
				j++;
			City* buf = new City(inputList[i][1], stoi(inputList[i][2]));
			(*adjancencyList[j]).push(*buf);
		}

		j = 0;
		if (inputList[i][3] != "-1") {
			while (inputList[i][1] != (*adjancencyList[j])[0].name)
				j++;
			City* buf = new City(inputList[i][0], stoi(inputList[i][3]));
			(*adjancencyList[j]).push(*buf);
		}
	}

	
	for (int i = 0; i < cities.getSize(); i++) {
		(*adjancencyList[i]).sort();
	}

	

	string source, destination;
	cout << "Source:";
	cin >> source;
	cout << "Destination:";
	cin >> destination;

	int infinity = INT_MAX;

	ProcessCity* processCity = new ProcessCity[cities.getSize()];	

	string* indices = new string[cities.getSize()]; 

	
	for (int i = 0; i < cities.getSize(); i++) {
		indices[i] = (*adjancencyList[i])[0].name;
		processCity[i].name = (*adjancencyList[i])[0].name;
		processCity[i].isVisited = false;
		processCity[i].disatnce = infinity;
		if ((*adjancencyList[i])[0].name == source)
			processCity[i].disatnce = 0;
	}

	
	while (!allVisited(processCity, cities.getSize())) {
		int curNodeIndex = minDistance(processCity, cities.getSize()); 

		
		for (int i = 1; i < (*adjancencyList[curNodeIndex]).getSize(); i++) {
			
			if (processCity[getIndex(indices, (*adjancencyList[curNodeIndex])[i].name)].isVisited == false &&
				processCity[curNodeIndex].disatnce + (*adjancencyList[curNodeIndex])[i].cost <
				processCity[getIndex(indices, (*adjancencyList[curNodeIndex])[i].name)].disatnce) {

				processCity[getIndex(indices, (*adjancencyList[curNodeIndex])[i].name)].disatnce =
					processCity[curNodeIndex].disatnce + (*adjancencyList[curNodeIndex])[i].cost;
			}
			else
				continue;
		}
		processCity[curNodeIndex].isVisited = true;
	}


	

	int* ver = new int[cities.getSize()];
	int end = getIndex(indices, destination);
	int start = getIndex(indices, source);
	ver[0] = end;
	int k = 1; 
	int weight = processCity[end].disatnce;

	while (end != start) {
		for (int i = 0; i < cities.getSize(); i++) {
			if (isConnected(indices, adjancencyList, i, end) != -1) {
				int temp = weight - isConnected(indices, adjancencyList, i, end);
				if (temp == processCity[i].disatnce) {
					weight = temp;
					end = i;
					ver[k] = i;
					k++;
				}
			}
		}
	}

	cout << endl;
	cout << endl;
	cout << endl;
	for (int i = k - 1; i > 0; i--)
		cout << indices[ver[i]] << " -> ";
	cout << indices[ver[0]];
	cout << endl;
	cout << endl;
	cout << endl;


	end = getIndex(indices, destination);
	cout << "Эффективная стоимость:" << processCity[end].disatnce << '\n';
}