#include"prog5.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
using namespace std;

// function Converts string to float
float convertToFloat(string s)
{
	istringstream i(s);
	float x;
	if (!(i >> x))
		x = 0;
	return x;
}

// Function returns a string representing cost Struct
string displayCost(Cost c)
{
	string str = "";
	// converts to string
	string h = to_string(c.care_hours);
	string ch = to_string(c.per_hour_cost);
	string fc = to_string(c.weekly_feed_cost);
	string sc = to_string(c.weekly_supplies_cost);
	// adds to string and sets precision
	str += "Number of Hours to take care for Dinosaur:\t" + h.substr(0, h.find(".") + 3); +" hours";
	str += "\nCost per Hours of taking Care of Dinosaur:\t$" + ch.substr(0, ch.find(".") + 3) + "\n";
	str += "Cost to feed Dinosaur:                    \t$" + fc.substr(0, fc.find(".") + 3) + "\n";
	str += "Grooming and Supplies Cost:               \t$" + sc.substr(0, sc.find(".") + 3) + "\n";
	return str;
}

// function calculates and returns weekly cost for a Dinosaur
float calculteWeeklyCost(Dinosaur d)
{
	return (d.cost.care_hours * d.cost.per_hour_cost) + d.cost.weekly_feed_cost + d.cost.weekly_supplies_cost;
}

// Function returns a string that represents a dinosaur
string displayDinosaur(Dinosaur d)
{
	string str = "";
	str += "Name:      \t" +d.name + "\n";
	str+= "Description:";
	int c = 0;
	// wraps description
	for (int i = 0; i < d.description.length(); i++)
	{
		if (c % 60 == 0)
		{
			while (d.description[i] != ' ' && i != 0)
			{
				str+= d.description[i];
				i++;
			}
			str+= d.description[i];
			str+= "\n                ";
			c = 0;
		}
		str+= d.description[i];
		c++;
	}
	str+= "\n\n";
	//converts to string
	string l = to_string(d.average_length);
	string h = to_string(d.average_height);
	str += "Length:    \t" + l.substr(0, l.find(".") + 3) + " feet\n";
	str += "Height:    \t" + h.substr(0, h.find(".") + 3) + " feet\n";
	str += "Location:  \t" + d.location + "\n";
	if (d.is_dangerous)
		str+= "Dangerous?\tyes\n";
	else
		str+= "Dangerous?\tno\n";
	str += displayCost(d.cost); //gets cost
	return str;
}

// Function Inputs a Dinosaur
void inputDinosaur(Dinosaur arr[], int index)
{
	cin.clear();
	char c;
	cout << "NAME: ";
	cin >> arr[index].name; //inputs Name
	cout << "DESCRIPTION: ";
	cin.ignore();
	getline(cin, arr[index].description); // inputs description
	cout << "AVERAGE LENGTH (in feet): ";
	cin >> arr[index].average_length; //inputs length
	cout << "AVERAGE HEIGHT (in feet):";
	cin >> arr[index].average_height; //inputs height
	cout << "LOCATION: ";
	cin.ignore();
	getline(cin, arr[index].location); //inputs location
	cout << "IS IT A DANGEROUS DINOSAUR? (y or n): ";
	cin >> c;
	//inputs dangerous 
	if (c == 'Y' || c == 'y')
		arr[index].is_dangerous = true;
	else
		arr[index].is_dangerous = false;
	cout << "How many hours do you spend caring for the " << arr[index].name << "?\nNUM HOURS: ";
	cin >> arr[index].cost.care_hours; // inputs care hours
	cout << "What is the cost per hour for caring for the " << arr[index].name << "?\nCOST PER HOUR: ";
	cin >> arr[index].cost.per_hour_cost; //inputs per hour cost
	cout << "How much money do you spend on food for the  " << arr[index].name << "?\nFOOD COST: ";
	cin >> arr[index].cost.weekly_feed_cost; //inputs weekly feed cost
	cout << "How much money do you spend on grooming and medical supplies for the  " 
		<< arr[index].name << "?\nSUPPLY COST: ";
	cin >> arr[index].cost.weekly_supplies_cost; //inputs supplies cost
}

