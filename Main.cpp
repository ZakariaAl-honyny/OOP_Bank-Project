
#include <iostream>
#include "clsBankClient.h";
#include "clsInputValidate.h";

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

int main()
{
    AddNewClient();
    system("pause>0");
    return 0;
}



