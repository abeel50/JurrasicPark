#include"prog5.h"
#include<iostream>

// Main Function
int main()
{
	Dinosaur arr[100]; // Dinosaur's Array
	int num_of_dinosaurs = 0;  //Current number of dinosaurs
	int choice;
	do
	{
		// displays Menu
		displayMainMenu();
		// Inputs Choice
		cout << "CHOICE: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			num_of_dinosaurs = enterDinosaurs(arr, num_of_dinosaurs);
			break;
		case 2:
			num_of_dinosaurs = deleteDinosaur(arr, num_of_dinosaurs);
			break;
		case 3:
			displayDinosaurs(arr, num_of_dinosaurs);
			break;
		case 4:
			displayStats(arr, num_of_dinosaurs);
			break;
		case 5: 
			cout << "\nExiting Program\n";
			break;
		default:
			cout << "You didn't entered correct choice. Try Again\n";
			break;
		}
	} while (choice != 5);
	return 0;
}