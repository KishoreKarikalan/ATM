    #include<iostream>
    #include <ctime>
    #include <stack>
    #include <cstring>
    #include <fstream>

    using namespace std;

    namespace udt
    {
        struct Date
        {
            int d;//Date
            int m;//Month
            int y;//Year

            void operator() (char s[10])
            {
                m=int(s[0]-'0')*10+int(s[1]-'0');
                y=int(s[3]-'0')*10+int(s[4]-'0');
            }
            void operator() ()
            {
                char month[10];
                time_t now = time(0);
                char* date_time = ctime(&now);
                y=(date_time[22]-'0')*10+(date_time[23]-'0');//Converts string to int.
                month[0]=date_time[4];
                month[1]=date_time[5];
                month[2]=date_time[6];
                switch (month[0])
                {
                case 'F':
                    m=2;
                    break;
                case 'M':
                    if(month[2]=='r') m=3;
                    else m=5;
                    break;
                case 'A':
                    if(month[1]=='p') m=4;
                    else m=8;
                    break;
                case 'J':
                    if(month[1]=='a') m=1;
                    else if(month[2]=='n') m=6;
                    else m=7;
                    break;
                case 'S':
                    m=9;
                    break;
                case 'O':
                    m=10;
                    break;
                case 'N':
                    m=11;
                    break;
                case 'D':
                    m=12;
                    break;
                default:
                    break;
                }
                d = (date_time[9]-'0')*10+(date_time[10]-'0');
            }
            bool check()
            {
                struct Date current;
                current();
                if(current.y>y || (current.m>m && current.y==y)) return false;
                return true;
            }
            friend ostream& operator<< (ostream& os,Date& d)
            {
                os<<d.d<<'/'<<d.m<<'/'<<d.y;
                return os;
            }
        };

        struct Transaction
        {
            Date date;
            int amt;
            float balance;
            bool res;
            Transaction* next=NULL;

            void operator() (int amt_,int balance_,bool res_=true)
            {
                amt=amt_; balance=balance_;res=res_;
                date();//functor call.
            }
            void print()
            {
                cout<<date<<amt<<balance<<(res==0)?"Failed":"Sucess";
                cout<<endl;
            }
        };

        Transaction* head=NULL;

        class Account
        {
        protected:
            char name[10];
            float balance;
        public:
            char acc_no[10];
            void getData()
            {
                cout<<"Enter name,account number,balance : \n";
                cin>>name>>acc_no>>balance;
            }

            int viewBal()
            {
                return balance;
            }
        };
         bool isFull(int top)
        {
            if(top>99) return true;
            return false;
        }
        bool isEmpty(int top)
        {
            if(top<=-1) return true;
            return false;
        }
        class Card : public Account
        {
            char card_no[10];
            Date validUpto;
            int PIN;
            Transaction history[100];
            
        public:
            int top=-1;
            void getData()
            {
                Account::getData();
                char temp[10];
                cout<<"Enter card Number,Expiration date,PIN :\n";
                cin>>card_no>>temp>>PIN;
                validUpto(temp);
            }
            string holderName()
            {
                return name;
            }
            string setPin()
            {
                char acc[10];
                int pin1,pin2;
                cout<<"Enter acc_no :\n";
                cin>>acc;
                cout<<"Enter New PIN :\n";
                cin>>pin1;
                cout<<"ReEnter New PIN :\n";
                cin>>pin2;
                if(strcmp(acc,acc_no)==0 && pin1==pin2)
                {
                    PIN=pin1;
                    return "PIN set sucessfully";
                }
                else
                {
                    return "PIN not SET";
                }
            }
            bool checkValidity()
            {
                return validUpto.check();
            }
            bool compCard(char cardNumber[10])
            {
                if(strcmp(card_no,cardNumber)==0) return true;
                return false;
            }

            void addToList(Transaction*);
            void pushToStack(Transaction&);

            void withdraw(int amt)
            {
                int pin1;
                struct Transaction *curr=new Transaction;

                if(amt<balance)
                {
                    cout<<"Enter PIN :\n";
                    cin>>pin1;
                    if(pin1==PIN)
                    {
                        balance-=amt;
                        (*curr)(amt,balance);
                        cout<<"Transaction Completed.\n ";
                    }
                    else
                    {
                        cout<<"Transaction Not Completed.\n";
                        (*curr)(amt,balance,false);
                    }

                }
                else
                {
                    cout<<"InSufficient Balance.\n";
                    (*curr)(amt,balance,false);
                }
                pushToStack(*curr);
                addToList(curr);
            }
            void viewHistory()
            {
                int temp=top;
                if(isEmpty(temp))
                    cout<<"\nNo Transaction History Available\n";
                else
                    cout<<"\nDate\t\tAmount\tBalance Left\tTransaction Status\n";
                while(!isEmpty(temp))
                {
                    cout<<history[temp].date<<"\t"<<history[temp].amt<<"\t"<<history[temp].balance<<"\t\t"<<[](bool a){return a==1?"Success": "Failed";}(history[temp].res)<<endl;
                    temp--;
                }
            }
        };
        void Card::pushToStack(Transaction &val)
        {
            if(!isFull(top))
                history[++top]=val;
        }

        void Card::addToList(Transaction* curr)
        {
            Transaction* temp=head;
            if(temp==NULL)
            {
                temp=curr;
                temp->next=NULL;
            }
            while(temp->next!=NULL)
            {
                temp=temp->next;
            }
            temp->next=curr;
            temp->next->next=NULL;
        }

        
    }