//function displays Main Menu of program
void displayMainMenu()
{
	cout << "\n\n";
	cout << "What would you like to do?\n";
	cout << "\t1.  Enter some Dinosaurs\n";
	cout << "\t2.  Delete a Dinosaur\n";
	cout << "\t3.  List/Print Dinosaurs\n";
	cout << "\t4.  Print Statistics on Dinosaur Cost\n";
	cout << "\t5.  End Program\n";
	cout << "Enter 1, 2, 3, 4 or 5.\n";
}

// function readsDinosaurs from File
int loadDinosaursFromFile(Dinosaur arr[], int numOfDinosaurs)
{
	// Inputs File Name
	string fileName;
	cout << "\n\n";
	cout << "What is the name of the file with your list of Dinosaurs? (ex: fileName.txt)\nFILENAME: ";
	cin >> fileName;

	// Opens File for reading data
	fstream f(fileName, ios::in);

	// if file does not exist
	if (!f.good())
	{
		cout << "File not found. Returning to Main Menu\n";
		f.close();
		return numOfDinosaurs;
	}
	
	// if file exists
	int count = 0;
	Dinosaur d;
	// reads until end of file
	while (!f.eof())
	{
		string str;
		getline(f, d.name, '#'); // reads Name
		getline(f, d.description, '#'); //reads Description

		getline(f, str, '#');
		d.average_length = convertToFloat(str); //length

		getline(f, str, '#');
		d.average_height = convertToFloat(str);// height

		getline(f, d.location, '#');// location

		getline(f, str, '#');
		d.is_dangerous = convertToFloat(str);//is dangerous

		getline(f, str, '#');
		d.cost.care_hours = convertToFloat(str); // care hours

		getline(f, str, '#');
		d.cost.per_hour_cost = convertToFloat(str); // per hour cost

		getline(f, str, '#');
		d.cost.weekly_feed_cost = convertToFloat(str); // food cost

		getline(f, str, '#');
		d.cost.weekly_supplies_cost = convertToFloat(str); // supplies cost

		// adds Dinosaur to array
		arr[numOfDinosaurs] = d;
		numOfDinosaurs++;
		count++;

		// if limit is reached
		if (numOfDinosaurs == 100)
		{
			cout << count << " Dinosaur(s) added to zoo from " << fileName << "\n";
			cout << "Zoo is at full capacity. Not able to add Dinosaurs\n";
			f.close();
			return numOfDinosaurs;
		}
	}
	//closes file and returns new number of dinosaurs
	f.close();
	cout << "\n\nAll Dinosaurs from " << fileName << " have been added to program\n.";
	return numOfDinosaurs;
}

// Function Inputs Dinosaurs Manually from User
int inputDinosaursManually(Dinosaur arr[], int numofDinosaurs)
{
	char choice;
	do
	{
		// if zoo is full
		if (numofDinosaurs == 100)
		{
			cout << "Zoo is at full capacity. Not able to add more Dinosaurs\n";
			break;
		}
		// inputs dinosaurs
		inputDinosaur(arr, numofDinosaurs);
		numofDinosaurs++;
		//checks if user want to input another dinosaur
		cout << "\n\nDo You want to add another dinosaur? (y/n)\nCHOICE: ";
		cin >> choice;
	} while (choice != 'N' && choice != 'n');
	return numofDinosaurs;

}

// function adds new dinosaurs to system
int enterDinosaurs(Dinosaur arr[], int numOfDinosaurs)
{
	// zoo is full
	if (numOfDinosaurs == 100)
	{
		cout << "Zoo is at full capacity. Not able to add Dinosaurs\n";
		return numOfDinosaurs;
	}

	int choice;
	while (true)
	{
		//displays mene
		cout << "\n\n";
		cout << "What would you like to do?\n";
		cout << "\t1.  Load My Dinosaurs from file\n";
		cout << "\t2.  Enter one Dinosaur Manually\n";

		cout << "CHOICE: ";
		cin >> choice;

		// selects choice
		switch (choice)
		{
		case 1:
			//reads from file
			return loadDinosaursFromFile(arr, numOfDinosaurs);
			break;
		case 2: 
			// inputs manually
			return inputDinosaursManually(arr, numOfDinosaurs);
			break;
		default:
			cout << "You didn't entered correct choice. Try Again\n";
			break;
		}
	} 
}

