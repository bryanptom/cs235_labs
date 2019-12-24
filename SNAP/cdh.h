#include <iostream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <string>

#ifndef CDH_H
#define CDH_H

using namespace std;

class Cdh {
public:

	Cdh() {
		courseDay = "";
		courseTime = "";
		courseName = "";

	}
	Cdh(string course, string day, string time) {
		courseDay = day;
		courseTime = time;
		courseName = course;
	}

	string getCourseName()  const { return courseName; }
	string getCourseDay() const { return courseDay; }
	string getCourseTime() const { return courseTime; }

private:
	string courseName;
	string courseDay;
	string courseTime;

	string toString() const
	{
		stringstream out;
		out << "cdh(" << getCourseName() << "," << getCourseDay() << "," << getCourseTime() << ")" << "\n";
		return out.str();
	}
	friend std::ostream& operator<< (ostream& os, const Cdh& Cdh)
	{
		os << Cdh.toString();
		return os;
	}


};

#endif
