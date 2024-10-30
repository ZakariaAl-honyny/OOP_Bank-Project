#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private:

	enum enTransactionsMenueOptions {
		eDeposit = 1, eWithDraw = 2, eShowTotalBalance = 3, eShowMainMenue = 4
	};

	static void _GoBackToTransactionsMenue()
	{
		cout << "\n\nPress any key to go back to Transactions menue...";
		system("pause>0");
		ShowTransactionsMenue();
	}

	static short _ReadTransactionsMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 4]? ";
		short Choice = 0;
		Choice = clsInputValidate::ReadShortNumberBetween(1, 4, "\t\t\t\t\tError, Enter Number Between 1 to 4 ?: ");

		return Choice;
	}

	static void _ShowDepositScreen()
	{
		//cout << "\nDeposit Screen will be here soon...\n";
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		//cout << "\nWithdraw Screen will be here soon...\n";
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalacesScreen()
	{
		//cout << "\nTotal Balances Screen will be here soon...\n";
		clsTotalBalancesScreen::ShowTotalBalances();
	}

	static void _PerformTransactionsMenueOption(enTransactionsMenueOptions TransactiosMenueOption)
	{
		switch (TransactiosMenueOption)
		{
		case enTransactionsMenueOptions::eDeposit:
		{
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenue();
			break;
		}

		case enTransactionsMenueOptions::eWithDraw:
		{
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenue();
			break;
		}

		case enTransactionsMenueOptions::eShowTotalBalance:
		{
			system("cls");
			_ShowTotalBalacesScreen();
			_GoBackToTransactionsMenue();
			break;
		}

		case enTransactionsMenueOptions::eShowMainMenue:
		{
			//do nothing here the main screen will handle it :-) ;
		}

		}
	}


public:

	static void ShowTransactionsMenue()
	{

		system("cls");
		_DrawScreenHeader("\t  Transactions Screen");

		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t\t   Transactions  Menue\n";
		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] With draw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Main menue.\n";
		cout << setw(37) << left << "" << "=============================================\n";
		_PerformTransactionsMenueOption((enTransactionsMenueOptions)_ReadTransactionsMenueOption());
	}

};

