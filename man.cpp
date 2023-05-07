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

string getRemaining(string command)
{
    int position = command.find(' ');

    if (position != command.length())
    {
        return command.substr(position + 1);
    }
    else
    {
        return "";
    }
}

int ft_man(string element)
{
    string line;

    ifstream file("bingbong.txt");
    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (line.substr(0, element.size() + 2) == "# " + element)
            {
                while (getline(file, line) && line[0] != '#')
                {
                    cout << line << endl;
                }
                file.close();
                return 0;
            }
        }
        file.close();
    }
    cout << "No manual entry for " << element << endl;
    return 1;
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
        element = getRemaining(command);
        getFirstArg(command);
        cout << "Command is " << command << endl;
        cout << "Element is " << element << endl;
        // cout << "ArgC is " << argc << endl << endl;

        if (command.compare("exit") == 0)
            cout << "Exiting Shell." << endl;
        
        else if (command.compare("clear") == 0)
            system ("clear");

        else if (command.compare("man") == 0 && argc >= 2)
            ft_man(element);

        else
            cout << "Command not found." << endl;

    } while (command != "exit");
    
    system("clear");
    return 0;
}