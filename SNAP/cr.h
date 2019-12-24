#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#ifndef CR_H
#define CR_H

using namespace std;

class Cr {
public:

	Cr() {
		courseRoom = "";
		courseName = "";

	}
	Cr(string course, string room) {
		courseRoom = room;
		courseName = course;
	}

	string getCourseName() const { return courseName; }
	string getCourseRoom() const { return courseRoom; }

private:
	string courseName;
	string courseRoom;


	string toString() const
	{
		stringstream out;
		out << "cr(" << getCourseName() << "," << getCourseRoom() << ")" << "\n";
		return out.str();
	}
	friend std::ostream& operator<< (ostream& os, const Cr& Cr)
	{
		os << Cr.toString();
		return os;
	}

};

#endif
