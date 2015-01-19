#pragma once
#include <chrono>
#include <thread>
#include "cContactCard.h"
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

template <typename T1 = cContactCard, typename T2 = vector<T1 *> >
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
    friend int mcLoadDatabaseFromFile();
    template<typename T>
    friend bool mcCompareTwoObjects(T* pcFirstObjToCompare, T* pcSecondObjToCompare);

private:

    T2 vDatabase;

};

