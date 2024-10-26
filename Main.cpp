
#include <iostream>
#include <iomanip>
#include "clsBankClient.h";
#include "clsInputValidate.h";
#include "clsUitil.h";

//Update Client Solution
void ReadClientInfo(clsBankClient& Client)
{

    cout << "\nEnter FirstName: ";
    Client.FirstName = clsInputValidate::ReadString();

    cout << "\nEnter LastName: ";
    Client.LastName = clsInputValidate::ReadString();

    cout << "\nEnter Email: ";
    Client.Email = clsInputValidate::ReadString();

    cout << "\nEnter Phone: ";
    Client.Phone = clsInputValidate::ReadString();

    cout << "\nEnter PinCode: ";
    Client.PinCode = clsInputValidate::ReadString();

    cout << "\nEnter Account Balance: ";
    Client.AccountBalance = clsInputValidate::ReadfloatNumber();
}

void UpdateClient()
{
    string AccountNumber = "";

    cout << "\nPlease Enter Client Account Number: ";
    AccountNumber = clsInputValidate::ReadString();

    while (!clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "\nAccount number is not found, chooce anther one: ";
        AccountNumber = clsInputValidate::ReadString();
    }

    clsBankClient Client1 = clsBankClient::Find(AccountNumber);
    Client1.Print();


    cout << "\nUpdate Client Info:";
    cout << "\n______________________\n";

    //Update just one item from data Client
   /* Client1.Phone = "421252343434";
    Client1.Save();*/

    //Update all Info Client
    ReadClientInfo(Client1);

    clsBankClient::enSaveResults SaveResult;

    SaveResult = Client1.Save();

    switch (SaveResult)
    {
    case clsBankClient::enSaveResults::svSucceeded:
    {
        cout << "\nAccount Update successfully :-).\n";
        Client1.Print();
        break;
    }
    case clsBankClient::enSaveResults::svFaildEmptyObject:
    {
        cout << "\nError Account was not saved decause it's Empty.";
        break;
    }

    }
}


//Add New Client Solution

void AddNewClient()
{
    string AccountNumber = "";

    cout << "\nPlease Enter Account Number: ";
    AccountNumber = clsInputValidate::ReadString();

    while (clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "\nAccount number is already used, Enter anther one: ";
        AccountNumber = clsInputValidate::ReadString();
    }

    cout << "\nAdd New Client:";
    cout << "\n_____________________\n";

    clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

    ReadClientInfo(NewClient);

    clsBankClient::enSaveResults SaveResult;

    SaveResult = NewClient.Save();

    switch (SaveResult)
    {

    case clsBankClient::enSaveResults::svFaildEmptyObject:
    {
        cout << "\nError Account was not saved because it's Empty :-(.\n";
        break;
    }

    case clsBankClient::enSaveResults::svSucceeded:
    {
        cout << "\nAcount Added successfully :-).\n";
        NewClient.Print();
        break;
    }

    case clsBankClient::enSaveResults::svFaildAccountNumberExists:
    {
        cout << "\nError Acount was not saved because account number is used!\n";
        break;
    }

    }

}

//Delete Client Solution

void DeleteClient()
{
    string AccountNumber = "";

    cout << "\nPlease Enter Client Account Number: ";
    AccountNumber = clsInputValidate::ReadString();

    while (!clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "\nAccount number is not found, chooce anther one: ";
        AccountNumber = clsInputValidate::ReadString();
    }

    clsBankClient DeleteClient = clsBankClient::Find(AccountNumber);
    DeleteClient.Print();

    cout << "\nAre you sure you want to delete this client Enter y/n ?: ";

    char Answer = 'n';
    cin >> Answer;

    if (Answer == 'Y' || Answer == 'y')
    {
        if (DeleteClient.Delete())
        {
            cout << "\Client Deleted Successfully :-)\n";
            DeleteClient.Print();
        }
        else
        {
            cout << "\nError client was not Deleted :-(\n";
        }
    }
}

//List Clients Solution

void PrintClientRecordLine(clsBankClient Client)
{
    cout << "|" << left << setw(15) << Client.AccountNumber();
    cout << "|" << left << setw(20) << Client.FullName();
    cout << "|" << left << setw(12) << Client.Phone;
    cout << "|" << left << setw(20) << Client.Email;
    cout << "|" << left << setw(10) << Client.PinCode;
    cout << "|" << left << setw(12) << Client.AccountBalance;

}

void ShowClientsList()
{
    vector<clsBankClient> vClients = clsBankClient::GetClientsList();

    cout << "\n\t\t\t\tClient list (" << vClients.size() << ") Client(s).\n";

    cout << "\n________________________________________________________________________________________________\n" << endl;
    cout << "|" << left << setw(15) << "Account Number";
    cout << "|" << left << setw(20) << "Full Name";
    cout << "|" << left << setw(12) << "Phone";
    cout << "|" << left << setw(20) << "Email";
    cout << "|" << left << setw(10) << "Pin Code";
    cout << "|" << left << setw(12) << "Balance";
    cout << "\n________________________________________________________________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tno Clients Available In the System :-(";
    else
    {

        for (clsBankClient& Client : vClients)
        {
            PrintClientRecordLine(Client);
            cout << endl;
        }

    }
    cout << "\n________________________________________________________________________________________________\n" << endl;

}

//Total Balances Solution

void PrintClientRecordBalanceLine(clsBankClient Client)
{
    cout << "|" << left << setw(15) << Client.AccountNumber();
    cout << "|" << left << setw(40) << Client.FullName();
    cout << "|" << left << setw(12) << Client.AccountBalance;
}

void ShowTotalBalances()
{
    vector<clsBankClient> vClients = clsBankClient::GetClientsList();

    cout << "\n\t\t\tClient list (" << vClients.size() << ") Client(s).\n";

    cout << "\n_______________________________________________________________________\n" << endl;
    cout << "|" << left << setw(15) << "Account Number";
    cout << "|" << left << setw(40) << "Client Name";
    cout << "|" << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________________________\n" << endl;

    double TotalBalances = clsBankClient::GetTotalBalances();

    if (vClients.size() == 0)
        cout << "\t\t\tno Clients Available In the System :-(";
    else
    {

        for (clsBankClient& Client : vClients)
        {
            PrintClientRecordBalanceLine(Client);
            cout << endl;
        }

    }
    cout << "\n_______________________________________________________________________\n" << endl; cout << "\t\t\tTotal Balances = " << TotalBalances;
    cout << "\n\t\t\t(" << clsUitil::NumberToText(TotalBalances) << ")" << endl;

}

int main()
{
    ShowTotalBalances();
    system("pause>0");
    return 0;
}










