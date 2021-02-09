#include "IterationMain.cpp"
#include <iostream>
using namespace std;


int main(){
    char* folder_name = (char*)R"(test/sat)";
    // string folder_name=R"(test/sat)";
    int m=100;
    int error=BenchmarkRun(folder_name,m);
    // BenchmarkRun();
    return 0;
}