#include<iostream>
#include<fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Student {
    string roll, name, fname, address;
};

class temp{
    string rollNum,name,fName,address,search;
    fstream file;
    public:
    void addStu();
    void viewStu();
    void searchStu();
    void deleteStu();
    void editStu();
}obj;

int main(){

    char choice;
    cout<<"---------------------------"<<endl;
    cout<<"1- Add Student Record"<<endl;
    cout<<"2- View All Student Record"<<endl;
    cout<<"3- Search Student Record"<<endl;
    cout<<"4- Exit"<<endl;
    cout<<"5- Delete Student Record"<<endl;
    cout<<"6- Edit Student Record"<<endl;
    cout<<"---------------------------"<<endl;
    cin>>choice;

    switch(choice){
        case '1':
            cin.ignore();
            obj.addStu();
        break;
        case '2':
            cin.ignore();
            obj.viewStu();
        break;
        case '3':
            cin.ignore();
            obj.searchStu();
        break;
        case '4':
            return 0;
        break;
        case '5':
            cin.ignore();
            obj.deleteStu();
        break;
        case '6':
            cin.ignore();
            obj.editStu();
        break;
        default:
            cout<<"Invalid Choice...!";
    }

}

void temp :: addStu(){
    
    cout<<"Enter Student Roll Number :: ";
    getline(cin,rollNum);
    cout<<"Enter Student Name ::";
    getline(cin,name);
    cout<<"Enter Student Father Name ::";
    getline(cin,fName);
    cout<<"Enter Student Address ::";
    getline(cin,address);

    file.open("stuData.txt",ios :: out | ios :: app);
    file<<rollNum<<"*";
    file<<name<<"*";
    file<<fName<<"*";
    file<<address<<endl;
    file.close();
}

void temp :: viewStu(){

    vector<Student> students;
    Student s;

    file.open("stuData.txt", ios::in);

    if (!file) {
        cout << "No record found!" << endl;
        return;
    }

    // Read file into vector
    while (getline(file, s.roll, '*')) {
        getline(file, s.name, '*');
        getline(file, s.fname, '*');
        getline(file, s.address);
        students.push_back(s);
    }
    file.close();

    // Sort by Roll Number
    sort(students.begin(), students.end(),
         [](Student a, Student b){
             return a.roll < b.roll;   // lexicographical sort
         });

    // Table Header
    cout << "\n";
    cout << left
         << setw(12) << "Roll No"
         << setw(25) << "Name"
         << setw(25) << "Father Name"
         << setw(25) << "Address" << endl;

    cout << string(87, '-') << endl;

    // Display Sorted Records
    for (auto &st : students) {
        cout << left
             << setw(12) << st.roll
             << setw(25) << st.name
             << setw(25) << st.fname
             << setw(25) << st.address << endl;
    }
}

void temp :: searchStu(){

    cout<<"Enter Student Roll Number :: ";
    getline(cin,search);
    
    file.open("stuData.txt",ios :: in);
    getline(file,rollNum,'*');
    getline(file,name,'*');
    getline(file,fName,'*');
    getline(file,address,'\n');
    while(!file.eof()){
        if(rollNum == search){
            cout<<endl;
            cout<<"Student Roll Number :: "<<rollNum<<endl;
            cout<<"Student Name :: "<<name<<endl;
            cout<<"Student Father Name :: "<<fName<<endl;
            cout<<"Student Address :: "<<address<<endl;       
        }
        getline(file,rollNum,'*');
        getline(file,name,'*');
        getline(file,fName,'*');
        getline(file,address,'\n');
    }
    file.close();
}

void temp :: deleteStu(){

    string roll;
    bool found = false;

    cout<<"Enter Student Roll Number to Delete :: ";
    getline(cin, roll);

    ifstream fin("stuData.txt");
    ofstream fout("temp.txt");

    while (getline(fin, rollNum, '*')) {
        getline(fin, name, '*');
        getline(fin, fName, '*');
        getline(fin, address);

        if (rollNum == roll) {
            found = true;   // record পাওয়া গেছে
        } else {
            fout << rollNum << "*"
                 << name << "*"
                 << fName << "*"
                 << address << endl;
        }
    }

    fin.close();
    fout.close();

    remove("stuData.txt");
    rename("temp.txt", "stuData.txt");

    if (found)
        cout<<"\nRecord Deleted Successfully!\n";
    else
        cout<<"\nRecord Not Found!\n";
}

void temp :: editStu(){

    string roll;
    bool found = false;

    cout << "Enter Student Roll Number to Edit :: ";
    getline(cin, roll);

    ifstream fin("stuData.txt");
    ofstream fout("temp.txt");

    while (getline(fin, rollNum, '*')) {
        getline(fin, name, '*');
        getline(fin, fName, '*');
        getline(fin, address);

        if (rollNum == roll) {
            found = true;

            cout << "\nCurrent Details:\n";
            cout << "Name: " << name << endl;
            cout << "Father Name: " << fName << endl;
            cout << "Address: " << address << endl;

            cout << "\nEnter New Details\n";
            cout << "Enter Name :: ";
            getline(cin, name);
            cout << "Enter Father Name :: ";
            getline(cin, fName);
            cout << "Enter Address :: ";
            getline(cin, address);

            fout << rollNum << "*"
                 << name << "*"
                 << fName << "*"
                 << address << endl;
        }
        else {
            fout << rollNum << "*"
                 << name << "*"
                 << fName << "*"
                 << address << endl;
        }
    }

    fin.close();
    fout.close();

    remove("stuData.txt");
    rename("temp.txt", "stuData.txt");

    if (found)
        cout << "\nRecord Updated Successfully!\n";
    else
        cout << "\nStudent Record Not Found!\n";
}
