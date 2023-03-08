#include <iostream>
#include <fstream>
#include <string>
//purpose is to match a list of TAs
using namespace std;

struct Student {
    string caller;
    int time;
    bool isFirst;
    string callee;
    Student *partner;
};

Student *read_students(string filename, int *num_students);
int count_students(string filename);
void match_students(Student *students, int num_students);
void print_pairings(Student *students, int num_students);

int main(int argc, char *argv[]) {
    //Make sure I was actually given a filename on the command-line
    if (argc < 2) {
        cerr << "ERROR: Expecting a file name as a command-line argument." << endl;
        exit(EXIT_FAILURE);
    }

    //Read in the students from the provided file
    int num_students;
    Student *students = read_students(argv[1], &num_students);
    
    //Find partners for as many students as you can
    match_students(students, num_students);
    
    //Print out the partnerings
    print_pairings(students, num_students);
    
    //Delete the student memory from the heap
    delete [] students;
    return 0;
} 

// print_pairings
// Input: A pointer to an array of students and the size of the array.
// Description: Print the pairings between students (or the lack thereof).
// Output: A message printed with cout.
void print_pairings(Student *students, int num_students) {
    int total_time = 0;
    Student *myCallerList = nullptr;
    //Student *myCallerList = new Student[num_students];
    //tells first person
    for (int i = 0; i < num_students; i++) {
        if (students[i].partner == nullptr){
                cout<< students[i].caller<<endl;
                myCallerList = &students[i];
        }
        if (students[i].isFirst != true){
            total_time = total_time + students[i].time;
        }
    }

        
    if(myCallerList != nullptr){
        cout<<"first person to is "<<myCallerList[0].caller<<endl;
        cout<<"the out time is "<<total_time<<endl;
    }else{
        cout<<"Damn you Harold"<<endl;
    }
}

// match_students
// Input: A pointer to an array of students and the size of the array.
// Description: Match students with a partner who can work at the same time.
// Output: Potentially modifies the 'partner' field of elements of the 
//         students array.
void match_students(Student *students, int num_students) {
    //thjis loop sets the pointer 
    for (int i = 0; i < num_students; i++) {
        //cout<<"the name: "<<students[i].name << " the partner is "<< students[i].rPartner<< " and the time is: "<< students[i].time<<"\n";
        for (int j = 0; j < num_students; j++){
            if(students[i].caller == students[j].callee){
                students[i].partner = &students[j];
                break;
            }
        }
    }

    //this loop sets if it should be counted
    
    for (int i = 0; i < num_students; i++){
        for (int j = 0; j < num_students; j++){
            if(i != j){
                if(students[i].callee == students[j].callee && students[i].isFirst != true ){
                    students[j].isFirst =  true;
                }
            }
        }
    }
}

// read_students
// Input: A file name and a pointer to store the number of students in the file.
// Description: Read a file into an array of Student structs.
// Output: A pointer to the array of Student structs, dynamically allocated on
//         the heap. 
Student *read_students(string filename, int *num_students) {
    *num_students = count_students(filename);
    //cout<<"the total students are: "<< *num_students<< "\n";
    Student *students = new Student[*num_students];
    
    ifstream infile(filename.c_str());
    if (infile.fail()) {
        cerr << "ERROR: Error opening file, please check file name: " 
             << filename << endl;
        exit(EXIT_FAILURE);
    }
    
    string name;
    int time;
    string partner;
    string skip;
    //need to skip the first line
    infile >>skip;
    for (int i = 0; i < *num_students; i++) {
        infile >> name >> time >> partner;
        students[i].caller = name;
        students[i].time = time;
        students[i].partner = nullptr;
        students[i].callee = partner;
        students[i].isFirst = false;
    }
    infile.close();
    
    return students;
}

// count_students
// Input: A file name.
// Description: Read through the file of student information just to count the
//              lines (one for each student). 
// Output: The number of students in the file.
int count_students(string filename) {
    ifstream infile(filename);
    if (infile.fail()) {
        cerr << "ERROR: Error opening file, please check file name: " 
             << filename << endl;
        exit(EXIT_FAILURE);
    }
    
    int student_count = 0;
    //first line is the total students
    infile >> student_count;
    //cout<<student_count<<"\n";

    infile.close();
    
    return student_count;
}
