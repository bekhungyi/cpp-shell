#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

struct s_data
{
    string id;
    float age;
    float math;
    float science;
    float malay;
};

string getFirstParameter(string str)
{
	int i = 0;
	string FirstParameter;
	do
	{
		FirstParameter = FirstParameter + str[i];
		i++;
	} while ((str[i] != ' ' && str[i] != '\0')); // ‘\0" indicates end of the string
												 // loop until the first space is found or the end of the string is reached
	return FirstParameter;
}

int wordCounter(string str)
{
	int count;
	int i;
	if (str.length() > 0)
		count = 1; // initial word count is 1

	for (i = 0; i < str.length() - 1; i++) // loop until one character before the end of the string so that
										   // if user key in an additional space at the end of the commandline, the number of parameter will not increment
	{
		if (str[i] == ' ' && str[i + 1] != ' ') // to make sure that when user input 2 spaces continuously,only 1 space is taken into account
			count++;							// if any space detected,word count is incremented
	}

	return count;
}

string trimStr(string str)
{
    string nstr;

    nstr = str.substr(0, str.find(","));
    return (nstr);
}

void printData(int cols, int rows, const vector<s_data *> data)
{
    for (int r = 0; r < rows; r++)
	{
        s_data line = *data[r];
        cout << "ID: " << line.id << " ";
        cout << "Age: " << line.age << " ";
        cout << "Math: " << line.math << " ";
        cout << "Science: " << line.science << " ";
        cout << "Malay: " << line.malay << " ";
        cout << endl;
    }
}

void printSum(int cols, int rows, const vector<s_data *> data)
{
    int sum = 0;

    for (int r = 0; r < rows; r++)
	{
        s_data line = *data[r];
        sum = sum + line.age;
    }
    cout << "Sum: " << sum << endl;
}

float trimNum(string str)
{
    float   nnum;

    str = str.substr(0, str.find(","));
    nnum = stof(str);
    return (nnum);
}

void    *initArr(int cols, int rows, vector<s_data> &data)
{
    for (int i = 0; i < rows; i++)
    {
        s_data temp;
        data.push_back(temp);
    }
    return (0);
}

int ft_load(string filename, int paramCount, int &cols, int &rows, vector<string> &titles, vector<string> &types, vector<s_data *> &data)
{
    ifstream file;
    file.open(filename);
    if (!file.is_open())
    {
        cout << "File not found!" << endl;
        return (0);
    }

    file >> cols;
    file >> rows;
    string str;
    for (int i = 0; i < cols; i++)
    {
        file >> str;
        titles.push_back(str);
    }
    for (int i = 0; i < cols; i++)
    {
        file >> str;
        types.push_back(str);
    }
    for (int r = 0; r < rows; r++)
    {
        s_data *line = new s_data;
        for (int c = 0; c < cols; c++)
        {
            string str;
            if (c == 0)
            {
                file >> str;
                str = trimStr(str);
                line->id = str;
                // cout << str << endl;
            }
            else if (c == 1)
            {
                file >> str;
                str = trimStr(str);
                line->age = stof(str);
                // cout << str << endl;
            }
            else if (c == 2)
            {
                file >> str;
                str = trimStr(str);
                line->math = stof(str);
                // cout << str << endl;
            }
            else if (c == 3)
            {
                file >> str;
                str = trimStr(str);
                line->science = stof(str);
                // cout << str << endl;
            }
            else if (c == 4)
            {
                file >> str;
                str = trimStr(str);
                line->malay = stof(str);
                // cout << str << endl;
            }
        }
        data.push_back(line);
    }
    file.close();
    return (1);
}

void    ft_store(string filename, int cols, int rows, const vector<s_data *> data)
{
    ofstream file;
    file.open(filename);
    if (!file.is_open())
    {
        cout << "File not found!" << endl;
        return ;
    }
    for (int r = 0; r < rows; r++)
    {
        s_data line = *data[r];
        file << line.id << ", ";
        file << line.age << ", ";
        file << line.math << ", ";
        file << line.science << ", ";
        file << line.malay << endl;
    }
    file.close();
}

void    ft_clone(string filename)
{
    string  file1, file2;
    string  line;

    file1 = getFirstParameter(filename);
    file2 = filename.substr(filename.find(" ") + 1, filename.length());

    ifstream inFile(file1);
    ofstream outFile(file2);
    if (inFile && outFile) {
  
        while (getline(inFile, line)) {
            outFile << line << "\n";
        }
        cout << "Copy Finished \n";
    }
    else {
        printf("Cannot read File");
    }
    inFile.close();
    outFile.close();
}

