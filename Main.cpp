

#include <iostream>
#include "clsBankClient.h";

using namespace std;

int main()
{
    
    clsBankClient Client1 = clsBankClient::Find("A101");
    Client1.Print();

    clsBankClient Client2 = clsBankClient::Find("A101", "1234");
    Client2.Print();

    cout << Client2.IsEmpty() << endl;

    cout << clsBankClient::IsClientExist("A101") << endl;
}
