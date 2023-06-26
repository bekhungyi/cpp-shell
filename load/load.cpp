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
    if (nstr.at(0) == '\n' || nstr.at(0)==' ')
        nstr = nstr.substr(1);

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

void printSum(int cols, int rows, vector<string> titles, vector<vector<float>> ndata)
{
    int sum = 0;

    for (int r = 0; r < rows; r++)
	{
        for (int c = 0; c < cols; c++)
		{
			if (titles[c] == "Malay")
				sum += ndata[r][c];
		}
    }
    cout << "Sum: " << sum << endl;
}

int	checkNum(string str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		if (str[i] < '0' || str[i] > '9')
		{
			cout << "Parameter is not a valid number" << endl;
			return (0);
		}
		i++;
	}
	return (1);
}

int	checkTitle(string str, int rows, vector<string> titles)
{
	int i = 0;

	str = getFirstParameter(str);
	while (i < rows)
	{
		if (titles[i] == str)
			return (1);
		i++;
	}
	cout << "Title not found." << endl;
	return (0);
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

int ft_load(string filename, int &cols, int &rows, vector<string> &titles, vector<string> &types, vector<vector<string>> &sdata, vector<vector<float>> &ndata)
{
	if (filename.length() < 4 || filename.substr(filename.length() - 4) != ".csv") 
    {
        cout << "Invalid file." << endl;
		return (0);
    }
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
        str = trimStr(str);
        titles.push_back(str);
    }
    for (int i = 0; i < cols; i++)
    {
        file >> str;
        str = trimStr(str);
        types.push_back(str);
    }

    sdata.resize(rows);
    ndata.resize(rows);
    for (int r = 0; r < rows; r++)
    {
        sdata[r].resize(cols);
        ndata[r].resize(cols);

        float num;
        string 	str;
        int c = 0, c1 = 0, c2 = 0;
        while (c < cols)
        {
            if (types[c] == "number")
            {
                file >> str;
                num = stof(trimStr(str));
                ndata[r][c1] = num;
                c1++;
            }
            else if (types[c] == "string")
            {
                if (c < cols - 1)
                    getline(file, str, ',');
                else
                    file >> str;
                str = trimStr(str);
                sdata[r][c2] = str;
                c2++;
            }
            c++;
        }
    }
    file.close();
    return (1);
}

void    ft_store(string filename, int cols, int rows, vector<string> titles, vector<string> types, vector<vector<string>> sdata, vector<vector<float>> ndata)
{
	if (filename.length() < 4 || filename.substr(filename.length() - 4) != ".csv") 
    {
        cout << "Invalid file." << endl;
		return ;
    }
    ofstream file;
    file.open(filename);

	file << cols << endl;
	file << rows << endl;
	for (int c = 0; c < cols; c++) {
		file << titles[c];
		if (c != cols - 1)
			file << ", ";
	}
	file << endl;
	for (int c = 0; c < cols; c++) {
		file << types[c];
		if (c != cols - 1)
			file << ", ";
	}
	file << endl;
    for (int r = 0; r < rows; r++)
    {
		int c = 0, c1 = 0, c2 = 0;
		while (c < cols)
		{
			if (types[c] == "number")
			{
				file << ndata[r][c1];
				if (c != cols - 1)
					file << ", ";
				c1++;
			}
			else
			{
				file << sdata[r][c2];
				if (c != cols - 1)
					file << ", ";
				c2++;
			}
			c++;
		}
		file << endl;
    }
    file.close();
	cout << "Data has been stored into " << filename << "." << endl;
}

void    ft_clone(string filename)
{
    string  file1, file2;
    string  line;

    file1 = getFirstParameter(filename);
    file2 = filename.substr(filename.find(" ") + 1, filename.length());
	if (file1.length() < 4 || file1.substr(file1.length() - 4) != ".csv" || file2.length() < 4 || file2.substr(file2.length() - 4) != ".csv") 
    {
        cout << "Invalid file." << endl;
		return ;
    }
    ifstream inFile(file1);
    ofstream outFile(file2);
    if (inFile && outFile) {
  
        while (getline(inFile, line)) {
            outFile << line << "\n";
        }
        cout << "Finished copying.\n";
    }
    else {
        printf("Cannot access File.");
    }
    inFile.close();
    outFile.close();
}

void    ft_html(string filename, int cols, int rows, vector<string> titles, vector<string> types, vector<vector<string>> sdata, vector<vector<float>> ndata)
{
	if (filename.length() < 5 || filename.substr(filename.length() - 5) != ".html") 
    {
        cout << "Invalid file." << endl;
		return ;
    }
    ofstream file;
    file.open(filename);
	file << "<style>table {border-collapse: collapse;}th, td {padding: 5px;border: 1px solid black;}</style>" << endl;
    file << "<table>" << endl;
	for (int i = 0; i < cols; i++) {
		titles[i] = "<th>" + titles[i] + "</th>";
        file << titles[i] << endl;
    }
    for (int r = 0; r < rows; r++) {
		file << "<tr>" << endl;
		int	c1, c2;
		c1 = c2 = 0;
        for (int c = 0; c < cols; c++)
		{
			if (types[c] == "number")
			{
				string	tmp;
				tmp = to_string(ndata[r][c1]);
				file << "<td>" + tmp + "</td>" << endl;
				c1++;
			}
			else
			{
				file << "<td>" + sdata[r][c2] + "</td>" << endl;
				c2++;
			}
		}
        file << "</tr>" << endl;
    }
    file << "</table>" << endl;
    file.close();
	cout << "Data has been formated and stored into " << filename << "." << endl;
}

