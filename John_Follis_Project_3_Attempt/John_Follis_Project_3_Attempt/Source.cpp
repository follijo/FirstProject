#include <Python.h>
#include <iostream>
#include<sstream> //This allows me to switch between type casts 
#include<fstream> //This allows me to open and read a file 
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;
/*The beginning part of the program is the starter code to be able
interact with the Python program and call on the functions*/

void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("CS210_Starter_PY_Code");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

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
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code");
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

int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code");
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

/*This will print the menu as well as ask and validate the users input.
If the input is invalid then another message will be displayed.*/
int Menu() {
	int userInput = 0;

	do {
		cout << "Please Enter Your Selection." << endl;
		cout << "1: All Items Purachsed w/ number Times Items were Purchased" << endl;
		cout << "2: How many times a specific item was purchased" << endl;
		cout << "3: Histogram listing all items purchased w/ special character showing how may times the Item was Purchased." << endl;
		cout << "Enter 4 to Exit" << endl;
		cin >> userInput;
		if (userInput < 1 || userInput > 4) {
			cout << "Invalid Entry. Please Enter a Valid Number." << endl;
			cout << endl;
		}
	} while (userInput != 1 && userInput != 2 && userInput != 3 && userInput != 4);

	cout << endl;

	return userInput;
	
}

/*In this function I open the file made in Python and print put the contents.
However instead of printing a number a special character is printed indicating 
the number of time the item was purchased.*/

void readFilePrintHistogram() {
	string line;
	int num = 1;
	int num2;
	ifstream myfile;
	string file_name = "frequency.dat";
	string word;

	myfile.open(file_name.c_str());
	if (myfile.is_open()) {
		while (myfile >> word) {

			if ((num % 2) != 0) {
				cout << word;
				num++;
			}
			else if ((num % 2) == 0)
			{
				stringstream replace;
				replace << word;
				replace >> num2;

				cout << " ";

				for (int i = 0; i < num2; i++) {
					
					cout << "*";

				}
				
				num++;
				cout << endl;
			}
			
		}
		myfile.close();
	}
}

/*In the main program I call the Menu function that returns a value then I use a switch to 
check each of the cases. Each case will call a Python function. The first case will print all the items
and how many times they were purchased. The second case askes the user to enter a specific item to see how many 
were purchased returning a number value. The third case will create a file in Python and then call the readFilePrintHistogram
function. The fourth case will end the program.*/

void main()
{
	int userInput;
	string item;

	userInput = Menu();


	switch (userInput)
	{
	case 1:
		CallProcedure("printAllItems");
		cout << endl;
		break;

	case 2:
		cout << "Enter an item to see how many times it was purchased." << endl;
		cin >> item;
		cout << callIntFunc("PrintSelectItem", item) << endl;
		cout << endl;
		break;

	case 3:
		CallProcedure("createFile");
		readFilePrintHistogram();
		cout << endl;
		break;

	case 4:
		break;
	}
	
}
