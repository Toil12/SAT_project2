#include <iostream>
#include <direct.h>
#include <io.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

template <class T>
int getArrayLen(T& array){
    return (sizeof(array) / sizeof(array[0]));
}

string getCwd(){
    char buff[1000];
    _getcwd(buff, 1000);
    string root_path=buff;
    return root_path;
}

vector<char*> getFilesList(const char * dir)
{
	vector<char*> allPath;
	char dirNew[200];
	strcpy(dirNew, dir);
	strcat(dirNew, "\\*.*");    // first search
	intptr_t handle;
	_finddata_t findData;
	handle = _findfirst(dirNew, &findData);
	if (handle == -1) {// check success
		cout << "can not found the file ... " << endl;
		return allPath;
	}      
	do
	{
		if (findData.attrib & _A_SUBDIR)
		{
			//若该子目录为"."或".."，则进行下一次循环，否则输出子目录名，并进入下一次搜索
			if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
				continue;
			//cout << findData.name << "\t<dir>\n";
			// 在目录后面加上"\\"和搜索到的目录名进行下一次搜索
			strcpy(dirNew, dir);
			strcat(dirNew, "\\");
			strcat(dirNew, findData.name);
			vector<char*> tempPath=getFilesList(dirNew);
			allPath.insert(allPath.end(), tempPath.begin(), tempPath.end());
		}
		else //不是子目录，即是文件，则输出文件名和文件的大小
		{
			char *filePath=new char[200];
            strcpy(filePath, dir);
			strcat(filePath, "\\");
			strcat(filePath, findData.name);
			
			//cout << filePath << "\t" << findData.size << " bytes.\n";
            char* pCNF = strstr(filePath,".cnf");
            if (pCNF==NULL) continue;
            else allPath.push_back(filePath);
		}
	} while (_findnext(handle, &findData) == 0);
	_findclose(handle);    // 关闭搜索句柄
	return allPath;
}

void file_run(string folder_name)
{
    string project_path=getCwd();
    string data_folder_name=folder_name;
    string file_name=project_path+"\\"+data_folder_name;
    vector<char*> allPath=getFilesList(file_name.c_str());
    for (vector<char*>::iterator iter = allPath.begin(); iter != allPath.end(); iter++)
    {   
        string pb;
        pb=*iter;
        cout << pb << endl;
    }
}