#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "snap.h"
#include "csg.h"
#include "CourseInfo.h"


#ifndef STUDENT_H
#define STUDENT_H

/*Defines Student Class---
Contains a single Snap object, several Csg objects (one per course) and one CourseInfo object for each Csg.
*/
using namespace std;

class Student
{
	public:

		Student() {
			studentInfo = Snap();
		}

		Student(Snap info) {
			studentInfo = info;
		}
		//setters and getters
		vector<Csg> getStudentGrades() const { return studentGrades; }
		void addStudentGrade(Csg courseGrade) { studentGrades.push_back(courseGrade); }
		Snap getStudentInfo() const { return studentInfo; }
		vector<CourseInfo> getStudentCourses() const { return studentCourses; }
		void addCourse(CourseInfo course) { studentCourses.push_back(course); }

		//takes a courseName and returns the student's grade in that course. 
		string gradeLookup(string courseName) const {
			for (unsigned int i = 0; i < studentGrades.size(); i++) {
				if (studentGrades[i].getCourseName() == courseName) {
					return studentGrades[i].getStudentGrade();
				}
			}
		}


    private:
		Snap studentInfo;
		vector<Csg> studentGrades;
		vector<CourseInfo> studentCourses;


		string toString() const {
			stringstream out;
			out << getStudentInfo().getStudentName() << ", " << getStudentInfo().getStudentId() << ", " << getStudentInfo().getStudentAddress() << ", " << getStudentInfo().getStudentPhone() << "\n";
			for (unsigned int i = 0; i < studentCourses.size(); i++) {
				out << studentCourses[i].getCourseRoom().getCourseName() << " ";
				for (unsigned int j = 0; j < studentCourses[i].getCourseTimes().size(); j++) {
					out << studentCourses[i].getCourseTimes()[j].getCourseDay();
				}
				out << " " << studentCourses[i].getCourseTimes()[0].getCourseTime() << ", ";
				out << studentCourses[i].getCourseRoom().getCourseRoom() << "\n";
			}
			return out.str();
		}

		friend std::ostream& operator<< (ostream& os, const Student& Student)
		{
			os << Student.toString();
			return os;
		}






};
#endif