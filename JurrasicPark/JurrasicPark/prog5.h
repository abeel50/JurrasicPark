#pragma once
#ifndef PROG5_H
#define PROG5_H

#include<string>

using namespace std;

// structure Cost
typedef struct
{
	float care_hours;
	float per_hour_cost;
	float weekly_feed_cost;
	float weekly_supplies_cost;
}Cost;

string displayCost(Cost c);

// Structure Dinosaur
typedef struct
{
	string name;
	string description;
	float average_length;
	float average_height;
	string location;
	bool is_dangerous;
	Cost cost;
}Dinosaur;

//Dinosaur's Function
string displayDinosaur(Dinosaur);
void inputDinosaur(Dinosaur [] ,int);
float calculteWeeklyCost(Dinosaur);

float convertToFloat(string s);
void displayMainMenu();

// input Dinosaurs Functions
int enterDinosaurs(Dinosaur[], int);
int loadDinosaursFromFile(Dinosaur[], int);
int inputDinosaursManually(Dinosaur[], int);

// Print Dinosaurs Functions
void displayDinosaurs(Dinosaur[], int);
void showDinosaursOnScree(Dinosaur[], int);
void printDinosaaurstoFile(Dinosaur[], int);

// Print stats Function
void displayStats(Dinosaur[], int);

// function deletes a dinosaur
int deleteDinosaur(Dinosaur[], int);
bool moveArrayElements(Dinosaur[], int, string);
#endif