#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cmath>
#include <Windows.h>
#include "FileOperations.cpp"
using namespace std;

typedef struct DataNode {
    int data = 0;  //记录该数据节点的值
    DataNode *next{};  //指向下一个数据节点
}DataNode;

typedef struct HeadNode {
    int Num = 0;  //记录该行子句的数据个数
    DataNode *right{}; //指向到子句第一个数据节点
    HeadNode *down{}; //指向到下一行子句
}HeadNode;


struct times{
    int data = 0;
    int count = 0;
    int Positive = 0;
    int Negative = 0;
    int MOM_num = 0;
    float JW = 0.0;
    float JW_pos = 0.0;
    float JW_neg = 0.0;
    int Boehm = 0;
};

bool comp(const times &a,const times &b) {
    return a.count > b.count;
}

bool comp_MOM(const times &a,const times &b) {
    return a.MOM_num > b.MOM_num;
}

bool comp_JW(const times &a,const times &b) {
    return a.JW > b.JW;
}

bool comp_Boehm(const times &a,const times &b) {
    return a.Boehm > b.Boehm;
}

int DLIS_choose (HeadNode* LIST,int VARNUM) {
    HeadNode* PHead = LIST;
    times record[VARNUM];
    for (; PHead != nullptr; PHead = PHead->down)//装入数组
    {
        DataNode* Pdata = PHead->right;
        for (; Pdata != nullptr; Pdata = Pdata->next)
        {
            record[abs(Pdata->data)-1].data = abs(Pdata->data); //记录每个数值
            record[abs(Pdata->data)-1].count++; //记录每个数值出现的次数
        }
    }
    //排序
    sort(record,record+VARNUM,comp);//最高的在最前面
    //选取变元
    return record[0].data;  //选取出现次数最多的variable
}


int DLCS_choose (HeadNode* LIST,int VARNUM) {
    HeadNode* PHead = LIST;
    times record[VARNUM];
    for (; PHead != nullptr; PHead = PHead->down)//装入数组
    {
        DataNode* Pdata = PHead->right;
        for (; Pdata != nullptr; Pdata = Pdata->next)
        {
            record[abs(Pdata->data)-1].data = abs(Pdata->data); //记录每个数值
            record[abs(Pdata->data)-1].count++; //记录每个数值出现的次数
            if(Pdata->data > 0) record[abs(Pdata->data)-1].Positive++;
            else record[abs(Pdata->data)-1].Negative++;
        }
    }
    //排序
    sort(record,record+VARNUM,comp);//最高的在最前面
    //选取变元
    if(record->Positive > record->Negative) return record[0].data;  //选取出现次数最多的variable
    else return 0-record[0].data;
}

int smallest_clauses_size(HeadNode* LIST){
     HeadNode* PHead = LIST;
     int width;
     width = PHead->Num;
     for (; PHead != nullptr; PHead = PHead->down){
        if (width > PHead->Num){
          width = PHead->Num;
        }
     }
     return width;
}

int MOM_choose (HeadNode* LIST,int VARNUM, int k=2) {
    HeadNode* PHead = LIST;
    times record[VARNUM];
    int smallest_width;
    smallest_width = smallest_clauses_size(LIST);
    for (; PHead != nullptr; PHead = PHead->down)//装入数组
    {   
        if (PHead->Num == smallest_width ){
          DataNode* Pdata = PHead->right;
          for (; Pdata != nullptr; Pdata = Pdata->next)
          {
              record[abs(Pdata->data)-1].data = abs(Pdata->data); //记录每个数值
              record[abs(Pdata->data)-1].count++; //记录每个数值出现的次数
              if(Pdata->data > 0) record[abs(Pdata->data)-1].Positive++;
              else record[abs(Pdata->data)-1].Negative++;
          }
        }      
    }
    for(int i=0; i<VARNUM; i++){
      record[i].MOM_num =(record[i].Positive)+ (record[i].Negative)*pow(2,k)+record[i].Positive*record[i].Negative;
    }
    //排序
    sort(record,record+VARNUM,comp_MOM);//最高的在最前面
    //选取变元
    return record[0].data;  //选取出现次数最多的variable
}

