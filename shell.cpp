#include <iostream>
#include <fstream>

using namespace std;

int argCount(string command)
{
    int i = 0;
    int count = 1;
    while (command[i] != '\0')
    {
        if (command[i] == ' ')
        {
            count++;
        }
        i++;
    }
    return count;
}

void getFirstArg(string& element)
{
    int i = 0;
    while (element[i] != ' ' && element[i] != '\0')
    {
        i++;
    }
    element = element.substr(0, i);
}

string ft_trim(string command)
{
    int pos = command.find(' ');
    if (pos != string::npos) {
        return command.substr(pos+1);
    }
    else {
        return "";
    }
}

int ft_load(string element)
{
    int i = element.length();

    if (i >= 4 && element.substr(i - 4) == ".csv") 
    {
        cout << "Success: " << element << " is loaded." << endl;
    }
    else
        cout << "Error: " << element << " is not a .csv file." << endl;
    return 0;
}

int ft_store(string element)
{
    int i = element.length();

    if (i >= 4 && element.substr(i - 4) == ".csv") 
    {
        cout << "Success: Data is stored to " << element << "." << endl;
    }
    else
        cout << "Error: " << element << " is not a .csv file." << endl;
    return 0;
}

int ft_clone(string element)
{
    ofstream    output;
    int i = element.length();

    if (i >= 4 && element.substr(i - 4) == ".csv") 
    {
        cout << "Success: Data is stored to " << element << "." << endl;
    }
    else
        cout << "Error: " << element << " is not a .csv file." << endl;
    return 0;
}

int ft_htmlOne(string element)
{
    int i = element.length();

    if (i >= 5 && element.substr(i - 5) == ".html") 
    {
        cout << "Success: Data is stored to " << element << "." << endl;
    }
    else
        cout << "Error: " << element << " is not a .html file." << endl;
    return 0;
}

int ft_htmlTwo(string element)
{
    return 0;
}

int main()
{
    system ("clear");
    string command, element;
    int argc;

    cout << "Shell is running." << endl;
    do {
        cout << "$ ";
        getline(cin, command);
        argc = argCount(command);
        element = ft_trim(command);
        getFirstArg(command);
        cout << "Command is " << command << endl;
        cout << "Element is " << element << endl;
        cout << "ArgC is " << argc << endl << endl;

        if (command.compare("exit") == 0)
            cout << "Exiting Shell." << endl;

        else if (command.compare("load") == 0)
        {
            if (argc < 2)
                cout << "Error: No file to be loaded." << endl;
            else if (argc == 2)
                ft_load(element);
            else if (argc > 2)
                cout << "Error: Only one file can be loaded." << endl;
        }

        else if (command.compare("store") == 0)
        {
            if (argc < 2)
                cout << "Error: No file to be stored." << endl;
            else if (argc == 2)
                ft_store(element);
            else if (argc > 2)
                cout << "Error: Only one file can be stored to." << endl;
        }

        else if (command.compare("clone") == 0)
        {
            if (argc < 3)
                cout << "Error: Not enough parameter." << endl;
            else if (argc == 3)
                ft_clone(element);
            else if (argc > 3)
                cout << "Error: Too much parameters." << endl;
        }

        else if (command.compare("html") == 0)
        {
            if (argc < 2)
                cout << "Error: Not enough parameter." << endl;
            else if (argc == 2)
                ft_htmlOne(element);
            else if (argc == 3)
                ft_htmlTwo(element);
            else if (argc > 3)
                cout << "Error: Too much parameters." << endl;
        }
        
    } while (command != "exit");
    
    system("clear");
    return 0;
}