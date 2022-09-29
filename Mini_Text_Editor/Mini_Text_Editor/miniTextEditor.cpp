#include "miniTextEditor.h"
using namespace std;


//void miniTextEditor::add()
//{
//	line l;
//
//	cout << "Enter Line Number" << endl;
//	cin >> l.number;
//	int val = l.number - lines.size();
//	if (val > 1)
//	{
//		char answer;
//		cout << "number is so far \n";
//		cout << "are you want to add ?(n/y)" << endl;
//		cin >> answer;
//		if (answer == 'y')
//			add();
//	}
//
//	else if (val <= 0)
//	{
//		char answer;
//		cout << "number is exist \n";
//		cout << "are you want to add ?(n/y)" << endl;
//		cin >> answer;
//		if (answer == 'y')
//			add();
//	}
//	else
//	{
//		add2();
//		cout << "Line added successfully \n" << endl;
//	}
//
//}


void miniTextEditor::add(bool voice)
{
	operation o;
	string text;

	cout << "Enter Your Text :" << endl;
	Voice_Func("Enter Your Text", voice);

	cin.ignore();
	getline(cin, text);

	cout << "Text added successfully \n" << endl;
	Voice_Func("Text added successfully ", voice);

	size++;
	lines.insert({ size , text });
	dataToFile();
	//for undo operation:
	o.ope = "add";
	o.pos_main = size;
	op.push(o);

}

void miniTextEditor::delete_Line(bool voice)
{
	if (!lines.empty()) {
		operation o;
		line l;
		o.ope = "delete";

		cout << "enter number of Line" << endl;
		Voice_Func("enter number of Line", voice);

		cin >> l.number;
		while (cin.fail())
		{
			cout << "you should enter number not text" << endl;
			Voice_Func("you should enter number not text", voice);

			cin.clear();
			cin.ignore(256, '\n');

			cout << "enter number of Line" << endl;
			Voice_Func("enter number of Line", voice);

			cin >> l.number;
		}
		if (l.number <= size && l.number > 0)
		{
			o.pos_main = l.number;
			auto t = lines.find(l.number);
			//for undo operation:
			l.text = t->second;
			del.push(l);
			op.push(o);

			lines.erase(l.number);
			map<int, string> temp;
			map<int, string> ::iterator it;
			size--;
			int counter = 1;
			for (it = lines.begin(); it != lines.end(); it++)
			{
				temp.insert({ counter , it->second });
				counter++;
			}

			lines.clear();
			lines = temp;
			temp.clear();
			dataToFile();

			cout << "Line deleted successfully \n" << endl;
			Voice_Func("Line deleted successfully", voice);
		}
		else
		{
			cout << "line not exist...try again" << endl;
			Voice_Func("line not exist...try again", voice);
		}
	}
}

void miniTextEditor::delete_file(char NoteName[40], bool voice) {
	int status;
	status = remove(NoteName);
	if (status == 0) {

		cout << "\nNote Is Deleted!";
		Voice_Func("Note Is Deleted!", voice);

	}

	cout << endl;

}

void miniTextEditor::Delete_saved_file(char notename[30]) {

	ifstream save_files("saved_files.txt");
	string line;
	ofstream temp;
	temp.open("temp.txt");
	while (getline(save_files, line)) {
		if (line != notename)
		{
			temp << line << endl;
		}
	}
	temp.close();
	save_files.close();

	remove("saved_files.txt");
	int d = rename("temp.txt", "saved_files.txt");

}

void miniTextEditor::combine_two_files(char note1[40], char note2[40], char newnote[40]) {

	ifstream n1(note1);
	ifstream n2(note2);
	string line;
	ofstream nw;
	nw.open(newnote);
	int i = 1;
	while (n1.good())
	{
		getline(n1, line);
		int x = 0;
		if (line == " ") {
			break;
		}

		if (line.length() == 0)
		{
			continue;
		}
		combine.insert({ i, line });
		i++;
	}
	while (n2.good())
	{
		getline(n2, line);
		int x = 0;
		if (line == " ") {
			break;
		}

		if (line.length() == 0)
		{
			continue;
		}
		combine.insert({ i,line });
		i++;
	}
	map<int, string> ::iterator it;

	for (it = combine.begin(); it != combine.end(); it++)
	{
		nw << it->first << "-" << it->second << endl;
	}

}