int main()
{
	int num_parameter;
	string command, commandLine;
	system("clear");

	const vector<tuple<int, string, int, string, string>> CommandList{
		make_tuple<>(1, "load", 2, "File is loaded.", "$ load filename.csv"),
		make_tuple<>(2, "store", 2, "Data is stored into the csv formatted file.", "$ store filename.csv"),
		make_tuple<>(3, "clone", 3, "Data is cloned from the source file to the destination file.", "$ clone file1.csv file2.csv "),
		make_tuple<>(4, "html", 2, "Data is store into the html formatted file.", "$ html filename.html "),
		make_tuple<>(5, "html", 3, "Data from a csv formatted file is converted to the html formatted file.", "$ html file1.csv file2.html "),
		make_tuple<>(6, "min", 1, "The names and minimum values of all column is shown", "$ min"),
		make_tuple<>(7, "min", 2, "The name and minimum value of entered column is shown", "$ min column"),
		make_tuple<>(8, "max", 1, "The names and maximum values of all column is shown", "$ max "),
		make_tuple<>(9, "max", 2, "The name and maximum value of the entered column is shown", "$ max column "),
		make_tuple<>(10, "median", 1, "The median for the number columns is shown", "$ median"),
		make_tuple<>(11, "median", 2, "The median for the entered column is shown", "$ median column"),
		make_tuple<>(12, "mean", 1, "The mean of all columns is shown", "$ mean"),
		make_tuple<>(13, "mean", 2, "The mean of entered column is shown", "$ mean column"),
		make_tuple<>(14, "variance", 1, "The variance of all columns is shown", "$ variance"),
		make_tuple<>(15, "variance", 2, "The variance of the entered column is shown", "$ variance column "),
		make_tuple<>(16, "stdv", 1, "The standard deviation of all columns is shown", "$ stdv"),
		make_tuple<>(17, "stdv", 2, "The standard deviation of entered column is shown", "$ stdv column"),
		make_tuple<>(18, "add", 3, "The column resulted from adding the two columns entered is displayed", "$ add column1 column2"),
		make_tuple<>(19, "sub", 3, "The column resulted from subtracting column 1 from column 2 is displayed", "$ sub column1 column2"),
		make_tuple<>(20, "corr", 3, "The correlation between column 1 and column 2 is computed using Pearson correlation", "$ corr column1 column2"),
		make_tuple<>(21, "regression", 2, "The linear regression line formula for selected column is computed", "$ regression column"),
		make_tuple<>(22, "show", 1, " The data is read from the file and shown.", "$ show"),
		make_tuple<>(23, "show", 2, "The specific column is shown.", "$ show column"),
		make_tuple<>(24, "titles", 1, "The titles of all the columns for the file is shown.", "$ titles"),
		make_tuple<>(25, "report", 1, "The report which shows all the statistics for all the columns is shown.", "$ report "),
		make_tuple<>(26, "rows", 1, "The number of rows loaded is displayed.", "$ rows"),
		make_tuple<>(27, "columns", 1, "The number of columns loaded is displayed.", "$ columns "),
		make_tuple<>(28, "vhisto", 2, "A text histogram for the column entered is shown.Y-axis will be the frequency of the data.", "$ vhisto column"),
		make_tuple<>(29, "hhisto", 2, "A histogram for the specific column is displayed. X-axis will be the frequency of the data", "$ hhisto column"),
		make_tuple<>(30, "sort", 2, "The column value is used to classify the data", "$ sort column"),
		make_tuple<>(31, "help", 1, "The commands available and the methods to use them is shown.", "$ help "),
		make_tuple<>(32, "man", 2, "The command entered and its function is displayed.", "$ man command "),
		make_tuple<>(33, "oddrows", 1, "The odd rows of data is shown.", "$ oddrows "),
		make_tuple<>(34, "evenrows", 1, "The even rows of the data is shown", "$ evenrows "),
		make_tuple<>(35, "primes", 2, "The prime numbers in the specific column is shown.", "$ primes column"),
		make_tuple<>(36, "delete occurrence", 4, "Every row that has the specific value under a specific column is deleted.", "$ delete occurrence column value "),
		make_tuple<>(37, "delete row", 3, "The specific row of the loaded data is deleted", "delete row value"),
		make_tuple<>(38, "delete column", 3, "The specific column is deleted.", "delete column value"),
		make_tuple<>(39, "insert row", 7, "The stated values is inserted to the data in the memory with a new row. The total number of row has been increased by 1.", "insert row data"),
		make_tuple<>(40, "replace", 3, "The specific number stated in all column is replaced by a new number stated.", "replace val1 val2"),
		make_tuple<>(41, "replace", 4, "All of the specific number in a specific column stated is replaced by a new number stated.", "replace column val1 val2"),
		make_tuple<>(42, "exit", 1, "The program is terminated.", "$ exit")};

	cout << "Shell running..." << endl;
	do
	{
		cout << "$ ";
		getline(cin, commandLine);
		command = getFirstParameter(commandLine);
		num_parameter = wordCounter(commandLine);

		int i = 1;
		string comList;
		if (command == "exit")
		{
			cout << "Exiting" << endl;
			break;
		}
		else if (command == "load")
		{
			int                 cols, rows;
			string              filename;
			vector<string>      titles;
			vector<string>      types;
			vector<s_data *>    data;

			filename = commandLine.substr(commandLine.find(" ") + 1);
			if (ft_load(filename, num_parameter, cols, rows, titles, types, data))
			{
				printf("%s loaded\n", filename.c_str());
				do
				{
					cout << "$ ";
					getline(cin, commandLine);
					command = getFirstParameter(commandLine);
                    filename = commandLine.substr(commandLine.find(" ") + 1);

					if (command == "load")
						cout << "Error: Do not load multiple files." << endl;
					else if (command == "size")
					{
						cout << "Columns: " << cols << endl;
						cout << "Rows: " << rows << endl;
					}
					else if (command == "titles")
					{
						for(i = 0; i < cols; i++)
							cout << titles[i] << " ";
						cout << "x" << endl;
					}
					else if (command == "list")
					{
						printData(cols, rows, data);
					}
                    else if (command == "sum")
					{
						printSum(cols, rows, data);
					}
                    else if (command == "store")
						ft_store(filename, cols, rows, data);
                    else if (command == "clone")
						ft_clone(filename);
					else if (command == "exit")
						cout << "Exiting" << endl;
					else
						cout << "Error: Command not found." << endl;
				} while (command != "exit");
			}
		}
		if (i <= 42)
		{
			while (i <= 42)
			{
				comList = get<1>(CommandList[i]);
				if (command == comList && command != "exit")
				{
					cout << "No file loaded yet." << endl;
					break;
				}
				i++;
			}
		}
		if (i > 42 && command != "exit" && command != "load")
			cout << "Error: Unknown command" << endl;
	} while (command != "exit");
}
