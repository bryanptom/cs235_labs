#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

//outputs the student names and exam scores to the output file
void outputStudentScores(double** scoresArray, string* names, int numStudents, int numExams, ofstream& out) {
	
	out << "Student Scores:" << "\n";
	for (int i = 0; i < numStudents; i++) {
		out << setw(20) << names[i] << " ";
		for (int j = 0; j < numExams; j++) {
			out << setw(6) << scoresArray[i][j];
		}
		out << "\n";
	}
}

//outputs the average score for each exam to the outfile
double *outputExamAverages(double** scoresArray, int numStudents, int numExams, ofstream& out) {
	out << "\n" << "Exam Averages : " << "\n";
	double* averageScores = new double[numExams];
	double sum = 0;
	double average = 0;

	for (int i = 0; i < numExams; i++) {
		out << setw(20) << "Exam " << to_string(i + 1) << " Average =    ";
		sum = 0;
		for (int j = 0; j < numStudents; j++) {
			sum += scoresArray[j][i];
		}

		average = sum / numStudents;
		out << fixed << setprecision(1) << average << "\n";
		averageScores[i] = average;
	}

	return averageScores;
}

//outputs the student names and their scores and grades on each exam to the outfile
void outputStudentExamGrades(double** scoresArray, string* names, int numStudents, int numExams, ofstream& out, double* averageScores) {
	out << "\n" << "Student Exam Grades: " << "\n";
	for (int i = 0; i < numStudents; i++) {
		out << setw(20) << names[i];
		for (int j = 0; j < numExams; j++) {
			out << setw(6) << setprecision(0) << scoresArray[i][j] << "(";

			if (scoresArray[i][j] - averageScores[j] > 15) out << "A)";
			else if (scoresArray[i][j] - averageScores[j] > 5) out << "B)";
			else if (averageScores[j] - scoresArray[i][j] > 15) out << "E)";
			else if (averageScores[j] - scoresArray[i][j] > 5) out << "D)";
			else out << "C)";
		}
		out << "\n";
	}
}

//outputs the total number of each grade (A, B, C, etc) for each exam
void outputExamGrades(double** scoresArray, int numStudents, int numExams, ofstream& out, double* averageScores) {
	out << "\n" << "Exam Grades:" << "\n";
	string grades[5] = { "A", "B", "C", "D", "E" };
	int studGrades[5];

	for (int j = 0; j < numExams; j++) {

		out << setw(15) << "Exam " << j + 1;

		for (int k = 0; k < 5; k++) {
			studGrades[k] = 0;
		}

		for (int i = 0; i < numStudents; i++) {
			if (scoresArray[i][j] - averageScores[j] > 15) studGrades[0]++;
			else if (scoresArray[i][j] - averageScores[j] > 5) studGrades[1]++;
			else if (averageScores[j] - scoresArray[i][j] > 15) studGrades[4]++;
			else if (averageScores[j] - scoresArray[i][j] > 5) studGrades[3]++;
			else studGrades[2]++;
		}

		for (int k = 0; k < 5; k++) {
			out << setw(6) << studGrades[k] << "(" << grades[k] << ")";
		}
		out << "\n";
	}
}

//outputs each student's average grade (both percentage and letter grade) and the overall class average grade 
void outputStudentFinalGrades(double** scoresArray, string* names, int numStudents, int numExams, ofstream& out, double* averageScores) {
	double* finalGrades = new double[numStudents];
	double averageGrade = 0.0;
	double totalGrade = 0.0;
	double gradeAdder = 0.0;

	out << '\n' << "Student Final Grades : " << '\n';

	for (int i = 0; i < numStudents; i++) {
		totalGrade = 0;

		for (int j = 0; j < numExams; j++) {
			totalGrade += scoresArray[i][j];
		}

		finalGrades[i] = totalGrade / numExams;
		gradeAdder += finalGrades[i];
	}

	averageGrade = gradeAdder / numStudents;


	for (int i = 0; i < numStudents; i++) {
		out << setw(20) << names[i];
		out << fixed << setprecision(1) << setw(6) << finalGrades[i] << "(";

		if (finalGrades[i] - averageGrade > 15) out << "A)";
		else if (finalGrades[i] - averageGrade > 5) out << "B)";
		else if (averageGrade - finalGrades[i] > 15) out << "E)";
		else if (averageGrade - finalGrades[i] > 5) out << "D)";
		else out << "C)";

		out << "\n";
	}

	out << setw(20) << "Class Average Score = " << fixed << setprecision(1) << averageGrade << "\n";
	delete [] finalGrades;
}


int main(int argc, char* argv[])
{

	//Open the in and out streams
	ifstream in(argv[1]);
	ofstream out(argv[2]);

	//Get values for the number of students and number of exams
	int numStudents;
	int numExams;
	in >> numStudents >> numExams;
	in.ignore(std::numeric_limits<int>::max(), '\n');
	
	//initialize variables for imputing data
	string* names = new string[numStudents];
	string line;
	string name;
	int nameLength = 0;
	double** scoresArray = new double* [numStudents];
	int end;
	int score;
	int start;
	signed int zero = 0;
	signed int lineLength;

	//save data for student names and exam scores to dynamic string arrays
	for (int i = 0; i < numStudents; i++) {

		getline(in, line);
		nameLength = 0;
		while (!isdigit(line[nameLength])) nameLength++;
		name = line.substr(0, nameLength - 1);
		names[i] = name;

		start = nameLength;

		lineLength = line.length();

		scoresArray[i] = new double[numExams];

		for (int j = 0; j < numExams; j++) {
			if (start > zero && start < lineLength) {

				end = line.find(" ", start + 1);
				score = stoi(line.substr(start, end));


				scoresArray[i][j] = score;
				start = end;
			}
		}
	}

	//outputs required data (see member functions for descriptions of outputs)

	outputStudentScores(scoresArray, names, numStudents, numExams, out);

	double *averageScores = outputExamAverages(scoresArray, numStudents, numExams, out);

	outputStudentExamGrades(scoresArray, names, numStudents, numExams, out, averageScores);

	outputExamGrades(scoresArray, numStudents, numExams, out, averageScores);

	outputStudentFinalGrades(scoresArray, names, numStudents, numExams, out, averageScores);

	//deletes allocated memory to avoid memory leaks
	for (int i = 0; i < numStudents; i++) {
			delete [] scoresArray[i];
		}
	delete[] scoresArray;
	delete [] names;
	delete [] averageScores;

	return 0;
};

