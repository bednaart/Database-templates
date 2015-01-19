#pragma once
#include <chrono>
#include <thread>
#include "cContactCard.h"
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

template<typename T1 = cContactCard, typename T2 = vector>
class cAddressBook
{
public:
	cAddressBook();
	~cAddressBook();
	int mcAddContact();
	int mcAddContact(string sNameFromFile, string sEmailFromFile, string sPhoneFromFile);
	int mcRemoveContact();
	void mcSearchForContact();
	int mcShowMenu();
	void mcDisplayAllContacts();
	void mcSortEntriesInDatabase();
	int mcLoadDatabaseFromFile();
    friend bool mcCompareTwoObjects(T1* pcFirstObjToCompare, T1* pcSecondObjToCompare);

private:

    T2<T1 *> vDatabase;

};

