#include <iostream>
#include <algorithm>
#include<stdlib.h>
#include"miniTextEditor.h"
using namespace std;

int choice_operation;
bool answer_file = false;
miniTextEditor e;

void Voice_Func(string input_phrase, bool voice);
void Welcome_Func();
void operation_Func(bool voice);
void file_choice(bool voice);
void file();


int main()
{

	Welcome_Func();

	return 0;
}


void Welcome_Func() {

	cout << "\t \t \t----------------------------Welcome to Mini Text Editor----------------------------\n\n";
	/*  " doing function for these sentences for reusability so we can call it to any sentence "
	string welcome = "Welcome";
	string welcome_command = "espeak \"" + welcome + "\"";
	const char* char_welcome_command = welcome_command.c_str();
	system(char_welcome_command);
	*/
	Voice_Func("Welcome to Mini Text Editor", true);

	cout << "Hello, how are you?";
	Voice_Func("Hello, how are you?", true);
	cout << " We hope you are well...." << endl;
	Voice_Func("We hope you are well....", true);

	cout << "if you want the voice assistant enter Y for Yes otherwise enter N for No " << endl;
	Voice_Func("if you want the voice assistant enter Y for YES ", true);
	Voice_Func("otherwise enter N for No ", true);

	string choice_voice;



	while (true) {
		cin >> choice_voice;

		if (choice_voice == "y" || choice_voice == "Y") {
			file_choice(true);
			file();
			operation_Func(true);
			break;
		}
		else if (choice_voice == "n" || choice_voice == "N") {
			file_choice(false);
			file();
			operation_Func(false);
			break;
		}
		else {
			cout << "please only enter y or n " << endl;
			Voice_Func("please only enter y or n ", true);
			continue;
		}
	}
}
void file() {
	ifstream MyFile;
	MyFile.open(e.found_file);
	if (MyFile) {
		e.assignData();
	}
	else {
		ofstream MyFile;
		MyFile.open(e.found_file);

	}
	MyFile.close();
}

void Voice_Func(string input_phrase, bool voice) {
	if (voice) {
		string command = "espeak \"" + input_phrase + "\"";
		const char* char_command = command.c_str();
		system(char_command);
	}
}

