#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;

void printTitlesAndLogo(){
	cout<<"====================================================================================="<<endl;
	cout<<"====\t\t\t E-CHALLAN SYSTEM CONSOLE APPLICATION \t\t\t ===="<<endl;
	cout<<"====================================================================================="<<endl;
}
void welcomeMessage() {
	system("cls");
	printTitlesAndLogo();
	cout<<"\t Welcome to electronic challan system. \n";
	cout<<"\t E-CHALLAN provides you easy access to: \n";
	cout<<"\t\t - Register your new vehicle and their tax. \n";
	cout<<"\t\t - Pay challans on-the-go.\n";
	cout<<"\t\t - View your vehicle's tax history\n\n";
}

void newRegistration(){
	system("cls");
	string cnic;
	printTitlesAndLogo();
	
	cout<<"----- NEW REGISTRATION OF VEHICLE \n";
	cout<<"Please enter CNIC: ";
	cin>>cnic;
	
	ifstream file, file2;		//file1 is for registration, file2 is for payment
	
	bool registered = false, payment=false;
	
	file.open("database\\registeredcnic.txt");
	file2.open("database\\registeredpaidcnic.txt");
	
	string toCheckCNIC;
	
	//Check if user has registered but haven't paid yet.
	while (std::getline(file, toCheckCNIC))
    {
        if(toCheckCNIC==cnic){
        	registered = true;
		}
    }
	
	//Check if user has registered and has also done their payment
	while (std::getline(file2, toCheckCNIC))
    {
        if(toCheckCNIC==cnic){
        	payment = true;
		}
    }
    
	if(payment)
	{
		cout<<"You have already registered and paid your tax.\nThank you for using E-Challan System"<<endl;
		file.close();
		file2.close();
	}
	else if(registered)
	{
		cout<<"You have already registered but haven't paid registration fee.\nDo you wish to pay your tax?"<<endl;
		system("pause");
		file.close();
		file2.close();
	}
	else {
		file.close();
		file2.close();
		string company, type, model, year;
		cout<<"Please add your vehicle details.. "<<endl;
		cout<<"Type (Bike, Car, Mini-Truck, Truck, Mini-Van, Van): "; cin>>type;
		cout<<"Company: "; cin>>company;
		cout<<"Model: "; cin>>model;
		cout<<"Year of Purchase: "; cin>>year;
		company = "Company: "+company;
		type = "Type: "+type;
		model = "Model: "+model;
		year = "Year: "+year;
		
		ofstream file3, file4;
		
		// Saving vehicle details in a separate file in vehicle details folder
		string outputFileNameConvention = "vehicledetails\\"+cnic;
		file3.open(outputFileNameConvention.c_str());
		file3<<company<<endl<<type<<endl<<model<<endl<<year;
		file3.close();
		
		//Saving cnic in registered users file
		file4.open("database\\registeredcnic.txt",std::ios_base::app);
		file4<<endl<<cnic<<endl;
		file4.close();
		
	}
	system("pause");
	file.close();
	
}

int main(){
	string name;
	string password = "ABC1122";
	string enteredPassword, confirmExit;
	
	ofstream file;
	int deniedLoginCount = 0, choice = 9;
	while(deniedLoginCount < 3){
		
		system("cls");
		printTitlesAndLogo();
		cout<<"LOGIN TO CONTINUE"<<endl;
		
		if(deniedLoginCount > 0) {
			cout<<" --- login failed. try again. ---"<<endl;
		}
		
		cout<<"Enter Password: ";
		cin>>enteredPassword;
		if(enteredPassword == password){
			deniedLoginCount = 0;
			do{
			system("cls");
			welcomeMessage();
			cout<<"Login Successful! \nEnter your choice: \n";
			cout<<"\t (1) NEW VEHICLE REGISTRATION\n";
			cout<<"\t (2) VIEW YOUR DETAILS\n";
			cout<<"\t (3) PAY YOUR CHALLAN / TAX\n";
			cout<<"\t (0) EXIT / TAX\n";
			cin>>choice;
			
			if(choice == 1) { newRegistration(); }
		}
		while(choice!=0);
		}
		else {
			deniedLoginCount++;
			if(deniedLoginCount < 3) {
			system("cls");
			}
		}
		if(choice == 0 && deniedLoginCount == 0) {
			cout<<"Confirmation to exit program (Y/N): ";
			cin>>confirmExit;
			if(confirmExit == "Y"){
				break;
			}
		}
	}
	system("cls");
	if(deniedLoginCount >= 3) {
		printTitlesAndLogo();
		cout<<"\nToo many unsuccessful logins. \nExited E-CHALLAN system after 3 unsuccessful login attempts. \nRe-launch to continue.";
	}
	else {
	printTitlesAndLogo();
	cout<<"\n\n Thank you for using E-Challan System :)"; }

}
