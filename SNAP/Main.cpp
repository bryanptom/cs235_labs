#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include "Student.h"
#include "Course.h"

using namespace std;


int main(int argc, char* argv[])
{


	//Open the in and out streams
	ifstream in(argv[1]);
	ofstream out(argv[2]);


	//initailize the vectors to store imput
	vector<Snap> snaps;
	vector<Cr> crs;
	vector <Csg> csgs;
	vector <Cdh> cdhs;

	out << "Input Strings: " << "\n";

	//imput from the in file and store the lines as objects of snaps, crs, etc.
	for (string line; getline(in, line);)	
	{
		try {
			if ("cr(" == line.substr(0, 3)) {
				out << line << "\n";

				string courseName = line.substr(3, line.find(',') - 3);
				line = line.substr(line.find(',') + 1);
				string room = line.substr(0, line.find(')'));
				crs.push_back(Cr(courseName, room));
			}
			else if ("csg(" == line.substr(0, 4)) {
				out << line << "\n";

				string courseName = line.substr(4, line.find(',') - 4);
				line = line.substr(line.find(',') + 1);
				string studentId = line.substr(0, line.find(','));
				line = line.substr(line.find(',') + 1);
				string grade = line.substr(0, line.find(')'));
				csgs.push_back(Csg(studentId, grade, courseName));

			}
			else if ("cdh(" == line.substr(0, 4)) {
				out << line << "\n";

				string courseName = line.substr(4, line.find(',') - 4);
				line = line.substr(line.find(',') + 1);
				string day = line.substr(0, line.find(','));
				line = line.substr(line.find(',') + 1);
				string time = line.substr(0, line.find(')'));
				cdhs.push_back(Cdh(courseName, day, time));
			}
			else if ("snap(" == line.substr(0, 5)) {
				out << line << "\n";

				string id = line.substr(5, line.find(',') - 5);
				line = line.substr(line.find(',') + 1);
				string name = line.substr(0, line.find(','));
				line = line.substr(line.find(',') + 1);
				string address = line.substr(0, line.find(','));
				line = line.substr(line.find(',') + 1);
				string phone = line.substr(0, line.find(')'));
				snaps.push_back(Snap(id, name, address, phone));
			}
			else {
				throw 1;
			}

		}
		catch (int){
			out << "**Error: " << line << "\n";
		}
	}

	//output the vectors we just saved
	out << "Vectors:" << "\n";

	for (unsigned int i = 0; i < snaps.size(); i++) {
		out << snaps[i];
	}
	for (unsigned int i = 0; i < csgs.size(); i++) {
		out << csgs[i];
	}
	for (unsigned int i = 0; i < cdhs.size(); i++) {
		out << cdhs[i];
	}
	for (unsigned int i = 0; i < crs.size(); i++) {
		out << crs[i];
	}

	//initialize vectors of CourseInfo, Course, and Student objects
	vector<CourseInfo> courseInfoList;
	vector<Course> courseList;
	vector<Student> studentList;

	//use each cr object to create a CourseInfo object
	for (unsigned int i = 0; i < crs.size(); i++) {
		courseInfoList.push_back(CourseInfo(crs[i]));
	}

	//use each snap object to create a student object
	for (unsigned int i = 0; i < snaps.size(); i++) {
		studentList.push_back(Student(snaps[i]));
	}

	//add each cdh object to the relavent CourseInfo object
	for (unsigned int i = 0; i < cdhs.size(); i++) {
		for (unsigned int j = 0; j < courseInfoList.size(); j++) {
			if (courseInfoList[j].getCourseRoom().getCourseName() == cdhs[i].getCourseName()) {
				courseInfoList[j].addCourseTime(cdhs[i]);
			}
		}
	}

	//adds csg object to the relavent CourseInfo and Student objects.
	for (unsigned int i = 0; i < csgs.size(); i++) {
		for (unsigned int j = 0; j < courseInfoList.size(); j++) {
			if (courseInfoList[j].getCourseRoom().getCourseName() == csgs[i].getCourseName()) {
				courseInfoList[j].addStudentGrade(csgs[i]);
			}
		}

		for (unsigned int j = 0; j < studentList.size(); j++) {
			if (studentList[j].getStudentInfo().getStudentId() == csgs[i].getStudentId()) {
				studentList[j].addStudentGrade(csgs[i]);	
			}
		}
	}

	//creates a Course object for each CourseInfo object
	for (unsigned int i = 0; i < courseInfoList.size(); i++) {
		courseList.push_back(Course(courseInfoList[i]));
	}

	//adds all students in a course to that Course object in csg order
	for (unsigned int i = 0; i < courseList.size(); i++) {
		for (unsigned int j = 0; j < courseList[i].getCourseInfo().getStudentGrades().size(); j++) {
			for (unsigned int k = 0; k < studentList.size(); k++) {
				if (courseList[i].getCourseInfo().getStudentGrades()[j].getStudentId() == studentList[k].getStudentInfo().getStudentId()) {
					courseList[i].addStudent(studentList[k]);
				}
			}
		}
	}
	
	//adds all relavent CourseInfo objects to each student
	for (unsigned int i = 0; i < studentList.size(); i++) {
		for (unsigned int j = 0; j < studentList[i].getStudentGrades().size(); j++) {
			for (unsigned int k = 0; k < courseInfoList.size(); k++) {
				for (unsigned int l = 0; l < courseInfoList[k].getStudentGrades().size(); l++) {
					if (studentList[i].getStudentGrades()[j].getStudentId() == courseInfoList[k].getStudentGrades()[l].getStudentId() && studentList[i].getStudentGrades()[j].getCourseName() == courseInfoList[k].getStudentGrades()[l].getCourseName()) {
						studentList[i].addCourse(courseInfoList[k]);
					}
				}
			}
		}
	}



	out << "Course Grades:" << "\n";

	for (unsigned int i = 0; i < courseList.size(); i++) {
		out << courseList[i] << "\n";
	}

	out << "Student Schedules:" << "\n";

	for (unsigned int i = 0; i < studentList.size(); i++) {
		out << studentList[i] << "\n";
	}


	return 0;
}