void    ft_html2(string filename)
{
	string file1, file2;
	int	cols, rows;
	vector<string> titles;
	vector<string> types;
	vector<vector<string>> sdata;
	vector<vector<float>> ndata;

	file1 = getFirstParameter(filename);
	file2 = filename.substr(filename.find(" ") + 1, filename.length());
	if (file1.length() < 4 || file1.substr(file1.length() - 4) != ".csv") 
    {
        cout << "Invalid file." << endl;
		return;
    }
	if (file2.length() < 5 || file2.substr(file2.length() - 5) != ".html") 
    {
        cout << "Invalid file." << endl;
		return;
    }
	ft_load(file1, cols, rows, titles, types, sdata, ndata);
	ft_html(file2, cols, rows, titles, types, sdata, ndata);
}

/****************************/
/*			Part 4			*/
/****************************/

void	ft_delete_row(int r, int &cols, int &rows, vector<string> &titles, vector<string> &types, vector<vector<string>> &sdata, vector<vector<float>> &ndata)
{
	sdata.erase(sdata.begin() + r); // Remove the row from sdata
    ndata.erase(ndata.begin() + r); // Remove the row from ndata

	rows -= 1;
	cout << "Row has been deleted" << endl;
}

void	ft_delete_col(string param, int &cols, int &rows, vector<string> &titles, vector<string> &types, vector<vector<string>> &sdata, vector<vector<float>> &ndata)
{
	for (int r = 0; r < rows; r++)
	{
		int c1 = 0, c2 = 0;
		for (int c = 0; c < cols; c++)
		{
			if (titles[c] == param)
			{
				if (types[c] == "string")
					sdata[r].erase(sdata[r].begin() + c1);
				else
					ndata[r].erase(ndata[r].begin() + c2);
			}
			if (types[c] == "string")
				c1++;
			else
				c2++;
		}
	}
	for (int c = 0; c < cols; c++)
	{
		if (titles[c] == param)
		{
			titles.erase(titles.begin() + c);
			types.erase(types.begin() + c);
		}
	}
	cols -= 1;
	cout << "Column has been deleted." << endl;
}

void	ft_delete_occur(string params, int &cols, int &rows, vector<string> &titles, vector<string> &types, vector<vector<string>> &sdata, vector<vector<float>> &ndata)
{
	int scol, srow;
	string	colName = getFirstParameter(params);
	float	colNum = stof(params.substr(params.find(" ") + 1, params.length()));

	scol = cols;
	srow = rows;
	for (int r = srow - 1; r >= 0; r--)
	{
		int c1 = 0;
		for (int c = 0; c < scol; c++)
		{
			if (titles[c] == colName && ndata[r][c1] == colNum)
			{
				ft_delete_row(r, cols, rows, titles, types, sdata, ndata);
				break;
			}
			if (types[c] == "number")
				c1++;
		}
	}
}

void	ft_delete(string params, int &cols, int &rows, vector<string> &titles, vector<string> &types, vector<vector<string>> &sdata, vector<vector<float>> &ndata)
{
	int	num_param = wordCounter(params);
	string	dltCommand = getFirstParameter(params);
	params = params.substr(params.find(" ") + 1, params.length());
	if (dltCommand == "occurrence" && num_param == 3)
	{
		if (checkTitle(params, rows, titles))
			ft_delete_occur(params, cols, rows, titles, types, sdata, ndata);
	}
	else if (dltCommand == "row" && num_param == 2)
	{
		if (checkNum(params))
		{
			int	rowNum = stoi(params) - 1;
			if (rowNum >= rows)
			{
				cout << "The input has exceeded the available rows." << endl;
				return ;
			}
			ft_delete_row(rowNum, cols, rows, titles, types, sdata, ndata);
		}
	}
	else if (dltCommand == "column" && num_param == 2)
	{
		if (checkTitle(params, rows, titles))
			ft_delete_col(params, cols, rows, titles, types, sdata, ndata);
	}
	else
		cout << "Delete command invalid." << endl;
}

void	ft_insert(string params, int &cols, int &rows, vector<string> &titles, vector<string> &types, vector<vector<string>> &sdata, vector<vector<float>> &ndata)
{
	string str;

	sdata.resize(rows + 1, vector<string>(cols));
	ndata.resize(rows + 1, vector<float>(cols));
	rows += 1;
	int	c1, c2;
	c1 = c2 = 0;
	for (int c = 0; c < cols; c++)
	{
		str = getFirstParameter(params);
		if (types[c] == "number")
		{
			ndata[rows - 1][c1] = stof(str);
			c1++;
		}
		else
		{
			sdata[rows - 1][c2] = str;
			c2++;
		}
		params = params.substr(params.find(" ") + 1, params.length());
	}
	cout << "Data is inserted to the last row." << endl;
}