int Jeroslaw_Wang_choose (HeadNode* LIST,int VARNUM) {
    HeadNode* PHead = LIST;
    times record[VARNUM];
    for (; PHead != nullptr; PHead = PHead->down)//装入数组
    {
        DataNode* Pdata = PHead->right;
        for (; Pdata != nullptr; Pdata = Pdata->next)
        {
            record[abs(Pdata->data)-1].data = abs(Pdata->data); //记录每个数值
            record[abs(Pdata->data)-1].JW += float(pow(2, -PHead->Num));
        }
    }
    //排序
    sort(record,record+VARNUM,comp_JW);//最高的在最前面
    //选取变元
    return record[0].data;  //选取出现次数最多的variable
}

int Jeroslaw_Wang_choose_literal (HeadNode* LIST,int VARNUM) {
    HeadNode* PHead = LIST;
    times record[VARNUM];
    for (; PHead != nullptr; PHead = PHead->down)//装入数组
    {
        DataNode* Pdata = PHead->right;
        for (; Pdata != nullptr; Pdata = Pdata->next)
        {
            record[abs(Pdata->data)-1].data = abs(Pdata->data); //记录每个数值
            if(Pdata->data > 0) {
              record[abs(Pdata->data)-1].JW_pos += float(pow(2, -PHead->Num));
            }
            else {
              record[abs(Pdata->data)-1].JW_neg += float(pow(2, -PHead->Num));
            }
        }
    }
    for(int i=0; i<VARNUM; i++){
    record[i].JW =(record[i].JW_pos)+ (record[i].JW_pos);
  }
    //排序
    sort(record,record+VARNUM,comp_JW);//最高的在最前面
    //选取变元
    return record[0].data;  //选取出现次数最多的variable
}

int Boehm_choose (HeadNode* LIST,int VARNUM, int Alpha=1, int Belta=2) {
    HeadNode* PHead = LIST;
    times record[VARNUM];
    for (; PHead != nullptr; PHead = PHead->down)//装入数组
    {
        DataNode* Pdata = PHead->right;
        for (; Pdata != nullptr; Pdata = Pdata->next)
        {
            record[abs(Pdata->data)-1].data = abs(Pdata->data); //记录每个数值
            record[abs(Pdata->data)-1].count++; //记录每个数值出现的次数
            if(Pdata->data > 0) record[abs(Pdata->data)-1].Positive++;
            else record[abs(Pdata->data)-1].Negative++;
        }
    }
    //排序
     for(int i; i<VARNUM; i++){
        if(record[i].Positive >= record[i].Negative){
           record[i].Boehm = Alpha*record[i].Positive + Belta*record[i].Negative;
          }
        else {
          record[i].Boehm = Alpha*record[i].Negative + Belta*record[i].Positive;
          }
    }
    
    sort(record,record+VARNUM,comp_Boehm);//最高的在最前面
    //选取变元
    return record[0].data;  //选取H最大的variable
}


HeadNode* CreateClause(int &VARNUM,string name) {
    //FileOpen
    string HFilePath =name;
    string path = HFilePath;
    ifstream fis(path);
    if(!fis){
        cout<<"File can not open.";
        exit(1);
    }
    char ch;
    char buf[500];
    fis>>ch;
    while (ch != 'p') {
        fis.getline(buf,500);
        fis>>ch;
    }
    string cnf;
    int VarNum,ClauseNum;
    fis>>cnf>>VarNum>>ClauseNum;
    fis.get();

    /*and write into 2 dimensional link lists*/
    //loading the initial node
    HeadNode* HEAD = new HeadNode;
    HeadNode* headRear = HEAD;
    HeadNode* END = new HeadNode;
    for (int i = 0 ; i < ClauseNum ; i++) {
        //load on the data lists
        int temp;
        fis>>temp;
        //load the first data node
        DataNode* front = new DataNode;
        front->data = temp;
        headRear->right = front;
        headRear->Num++;
        //the >2th data loading
        fis >> temp;
        while (temp != 0) {
            DataNode* rear = new DataNode;
            front->next = rear;
            rear->data = temp;
            front = front->next;
            headRear->Num++;
            fis >> temp;
        }
        front->next = nullptr;
        fis.get();//换行符
        HeadNode *tp = new HeadNode;
        headRear->down = tp;
        END = headRear;
        headRear = headRear->down;
    }
    END->down = nullptr;
    /*
    //output link lists
    HeadNode* Phead = HEAD;
    DataNode* front;
    cout<<"CnfParser\n";
    while(Phead != nullptr) {
        front = Phead->right;
        while(front != nullptr) {
            cout<<front->data<<" ";
            front = front->next;
        }
        cout<<endl;
        Phead = Phead->down;
    }
     */
    VARNUM = VarNum;
    cout<<"finish"<<endl;
    return HEAD;
}





