#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#ifndef CSG_H
#define CSG_H


using namespace std;

class Csg {
	public:

		Csg() {
			studentId = "";
			studentGrade = "";
			courseName = "";

		}
		Csg(string id, string grade, string course) {
			studentId = id;
			studentGrade = grade;
			courseName = course;
		}

		string getCourseName() const { return courseName; }
		string getStudentId() const { return studentId; }
		string getStudentGrade() const { return studentGrade; }

	private:

		string studentId;
		string studentGrade;
		string courseName;

		string toString() const
		{
			stringstream out;
			out << "csg(" << getCourseName() << "," << getStudentId() << "," << getStudentGrade() << ")" << "\n";
			return out.str();
		}
		friend std::ostream& operator<< (ostream& os, const Csg& Csg)
		{
			os << Csg.toString();
			return os;
		}

};

#endif
