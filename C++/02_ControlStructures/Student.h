// Student class that stores a student name and average

#include <string>

class Student {
    public:
        // Student constructor
        Student(std::string studentName, int studentAverage) :name(studentName) {
            setAverage(studentAverage);
        }

        // Sets the student's name
        void setName(std::string studentName){
            name = studentName;
        }

        // Retrieves the student's name
        std::string getName(){
            return name;
        }

        // Sets the student's average
        void setAverage(int studentAverage){
            if(studentAverage > 0){
                if(studentAverage <= 100){
                    average = studentAverage;
                }
            }
        }

        // Retrieves the student's average
        int getAverage(){
            return average;
        }

        // Determines and returns the student's letter grade
        std::string getLetterGrade(){
            std::string letterGrade;

            if(average >= 90){
                letterGrade = "A";
            } else if(average >= 80){
                letterGrade = "B";
            } else if(average >= 70){
                letterGrade = "C";
            } else if(average >= 60){
                letterGrade = "D";
            } else {
                letterGrade = "F";
            }

            return letterGrade;
        }

    private:
        std::string name;
        int average{0};
};