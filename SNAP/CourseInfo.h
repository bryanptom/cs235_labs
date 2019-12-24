#ifndef COURSEINFO_H
#define COURSEINFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "cdh.h"
#include "cr.h"
#include "csg.h"

using namespace std;

class CourseInfo
{
	public:

		CourseInfo() {
			courseRoom = Cr();
		}

		CourseInfo(Cr room) {
			courseRoom = room;
		}

		vector<Csg> getStudentGrades() const { return studentGrades; }
		void addStudentGrade(Csg grade) { studentGrades.push_back(grade); }
		vector<Cdh> getCourseTimes() const { return courseTimes; }
		void addCourseTime(Cdh time) { courseTimes.push_back(time); }
		Cr getCourseRoom() const { return courseRoom; }

	private:
		Cr courseRoom;
		vector<Csg> studentGrades;
		vector<Cdh> courseTimes;


};

#endif