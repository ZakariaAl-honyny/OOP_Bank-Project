#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h";
#include "clsString.h";

using namespace std;

class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkdForDelete = false;

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
				if (Client._MarkdForDelete == false)
				{
					//we only write records that are not marked for delete.
					DataLine = _ConvertClientObjectToLine(Client);
					MyFile << DataLine << endl;
				}
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

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
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
		string PinCode, float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)
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

	//Property Set
	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	//Property Get
	string GetPinCode()
	{
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

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

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{

		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{
				return enSaveResults::svFaildEmptyObject;
			}
			break;
		}

		case enMode::UpdateMode:
		{

			_Update();

			return enSaveResults::svSucceeded;

			break;
		}

		case enMode::AddNewMode:
		{
			//This will add new record to file or database
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();

				//we will need to set the mode to update after add new
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}

			break;
		}

		}
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		return (!Client1.IsEmpty());
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& Client : _vClients)
		{
			if (Client.AccountNumber() == _AccountNumber)
			{
				Client._MarkdForDelete = true;
				break;
			}

		}

		_SaveClientsDataToFile(_vClients);

		*this = _GetEmptyClientObject();

		return true;
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

};





