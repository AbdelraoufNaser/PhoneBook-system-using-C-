#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;
class hashTable
{
private:
	static const int tableSize = 100; //Size of hashTable
	struct item
	{
		string name; //Variable to store names
		int phone; //Variable to store phone numbers
		item* next;
	};
	item* hash[tableSize];
public:
	hashTable();
	//default constructor
	~hashTable();
	//destructor
	hashTable(const hashTable &P1);
	//copyconstructor
	int Hash(string key); //hash function protoype
	void AddItem(string name, int phone);//AddItem function prototype
	//Function to add a new contact
	void printTable();
	//Function to output all data stored
	int numberOfContacts(int index);
	//Function to count number of items that is in a list stored in a single index
	void searchContact(string name);
	//Function to search for a contact
	void removeContact(string name);
	//Fuction to delete a contact
};
int hashTable::Hash(string key)
{
	int hash = 0;
	int index;
	for (int i = 0; i<key.length(); i++)
	{
		hash = hash + key[i];
	}
	index = hash % tableSize;
	return index;
	//Total ASCII value of every charcter in the string is divided by the table size and the reminder will be stored in the index variable
}
hashTable::hashTable()
{
	for (int i = 0; i< tableSize; i++)
	{
		hash[i] = new item;
		hash[i]->name = "empty";
		hash[i]->phone = 0;
		hash[i]->next = NULL;
		//for each index the pointer will point to a new item and gives it name and phone number values then the "next" pointer points to nothing
	}
}
hashTable::hashTable(const hashTable &P1)
{
	for (int i = 0; i< tableSize; i++)
	{
		hash[i] = P1.hash[i];
		hash[i]->name = P1.hash[i]->name;
		hash[i]->phone = P1.hash[i]->phone;
		hash[i]->next = P1.hash[i]->next;
	}
}
void hashTable::AddItem(string name, int phone)
{
	int index = Hash(name);
	if (hash[index]->name == "empty")
	{
		hash[index]->name = name;
		hash[index]->phone = phone;
		//Overwrite the default value with the new added values
	}
	else
	{
		item* ptr = hash[index];
		item* n = new item;
		n->name = name;
		n->phone = phone;
		n->next = NULL;
		while (ptr->next != NULL) //Pointing to the end
		{
			ptr = ptr->next;
		}
		ptr->next = n;
	}
}
int hashTable::numberOfContacts(int index)
{
	int count = 0;
	if (hash[index]->name == "empty") //default value
	{
		return count;
	}
	else
	{
		count++;
		item* ptr = hash[index]; //points to the first item in this index
		while (ptr->next != NULL) //checking if it is pointing to nothing
		{
			count++; //count next item
			ptr = ptr->next; //moves pointer to next item
		}
	}
	return count;
}
void hashTable::printTable()
{
	int number; //Variable to store number of elements in each bucket
	for (int i = 0; i<tableSize; i++)
	{
		number = numberOfContacts(i);
		if (number>0)
		{
			cout << "-------------\n";
			cout << "index= " << i << endl;
			cout << hash[i]->name << endl; //print name stored in that index
			cout << "0" << hash[i]->phone << endl; // print phone number stored in that index
			cout << "number of items= " << number << endl; //check if there any other items in that bucket
			cout << "-------------\n";
			
		}
		
	}
}
void hashTable::searchContact(string name)
{
	int index = Hash(name);
	bool foundName = false;
	int phone;
	item* ptr = hash[index];
	while (ptr != NULL)
	{
		if (ptr->name == name) //compare between stored name and passed name
		{
			foundName = true;
			phone = ptr->phone; //phone variable equal to phone variable inside the current item being pointed to
		}
		ptr = ptr->next; //move pointer to next item in the list
	}
	if (foundName == true)
	{
		cout << "The contact is found and its number is: " << phone << endl;
	}
	else
	{
		cout << name << "'s info was not found \n";
	}
}
void hashTable::removeContact(string name)
{
	int index = Hash(name);
	item* delptr;
	item* p1;
	item* p2;
	//case0 - bucket is empty
	if (hash[index]->name == "empty" && hash[index]->phone == 0)
	{
		cout << name << " was not found \n";
	}
	//case1 - only 1 item is contained in the bucket and the name is matching
	else if (hash[index]->name == name && hash[index]->next == NULL)
	{
		hash[index]->name = "empty";
		hash[index]->phone = 0;
		cout << "contact was removed \n";
	}
	// case2 match is located in the first item in the bucket but there are more items in the same bucket
	else if (hash[index]->name == name)
	{
		delptr = hash[index];
		hash[index] = hash[index]->next;
		delete delptr;
		cout << name << " was removed \n";
	}
	// case 3- bucket contains items but first item is not a match
	else
	{
		p1 = hash[index]->next;
		p2 = hash[index];
		while (p1 != NULL && p1->name != name)
		{
			p2 = p1;
			p1 = p2->next;
		}
		// case3.1 no match
		if (p1 != NULL)
		{
			cout << name << " was not found \n";
		}
		//case 3.2 - match is found
		else
		{
			delptr = p1;
			p1 = p1->next;
			p2->next = p1;
			delete delptr;
			cout << name << " was removed \n";
		}

	}


}
hashTable::~hashTable(){ delete[] hash; }

int main()
{
	string cont;
	int number;
	int ch;
	hashTable phonebook;
	do
	{
		cout << "............................................\n";
		cout << "           PHONE BOOK MANAGEMENT\n";
		cout << "............................................\n\n";
		cout << "::::::::::::::: PROGRAM MENU :::::::::::::::\n";
		cout << "0. Exit\n";
		cout << "1. Add New Phone Record\n";
		cout << "2. Display All Saved Records\n";
		cout << "3. Search Specific Record\n";
		cout << "4. Delete Specific Record\n";
		cout << "Enter Your Choice : ";
		cin >> ch;
		switch (ch)
		{
		case 0:
		{
				  break;
		}
		case 1:
		{
				  cout << "Enter the contact name:  ";
				  cin >> cont;
				  cout << endl;
				  cout << "Enter the phone number: ";
				  cin >> number;
				  cout << endl;
				  phonebook.AddItem(cont, number); break;
		}
		case 2: phonebook.printTable(); break;
		case 3:
		{
				  cout << "Enter the contact name:  ";
				  cin >> cont;
				  cout << endl;
				  phonebook.searchContact(cont); break;

		}
		case 4:
		{
				  cout << "Enter the contact name:  ";
				  cin >> cont;
				  cout << endl;
				  phonebook.removeContact(cont); break;
		}
		}

	} while (ch);
	
}