#define TRUE 1
#define FALSE 0
#define NoAnwser -1
typedef int status;
struct consequence {
    int value = -1;//the value of variable
    bool puretag=false;//when true,mean this is pure literal
};


status DPLL(HeadNode *LIST,consequence *result,int);
HeadNode* IsSingleClause(HeadNode*);
status IsEmptyClause(HeadNode*);
HeadNode* ADDSingleClause(HeadNode*,int);
HeadNode* Duplication(HeadNode*);

HeadNode* PureLiteralElimination(HeadNode*, int,consequence*);
void DeleteHeadNode(HeadNode*,HeadNode*&);
void DeleteDataNode(int,HeadNode*&);
void show(struct consequence *,int);
int PureLiteralEliminationOneVar(HeadNode*,int);


status DPLL(HeadNode *LIST,consequence *result,int VARNUM) {
    //单子句规则
    HeadNode* Pfind = LIST;
    HeadNode* SingleClause = IsSingleClause(Pfind); //判断Pfind里是否存在单子句。遍历头节点，若任意一行的Num存在为1的情况，即证明存在单子句，并返回单子句的指针
    while (SingleClause != nullptr) {
        SingleClause->right->data > 0 ? result[abs(SingleClause->right->data)-1].value = TRUE : result[abs(SingleClause->right->data)-1].value = FALSE;
        int temp = SingleClause->right->data;
        DeleteHeadNode(SingleClause,LIST);//删除单子句这一行
        DeleteDataNode(temp,LIST);//删除相等或相反数的节点
        if(!LIST) return TRUE; //List为空，所以满足
        else if(IsEmptyClause(LIST)) return FALSE; //存在空子句，所以不满足
        Pfind = LIST;
        SingleClause = IsSingleClause(Pfind);;//回到头节点继续进行检测是否有单子句
    }
    //分裂策略
    int Var =Jeroslaw_Wang_choose(LIST,VARNUM);//选取变元
    HeadNode* replica = Duplication(LIST);//存放LIST的副本replica
    HeadNode *temp1 = ADDSingleClause(LIST,Var);//装载变元成为单子句，并将此单子句放在首位
    if(DPLL(temp1,result,VARNUM)) return TRUE;
    else {
        HeadNode *temp2 = ADDSingleClause(replica,-Var);
        return DPLL(temp2,result,VARNUM);
    }
}

status IsEmptyClause(HeadNode* LIST) {
    HeadNode* PHead = LIST;
    while (PHead != nullptr) {
        if(PHead->Num == 0)
            return TRUE;
        PHead = PHead->down;
    }
    return FALSE; //没有空子句
}

HeadNode* IsSingleClause(HeadNode* Pfind) {
    while (Pfind != nullptr ) {
        if((Pfind->Num == 1))
            return Pfind;
        Pfind = Pfind->down;
    }
    return nullptr;
}

