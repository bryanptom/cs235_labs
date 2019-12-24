#include "CourseInfo.h"
#include "Student.h"

#include <iostream>
#include <fstream>
#include <string>
#include <ostream>
#include <vector>

#ifndef COURSE_H
#define COURSE_H

using namespace std;

class Course
{
public:



	Course() {
		courseInfo = CourseInfo();
	}

	Course(CourseInfo info) {
		courseInfo = info;
	}

	vector<Student> getStudentList() const { return studentList; }
	void addStudent(Student student) { studentList.push_back(student); }
	CourseInfo getCourseInfo() const { return courseInfo; }

private:

	vector<Student> studentList;
	CourseInfo courseInfo;


	string toString() const {
		stringstream out;
		for (unsigned int i = 0; i < getStudentList().size(); i++) {
			out << courseInfo.getCourseRoom().getCourseName() << "," << getStudentList()[i].getStudentInfo().getStudentName() << "," << getStudentList()[i].gradeLookup(courseInfo.getCourseRoom().getCourseName()) << "\n";
		}
		return out.str();
	}

	friend std::ostream& operator<< (ostream& os, const Course& Course)
	{
		os << Course.toString();
		return os;
	}
};

#endif