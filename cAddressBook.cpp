#include "cAddressBook.h"
#include "tinyxml2-master\tinyxml2.cpp"

using namespace tinyxml2;


cAddressBook<T1, T2>::cAddressBook()
{
}

cAddressBook<T1, T2>::~cAddressBook()
{
    T1<T2 *>::iterator it;
    for(it = vDatabase.begin(); it != vDatabase.end(); it++)
    {
        delete *it;
        *it=nullptr;
    }

    vDatabase.clear();

}

int cAddressBook<T1, T2>::mcAddContact()
{
    T2* mcNewContact = new T2();

	mcNewContact->mcGetDataFromUser();

    vDatabase.push_back(mcNewContact);
    cout << endl << " New contact added!";
    return 0;
}

int cAddressBook<T1, T2>::mcAddContact(string sNameFromFile, string sEmailFromFile, string sPhoneFromFile)
{
    T2* mcNewContact = new T2(sNameFromFile, sEmailFromFile, sPhoneFromFile);

    vDatabase.push_back(mcNewContact);

    return 0;
}

int cAddressBook<T1, T2>::mcRemoveContact()
{
    cAddressBook<T1, T2>::mcDisplayAllContacts();
	string sContactToRemove;
	int iIsAnythingFound = 0;

    if (!vDatabase.empty())
	{
		cout << "Type contact name to remove: ";
		cin >> sContactToRemove;

        T1<T2 *>::iterator it = vDatabase.begin();
        for(it = vDatabase.begin(); it != vDatabase.end(); it++)
        {
            if ((*it)->mcGetName() == sContactToRemove)
            {
                delete *it;
                *it = nullptr;
                vDatabase.erase(it);

                cout << endl << "\tContact " << sContactToRemove << " removed!" << endl;
                iIsAnythingFound++;
                this_thread::sleep_for(chrono::seconds(1));
                break;
            }

        }

        if (0 == iIsAnythingFound && it == vDatabase.end())
        {
            cout << "No matches found! Contact not removed!";
            this_thread::sleep_for(chrono::seconds(1));
        }

        return 0;
	}
    else
    {
        cout << "Database is empty!";
        this_thread::sleep_for(chrono::seconds(1));
        return 1;
    }

}



int cAddressBook<T1, T2>::mcShowMenu()
{
	int iChoosenOption;
	string sChoosenOption;
	system("CLS");
	cout << "Address Book Menu:" << endl;
	cout << "1. Add new contact" << endl;
	cout << "2. Search for contact" << endl;
	cout << "3. Display all contacts" << endl;
	cout << "4. Remove contact" << endl;
	cout << "5. Load contacts from file database.xml" << endl;
	cout << "0. Exit" << endl << endl;

	cout << "Choosen option: ";
	cin >> sChoosenOption;


	if (1 == sChoosenOption.length() && isdigit(sChoosenOption[0]))
	{
		iChoosenOption = atoi(sChoosenOption.c_str());
	}
	else
	{
		iChoosenOption = -1;
	}

	return iChoosenOption;

}


void cAddressBook<T1, T2>::mcDisplayAllContacts()
{

    if (vDatabase.empty())
	{
		cout << endl << "\tDatabase is empty!";
		this_thread::sleep_for(chrono::seconds(1));
	}
	else
	{
        int iNumberOfContact = 1;
        T1<T2 *>::iterator it;

        for(it = vDatabase.begin(); it != vDatabase.end(); it++, iNumberOfContact++)
        {
			cout << endl << "\t" << iNumberOfContact << ".";
            cout << endl << "\tName: " << (*it)->mcGetName();
            cout << endl << "\tEmail: " << (*it)->mcGetEmail();
            cout << endl << "\tPhone: " << (*it)->mcGetPhone();
			cout << endl << endl;
		}
		system("PAUSE");
	}

}

void cAddressBook<T1, T2>::mcSearchForContact()
{
	string sTextToFind;
	int iNumberOfContact = 1, iIsAnythingFound = 0;

	cout << endl << "Type part of name, email or phone to find." << endl << "Find: ";
	cin >> sTextToFind;

    if (vDatabase.empty())
	{
		cout << endl << "Database is empty!" << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
	else
	{
        T1<T2 *>::iterator it;

        for(it = vDatabase.begin(); it != vDatabase.end(); it++, iNumberOfContact++)
        {
            if ((string::npos != ((*it)->mcGetName()).find(sTextToFind)) || (string::npos != ((*it)->mcGetEmail()).find(sTextToFind)) || (string::npos != ((*it)->mcGetPhone()).find(sTextToFind)) )
			{	
				cout << endl << "\t" << iNumberOfContact << ".";
                cout << endl << "\tName: " << (*it)->mcGetName();
                cout << endl << "\tEmail: " << (*it)->mcGetEmail();
                cout << endl << "\tPhone: " << (*it)->mcGetPhone();
				cout << endl;
				iIsAnythingFound++;
			}
		}

		if (0 == iIsAnythingFound)
		{
			cout << "No matches found!";
		}

		cout << endl;
		system("PAUSE");
	}



}

template<typename T>
bool mcCompareTwoObjects(T* pcFirstObjToCompare, T* pcSecondObjToCompare)
{
    return (*pcFirstObjToCompare < *pcSecondObjToCompare);
}


void cAddressBook<T1, T2>::mcSortEntriesInDatabase()
{
    sort((vDatabase.begin()), (vDatabase.end()), mcCompareTwoObjects<T2>);
}


int cAddressBook<T1, T2>::mcLoadDatabaseFromFile()
{
    XMLDocument* xmlDatabase = new XMLDocument;

    const char * sFileLocation = "d:/_SelfStudy/Database-templates/database.xml";

    if (!xmlDatabase->LoadFile(sFileLocation))
	{
		XMLElement* xmlContactsIterator, *xmlContactsDataIterator;
		vector<string>* vNewContactFromFile = new vector<string>;

		xmlContactsIterator = xmlDatabase->FirstChildElement("AddressBook")->FirstChildElement("Contact");

		for (xmlContactsIterator; xmlContactsIterator != NULL; xmlContactsIterator = xmlContactsIterator->NextSiblingElement())
		{
			for (xmlContactsDataIterator = xmlContactsIterator->FirstChildElement(); xmlContactsDataIterator != NULL; xmlContactsDataIterator = xmlContactsDataIterator->NextSiblingElement())
			{
				vNewContactFromFile->push_back(xmlContactsDataIterator->GetText());
			}
			mcAddContact(vNewContactFromFile->at(0), vNewContactFromFile->at(1), vNewContactFromFile->at(2));
			vNewContactFromFile->clear();
		}

		xmlDatabase->Clear();
	}

	
	return 0;
}