HeadNode* Duplication(HeadNode* LIST) { //此处检验传参正常，开始检查复制有无逻辑错误
    HeadNode* SrcHead = LIST;

    HeadNode* ReHead = new HeadNode;//新链表的头节点
    ReHead->Num = SrcHead->Num;//复制第一个头节点
    HeadNode* Phead = ReHead;//Phead创建头节点
    DataNode *ReData = new DataNode;//新链表的数据节点
    DataNode *FirstSrcData = SrcHead->right;//用于创建第一行的第一个数据节点
    ReData->data = FirstSrcData->data;//新链表的第一个数据节点的数值
    Phead->right = ReData;
    for (FirstSrcData = FirstSrcData->next;FirstSrcData != nullptr; FirstSrcData = FirstSrcData->next) {//第一行链表复制完成
        DataNode *NewDataNode = new DataNode;
        NewDataNode->data = FirstSrcData->data;
        ReData->next = NewDataNode;
        ReData = ReData->next;
    }
    //此下行数节点的复制 >=2th
    for(SrcHead = SrcHead->down; SrcHead != nullptr ; SrcHead = SrcHead->down) {
        HeadNode* NewHead = new HeadNode;
        DataNode* NewData = new DataNode;
        NewHead->Num = SrcHead->Num;
        Phead->down = NewHead;
        Phead = Phead->down;
        DataNode* SrcData = SrcHead->right;
        NewData->data = SrcData->data;
        Phead->right = NewData;//第一个数据节点
        for (SrcData = SrcData->next;SrcData != nullptr; SrcData = SrcData->next) {//此行剩下的数据节点
            DataNode* node = new DataNode;
            node->data = SrcData->data;
            NewData->next = node;
            NewData = NewData->next;
        }
        NewData->next = nullptr;
    }
    Phead->down = nullptr;

    return ReHead;
}

HeadNode* ADDSingleClause(HeadNode* LIST,int Var) { //所加的单子句位于链表的头
    HeadNode* AddHead = new HeadNode;
    DataNode* AddData = new DataNode;
    AddData->data = Var;
    AddData->next = nullptr;
    AddHead->right = AddData;
    AddHead->Num = 1;
    AddHead->down = LIST;
    LIST = AddHead;
    return LIST;
}

void DeleteDataNode(int temp,HeadNode *&LIST) {
    for (HeadNode* pHeadNode = LIST; pHeadNode != nullptr ; pHeadNode = pHeadNode->down)
        for (DataNode *rear = pHeadNode->right; rear != nullptr ; rear = rear->next) {
            if (rear->data == temp)  //相等删除整行
                DeleteHeadNode(pHeadNode,LIST);
            else if (abs(rear->data) == abs(temp)) { //仅仅是绝对值相等铲除该节点
                if(rear == pHeadNode->right) { //头节点删除
                    pHeadNode->right = rear->next;
                    pHeadNode->Num--;
                }
                else{ //删除普通节点
                    for (DataNode* front = pHeadNode->right; front != nullptr; front= front->next)
                        if(front->next == rear) {
                            front->next = rear->next;
                            pHeadNode->Num--;
                        }
                }
            }
        }
}

void DeleteHeadNode(HeadNode *Clause,HeadNode *&LIST) {
    if (!Clause) return;
    if(Clause == LIST)
        LIST = Clause->down;
    else {
        for (HeadNode *front = LIST; front != nullptr; front = front->down)
            if (front->down == Clause) {
                front->down = Clause->down;
            }
    }
}

int PureLiteralEliminationOneVar(HeadNode* LIST,int checkVar){
    bool find_tag=false;
    bool ptag=true;
    //check from head
    for(HeadNode* pHeadNode=LIST; pHeadNode != nullptr ; pHeadNode = pHeadNode->down){
        //if unit clause, break
        if (pHeadNode->Num==1){
            if((abs(pHeadNode->right->data)==checkVar)&&(!find_tag)) {checkVar=pHeadNode->right->data;continue;}
            else{
                if((abs(pHeadNode->right->data)==checkVar)&&(find_tag)&&(pHeadNode->right->data!=checkVar)) break;
                else continue;
            }
        }    
        else{
            //in normal clause
            for(DataNode *rear = pHeadNode->right; rear != nullptr ; rear = rear->next){
                if(abs(rear->data)==checkVar){
                    //first touch,assignment
                     if(!find_tag){find_tag=true;checkVar=rear->data;continue;}
                    //not first touch and with different sign, not pure literal
                     else if (rear->data!=checkVar){ptag=false;break;}    
                    }
                else continue;                  
                }
            } 
        if(ptag) continue;
        else break;             
        }
    return ptag,checkVar;
}

