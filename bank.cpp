#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define INCLUDE_Intro_MODULE
using namespace std;


class Account{ //class for all the account related functions
	protected:
	string FirstName, LastName, Password , ConfirmPassword,Type;
	int AccountNumber;
	int DepositAmount1;
	static int Accounts;

public:
	void intro();					//Function to display the intro screen
	void main_menu();				//Function to display the main menu of the software
	void CreateAccount(); 	 		//Function to get information from user for the account
	void Show_info(int AccountNumber);	//Function to show information of a created account
	void ModifyAccount();		 		//Function to modify account
	void WithdrawAmount();		//function to withdraw amount from an existing account
	void DepositAmount();		//Function to deposit amount into an existing account
	void DeleteAccount();		//Function to delete an account
	void CurrentAmount();		//Function to check the current amount of an existing account
	void AllAccounts();			//Function to show information of all the accounts
	Account();                  //Constructer
	~Account();					//Destructer
		
};
class FileHandeling:public Account{		//class for all the file handeling 
	public:
	void Writer(int AccountNumber,string FirstName,string LastName,string Password,string Type,int DepositAmount1);//Writes data in a text file	
	void Modifier(int AccountNumber,string FirstName,string LastName,string Password,string Type,int DepositAmount1);//Modify a text file
	int AmountReading(int AccountNumber); // Read the amount from an account file
	void AmountUpdater(int finalamount,int AccountNumber); //update the amount of an account after deposit or withdraw
	void Record(int AccountNumber);//Write Account Numbers In A File

};
void FileHandeling::Record(int AccountNumber){
	AccountNumber;
    ostringstream str1; 
    str1 << AccountNumber; 
    string fname = str1.str();
	ofstream outfile;
	outfile.open("Record.txt", ios_base::app);
  	outfile<<fname;
  	outfile<<"\n";
}
void FileHandeling::AmountUpdater(int finalamount,int AccountNumber){
	string fname;
	string text;
	text=".txt";
	ostringstream str1;
    str1 << AccountNumber;
	fname=str1.str();
	string Address;
	Address=fname+text;
	ifstream MyFile(Address.c_str());
	string result = "";

    if(MyFile.is_open()) {
        MyFile.seekg(0,ios_base::end);      //Start at end of file
        char ch = ' ';                  
        while(ch != '\n'){
            MyFile.seekg(-2,std::ios_base::cur); // leaves the last line
            if((int)MyFile.tellg() <= 0){     
                MyFile.seekg(0);                 
                break;
            }
            MyFile.get(ch); 
        }

        getline(MyFile,result);  
        string strReplace = result;
        string sfinalamount;
        stringstream convert(sfinalamount);
        convert>>finalamount;
    string strNew = sfinalamount;
    ifstream filein(Address.c_str()); 
    ofstream fileout("temp.txt"); //Temporary file
    if(!filein || !fileout)
    {
        cout << "Error opening files!" << endl;
    }

    string strTemp;
    int skiper=0;    // variable to skip \n once
    while(filein >> strTemp)
    {
        if(strTemp == strReplace){
            strTemp = strNew;
        }
        if (skiper==2||skiper==5||skiper==8||skiper==10||skiper==12){
		
        strTemp += "\n";
    }
	        fileout << strTemp;
	        skiper=skiper+1;
}
fileout<<"\n";
fileout<<finalamount;
fileout.close();
filein.close();
MyFile.close();
remove(Address.c_str());
rename("temp.txt",Address.c_str());
}
}
int FileHandeling::AmountReading(int AccountNumber){
	string fname;
	string text;
	text=".txt";
	ostringstream str1;
    str1 << AccountNumber;
	fname=str1.str();
	string Address;
	Address=fname+text;
	ifstream MyFile(Address.c_str());
	string result = "";

    if(MyFile.is_open()) {
        MyFile.seekg(0,std::ios_base::end);      //Start at end of file
        char ch = ' ';                      
        while(ch != '\n'){
            MyFile.seekg(-2,std::ios_base::cur); //will NOT check the last character
            if((int)MyFile.tellg() <= 0){        //If passed the start of the file,
                MyFile.seekg(0);                 //this is the start of the line
                break;
            }
            MyFile.get(ch);                      //Check the next character
        }

        getline(MyFile,result);
        int amount;
        stringstream convert(result);
        convert>>amount;
        MyFile.close();
        return amount;
    }
	}


