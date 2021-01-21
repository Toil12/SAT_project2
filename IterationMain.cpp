#include "DPLL.cpp"
#include "FileOperations.cpp"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// void BenchmarkRun(){
//     int VARNUM;
//     string filename = R"(G:\Workplace\c_documents\SAT_project2\sat\aim-100-1_6-yes1-1.cnf)";;
//     HeadNode* LIST = CreateClause(VARNUM,filename);
//     consequence result[VARNUM];//记录最终的真假值
//     clock_t StartTime,EndTime; //记录程序运行的时间
//     cout<<"Result: \n";
//     StartTime = clock();
//     int value = DPLL(LIST,result,VARNUM);
//     EndTime = clock();
//     if(value)
//         cout<<"S "<<TRUE<<endl;
//     else
//         cout<<"S "<<NoAnwser<<endl;
//     show(result,VARNUM);//输出解
//     cout<<"T "<<(double)(EndTime-StartTime)/CLOCKS_PER_SEC*1000.0<<" ms\n";


//     filename = R"(G:\Workplace\c_documents\SAT_project2\sat\aim-100-1_6-yes1-2.cnf)";;
//     LIST = CreateClause(VARNUM,filename);
//     consequence result2[VARNUM];//记录最终的真假值
//     cout<<"Result: \n";
//     StartTime = clock();
//     int value2 = DPLL(LIST,result2,VARNUM);
//     EndTime = clock();
//     if(value2)
//         cout<<"S "<<TRUE<<endl;
//     else
//         cout<<"S "<<NoAnwser<<endl;
//     show(result2,VARNUM);//输出解
//     cout<<"T "<<(double)(EndTime-StartTime)/CLOCKS_PER_SEC*1000.0<<" ms\n";

//     filename = R"(G:\Workplace\c_documents\SAT_project2\sat\aim-100-1_6-yes1-3.cnf)";;
//     LIST = CreateClause(VARNUM,filename);
//     consequence result3[VARNUM];//记录最终的真假值
//     cout<<"Result: \n";
//     StartTime = clock();
//     int value3 = DPLL(LIST,result3,VARNUM);
//     EndTime = clock();
//     if(value3)
//         cout<<"S "<<TRUE<<endl;
//     else
//         cout<<"S "<<NoAnwser<<endl;
//     show(result3,VARNUM);//输出解
//     cout<<"T "<<(double)(EndTime-StartTime)/CLOCKS_PER_SEC*1000.0<<" ms\n";
// }

struct DPLL_p{
    HeadNode *l{};
    consequence *r;
    int v;  
    int ret_value=-1;
}DPLL_p;

DWORD WINAPI Timer(LPVOID lpParameter)
{
  
    while (true)
    {
        continue;
    }   
}

DWORD WINAPI DPLLStuf(LPVOID lpParameter){
    struct DPLL_p *p=(struct DPLL_p*)lpParameter;
    cout<<p->l<<p->r<<p->v<<endl;
    p->ret_value=DPLL(p->l,p->r,p->v);
    cout<<p->ret_value<<endl;
    return 0;
}

DWORD WINAPI DoStuff2(LPVOID lpParameter)
{   
    int pass_number=0;
    char* tempname = (char*)lpParameter;
    string foldername=tempname;
    int VARNUM;
    string project_path=getCwd();
    string data_folder_name=foldername;//R"(test\sat)";
    string file_name=project_path+"\\"+data_folder_name;
    vector<char*> allPath=getFilesList(file_name.c_str());
    for (vector<char*>::iterator iter = allPath.begin(); iter != allPath.end(); iter++){   
        string file_name=*iter;
        cout << file_name<<" is working"<< endl;
        HeadNode* LIST = CreateClause(VARNUM,file_name);
        consequence result[VARNUM];//记录最终的真假值
        LIST=PureLiteralElimination(LIST,VARNUM,result);
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
        pass_number=1+pass_number;
        delete LIST;
        // delete result;
    }
    cout<<"pass numbers:"<<pass_number<<endl;
    return 0;
}

int BenchmarkRun(char *foldername,int minute) {  

    HANDLE hThread2 = CreateThread(
        NULL,    // Thread attributes
        0,       // Stack size (0 = use default)
        DoStuff2, // Thread start address
        foldername,    // Parameter to pass to the thread
        0,       // Creation flags
        NULL);   // Thread id

    if(WaitForSingleObject(hThread2,minute*1000)==WAIT_TIMEOUT) CloseHandle(hThread2);;


    return 0;
}