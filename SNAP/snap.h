#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#ifndef SNAP_H
#define SNAP_H

using namespace std;

class Snap   {
	public:

		Snap() {
			studentId = "";
			studentName = "";
			studentAddress = "";
			studentPhone = "";
		}
		Snap(string id, string name, string address, string phone) {
			studentId = id;
			studentName = name;
			studentAddress = address;
			studentPhone = phone;
		}

		string getStudentName() const { return studentName; }
		string getStudentId() const { return studentId; }
		string getStudentAddress() const { return studentAddress; }
		string getStudentPhone() const { return studentPhone; }

	private:
		string studentId;
		string studentName;
		string studentAddress;
		string studentPhone;


		string toString() const
		{
			stringstream out;
			out << "snap(" << getStudentId() << "," << getStudentName() << "," << getStudentAddress() << "," << getStudentPhone() << ")" << "\n";
			return out.str();
		}
		friend std::ostream& operator<< (ostream& os, const Snap& Snap)
		{
			os << Snap.toString();
			return os;
		}
};

#endif