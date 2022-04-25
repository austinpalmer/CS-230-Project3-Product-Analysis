/* This program was created by Austin Palmer.
   The purpose of this program is to allow a user to analyze the purchase frequency
   of a certain product and read/write files based on input.
   This program uses both Python and C++ to best analyze large amounts of data.
   Please see the comments in "PythonCode.py" at the top for references

   Sources for changing output color: 
   https://www.geeksforgeeks.org/how-to-print-colored-text-in-c/
*/
#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

int main()
{
	int userInput;
	string item;
	int times;
	ifstream inFS;
	system("Color 09");
	do {
		// Format and display menu
		cout << "1: Display all items purchased" << endl;
		cout << "2: Search for an item" << endl;
		cout << "3: Display histogram of all items purchased" << endl;
		cout << "4: Exit program" << endl;
		cout << "Enter your selection as a number  1, 2, 3 or 4." << endl;
		cin >> userInput;

		// Validate and analyze userInput
		switch (userInput) {
			case 1:
				// Call ItemFrequency in PythonCode
				CallProcedure("ItemFrequency");
				break;
			case 2:
				// Call SeachItem in PythonCode
				cout << "What item would you like to search for?" << endl;
				cin >> item;
				cout << item << " occurs " << callIntFunc("SearchItem", item) << " times.";
				break;
			case 3:
				// Call DisplayHistogram in PythonCode
				CallProcedure("DisplayHistogram");
				// Open frequency.dat which is created from DisplayHistogram
				inFS.open("frequency.dat");
				
				// While not the end of the file
				while (!inFS.eof()) {
					// Store item and the occurence
					system("Color 04");
					inFS >> item;
					inFS >> times;
					cout << item << " ";
					for (int i = 0; i < times; i++) {
						cout << "*";
					}
					cout << endl;
				}

				break;
			case 4:
				// Exit program
				cout << "Exiting program...";
				return 0;
			
			default:
				// Repeat program if invalid input
				cout << "Invalid input, try again." << endl;
				break;
		}
		// Clear screen
		for (int i = 0; i < 5; i++) { cout << endl; }
	} while (userInput != 4);

}