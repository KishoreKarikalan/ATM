/*                              ATM
    Data Structures Used :
        ->Stack (Transaction History)
        ->Array (To Load Card Details from File)
        ->Linked List (Track of All Transactions)
    User Defined Datatypes :
        ->Date          --struct    (Store date for validity & history)
        ->Transaction   --struct    (Stores Transaction Details)
        ->Account       --class     (Account details)
        ->Card:Account  --class     (Card Binds all the Datatypes)
    concept Used :
        ->Functors  -- Function Objects.
        ->Lambda Functions.
        ->Function pointers.
        ->Dynamic memory allocation.
        ->File operations.
        ->Inheritance.
    Concepts Learned :
        ->New way of Menu Driven Programming.
        ->UnNamed Functions OR Anonymous Function.
        ->Writting a Header File.
        ->Wide use and importance of namespace.
        ->Wide scope of Global variables.
        ->System functions are OS dependent.
*/

#include "udt.h" 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#define MAX 100
using namespace udt;        //User Defined Datatypes.
using namespace std;

Card arr[MAX];              //Load of All Card Details.
int count=0;
Card* ActiveCard=NULL;

//Declaration of functions used.
int menu();
bool load_data();       //Data from File is Loaded.
void getCard();         //User Inserts Card and Searched from acc details.
void checkBalance();    
void withDrawAmt();
void TransactionHistory(); 
void SetPin();
//function pointer.
void (*funcArr[])() ={checkBalance,withDrawAmt,TransactionHistory,SetPin,getCard};
//Main block.
int main()
{
    system("color CF");
    load_data();    //Data read from the File.
    getCard();      //Active card is searched and Set.
    char a;
    int ch;
    do
    {
        ch=menu();
        funcArr[ch-1]();    //menu.    
        cout<<endl<<endl;system("pause");
    }while(ch!=0);
}

bool load_data()
{
    ifstream file("acc_details.txt",ios::binary);
    file.read((char*)&arr[0],sizeof(arr[0])); count++;
    while(!file.eof())
    {
        file.read((char*)&arr[count],sizeof(arr[count])); count++;
    }
    file.close();
    return true;
}

void getCard()
{
    //Procedures for New Card.
    system("cls");
    ActiveCard = NULL;
    char card_number[10];
    cout<<"\n\n\n\t\t\tEnter Card Number\n\t\t\t";
    cin>>card_number;
    for(int i=0;i<count;i++)        //Linear Search.
    {
        if(arr[i].compCard(card_number))
        {
            ActiveCard = &arr[i];break;
        }
    }
    if(ActiveCard==NULL)
    {
        cout<<"Card not Found\n";system("pause");getCard();
    }
    else if(!ActiveCard->checkValidity())
    {
        cout<<"Your Card has been Expired\n";
        system("pause");getCard();ActiveCard=NULL;
    }
}

int menu()
{
    system("cls");
    cout<<"\t\t\tWelcome "<<ActiveCard->holderName()<<endl<<endl;
    int ch;
    cout<<"\n1.Check Balance\n2.Withdraw Amount\n3.Transaction History\n4.Set PIN\n5.Remove Your Card\n";
    cin>>ch;
    return ch;
}

void checkBalance()
{
    cout<<"\nRs."<<ActiveCard->viewBal();
}

void TransactionHistory()
{
    ActiveCard->viewHistory();
}

void SetPin()
{
    cout<<ActiveCard->setPin();
}

void withDrawAmt()
{
    int amount;
    cout<<"Enter Amount :\n";
    cin>>amount;
    ActiveCard->withdraw(amount);
}
