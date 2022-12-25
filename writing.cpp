#include "udt.h"
#include <string.h>
#include <fstream>

using namespace std;
int main()
{
    int ch;
    udt::Card a;
    ofstream filewrite("acc_details.txt",ios::binary|ios::app);
    ifstream fileread("transactions.txt",ios::binary);
    do
    {
        cout<<"1.Write Account Details.\n0.Exit\n";
        cin>>ch;
        switch(ch)
        {
            case 1:
                
                a.getData();
                filewrite.write((char*)&a,sizeof(a));
                break;
        }
    }while(ch!=0);
    filewrite.close();
}