void	ft_replace(string params, int &cols, int &rows, vector<string> &titles, vector<string> &types, vector<vector<string>> &sdata, vector<vector<float>> &ndata)
{
	float	target, sub;
	target = stof(getFirstParameter(params));
	sub = stof(params.substr(params.find(" ") + 1, params.length()));

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
			if (ndata[r][c] == target)
				ndata[r][c] = sub;
	}
	cout << "Every number " << target << " has been replaced with " << sub << "." << endl;
}

void	ft_replace2(string params, int &cols, int &rows, vector<string> &titles, vector<string> &types, vector<vector<string>> &sdata, vector<vector<float>> &ndata)
{
	float	target, sub;
	string	targetCol;

	targetCol = getFirstParameter(params);
	params = params.substr(params.find(" ") + 1, params.length());
	target = stof(getFirstParameter(params));
	sub = stof(params.substr(params.find(" ") + 1, params.length()));

	for (int r = 0; r < rows; r++)
	{
		int	c1 = 0;
		for (int c = 0; c < cols; c++)
		{
			if (titles[c] == targetCol && ndata[r][c1] == target)
				ndata[r][c1] = sub;
			if (types[c] == "number")
				c1++;
		}
	}
	cout << "Every number " << target << " in the column " << targetCol << " has been replaced with " << sub << "." << endl;
}

/****************************/
/*			Main F.			*/
/****************************/

int main()
{
	int num_parameter;
	string command, commandLine;
	system("cls");

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
		make_tuple<>(42, "clear", 1, "Screen cleared.", "$ clear"),
		make_tuple<>(43, "exit", 1, "The program is terminated.", "$ exit")};

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
		else if (command == "clear")
			system("cls");
		else if (command == "load")
		{
			int                 	cols, rows;
			string					filename;
			vector<string>			titles;
			vector<string>			types;
			vector<vector<string>>	sdata;
			vector<vector<float>>	ndata;

			if (num_parameter != 2)
				cout << "Invalid number of parameters." << endl;
			else
			{
				filename = commandLine.substr(commandLine.find(" ") + 1);
				if (ft_load(filename, cols, rows, titles, types, sdata, ndata))
				{
					cout << filename << " is loaded." << endl;
					do
					{
						cout << "$ ";
						getline(cin, commandLine);
						command = getFirstParameter(commandLine);
						num_parameter = wordCounter(commandLine);
						filename = commandLine.substr(commandLine.find(" ") + 1);

						if (command == "load")
							cout << "Error: Do not load multiple files." << endl;
						else if (command == "clear")
							system("cls");
						/****** Part 1 ******/
						else if (command == "store")
						{
							if (num_parameter == 2)
								ft_store(filename, cols, rows, titles, types, sdata, ndata);
							else
								cout << "Invalid number of parameters." << endl;
						}
						else if (command == "clone")
						{
							if (num_parameter == 3)
								ft_clone(filename);
							else
								cout << "Invalid number of parameters." << endl;
						}
						else if (command == "html")
						{
							if (num_parameter == 2)
								ft_html(filename, cols, rows, titles, types, sdata, ndata);
							else if (num_parameter == 3)
								ft_html2(filename);
							else
								cout << "Invalid number of parameters." << endl;
						}
						
						/****** Part 4 ******/
						else if (command == "delete" && (num_parameter == 3 || num_parameter == 4))
							ft_delete(filename, cols, rows, titles, types, sdata, ndata);
						else if (command == "insert")
						{
							string str = getFirstParameter(filename);
							if (str == "row")
							{
								if (num_parameter == cols + 2)
								{
									string param = filename.substr(filename.find(" ") + 1);
									ft_insert(param, cols, rows, titles, types, sdata, ndata);
								}
								else
									cout << "Wrong number of parameter." << endl;
							}
							else
								cout << "Error: Command not found." << endl;
						}
						else if (command == "replace" && num_parameter == 3)
						{
							if (checkNum(filename))
								ft_replace(filename, cols, rows, titles, types, sdata, ndata);
						}
						else if (command == "replace" && num_parameter == 4)
						{
							string colTitle = getFirstParameter(filename);
							string tmp = filename.substr(filename.find(" ") + 1);
							if (checkTitle(colTitle, rows, titles))
							{
								if (checkNum(tmp))
									ft_replace2(filename, cols, rows, titles, types, sdata, ndata);
							}
						}

						else if (command == "exit")
							cout << "Exiting" << endl;
						else
							cout << "Error: Command not found." << endl;
					} while (command != "exit");
				}
			}
		}
		if (i <= 43)
		{
			while (i <= 43)
			{
				comList = get<1>(CommandList[i]);
				if (command == comList && command != "exit" && command != "clear")
				{
					cout << "No file loaded yet." << endl;
					break;
				}
				i++;
			}
		}
		if (i > 43 && command != "exit" && command != "load" && command != "clear")
			cout << "Error: Unknown command" << endl;
	} while (command != "exit");
}
