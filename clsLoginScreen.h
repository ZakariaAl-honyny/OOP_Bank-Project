#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:

	static void _Login()
	{
		bool LoginFaild = false;
		string UserName, Password;

		do
		{
			if (LoginFaild)
			{
				system("cls");
				_DrawScreenHeader("\t\tLogin Screen");
				cout << "\nInvalid UserName/Password, Enter Again!\n";
			}

			cout << "\nEnter UserName? ";
			UserName = clsInputValidate::ReadString();
			cout << "Enter Password? ";
			Password = clsInputValidate::ReadString();
			
			CurrentUser = clsUser::Find(UserName, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		clsMainScreen::ShowMainMenue();
	}

public:

	static void ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\tLogin Screen");
		_Login();
	}
};

