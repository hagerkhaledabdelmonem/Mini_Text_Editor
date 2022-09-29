#pragma warning(disable : 4996)
#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include<stack>
#include<vector>
#include<map>

using namespace std;

class line
{
public:
	int number;
	string text;
};

struct operation {
	string ope = "nothing";
	int pos_main = 0;
	int re_count = 0;
};

class miniTextEditor
{
public:
	stack<operation> op;
	stack<line> del;
	map<int, string> lines;
	int size = 0;
	vector<string> file_name;
	string found_file;
	map<int, string> combine;

	void show(bool voice);
	void updateMap(bool voice);
	void FindAndReplace(string SearchStr, string replaceStr, bool voice);
	//void add();
	void add(bool voice);
	void delete_Line(bool voice);
	void saved_files_from_vector();
	void assign_files_to_vector();
	void assignData();
	string GetLine(int number_of_line, bool voice);
	void Find(string text, bool voice);
	void dataToFile();
	void clear();
	void clearAll();
	void undo();
	void insertATm(bool voice);
	void insertAT(int key, string txt);
	void splite(string str, char del);
	void delete_file(char NoteName[40], bool voice);
	void Delete_saved_file(char NoteName[30]);
	void combine_two_files(char note1[40], char note2[40], char newnote[40]);
	void add_multiple_lines(bool voice);
	void Voice_Func(string input_phrase, bool voice);

};