void Account::DepositAmount(){
	cout<<"Enter Account Number :"<<endl;
	cin>>AccountNumber;
FileHandeling F1;
int deposit;
int amount= F1.AmountReading(AccountNumber);
cout<<"Current Balance = "<<amount<<endl;
cout<<"Enter Amount You Want To Deposit: "<<endl;
cin>>deposit;
int finalamount;
	finalamount=amount+deposit;
	cout<<"Transaction Successful..."<<endl;
	cout<<"The Total Balance is "<<finalamount<<endl;
	cin.ignore();
	cin.get();
	main_menu();
F1.AmountUpdater(finalamount,AccountNumber);	
}
void Account::AllAccounts(){
	
ifstream MyFile("Record.txt");
if (MyFile.is_open()){
cout<<"All The Accounts Ever Regestered In This Bank Are :"<<endl;
char line;
while(!MyFile.eof())
{
MyFile.get (line);
cout<<line;
}
MyFile.close();

	cin.ignore();
	cin.get();
	main_menu();
}
else{
		cout<<"Cant Open File"<<endl;
	}
}
void Account::DeleteAccount(){
	cout<<"Enter Account Number To Delete Account:"<<endl;
	cin>>AccountNumber;
	string fname;
	string text;
	text=".txt";
	ostringstream str1;
    str1 << AccountNumber;
	fname=str1.str();
	string Address;
	Address=fname+text;
	remove(Address.c_str());
	cout<<"Account Has Been Deleted"<<endl;
	cin.ignore();
	cin.get();
	main_menu();
}
void Account::CurrentAmount(){
	cout<<"Enter Account Number:"<<endl;
	cin>>AccountNumber;
	
FileHandeling F1;
int current=F1.AmountReading(AccountNumber);
cout<<"The Current Amount In The Account No. "<<AccountNumber<< " Is: "<<current<<endl;

cin.ignore();
cin.get();
	main_menu();
}
void Account::WithdrawAmount(){
	cout<<"Enter Account Number :"<<endl;
	cin>>AccountNumber;
FileHandeling F1;
int withdraw;
int amount= F1.AmountReading(AccountNumber);
cout<<"Current Balance = "<<amount<<endl;
cout<<"Enter Amount You Want To Withdraw: "<<endl;
cin>>withdraw;
int finalamount;
if (amount>withdraw){
	finalamount=amount-withdraw;
	cout<<"Transaction Successful..."<<endl;
	cout<<"The Remaining Balance is "<<finalamount<<endl;
}
else{
	cout<<"Transaction Failed"<<endl;
	cout<<"Not Enough Balance..."<<endl;
}
F1.AmountUpdater(finalamount,AccountNumber);
	cin.ignore();
	cin.get();
	main_menu();
	
}

int Account::Accounts=0;


void FileHandeling::Modifier(int AccountNumber,string FirstName,string LastName,string Password,string Type,int DepositAmount1){
	ofstream myfile;
	string fname;
	string text;
	text=".txt";
	ostringstream str1;
    str1 << AccountNumber;
	fname=str1.str();
	string Address;
	Address=fname+text;
 myfile.open (Address.c_str());
  myfile << "Account Number : "<<AccountNumber<<"\n";
  myfile << "First Name : "<<FirstName<<"\n";
  myfile << "Last Name : "<<LastName<<"\n";
  myfile << "Password : "<<Password<<"\n";
  myfile << "Type : "<<Type<<"\n";
  myfile << "Current Amount : \n"<<DepositAmount1;
  myfile.close();	
}
void FileHandeling::Writer(int AccountNumber,string FirstName,string LastName,string Password,string Type,int DepositAmount1){
	ofstream myfile;
	string fname;
	string text;
	text=".txt";
	ostringstream str1;
    str1 << AccountNumber;
	fname=str1.str();
	string Address;
	Address=fname+text;
 myfile.open (Address.c_str());
  myfile << "Account Number :"<<AccountNumber<<"\n";
  myfile << "First Name :"<<FirstName<<"\n";
  myfile << "Last Name :"<<LastName<<"\n";
  myfile << "Password :"<<Password<<"\n";
  myfile << "Type :"<<Type<<"\n";
  myfile << "Current Amount : \n"<<DepositAmount1;
  myfile.close();
  
  myfile.close();
}
	
