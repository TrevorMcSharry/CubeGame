//Trevor McSharry
//A manually created "vector" that manages memory using delete[] and pointers
//11/24/2020
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

class doublevector {
  static constexpr double DOUBLE_DEFAULT_VALUE = -5.55;
  double *mValues;
  int mNumValues;

public:
  doublevector();
  ~doublevector();
  void resize(int new_size, double initial_value = DOUBLE_DEFAULT_VALUE);
  void push_back(double value);
  double &at(int index);
  const double &at(int index) const;
  unsigned long size() const;
};

void print_all(const doublevector &v) {
  if (v.size() == 0) {
    cout << "Vector is empty.\n";
  } 
  else {
    unsigned long i;
    for (i = 0; i < v.size(); i++) {
      cout << "[" << setfill('0') << right << setw(3) << i << "] = " << fixed
           << setprecision(4) << v.at(i) << '\n';
    }
  }
}

int main() {
  doublevector v;
  do {
    string command;
    cout << "Enter a command ('quit' to quit): ";
    if (!(cin >> command) || command == "quit") {
      break;
    } 
	
	else if (command == "push_back") {
      double value;
      cin >> value;
      v.push_back(value);
      cout << "Pushed back " << fixed << setprecision(4) << value << '\n';
    } 
	
	else if (command == "resize") {
      string line;
      int new_size;
      double initial;
      cin >> new_size;
      getline(cin, line);
      istringstream sin(line);

      if (sin >> initial) {
        v.resize(new_size, initial);
      }
	 
	 else {
        v.resize(new_size);
	  }
    } 
	
	else if (command == "size") {
      cout << v.size() << '\n';
    } 
	
	else if (command == "print") {
      print_all(v);
    } 
	
	else if (command == "get") {
      int index;
      cin >> index;
      
	  try {
        cout << "Value at " << index << " = " << setprecision(4) << fixed
             << v.at(index) << '\n';
      } 
	  
	  catch (out_of_range &err) {
        cout << err.what() << '\n';
      }
    } 
	
	else if (command == "set") {
      double d;
      int index;
      cin >> index >> d;
      
	  try {
        v.at(index) = d;
        cout << "SET: " << index << " = " << setprecision(4) << fixed
             << v.at(index) << '\n';
      } 
	  
	  catch (out_of_range &err) {
        cout << err.what() << '\n';
      }
    } 
	
	else if (command == "clear") {
      v.resize(0);
    } 
	
	else {
      cout << "Invalid command '" << command << "'\n";
    }
	
  } while (true);
  
  cout << '\n';
  
  return 0;
}
//Default constructor for doublevector
doublevector::doublevector() {
  mValues = nullptr;
  mNumValues = 0;
}
//Deconstructor for doublevector
doublevector::~doublevector() { 
  if(mValues != nullptr){
    delete[] mValues;
  }
}
//Function that resizes the "vector" using the new_size and initial_value.
//It creates a new pointer and does a for loop to assign the values to the new one
//I then delete the old pointer and assign my new values into the old pointer
void doublevector::resize(int new_size, double initial_value) { 
  if(new_size > mNumValues){
    double *newPtr = new double[new_size];
    for(int i = 0; i < mNumValues; i++){
      newPtr[i] = mValues[i];
    }
    for(int i = mNumValues; i < new_size; i++){
      newPtr[i] = initial_value;
      }

    if(mValues != nullptr){
      delete[] mValues;
    }
    mValues = newPtr;
    mNumValues = new_size;
    }
    
  else if(new_size < mNumValues){
    double *newPtr = new double[new_size];
    for(int i = 0; i < new_size; i++){
      newPtr[i] = mValues[i];
    }
    if(mValues != nullptr){
    delete[] mValues;
    }
    mValues = newPtr;
    mNumValues = new_size;
  }
  mNumValues = new_size;
}
//Function that adds a value to the end of the "vector"
void doublevector::push_back(double value) {
  resize(mNumValues + 1, value);
}
//These both have the same code and access the value at a specific point
double &doublevector::at(int index) { 
    if(index >= mNumValues) {
        ostringstream sout;
        sout << "Invalid index #" << index;
        throw out_of_range(sout.str());
    }
  return mValues[index];
}
const double &doublevector::at(int index) const{
  if(index >= mNumValues) {
        ostringstream sout;
        sout << "Invalid index #" << index;
        throw out_of_range(sout.str());
    }
  return mValues[index];
}
//Function that returns the size of the vector
unsigned long doublevector::size() const{
  unsigned long size = (unsigned long)mNumValues;
  return size;
}