void miniTextEditor::saved_files_from_vector()
{
	ofstream save_files("saved_files.txt");
	if (save_files.is_open()) {
		for (int i = 0; i < file_name.size(); i++) {
			save_files << file_name[i] << endl;
		}
	}
	save_files.close();
}

void miniTextEditor::assign_files_to_vector()
{
	string file_;
	ifstream read_files("saved_files.txt");
	if (read_files.is_open())
	{
		while (!read_files.eof())
		{
			getline(read_files, file_);
			if (file_ != "")
				file_name.push_back(file_);

		}
	}
	read_files.close();
}

void miniTextEditor::updateMap(bool voice)
{
	line n;
	operation o;
	int num;
	string txt;
	o.ope = "update";

	cout << "enter line number:\n";
	Voice_Func("enter line number", voice);

	cin >> num;
	while (cin.fail())
	{
		cout << "you should enter number not text" << endl;
		Voice_Func("you should enter number not text", voice);

		cin.clear();
		cin.ignore(256, '\n');

		cout << "enter line number:\n";
		Voice_Func("enter line number", voice);

		cin >> num;
	}
	if (num <= size && num > 0)
	{
		o.pos_main = num;
		n.number = num;

		cout << "enter Text:\n";
		Voice_Func("enter Text", voice);

		cin.ignore();
		getline(cin, txt);

		auto it = lines.find(num);
		n.text = it->second;
		del.push(n);
		op.push(o);
		it->second = txt;
		string x = to_string(num);
		dataToFile();

		cout << "Line Updated successfully \n" << endl;
		Voice_Func("Line Updated successfully", voice);

	}
	else
	{
		cout << "line not exist ..try again" << endl;
		Voice_Func("line not exist ..try again", voice);
	}
}

void miniTextEditor::FindAndReplace(string SearchStr, string replaceStr, bool voice)
{
	operation o;
	o.ope = "replace";
	bool check = false;
	bool reUndo = false;

	for (auto it = lines.begin(); it != lines.end(); it++)
	{
		int pos = it->second.find(SearchStr);
		line n;
		n.number = it->first;
		n.text = it->second;
		while (pos != string::npos)
		{
			it->second.replace(pos, SearchStr.size(), replaceStr);

			pos = it->second.find(SearchStr, pos + replaceStr.size());
			check = true;
			reUndo = true;
		}
		//for undo operaion:
		if (reUndo == true)
		{
			del.push(n);
			o.re_count++;
			reUndo = false;
		}

	}

	if (check == true)
	{
		cout << "done" << endl;
		Voice_Func("done", voice);
		dataToFile();
		op.push(o);
	}
	else
	{
		cout << "the sentance is not exist in the note " << endl;
		Voice_Func("the sentance is not exist in the note ", voice);

	}

}

void miniTextEditor::show(bool voice)
{
	map<int, string> ::iterator it;

	for (it = lines.begin(); it != lines.end(); it++)
	{
		cout << it->first << "-" << it->second << endl;
		Voice_Func(it->second, voice);
	}
}

void miniTextEditor::assignData()
{
	if (!lines.empty())
	{
		lines.clear();
		size = 0;
	}
	string line;
	char del = '-';
	// read file line by line and store in temp string
	// call fun splite to split the line numder and store in vector and text store in vector
	ifstream minitext(found_file, std::fstream::in | std::fstream::out | std::fstream::app);
	if (minitext.is_open())
	{
		while (!minitext.eof())
		{
			getline(minitext, line);
			splite(line, del);

		}
	}


}

