#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h";
#include "clsInputValidate.h";
#include <iomanip>
#include "clsAddNewClientScreen.h";


class clsDeleteClientScreen : protected clsScreen
{
private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n_______________________";
        cout << "\nFirstName  : " << Client.FirstName;
        cout << "\nLastName   : " << Client.LastName;
        cout << "\nFullName   : " << Client.FullName();
        cout << "\nEmail      : " << Client.Email;
        cout << "\nPhone      : " << Client.Phone;
        cout << "\nAcc. Number: " << Client.AccountNumber();
        cout << "\nPinCode    : " << Client.PinCode;
        cout << "\nBalance    : " << Client.AccountBalance;
        cout << "\n_______________________\n";
    }

public:

    static void ShowDeleteClientScreen()
    {

        _DrawScreenHeader("\t   Delete Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, chooce anther one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient DeleteClient = clsBankClient::Find(AccountNumber);
        //DeleteClient.Print();
        _PrintClient(DeleteClient);

        cout << "\nAre you sure you want to delete this client Enter y/n ?: ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (DeleteClient.Delete())
            {
                cout << "\nClient Deleted Successfully :-)\n";
                //DeleteClient.Print();
                _PrintClient(DeleteClient);
            }
            else
            {
                cout << "\nError client was not Deleted :-(\n";
            }
        }
    }

};