void file_choice(bool voice) {
	e.assign_files_to_vector();
	cout << "Your notes:" << endl;
	Voice_Func("Your notes:", voice);
	for (int i = 0; i < e.file_name.size(); i++) {
		cout << i + 1 << " - " << e.file_name[i] << endl;
		Voice_Func(e.file_name[i], voice);
	}
	while (true)
	{
		int num_oper;
		int pos = 0;

		cout << "\npress 1 to choose one of your notes";
		Voice_Func("press 1 to choose one of your notes", voice);

		cout << "\npress 2 to add new note";
		Voice_Func("press 2 to add new note", voice);

		cout << "\npress 3 to delete note";
		Voice_Func("press 3 to delete note", voice);

		cout << " \npress 4 to combine 2 Notes ";
		Voice_Func("press 4 to combine 2 Notes", voice);

		cout << "\npress 5 to Show Own Notes ";
		Voice_Func("press 5 to Show Own Notes", voice);

		cout << "\npress 6 to skip this operations";
		Voice_Func("press 6 to skip this operations", voice);

		cout << "\nEnter your choice: ";
		Voice_Func("Enter your choice", voice);

		cin >> num_oper;
		while (cin.fail())
		{
			cout << "you should enter number not text" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "\nEnter your choice: ";
			Voice_Func("Enter your choice", voice);
			cin >> num_oper;
		}
		if (num_oper == 1) {
			int numberoffile;
			bool file_found = false;
			cout << "enter note's number " << endl;
			Voice_Func("enter note's number", voice);
			cin >> numberoffile;
			while (cin.fail())
			{
				cout << "you should enter number not text" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cout << "enter note's number " << endl;
				Voice_Func("enter note's number", voice);
				cin >> numberoffile;
			}
			for (int i = 0; i < e.file_name.size(); i++)
			{
				if (i == numberoffile - 1) {
					e.found_file = e.file_name[i];
					file_found = true;
					break;
				}

			}
			if (file_found == false)
			{
				cout << "note not found " << endl;
				Voice_Func("note not found ", voice);
			}

			break;
		}

		else if (num_oper == 2) {
			string file_n;
			cout << "enter the new name" << endl;
			Voice_Func("enter the new name", voice);
			cin >> file_n;

			if (find(e.file_name.begin(), e.file_name.end(), (file_n + ".txt")) != e.file_name.end()) {
				e.found_file = file_n + "1" + ".txt";
				e.file_name.push_back(e.found_file);
			}
			else {
				e.file_name.push_back(file_n + ".txt");
				e.found_file = file_n + ".txt";
			}
			answer_file = true;
			break;
		}

		else if (num_oper == 3) {
			char NoteName[40];
			cout << "Enter the Name of Note: ";
			Voice_Func("Enter the Name of Note: ", voice);
			cin >> NoteName;
			bool check = false;

			for (int i = 0; i < e.file_name.size(); i++) {
				if (e.file_name[i] == NoteName)
				{
					check = true;
					pos = i;
				}
			}
			if (check == false)
			{
				cout << "Note Not Found!\n";
				Voice_Func("Note Not Found", voice);
			}
			if (check == true)
			{
				e.delete_file(NoteName, voice);
				e.Delete_saved_file(NoteName);
				e.file_name.erase(e.file_name.begin() + pos);
			}
			e.saved_files_from_vector();

		}

		else if (num_oper == 4)
		{
			char note1[40];
			char note2[40];
			bool check = false;
			while (check == false)
			{
				cout << "enter name of first note:" << endl;
				Voice_Func("enter name of first note", voice);
				cin >> note1;
				for (int i = 0; i < e.file_name.size(); i++) {
					if (e.file_name[i] == note1)
					{
						check = true;
					}
				}
				if (check == false)
				{
					cout << "Note Not Found!\n";
					Voice_Func("Note Not Found", voice);
				}
			}
			bool check2 = false;
			while (check2 == false)
			{
				cout << "enter name of Second note:" << endl;
				Voice_Func("enter name of Second note", voice);
				cin >> note2;
				for (int i = 0; i < e.file_name.size(); i++) {
					if (e.file_name[i] == note2)
					{
						check2 = true;
					}
				}
				if (check2 == false)
				{
					cout << "Note Not Found!\n";
					Voice_Func("Note Not Found", voice);
				}
			}

			string file_n;
			cout << "enter name of new Note" << endl;
			Voice_Func("enter name of new Note", voice);
			cin >> file_n;

			string x;
			if (find(e.file_name.begin(), e.file_name.end(), (file_n + ".txt")) != e.file_name.end()) {
				e.found_file = file_n + "1" + ".txt";
				e.file_name.push_back(e.found_file);
				x = e.found_file;
			}
			else {
				e.file_name.push_back(file_n + ".txt");
				e.found_file = file_n + ".txt";
				x = e.found_file;
			}
			e.saved_files_from_vector();

			char your_note[40];
			strcpy(your_note, x.c_str());
			e.combine_two_files(note1, note2, your_note);

		}

		else if (num_oper == 5)
		{
			cout << "Your notes:" << endl;
			Voice_Func("Your notes", voice);
			for (int i = 0; i < e.file_name.size(); i++) {
				cout << i + 1 << " - " << e.file_name[i] << endl;
				Voice_Func(e.file_name[i], voice);
			}
		}

		else if (num_oper == 6)
		{
			cout << "Your default file is " + e.file_name[0] << endl;
			Voice_Func("Your default file is " + e.file_name[0], voice);
			e.found_file = e.file_name[0];

			break;
		}

		else {
			cout << "Wrong choice..." << endl;
			Voice_Func("Wrong choice", voice);
		}
	}
	e.saved_files_from_vector();
}