void miniTextEditor::splite(string str, char del)
{
	string temp = "";
	int tempnumder = 0;
	string temptext = "";
	for (int i = 0; i < (int)str.size(); i++)
	{
		if (str[i] != del)
		{
			temp += str[i];

			tempnumder = atoi(&str[0]);
			if (i > 1)
				temptext += str[i];
		}
		else
		{
			temp = "";
		}

	}
	if (tempnumder != 0)
	{
		lines.insert({ tempnumder, temptext });
		size++;

	}

}

string miniTextEditor::GetLine(int number_of_line, bool voice)
{
	map<int, string>::iterator it;
	int counter = 0;

	for (it = lines.begin(); it != lines.end(); it++) {

		if (it->first == number_of_line) {
			counter++;
			Voice_Func(it->second, voice);
			return it->second;
			break;
		}
	}
	if (counter == 0) {

		Voice_Func("Number not founded", voice);
		return "Number not founded";

	}


}

void miniTextEditor::Find(string text, bool voice)
{
	while (true)
	{
		bool flag = false;
		for (auto it = lines.begin(); it != lines.end(); it++) {
			if (it->second.find(text) != string::npos)
			{
				cout << "Text at Line : " << it->first << endl;
				Voice_Func("Text at Line", voice);
				Voice_Func(to_string(it->first), voice);
				flag = true;
			}
		}
		if (flag == true) {
			break;
		}
		else {
			cout << "Text Not Founded" << endl;
			Voice_Func("Text Not Founded", voice);
			break;
		}
	}

}

void miniTextEditor::dataToFile()
{
	line n;
	fstream miniText;
	miniText.open(found_file, std::fstream::in | std::fstream::out | std::fstream::app);
	clear();
	auto it = lines.find(1);
	for (int i = 1; i <= size; i++)
	{
		n.number = it->first;
		n.text = it->second;
		miniText << it->first << '-' << it->second << '\n';
		it++;
	}
	miniText.close();
}

void miniTextEditor::clear()
{
	ofstream file(found_file);
	file << "";
}

void miniTextEditor::clearAll()
{
	auto it = lines.end();
	operation o;
	o.ope = "clear";
	//for undo operation:
	for (int i = 0; i < size; i++)
	{
		if (!lines.empty())
		{
			it--;
			line n;
			n.number = it->first;
			n.text = it->second;
			del.push(n);
			o.re_count++;
		}
	}
	//for clear :
	op.push(o);
	ofstream file(found_file);
	file << "";
	lines.clear();
	size = 0;
}

void miniTextEditor::undo()
{
	if (!op.empty())
	{
		operation p = op.top();
		if (p.ope == "add")
		{
			lines.erase(p.pos_main);
			size--;
			op.pop();
			dataToFile();
		}

		else if (p.ope == "delete")
		{
			if (p.pos_main == size + 1)
			{
				size++;
				lines.insert({ size , del.top().text });
				dataToFile();
			}
			else
			{
				map<int, string> temp;
				auto it = lines.begin();

				for (int i = 1; i <= p.pos_main; i++)
				{
					if (i == p.pos_main)
					{
						temp.insert({ p.pos_main , del.top().text });
					}
					else
					{
						temp.insert({ i , it->second });
					}
					it++;
				}
				size++;
				it = lines.find(p.pos_main);

				for (int i = p.pos_main; i <= lines.size(); i++)
				{
					temp.insert({ i + 1 , it->second });
					it++;
				}

				lines.clear();
				lines = temp;
				temp.clear();
			}
			dataToFile();
			op.pop();
			del.pop();
		}

		else if (p.ope == "update")
		{
			auto it = lines.find(p.pos_main);
			it->second = del.top().text;
			dataToFile();
			op.pop();
			del.pop();
		}

		else if (p.ope == "replace")
		{
			for (int i = 0; i < p.re_count; i++)
			{
				auto it = lines.find(del.top().number);
				it->second = del.top().text;
				del.pop();

			}
			op.pop();
			dataToFile();
		}

		else if (p.ope == "insert")
		{
			lines.erase(p.pos_main);
			map<int, string> temp;
			map<int, string> ::iterator it;
			size--;
			int counter = 1;
			for (it = lines.begin(); it != lines.end(); it++)
			{
				temp.insert({ counter , it->second });
				counter++;
			}

			lines.clear();
			lines = temp;
			op.pop();
			temp.clear();
			dataToFile();
		}

		else if (p.ope == "clear")
		{
			for (int i = 0; i < p.re_count; i++)
			{
				lines.insert({ del.top().number , del.top().text });
				del.pop();
				size++;

			}
			op.pop();
			dataToFile();
		}

		else if (p.ope == "multi")
		{
			for (int i = 0; i < p.re_count; i++)
			{
				lines.erase(size);
				size--;
			}
			op.pop();
			dataToFile();
		}
	}
	else
	{
		cout << "there is no operation to undo it " << endl;
	}
}