// function shows dinosaurs on screen
void showDinosaursOnScree(Dinosaur arr[], int numOfDinosaurs)
{
	// if zoo is empty
	if (numOfDinosaurs == 0)
	{
		cout << "\nNo Dinosaurs in Zoo\n!";
		return;
	}
	cout << "----------------------------------------------------------------\n";
	//displays dinosaurs
	for (int i = 0; i < numOfDinosaurs; i++)
	{
		cout << "Dinosaur " << i + 1 << ":\n";
		cout << displayDinosaur(arr[i]) << "\n";
	}
}

// function displays Dinosaurs
void displayDinosaurs(Dinosaur arr[], int numOfDinosaurs)
{
	int choice;
	while (true)
	{
		//displays Menu
		cout << "\n\n";
		cout << "What would you like to do?\n";
		cout << "\t1.  Print Dinosaurs to screen\n";
		cout << "\t2.  Print Dinosaurs to a File\n";

		cout << "CHOICE: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			// displays on screen
			showDinosaursOnScree(arr, numOfDinosaurs);
			return;
			break;
		case 2:
			//prints to file
			printDinosaaurstoFile(arr, numOfDinosaurs);
			return;
			break;
		default:
			cout << "You didn't entered correct choice. Try Again\n";
			break;
		}
	}

}

//Function Prints Dinosaurs to File
void printDinosaaurstoFile(Dinosaur arr[], int numOfDinosaurs)
{
	//if zoo is empty
	if (numOfDinosaurs == 0)
	{
		cout << "\nNo Dinosaurs in Zoo\n!";
		return;
	}
	//inputs file
	string fileName;
	cout << "what is the name of the file that they wish to print the Dinosaurs to\nFILENAME: ";
	cin>>fileName;
	//opens file
	fstream f(fileName, ios::out);
	//writes to file
	for (int i = 0; i < numOfDinosaurs; i++)
	{
		f << "Dinosaur " << i + 1 << ":\n";
		f << displayDinosaur(arr[i]) << "\n";
	}
	cout << "Your Dinosaurs have been entered to " << fileName << "\n";
	f.close();
}

// function Prints Stats for dinosaurs
void displayStats(Dinosaur arr[], int numOfDinosaurs)
{
	//zoo empty
	if (numOfDinosaurs == 0)
	{
		cout << "\nNo Dinosaurs in Zoo\n!";
		return;
	}
	cout << "\n\nCOST OF EACH DINOSAUR FOR ONE WEEK\n\n";
	cout << "DINOSAUR\t\tCOST\n";
	float total = 0.0f;
	for (int i = 0; i < numOfDinosaurs; i++)
	{
		//calculates stats
		total += calculteWeeklyCost(arr[i]);
		//displays stats
		cout << arr[i].name << "\t\t$" << calculteWeeklyCost(arr[i]) << "\n";
	}
	cout << "---------------------------------------------------\n";
	cout << "Total Cost\t\t$" << total << "\n";
}

//function checks an moves elements of array 
bool moveArrayElements(Dinosaur arr[],int numOfDinosaurs, string name)
{
	int index = -1;
	for (int i = 0; i < numOfDinosaurs; i++)
	{
		if (arr[i].name == name)
			index = i;
	}
	// if dinosaur not found
	if (index == -1)
		return false;
	//moves elements
	for (int i = index; i <= numOfDinosaurs - 1; i++)
		arr[i] = arr[i + 1];
	return true;
}

// Function deletes a dinosaur from array
int deleteDinosaur(Dinosaur arr[], int numOfDinosaurs)
{
	// zoo is empty
	if (numOfDinosaurs == 0)
	{
		cout << "\nNo Dinosaurs in Zoo\n!";
		return numOfDinosaurs;
	}
	//displays dinosaurs' names
	cout << "The following is a list of all the Dinosaurs you take care of:\n";
	for (int i = 0; i < numOfDinosaurs; i++)
		cout << arr[i].name << "\n";

	//inputs name
	string name;
	cin.ignore();
	cout << "\n\nWhat Dinosaur do you wish to remove?\nDINOSAUR NAME:";
	getline(cin, name);
	//deletes dinosaurs if foind
	if (moveArrayElements(arr, numOfDinosaurs, name))
	{
		cout << "You have removed " << name << "\n";
		return numOfDinosaurs - 1;
	}
	else
	{
		cout << name << " not found.\n";
		return numOfDinosaurs;
	}
}