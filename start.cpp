#include "IterationMain.cpp"
#include <iostream>
using namespace std;


int main(){
    char* folder_name = (char*)R"(sat)";
    // string folder_name=R"(test/sat)";
    int m=10;
    int error=BenchmarkRun(folder_name,m);
    // BenchmarkRun();
    return 0;
}