void operation_Func(bool voice) {
	int choice;
	system("cls");
	while (true)
	{

		cout << endl;
		cout << "\t\t\t\t\t\t\t********" << endl;
		cout << "\t\t\t\t\t\t\t* MENU *" << endl;
		cout << "\t\t\t\t\t\t\t********" << endl;
		cout << endl;
		Voice_Func("MENU", voice);
		cout << "1- To Add ";
		Voice_Func(" 1 To Add ", voice);

		cout << "\t\t\t\t2- To delete Line ";
		Voice_Func("2 To delete Line ", voice);

		cout << "\t\t\t\t3 - To Update Line " << endl;
		Voice_Func("3 To Update Line ", voice);

		cout << "4- To Replace ";
		Voice_Func("4 To Replace", voice);

		cout << "\t\t\t\t5- To Show ";
		Voice_Func("5 To Show ", voice);

		cout << "\t\t\t\t\t6- To get line" << endl;
		Voice_Func("6 To get line", voice);

		cout << "7- To clear all";
		Voice_Func("7 To clear all", voice);

		cout << "\t\t\t\t8- To find text ";
		Voice_Func("8 To find text ", voice);

		cout << "\t\t\t\t9- To undo the last operation " << endl;
		Voice_Func("9 To undo the last operation", voice);

		cout << "10- To Insert At position ";
		Voice_Func("10 To Insert At position", voice);

		cout << "\t\t11- To add multiple lines at the end";
		Voice_Func("11 To add multiple lines at the end ", voice);

		cout << "\t\t12- To Exit" << endl;
		Voice_Func("12 To Exit", voice);

		cout << "\nEnter your choice: ";
		Voice_Func("Enter your choice", voice);

		cin >> choice;
		while (cin.fail())
		{
			cout << "you should enter number not text" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "\nEnter your choice: ";
			Voice_Func("Enter your choice", voice);
			cin >> choice;
		}
		if (choice == 1)
		{
			e.add(voice);
		}

		else if (choice == 2)
		{
			e.delete_Line(voice);
		}

		else if (choice == 3)
		{
			e.updateMap(voice);
		}

		else if (choice == 4)
		{
			string searchStr, replaceStr;
			cout << "enter the sentence you want to be replaced" << endl;
			Voice_Func("enter the sentence you want to be replaced", voice);

			cin.ignore();
			getline(cin, searchStr);

			cout << "enter the sentence you want to add" << endl;
			Voice_Func("enter the sentence you want to add", voice);

			getline(cin, replaceStr);

			e.FindAndReplace(searchStr, replaceStr, voice);
		}

		else if (choice == 5)
		{
			cout << "note Content:" << endl;
			Voice_Func("note Content:", voice);
			e.show(voice);
		}

		else if (choice == 6)
		{
			int order;
			cout << "enter the number of line" << endl;
			Voice_Func("enter the number of line", voice);

			cin >> order;
			while (cin.fail())
			{
				cout << "you should enter number not text" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cout << "enter the number of line" << endl;
				Voice_Func("enter the number of line", voice);
				cin >> order;
			}
			cout << e.GetLine(order, voice) << endl;

		}

		else if (choice == 7)
		{
			e.clearAll();
		}

		else if (choice == 8)
		{
			string n;
			cout << "enter the text :" << endl;
			Voice_Func("enter the text :", voice);
			cin.ignore();
			getline(cin, n);
			e.Find(n, voice);
		}

		else if (choice == 9)
		{
			e.undo();
		}

		else if (choice == 10)
		{
			e.insertATm(voice);
		}

		else if (choice == 11)
		{
			e.add_multiple_lines(voice);
		}

		else if (choice == 12)
		{
			char answer_delete2 = 'n';
			if (answer_file) {
				cout << "Do You Wanna To Save Your Note ?(y/n)\n";
				Voice_Func("Do You Wanna To Save Your Note ?", voice);
				cin >> answer_delete2;
				char xx = 'n';
				if (answer_delete2 == 'n' || answer_delete2 == 'N') {
					string x = e.file_name[e.file_name.size() - 1];
					char your_note[40];
					strcpy(your_note, x.c_str());

					e.delete_file(your_note, voice);
					e.Delete_saved_file(your_note);
				}
				else {
					cout << "Note Is Saved \n";
					Voice_Func("Note Is Saved", voice);
				}
				answer_file = false;
			}
			exit(0);
		}

		else {
			cout << "Wrong choice...." << endl;
			Voice_Func("Wrong choice", voice);
		}


	}
}