HeadNode* PureLiteralElimination(HeadNode* LIST, int Varnumber,consequence *result){
   for(int i=1;i<=Varnumber;i++){
       int temp=i;
       bool pure_tag=false;
       pure_tag,temp =PureLiteralEliminationOneVar(LIST,temp);
       if(!pure_tag) continue;
       else{
            for (HeadNode* pHeadNode = LIST; pHeadNode != nullptr ; pHeadNode = pHeadNode->down)
                for (DataNode *rear = pHeadNode->right; rear != nullptr ; rear = rear->next) {      
                    for (DataNode* front = pHeadNode->right; front != nullptr; front= front->next)
                        if(front->next == rear) {
                            front->next = rear->next;
                            pHeadNode->Num--;
                        }
                    }
            }
        temp > 0 ? result[abs(temp)-1].value = TRUE : result[abs(temp)-1].value = FALSE;
        result[abs(temp)-1].puretag=true;
    }
    return LIST;
}


void show(struct consequence *result,int VarNum) {
    cout<<"V ";
    for(int i = 0; i < VarNum; i++) {
        if (result[i].value == TRUE)
            cout<<i+1<<" ";
        else if(result[i].value == FALSE)
            cout<<-(i+1)<<" ";
        else
            cout<<(i+1)<<" ";//剩下一堆可true可false，就索性输出true
    }
    cout<<endl;
}

int main() {
    string foldername=R"(sat)";
    int VARNUM;
    string project_path=getCwd();
    string data_folder_name=foldername;//R"(test\sat)";
    string file_name=project_path+"\\"+data_folder_name;
    vector<char*> allPath=getFilesList(file_name.c_str());
    for (vector<char*>::iterator iter = allPath.begin(); iter != allPath.end(); iter++){   
        int VARNUM;
        string filename =*iter;;
        HeadNode* LIST = CreateClause(VARNUM,filename);
        consequence result[VARNUM];//记录最终的真假值
        clock_t StartTime,EndTime; //记录程序运行的时间
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

// struct DPLL_p{
//     HeadNode *l{};
//     consequence *r;
//     int v;  
//     int ret_value=-1;
// }DPLL_p;

// DWORD WINAPI Timer(LPVOID lpParameter)
// {
  
//     while (true)
//     {
//         continue;
//     }   
// }

// DWORD WINAPI DPLLStuf(LPVOID lpParameter){
//     struct DPLL_p *p=(struct DPLL_p*)lpParameter;
//     cout<<p->l<<p->r<<p->v<<endl;
//     p->ret_value=DPLL(p->l,p->r,p->v);
//     cout<<p->ret_value<<endl;
//     return 0;
// }

// DWORD WINAPI DoStuff2(LPVOID lpParameter)
// {   
//     char* tempname = (char*)lpParameter;
//     string foldername=tempname;
//     int VARNUM;
//     string project_path=getCwd();
//     string data_folder_name=foldername;//R"(test\sat)";
//     string file_name=project_path+"\\"+data_folder_name;
//     vector<char*> allPath=getFilesList(file_name.c_str());
//     for (vector<char*>::iterator iter = allPath.begin(); iter != allPath.end(); iter++){   
//         string file_name=*iter;
//         cout << file_name<<" is working"<< endl;
//         HeadNode* LIST = CreateClause(VARNUM,file_name);
//         consequence result[VARNUM];//记录最终的真假值
//         LIST=PureLiteralElimination(LIST,VARNUM,result);
//         clock_t StartTime,EndTime;
//         cout<<"Result: \n";
//         StartTime = clock();

//         int value = DPLL(LIST,result,VARNUM);
//         EndTime = clock();
//         if(value)
//             cout<<"S "<<TRUE<<endl;
//         else
//             cout<<"S "<<NoAnwser<<endl;
//         show(result,VARNUM);//输出解
//         cout<<"T "<<(double)(EndTime-StartTime)/CLOCKS_PER_SEC*1000.0<<" ms\n";

//         delete LIST;
//         // delete result;
//     }
//     return 0;
// }


// int main() {  
//     char* foldername = (char*)R"(sat)";
//     HANDLE hThread2 = CreateThread(
//         NULL,    // Thread attributes
//         0,       // Stack size (0 = use default)
//         DoStuff2, // Thread start address
//         foldername,    // Parameter to pass to the thread
//         0,       // Creation flags
//         NULL);   // Thread id

//     if(WaitForSingleObject(hThread2,60*1000)==WAIT_TIMEOUT) CloseHandle(hThread2);;


//     return 0;
// }