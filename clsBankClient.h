#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h";
#include "clsString.h";

class clsBankClient : clsPerson
{
private:

	enum enMode {EmptyMode = 0, UpdateMode = 1};

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;

	static clsBankClient _ConvertLineToClientObject(string DateLine, string Sperator = "#//#")
	{
		
		vector<string> vClientData;
		vClientData = clsString::Split(DateLine, Sperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3],
			vClientData[4], vClientData[5], stod(vClientData[6]));

	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Sperator = "#//#")
	{
		string stClientRecord = "";

		stClientRecord += Client.FirstName + Sperator;
		stClientRecord += Client.LastName + Sperator;
		stClientRecord += Client.Email + Sperator;
		stClientRecord += Client.Phone + Sperator;
		stClientRecord += Client.AccountNumber() + Sperator;
		stClientRecord += Client.PinCode + Sperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;
	}

	static vector <clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//Read Mode

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return vClients;
	}

	static void _SaveClientsDataToFile(vector <clsBankClient> vClients)
	{

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);//OverWrite

		if (MyFile.is_open())
		{
			string DataLine;

			for (clsBankClient& Client : vClients)
			{
				DataLine = _ConvertClientObjectToLine(Client);
				MyFile << DataLine << endl;
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& Client : _vClients)
		{
			if (Client.AccountNumber() == AccountNumber())
			{
				Client = *this;
				break;
			}

		}

		_SaveClientsDataToFile(_vClients);
	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber,
		string PinCode, double AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	//Property Read noly 
	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(double ClientBalance)
	{
		_PinCode = PinCode;
	}

	double GetAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;

	void Print()
	{
		cout << "\nClient Card:";
		cout << "\n_______________________";
		cout << "\nFirstName  : " << FirstName;
		cout << "\nLastName   : " << LastName;
		cout << "\nFullName   : " << FullName();
		cout << "\nEmail      : " << Email;
		cout << "\nPhone      : " << Phone;
		cout << "\nAcc. Number: " << _AccountNumber;
		cout << "\nPinCode    : " << _PinCode;
		cout << "\nBalance    : " << _AccountBalance;
		cout << "\n_______________________\n";
	}

	static clsBankClient Find(string AccountNumber)
	{

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//Read Mode

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//Read Mode

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	enum enSaveResults {svFaildEmptyObject = 0, svSucceeded = 1};

	enSaveResults Save()
	{
		switch (_Mode)
		{
			case enMode::EmptyMode:
			{
				return enSaveResults::svFaildEmptyObject;
			}

			case enMode::UpdateMode:
			{

				_Update();

				return enSaveResults::svSucceeded;
			}

		}
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		return (!Client1.IsEmpty());
	}
};                                                         