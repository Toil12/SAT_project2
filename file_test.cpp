// #include <Windows.h>
// #include <iostream>
// #include <fstream>
// #include <ctime>
// #include <vector>
// #include <algorithm>
// #include <cmath>

// using namespace std;


// DWORD WINAPI DoStuff(LPVOID lpParameter)
// {
//     // The new thread will start here
//     clock_t start=clock();
//     clock_t current=clock();
//     char *ou=(char*)lpParameter;
//     while (true)
//     {
//     //    Sleep(1);
//        cout<<ou<<endl;
//     }    
//     return 0;
// }

// DWORD WINAPI DoStuff1(LPVOID lpParameter)
// {
//     // The new thread will start here
//     cout<<"kk"<<endl;
//     return 0;
// }

// int main()
// {   
// ;
//     char* send = (char*)"abc"; 
//     // Create a new thread which will start at the DoStuff function
//     HANDLE hThread1 = CreateThread(
//         NULL,    // Thread attributes
//         0,       // Stack size (0 = use default)
//         DoStuff, // Thread start address
//         send,    // Parameter to pass to the thread
//         0,       // Creation flags
//         NULL);   // Thread id
//     HANDLE hThread2 = CreateThread(
//         NULL,    // Thread attributes
//         0,       // Stack size (0 = use default)
//         DoStuff1, // Thread start address
//         NULL,    // Parameter to pass to the thread
//         0,       // Creation flags
//         NULL);   // Thread id
//     if ((hThread1 == NULL)||(hThread2==NULL))
//     {
//         // Thread creation failed.
//         // More details can be retrieved by calling GetLastError()
//         return 1;
//     }

//     // Wait for thread to finish execution
//     clock_t start=clock();
//     WaitForSingleObject(hThread1, 1);
//     clock_t end=clock();
//     cout<<(double)(start-end)/CLOCKS_PER_SEC*1000.0<<" ms";
//     // WaitForSingleObject(hThread2, INFINITE);

//     // Thread handle must be closed when no longer needed
//     CloseHandle(hThread1);
//     // CloseHandle(hThread2);

//     return 0;
// }