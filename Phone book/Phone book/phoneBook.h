#pragma once

#include <stdlib.h>

#define MAX_NAME_LENGTH 50
#define MAX_PHONE_NUMBER_LENGTH 20
#define MAX_CONTACTS_NUMBER 100

typedef enum
{
    success,
    outOfMemory = 2,
    openFileError
} ErrorCode;

// Phone book
typedef struct PhoneBook PhoneBook;

// Create phone book
PhoneBook* createPhoneBook(void);

// Get data from a file
ErrorCode initData(PhoneBook* const phoneBook, const char* const openningFileName);

// Add contact in phone book
ErrorCode addContact(PhoneBook* const phoneBook, const char name[MAX_NAME_LENGTH], const char phoneNumber[MAX_PHONE_NUMBER_LENGTH]);

// Print all contacts in phone book
void printContacts(const PhoneBook* const phoneBook);

// Find all contacts that match part of contact, entered by user
// choice = 3 - name, choice = 4 - phone number
size_t* findContactsByPartOfContact(const PhoneBook* const phoneBook, const char* const partOfContact, const int choice);

// Print contacts that match part of contact, entered by user
void printSuitableContacts(const PhoneBook* const phoneBook, const size_t* const suitableContacts, const int choice);

// Save phone book to file
ErrorCode saveData(const PhoneBook* const phoneBook, const char* const writtingFileName);

// Print commands for user
void printCommands(void);

// Delete phone book
void deletePhoneBook(PhoneBook** const phoneBook);