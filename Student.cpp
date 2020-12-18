/*
DSA mini project topic 3
Chia Dong (P1938113)
Justin Tan  (P1923731)
Yusuf  (P1923421)
*/

#include "Student.h"

Student::Student(std::string name, double GPA, std::vector<std::string> choices)
	: m_name(std::move(name)), m_GPA(GPA), m_choices(std::move(choices))	//member initializer list
{
}

//return Student GPA
double Student::getGPA() const {
	return m_GPA;
}

//return the name of Student
const std::string& Student::getName() const {
	return m_name;
}

//return the Sector that the student chose
const std::string& Student::getChoice(int i) const {
	return m_choices[i];
}