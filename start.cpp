#include "IterationMain.cpp"
#include <iostream>
using namespace std;


int main(){
    char* folder_name = (char*)R"(sat)";
    // string folder_name=R"(test/sat)";
    int error=BenchmarkRun(folder_name);
    // BenchmarkRun(folder_name);
    return 0;
}