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
        clock_t StartTime,EndTime;
        cout<<"Result: \n";
        StartTime = clock();

        // struct DPLL_p *input_parameters;
        // input_parameters->l=LIST;
        // input_parameters->r=result;
        // input_parameters->v=VARNUM;
        // HANDLE hThread3 = CreateThread(NULL,0,DPLLStuf,input_parameters,0,NULL);     
        // // // HANDLE hThread4= CreateThread(NULL,0,Timer,NULL,0,NULL);
        // if(WaitForSingleObject(hThread3,2*1000)==WAIT_OBJECT_0) {}
        // else continue;
        // CloseHandle(hThread3);


        // if(WaitForSingleObject(hThread4, 20*1000)==WAIT_TIMEOUT){
        //     if(WaitForSingleObject(hThread3, INFINITE)!=WAIT_OBJECT_0)
        //         CloseHandle(hThread3);
        //         CloseHandle(hThread4);
        // }
        int value = DPLL(LIST,result,VARNUM);
        EndTime = clock();
        if(value)
            cout<<"S "<<TRUE<<endl;
        else
            cout<<"S "<<NoAnwser<<endl;
        show(result,VARNUM);//输出解
        cout<<"T "<<(double)(EndTime-StartTime)/CLOCKS_PER_SEC*1000.0<<" ms\n";

        delete LIST;
        // delete result;
    }
    return 0;
}

int BenchmarkRun(char *foldername) {  

    HANDLE hThread2 = CreateThread(
        NULL,    // Thread attributes
        0,       // Stack size (0 = use default)
        DoStuff2, // Thread start address
        foldername,    // Parameter to pass to the thread
        0,       // Creation flags
        NULL);   // Thread id

    if(WaitForSingleObject(hThread2,20*1000)==WAIT_TIMEOUT) CloseHandle(hThread2);;


    return 0;
}