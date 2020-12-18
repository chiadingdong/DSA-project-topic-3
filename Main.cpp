/*
DSA mini project topic 3
Chia Dong (P1938113)
Justin Tan  (P1923731)
Yusuf  (P1923421)
*/

#include <fstream>
#include <iostream>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <string>
#include "Student.h"

void selectMethod();
void method1();
void method2();
void openfile();
//internal linkage data structure
static std::list<Student> Cohort; 
static std::unordered_map<std::string, int> SectorVacancies; //store the vacancies for each sector

int main()
{
	openfile();
	//sort student according to their GPA
	Cohort.sort([](const Student& lhs, const Student& rhs) -> bool
		{
			return lhs.getGPA() > rhs.getGPA();
		}
	);

	std::cout << "Vacancies available\n------------------\n";
	for (const auto& elm : SectorVacancies) {
		std::cout << elm.first << ":" << elm.second << '\n';
	}

	selectMethod();

	std::cout << "\n\nVacancies left\n-------------\n";
	for (const auto& elm : SectorVacancies) {
		std::cout << elm.first << ":" << elm.second << '\n';
	}

}



void openfile() {
	std::string sectors, vacancy;
	std::string name, GPA;
	std::vector <std::string> choices(5);
	//open Student Data file
	std::ifstream File1;
	File1.open("StudentData.txt");

	while (!File1.eof()) {
		getline(File1, name, ',');
		getline(File1, GPA, ',');
		getline(File1, choices[0], ',');
		getline(File1, choices[1], ',');
		getline(File1, choices[2], ',');
		getline(File1, choices[3], ',');
		getline(File1, choices[4]);
		Cohort.emplace_back(name, std::stod(GPA), choices);
	}
	File1.close();
	//open Sectors data file
	std::ifstream File2;
	File2.open("SectorsData.txt");
	while (!File2.eof()) {
		getline(File2, sectors, ',');
		getline(File2, vacancy);
		SectorVacancies[sectors] = stoi(vacancy);
	}
	File2.close();
}


void selectMethod() {
	char choice;
	while (true) {
		std::cout << "\nEnter the method to process the posting (1/2) :";
		std::cin >> choice;
		if (choice == '1' || choice == '2')
			break;
	}
	std::cout << '\n';
	switch (choice) {
	case '1':
		method1();
		break;

	case '2':
		method2();
		break;
	}
}

void method1() {
	int round = 0;
	std::cout << "\n~Method 1 is starting~ \n----------------------";
	std::list<Student>::iterator it = Cohort.begin();
	while (!Cohort.empty()) {
		std::string studentChoice = it->getChoice(round);
		if (SectorVacancies[studentChoice] != 0) {
			std::cout << "\nRound " << round + 1 << ": " << it->getName() << " got allocated to " << studentChoice;
			Cohort.erase(it++);
			SectorVacancies[studentChoice]--;
		}
		else
			++it;
		if (it == Cohort.end()) {
			++round;
			it = Cohort.begin();
		}
	}
}

void method2() {
	char input;
	bool condition = true;
	std::string sectorToFill;
	std::cout << "\n~Method 2 starting~\n-------------------";
	while (condition) {
		std::cout << "\nEnter the first alphabet of the sector(e.g I for IT) :";
		std::cin >> input;
		switch (input) {
		case 'a':
		case 'A':
			sectorToFill = "Aerospace";
			condition = false;
			break;
		case 'i':
		case 'I':
			sectorToFill = "IT";
			condition = false;
			break;
		case 'n':
		case 'N':
			sectorToFill = "NetworkandSecurity";
			condition = false;
			break;
		case 'p':
		case 'P':
			sectorToFill = "Power";
			condition = false;
			break;
		case 's':
		case 'S':
			sectorToFill = "SemiConductor";
			condition = false;
			break;
		default:
			std::cout << "You selected a wrong input!\n";
		}
	}
	int round = 0;
	std::list<Student>::iterator it = Cohort.begin();
	while (SectorVacancies[sectorToFill] != 0) {
		if (it == Cohort.end()) {
			++round;
			it = Cohort.begin();
		}
		if (it->getChoice(round) == sectorToFill) {
			std::cout << "\nRound " << round + 1 << ": " << it->getName() << " got allocated to " << sectorToFill;
			Cohort.erase(it++);
			SectorVacancies[sectorToFill]--;
		}
		else
			++it;
		
	}
	std::cout <<  '\n' << sectorToFill << " sector "  << " is filled\n\n";
	method1();
}
