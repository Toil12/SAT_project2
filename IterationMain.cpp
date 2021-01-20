#include "Optimized DPLL Algorithm.cpp"
#include "FileOperations.cpp"
#include <iostream>
using namespace std;

void BenchmarkRun(string foldername) {
    int VARNUM;
    string project_path=getCwd();
    string data_folder_name=foldername;//R"(test\sat)";
    string file_name=project_path+"\\"+data_folder_name;
    vector<char*> allPath=getFilesList(file_name.c_str());
    for (vector<char*>::iterator iter = allPath.begin(); iter != allPath.end(); iter++)
    {   
        string file_name=*iter;
        file_name=*iter;
        cout << file_name<<" is working"<< endl;
        HeadNode* LIST = CreateClause(VARNUM,file_name);
        consequence result[VARNUM];//记录最终的真假值
        clock_t StartTime,EndTime;
        cout<<"Result: \n";
        StartTime = clock();
        int value = DPLL(LIST,result,VARNUM);
        EndTime = clock();
        if(value)
            cout<<"S "<<TRUE<<endl;
        else
            cout<<"S "<<NoAnwser<<endl;
        show(result,VARNUM);//输出解
        cout<<"T "<<(double)(EndTime-StartTime)/CLOCKS_PER_SEC*1000.0<<" ms\n";
    }
}