Account::Account(){
	int AccountNumber=0;
	int DepositAmount=0;
}
Account::~Account(){
	
}
#ifdef INCLUDE_Intro_MODULE
void Account::intro(){
	cout<<"\n\n\n\t\t\t BANK ACCOUNT";
	cout<<"\n\n\t\t\t   MANAGEMENT";
	cout<<"\n\n\t\t\t \n\n\n\nMADE BY : Syed Ali Hashim and Muhammad Sharyar"<<endl;
	cout<<"\n\nProject: Object Oriented Programing";
	cout<<"\n\nProfessor: Dr. Nauman";
	cin.get();
	system("cls");	
}
#endif
void Account::main_menu(){
	int option;
	cout<<"\n\n\t\t\t Press 1-9 to perform the tasks"<<endl;
	cout<<"\n\n 1) Create Account"<<endl;
	cout<<"\n\n 2) Deposit Amount"<<endl;
	cout<<"\n\n 3) Withdraw Amount"<<endl;
	cout<<"\n\n 4) Current Amount"<<endl;
	cout<<"\n\n 5) Modify Account"<<endl;
	cout<<"\n\n 6) Delete Account"<<endl;
	cout<<"\n\n 7) Show List Of All Accounts"<<endl;
	cout<<"\n\n 8) Show Information Of Account"<<endl;
	cout<<"\n\n 9) Exit "<<endl;
	cin>>option;	
	system("cls");
	if (option==1){
	 CreateAccount();
	}
	if (option==5){
		ModifyAccount();
	}
	if (option==3){
		WithdrawAmount();
	}
	if (option==4){
		CurrentAmount();
	}
	if (option==6){
		DeleteAccount();
	}
	if (option==7){
		AllAccounts();
	}
	if (option==9){
		cout<<"Bank Management System"<<endl;
		cout<<"Fast Peshawar"<<endl;
		return;
	}
	if (option==2){
		DepositAmount();
	}
	if (option==8){
		cout<<"Enter Account Number"<<endl;
		cin>>AccountNumber;
		Show_info(AccountNumber);
		cin.ignore();
		cin.get();
		main_menu();
	}
	else {
		cout<<"Invalid Option...."<<endl;
		cin.get();
		cin.ignore();
		main_menu();
	}
	cin.ignore();
	cin.get();
		
}

void Account::CreateAccount(){
	
	cout<<"\n\n \t\t Enter First Name:"<<endl;
	cin>>FirstName;
	cout<<"\n\n \t\t Enter Last Name:"<<endl;
	cin>>LastName;
	cout<<"\n\n \t\t Enter Account Number:"<<endl;
	cin>>AccountNumber;
	cout<<"\n\n \t\t Enter Type Of Account:"<<endl;
	cin>>Type;
	cout<<"\n\n \t\t Create Password: "<<endl;
	cin>>Password;
	cout<<"\n\n \t\t Confirm Password: "<<endl;
	cin>>ConfirmPassword;
	while (Password != ConfirmPassword){
		cout<<"\n\n \t\t Password Does Not Match..."<<endl;
		cout<<"\n\n \t\t Confirm Password Again: "<<endl;
		cin>>ConfirmPassword;
	}
	cout<<"Enter Deposit Amount (Atleast 5000) : "<<endl;
		cin>>DepositAmount1;
	while (DepositAmount1<5000){
		cout<<"Enter Deposit Amount Again (Atleast 5000) : "<<endl;
		cin>>DepositAmount1;
	}
	FileHandeling F1;
	F1.Writer ( AccountNumber, FirstName, LastName, Password, Type, DepositAmount1);
	Show_info(AccountNumber); 
	F1.Record(AccountNumber);
	cin.get();
	cin.ignore();
	main_menu();
}
void Account::Show_info(int AccountNumber){
string fname;
	string text;
	text=".txt";
	ostringstream str1;
    str1 << AccountNumber;
	fname=str1.str();
	string Address;
	Address=fname+text;
ifstream MyFile(Address.c_str());
char line;

while(!MyFile.eof())
{
MyFile.get (line);
cout<<line;
}
MyFile.close();
}
void Account::ModifyAccount(){
	int select;
	cout<<"Enter Account Number : "<<endl;
	cin>>AccountNumber;
		
	cout<<"\n\n \t\t Enter First Name:"<<endl;
	cin>>FirstName;
	cout<<"\n\n \t\t Enter Last Name:"<<endl;
	cin>>LastName;
	cout<<"\n\n \t\t Enter Type Of Account:"<<endl;
	cin>>Type;
	cout<<"\n\n \t\t Create Password: "<<endl;
	cin>>Password;
	cout<<"\n\n \t\t Confirm Password: "<<endl;
	cin>>ConfirmPassword;
	while (Password != ConfirmPassword){
		cout<<"\n\n \t\t Password Does Not Match..."<<endl;
		cout<<"\n\n \t\t Confirm Password Again: "<<endl;
		cin>>ConfirmPassword;
	}
		cout<<"Enter Deposit Amount (Atleast 5000) : "<<endl;
		cin>>DepositAmount1;
	while (DepositAmount1<5000){
		cout<<"Enter Deposit Amount Again (Atleast 5000) : "<<endl;
		cin>>DepositAmount1;
	}
FileHandeling F1;

	F1.Modifier ( AccountNumber, FirstName, LastName, Password, Type, DepositAmount1);
	cin.get();
	cin.ignore();
	main_menu();
}

int main(){
	Account A1;
	A1.intro();
	A1.main_menu();
	return 0;
}
