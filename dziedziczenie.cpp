#include <iostream>
#include <string>

enum class sex {woman, man};

sex strToSex(std::string sexStr) {
  if (sexStr == "K") { return sex::woman; }
  else { return sex::man; }
}

double calcAvg(double arr[], unsigned int arrLength) {
  if (arrLength) {
    double degreeSum = 0;
    for (unsigned int i = 0; i < arrLength; i++) {
      degreeSum += arr[i];
    }
    return degreeSum;
  }
  return 0;
}


class Person {
  public:
    Person() = default;
    ~Person() = default;
    Person(std::string, std::string, float, float, int, sex);
    void displayInfo();
    float calcBMI();
    
  protected:
    sex gender;
  private:
    std::string name;
    std::string surname;
    float weight;
    float height;
    int age;

  friend class Student;
  friend class Worker;
  friend class Course;
};

class Student : public Person {
  public:
    Student() = default;
    ~Student() = default;
    Student(std::string, std::string, float, float, int, sex, std::string, int);
    double avgDegree() { return calcAvg(this->degreeList, this->degreeCount); }
    void pushDegree(double);
    friend bool operator<(Student&, Student&);
  private:
    std::string index_no;
    int semester;
    double degreeList[10] = {0.0};
    int degreeCount = 0;

  friend class Course;
};

class Course {
  public:
    Course() = default;
    ~Course() = default;
    Course(std::string);
    void add(Student*);
    void remove(std::string);
    // void studentUpdate(int);
    //sort descending students by average of mark
    void studentSort(int);
    //show top 3 of students in descending
    void topThree(int);
  
  private:
    std::string course_name;
    //change as pointer to objects
    Student* studentList[5][10] = {nullptr}; 
		//in each semester
    int studentCount[5] = {0};
		//all of students
    int student_amount = 0;
  
  friend class Student;
};

class Worker : public Person {
  public:
    Worker() = default;
    ~Worker() = default;
    Worker(std::string, std::string, float, float, int, sex, std::string, std::string, double, float);
    int calcYearsToRetire();
  private:
    std::string company_name;
    std::string workstation;
    double salary;
    float seniorityAge;
};


//////person's constructor and functions
Person::Person(std::string name, std::string surname, float weight, float height, int age, sex gender) {
  this->name = name;
  this->surname = surname;
  this->weight = weight;
  this->height = height;
  this->age = age;
  this->gender = gender;
}

float Person::calcBMI() {
  return (this->weight/(this->height*this->height))*10000;
}

void Person::displayInfo() {
  std::cout << this->name << " " << this->surname << " " << this->weight << " " << this->height << " " << this->age;
}

//////course's constructor and functions
Course::Course(std::string course_name) {
  this->course_name = course_name;
}

void Course::add(Student* toAdd) {
  int year_index = toAdd->semester - 1;
  
  this->studentList[year_index][this->studentCount[year_index]++] = toAdd;
  this->student_amount++;
}

void Course::remove(std::string toRem) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < this->studentCount[i]; j++) {
      if (toRem == this->studentList[i][j]->index_no) {
				for (int k = j; k < this->studentCount[i] - 1; k++) {
					this->studentList[i][k] = this->studentList[i][k+1];
          this->studentList[i][k+1] = nullptr;
        }
        this->studentCount[i]--;
        this->student_amount--;
        break;
      }
    }
  }
}

void Course::studentSort(int semesterToSort) {
	semesterToSort--;

	for (int i = 0; i < this->studentCount[semesterToSort] - 1; i++) {
		for (int j = 0; j < this->studentCount[semesterToSort] - 1; j++) {
      if (*studentList[semesterToSort][j] < *studentList[semesterToSort][j+1]) {
          std::swap(*studentList[semesterToSort][j], *studentList[semesterToSort][j+1]);
      }
		}
	}
}

void Course::topThree(int topInSemester) {
  this->studentSort(topInSemester);
  topInSemester--;

  int inSemester = (studentCount[topInSemester] > 3 ? 3 : studentCount[topInSemester]);
  for (int i = 0; i < inSemester; i++) {
    Student* studentTmp = studentList[topInSemester][i];

    std::cout << studentTmp->index_no << " " << studentTmp->name << " " << studentTmp->surname << " ";
  }

}

bool operator<(Student& a, Student& b) {
  return a.avgDegree() < b.avgDegree();
}

//////student's constructor and functions
Student::Student(std::string name, std::string surname, float weight, float height, int age, sex gender, std::string index_no, int semester) {
  this->name = name;
  this->surname = surname;
  this->weight = weight;
  this->height = height;
  this->age = age;
  this->gender = gender;
  this->index_no = index_no;
  this->semester = semester;
}

void Student::pushDegree(double degree_toAdd) {
  this->degreeList[this->degreeCount++] = degree_toAdd;
}

//////worker's constructor and functions
Worker::Worker(std::string name, std::string surname, float weight, float height, int age, sex gender, std::string company_name, std::string workstation, double salary, float seniorityAge) {
  this->name = name;
  this->surname = surname;
  this->weight = weight;
  this->height = height;
  this->age = age;
  this->gender = gender;
  this->company_name = company_name;
  this->workstation = workstation;
  this->salary = salary;
  this->seniorityAge = seniorityAge;
}

int Worker::calcYearsToRetire() {
  return (this->gender == sex::woman ? 60 - this->age : 65 - this->age);
}


int main() {
  std::string course_name;
  std::cin >> course_name;
  
  Course AWF(course_name);

  for (int i = 0; i < 10; i++) {
    
    std::string name,
    surname,
    index_no,
    genderHolder;

    float weight,
    height;
    sex gender = sex::woman;
    int age,
    semester;

    std::cin >> name >> surname >> weight >> height >> age >> genderHolder >> index_no >> semester;
    
    gender = strToSex(genderHolder);

    Student* stu = new Student(name, surname, weight, height, age, gender, index_no, semester);

    for (int j = 0; j < 5; j++) {
      double degree = 0.0;
      std::cin >> degree;
      stu->pushDegree(degree);
    }

    AWF.add(stu);
  }

  int choiceSem;
  std::cin >> choiceSem;
  AWF.topThree(choiceSem);

  for (int i = 0; i < 2; i++) { 
    std::string name,
    surname,
    genderHolder,
    company_name, 
    workstation;
    float weight,
    height,
    salary,
    seniorityAge;

    sex gender = sex::woman;
    int age;
    
    std::cin >> name >> surname >> weight >> height >> age >> genderHolder >> company_name >> workstation >> salary >> seniorityAge;
    gender = strToSex(genderHolder);

    Worker emplo = *new Worker(name, surname, weight, height, age, gender, company_name, workstation, salary, seniorityAge);
    std::cout << emplo.calcYearsToRetire();
    if (i < 1) {
      std::cout << " ";
    }

  }


  return 0;
}