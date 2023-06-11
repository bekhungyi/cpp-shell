//   Section number  :  TT3L
//   Group number    :  G3
//   Student  1.          :  1221304880, Lee Hua Le
//   Student  2.          :  1221305373, Loh Yie Xuan
//   Student  3.          :  1221304972, Cheah Nicole
//   Video recording      :  https://drive.google.com/file/d/1DpeV9r72G6upE6XbKlKPZz37u1PWsnSV/view?usp=sharing

/*
----------------------------------------------------------------
|      Function        |       Contributing member(s)          |
----------------------------------------------------------------
|    WordCounter()     |            Lee Hua Le                 |
|   getRemaining()     |           Loh Yie Xuan                |
|  getFirstParameter() |           Cheah Nicole                |
|       help()         |            Lee Hua Le                 |
|      manual()        |  Lee Hua Le,Loh Yie Xuan,Cheah Nicole |
|       main()         |  Lee Hua Le,Loh Yie Xuan,Cheah Nicole |
|   colour printing    |           Loh Yie Xuan                |
----------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <cstring>
using namespace std;

// This function is used to count the number of parameter
int WordCounter(string str)
{
    int count;
    int i;
    if (str.length() > 0)
        count = 1; // initial word count is 1

    for (i = 0; i < str.length() - 1; i++) // loop until one character before the end of the string so that
                                           // if user key in an additional space at the end of the commandline, the number of parameter will not increment
    {
        if (str[i] == ' ' && str[i + 1] != ' ') // to make sure that when user input 2 spaces continuously,only 1 space is taken into account
            count++;                            // if any space detected,word count is incremented
    }

    return count;
}

// This function is used to get the remaining word except for the first word
string getRemaining(string command)   // This function takes the "command" and returns everything after the first space character.
{                                     // Main usage of this is to retrieve the parameters that come after the command.
    int position = command.find(' '); // This line is to find the position of first space character

    if (position != command.length()) // If space character was found, it would return a substring that begins from the character after the space.
    {
        return command.substr(position + 1);
    }
    else // If no space character was found, it would just return an empty string.
    {
        return "";
    }
}

// This function is used to get the command(first parameter)
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

// This function is used to implement the help system
void help()
{
    string line;
    ifstream helpSystem("help.txt"); // read from the file "help.txt"
    if (helpSystem.is_open())        // check if the file is successfully open
    {
        while (getline(helpSystem, line)) // read each line of file and assign to line variable
        {
            cout << line << '\n'; // output the lines
        }
        helpSystem.close();
    }
}

// This function is used to implement the manual system
void manual(string CommandLine, vector<tuple<int, string, int, string, string>> CommandList)
{
    string searchCommand, ThisCommand;
    bool stop = false;
    searchCommand = getRemaining(CommandLine); // use getRemaining() to obtain the command needed for manual help
    int i = 0;
    do
    {

        if (i <= 40)
        {
            ThisCommand = get<1>(CommandList.at(i)); // assign the command in command list to ThisCommand

            if (searchCommand == ThisCommand)
            {
                cout << "Command searched : " << searchCommand << endl;
                cout << "Format           : " << get<4>(CommandList.at(i)) << endl;
                cout << "Function         : " << get<3>(CommandList.at(i)) << endl;
                cout << endl;
                if (searchCommand == get<1>(CommandList.at(i + 1))) // since some command can be entered in two formats, both format and their function is being shown
                {
                    cout << "Format           : " << get<4>(CommandList.at(i + 1)) << endl;
                    cout << "Function         : " << get<3>(CommandList.at(i + 1)) << endl;
                    cout << endl;
                    stop = true;
                }
                stop = true; // since the command is found, the loop should stop running
            }
            i++;
        }
    } while (stop == false && i <= 40);

    if (stop == false)
    {
        cout << "Command not found." << endl; // an error message is output if command is not found in the list
    }
}

int main()
{
    string command, commandLine;
    int num_parameter;
    system("cls");

    // a vector of tuple named CommandList that is used to store the following according to the order
    // serial number ,command ,number of parameters ,function ,command format
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
        make_tuple<>(41, "replace", 4, "All of the specific number in a specific column stated is replaced by a new number stated.", "replace column val1 val2")};

    cout << "Welcome to Basic Statistical Analysis Interpreter" << endl
         << "Please input your command" << endl;

    do
    {
        cout << "$ ";
        getline(cin, commandLine);
        command = getFirstParameter(commandLine);
        num_parameter = WordCounter(commandLine);

        int i = 0;
        string ThisCommand, OutputLine;
        string newLine, newcommand;
        do
        {
            if (command == "exit")
                OutputLine = "Exiting the program.";

            if (i <= 40)
            {

                ThisCommand = get<1>(CommandList.at(i));
                if (command == "man")
                {
                    if (command == ThisCommand)
                    {

                        if (num_parameter == 2 || num_parameter == 3) // man command can have either 2 or 3 parameters
                            OutputLine = get<3>(CommandList.at(i));   // the function is assigned to OutputLine
                        else
                            OutputLine = "Wrong number of parameters."; // implementation of an error message when number of parameter is wrong
                    }
                }
                else if (command == ThisCommand)
                {
                    if (num_parameter == get<2>(CommandList.at(i)))
                        OutputLine = get<3>(CommandList.at(i));
                    else if (num_parameter == get<2>(CommandList.at(i + 1)) && command == get<1>(CommandList.at(i + 1))) // there is some command with two formats so both formats should be checked
                        OutputLine = get<3>(CommandList.at(i + 1));
                    else
                        OutputLine = "Wrong number of parameters.";
                }
                else if (command == "delete" || command == "insert") // If the command is "delete" / "insert", this loop will be executed
                {
           
                    newLine = getRemaining(commandLine);                  // Create a new string to store the parameters after the command (ie: delete or insert).
                    command = command + " " + getFirstParameter(newLine); // Get first parameter from the new string and concatenate it to the command.

                    if (command == ThisCommand) // Check whether the "command" from above, matches the command at index "i" in the list
                    {

                        if (num_parameter == get<2>(CommandList.at(i))) // If the num of parameters matches the expected number for the command as per commandList,
                            OutputLine = get<3>(CommandList.at(i));     // the corresponding output string from the list would be assigned to be the outputline.
                        else
                            OutputLine = "Wrong number of parameters.";
                    }
                }
                else if (command == "cls") // check when user input "cls" command
                {
                    system("cls"); // carry out clear screen instruction
                    break;
                }

                i++;
            }
            if (i > 40)
                OutputLine = "Wrong Command."; // an error message is assigned to OutputLine if command is not found in the list

        } while (command != ThisCommand && OutputLine != "Exiting the program." && OutputLine != "Wrong Command.");

        if (OutputLine == "Wrong Command." || OutputLine == "Wrong number of parameters.")

            cout << "\033[31m" << OutputLine << "\033[0m" << endl
                 << endl;

        else if (OutputLine == "Exiting the program.")
        {
            cout << "\033[34m" << OutputLine << "\033[0m" << endl
                 << endl
                 << "Thank you for using BSAI." << endl
                 << endl;
        }

        else
            cout << "\033[32m" << OutputLine << "\033[0m" << endl
                 << endl;

        if (command == "help")
        {
            if (OutputLine != "Wrong number of parameters.")
            {
                cout << endl;
                help(); // call the help function
                cout << endl;
            }
        }

        if (command == "man")
        {
            if (OutputLine != "Wrong number of parameters.")
            {
                cout << "*************************************************" << endl;
                manual(commandLine, CommandList); // call the manual function
                cout << "*************************************************" << endl;
            }
        }
    } while (commandLine != "exit"); // stop the loop when command == "exit"

    return 0;
}