void miniTextEditor::insertATm(bool voice)
{
	int num;
	string txt;
	cout << "enter the number of line : " << endl;
	Voice_Func("enter the number of line", voice);

	cin >> num;
	while (cin.fail())
	{
		cout << "you should enter number not text" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cout << "enter the number of line : " << endl;
		Voice_Func("enter the number of line", voice);
		cin >> num;
	}
	if (num <= size && num > 0)
	{
		cout << "enter the text : " << endl;
		Voice_Func("enter the text", voice);

		cin.ignore();
		getline(cin, txt);
		insertAT(num, txt);
		dataToFile();
	}
	else if (num == size + 1)
	{
		add(voice);
	}
	else
	{
		cout << "line does not exist try again..." << endl;
		Voice_Func("line does not exist try again", voice);

		insertATm(voice);
	}

}

void miniTextEditor::insertAT(int key, string txt)
{
	map<int, string> temp;
	//for undo operation:
	operation o;
	o.ope = "insert";
	o.pos_main = key;
	op.push(o);
	//for insert at:
	auto it = lines.begin();

	for (int i = 1; i <= key; i++)
	{
		if (i == key)
		{
			temp.insert({ key , txt });
		}
		else
		{
			temp.insert({ i , it->second });
		}
		it++;
	}
	size++;
	it = lines.find(key);

	for (int i = key; i <= lines.size(); i++)
	{
		temp.insert({ i + 1 , it->second });
		it++;
	}

	lines.clear();
	lines = temp;
	temp.clear();

}

void miniTextEditor::add_multiple_lines(bool voice)
{

	int count;
	string text;
	cout << "Enter Your Text:\n";
	Voice_Func("Enter Your Text", voice);

	cin.ignore();
	getline(cin, text);

	cout << "Enter How Many Times You Wanna To repeat this line:";
	Voice_Func("Enter How Many Times You Wanna To repeat this line", voice);

	cin >> count;
	while (cin.fail())
	{
		cout << "you should enter number not text" << endl;
		Voice_Func("you should enter number not text", voice);

		cin.clear();
		cin.ignore(256, '\n');

		cout << "Enter How Many Times You Wanna To repeat this line:";
		Voice_Func("Enter How Many Times You Wanna To repeat this line", voice);
		cin >> count;
	}
	if (count > 0)
	{
		for (int i = 0; i < count; i++)
		{
			size++;
			lines.insert({ size, text });

		}
		//for undo operaion:
		operation o;
		o.ope = "multi";
		o.re_count = count;
		op.push(o);
		dataToFile();

	}
	else
	{
		cout << "please enter positive number...try again" << endl;
		Voice_Func("please enter positive number...try again", voice);

		add_multiple_lines(voice);
	}
}

void miniTextEditor::Voice_Func(string input_phrase, bool voice) {
	if (voice) {
		string command = "espeak \"" + input_phrase + "\"";
		const char* char_command = command.c_str();
		system(char_command);
	}
}
