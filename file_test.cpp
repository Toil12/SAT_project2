#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    string file_path="/home/femstld/C++/SAT_project2/test/sat/count4_2.cnf";
    ifstream fis(file_path);
    if(!fis){
        cout<<"File can not open.";
        exit(1);
    }
    else
    {
        cout<<"done";
    }

    return 0;

}