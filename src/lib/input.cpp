#include <iostream>
#include <iomanip>
#include "ansiEsc.h"
#include "data.h"
#include "input.h"
#include "namespaces.h"

using namespace std;
using namespace clients;
using namespace terminal;
using namespace commands;

// --- Function Prototypes
// void ignoreInput();
bool booleanQuestion(string message);
void wrongCommand(cmdStatus cmdStatus);
void wrongClientData(invalidClient wrongData);
void checkClientStatus(clientStatus clientStatus);
void pressEnterToCont(string message, bool warning);
int getClientId(string message);
float getFloat(string message, float low, float high);

// --- Functions

/*
// This prevents the program to crash if there's more input
void ignoreInput()
{
  while (getchar() != '\n')
    cin.clear();
}
*/

// Boolean Question
bool booleanQuestion(string message)
{
  string input;
  char c;

  while (true)
  {
    cout << "- " << message << " [y/N] ";
    getline(cin, input);

    c = tolower(input[0]);
    if (c == 'y')
    {
      cout << '\n';
      return true;
    }
    else if (c == 'n')
    {
      cout << '\n';
      return false;
    }
    else
      wrongCommand(wrongBooleanAnswer);
  }
}

// Function to Check if the Command Entered by the User is Correct
void wrongCommand(cmdStatus cmdStatus)
{
  string message = "ERROR: ";

  switch (cmdStatus)
  {
  case wrongBooleanAnswer:
    message.append("It's a Yes/No Question. You must type 'y', 'Y' or 'n', 'N'");
    break;
  case noCmd:
  case wrongMainCmd:
  case wrongSubCmd:
    if (cmdStatus == noCmd)
      message.append("No Command");
    else
      message.append((cmdStatus == wrongMainCmd) ? "Wrong Main Command" : "Wrong Subcommand");
    message.append(". Press ENTER to Display Help Message");
    break;
  case wrongViewClientsCmd:
  case wrongFilterClientsCmd:
  case wrongSortByParam:
  case wrongFieldParam:
  case wrongField:
    if (cmdStatus == wrongFilterClientsCmd || cmdStatus == wrongViewClientsCmd)
      message.append("Wrong Command");
    else if (cmdStatus == wrongSortByParam || cmdStatus == wrongFieldParam || cmdStatus == wrongField)
      message.append((cmdStatus == wrongSortByParam) ? "Wrong Sort By Parameter" : "Wrong Field");
    message.append(". Press ENTER to Display Search Data Parameters Message");
    break;
  }
  pressEnterToCont(message, true);
}

// Function to Check if the Client Data Typed by the User is Correct
void wrongClientData(invalidClient wrongData)
{
  string message = "Invalid: Client ";

  switch (wrongData)
  {
  case invalidClientId:
    message.append("ID");
    break;
  case invalidClientAccountNumber:
    message.append("Account Number");
    break;
  }
  pressEnterToCont(message, true);
}

// Function to Check if the Program Could Find a Client
void checkClientStatus(clientStatus clientStatus)
{
  string message;

  switch (clientStatus)
  {
  case clientNotFound:
    message = "Error 404: Client Not Found. Run \"Add Client Command\"";
    break;
  }
  pressEnterToCont(message, (clientStatus != clientFound) ? true : false);
}

// Function to Stop the Program Flow while the User doesn't press the ENTER key
void pressEnterToCont(string message, bool warning)
{
  string temp;

  printTitle(message, applyBgColor, applyFgColor, warning);
  getline(cin, temp);
  // ignoreInput();
}

// Function to Ask for Client Id
int getClientId(string message)
{
  string temp;

  while (true)
    try // Get Client ID
    {
      cout << message << ": ";
      getline(cin, temp);
      return stoi(temp);
    }
    catch (...)
    {
      wrongClientData(invalidClientId);
    }
}

// Function to Ask for a Float Input
float getFloat(string message, float low, float high)
{
  string temp;

  while (true)
    try // Get Floats
    {
      cout << message << " [" << setprecision(precision) << low << '-' << high << "]: ";
      getline(cin, temp);
      return stoi(temp);
    }
    catch (...)
    {
      pressEnterToCont("The Number is Out of that Range", true);
    }
}