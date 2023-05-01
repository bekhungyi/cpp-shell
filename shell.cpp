#include <iostream>
#include <fstream>

using namespace std;

/************************************************************/
/*      Misc. Funcions                                      */
/************************************************************/

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

/************************************************************/
/*      1. File Operations                                  */
/************************************************************/

int ft_load(string element)
{
    int i = element.length();

    if (i > 4 && element.substr(i - 4) == ".csv") 
    {
        cout << "Success: " << element << " is loaded." << endl;
    }
    else
        cout << "Error: " << element << " is not a valid file." << endl;
    return 0;
}

int ft_store(string element)
{
    int i = element.length();

    if (i > 4 && element.substr(i - 4) == ".csv") 
    {
        cout << "Success: Data is stored to " << element << "." << endl;
    }
    else
        cout << "Error: " << element << " is not a valid file." << endl;
    return 0;
}

int ft_clone(string element)
{
    string elementClone = ft_trim(element);
    string elementCopy = element;
    // string elementCloneCopy = elementClone;
    getFirstArg(elementCopy);
    if (elementCopy.length() > 4 && elementCopy.substr(elementCopy.length() - 4) == ".csv") 
    {
        if (elementClone.length() > 4 && elementClone.substr(elementClone.length() - 4) == ".csv")
            cout << "Success: Data is cloned to " << elementClone << "." << endl;
        else
            cout << "Error: Destination file is invalid." << endl;
    }
    else
        cout << "Error: Source file is invalid." << endl;
    return 0;
}

int ft_htmlOne(string element)
{
    int i = element.length();

    if (i > 5 && element.substr(i - 5) == ".html") 
    {
        cout << "Success: Data is stored to " << element << "." << endl;
    }
    else
        cout << "Error: " << element << " is not a valid file." << endl;
    return 0;
}

int ft_htmlTwo(string element)
{
    string elementClone = ft_trim(element);
    string elementCopy = element;
    string elementCloneCopy = elementClone;
    getFirstArg(elementCopy);
    if (elementCopy.length() > 4 && elementCopy.substr(elementCopy.length() - 4) == ".csv") 
    {
        if (elementCloneCopy.length() > 5 && elementCloneCopy.substr(elementCloneCopy.length() - 5) == ".html")
            cout << "Success: Data is cloned to " << elementClone << "." << endl;
        else
            cout << "Error: Destination file is invalid." << endl;
    }
    else
        cout << "Error: Source file is invalid." << endl;
    return 0;
}

/************************************************************/
/*      2. Statistical Commands                             */
/************************************************************/

int ft_minOne(string element)
{
    cout << "Minimum: min_value" << endl;
    return 0;
}

int ft_minTwo(string element)
{
    ft_trim(element);
    cout << "Minimum " << element << ": min_value" << endl;
    return 0;
}

/************************************************************/
/*      3. Display commands                                 */
/************************************************************/

int ft_showOne(string element)
{
    cout << "Here's the data read from the file:" << endl << "Example Data..." << endl;
    return 0;
}

int ft_showTwo(string element)
{
    ft_trim(element);
    cout << "Here's the data from " << element << " column:" << endl << "Example Data..." << endl;
    return 0;
}

/************************************************************/
/*      4. Add/Delete commands                              */
/************************************************************/

int deleteOccurrence(string param)
{
    int i = 0;
    string paramTwo = ft_trim(param);
    getFirstArg(param);
    while (paramTwo[i] != '\0')
    {
        if (paramTwo[i] < 48 || paramTwo[i] > 57)
        {
            cout << "Invalid parameters." << endl;
            return 0;
        }
        i++;
    }
    cout << "Deleted every row that has the " << param << " value of " << paramTwo << endl;
    return 0;
}

int deleteRow(string param)
{
    int i = 0;
    while (param[i] != '\0')
    {
        if (param[i] < 48 || param[i] > 57)
        {
            cout << param << " is not a valid number of row." << endl;
            return 0;
        }
        i++;
    }
    cout << "Deleted row number " << param << " from the loaded data." << endl;
    return 0;
}

int ft_delete(string element)
{
    string param = ft_trim(element);

    getFirstArg(element);
    int argc = argCount(param);
    if (element == "occurrence" && argc == 2)
        deleteOccurrence(param);
    else if (element == "row" && argc == 1)
        deleteRow(param);
    else if (element == "column" && argc == 1)
        cout << "Deleted the column " << param << endl;

    return 0;
}

int replaceOne(string element)
{
    cout << element << endl;
    string firstParam = element;
    string secondParam = ft_trim(element);
    getFirstArg(firstParam);

    int i = 0;
    while (firstParam[i] != '\0')
    {
        if (firstParam[i] < 48 || firstParam[i] > 57)
        {
            cout << firstParam << " is not a valid number." << endl;
            return 0;
        }
        i++;
    }
    i = 0;
    while (secondParam[i] != '\0')
    {
        if (secondParam[i] < 48 || secondParam[i] > 57)
        {
            cout << secondParam << " is not a valid number." << endl;
            return 0;
        }
        i++;
    }
    cout << "Replaced every number " << firstParam << " in all the columns with " << secondParam << endl;
    return 0;
}

int replaceTwo(string element)
{
    string colParam = element;
    string numParam = ft_trim(element);
    getFirstArg(colParam);

    string firstParam = numParam;
    string secondParam = ft_trim(numParam);
    getFirstArg(firstParam);
    int i = 0;
    while (firstParam[i] != '\0')
    {
        if (firstParam[i] < 48 || firstParam[i] > 57)
        {
            cout << firstParam << " is not a valid number." << endl;
            return 0;
        }
        i++;
    }
    i = 0;
    while (secondParam[i] != '\0')
    {
        if (secondParam[i] < 48 || secondParam[i] > 57)
        {
            cout << secondParam << " is not a valid number." << endl;
            return 0;
        }
        i++;
    }

    cout << "Replaced every " << firstParam << " with " << secondParam << " in the " << colParam << " column." << endl;
    return 0;
}

int ft_replace(string element)
{
    int argc = argCount(element);

    if (argc == 2)
        replaceOne(element);
    else if ( argc == 3)
        replaceTwo(element);
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
        // cout << "Command is " << command << endl;
        // cout << "Element is " << element << endl;
        // cout << "ArgC is " << argc << endl << endl;

        if (command.compare("exit") == 0)
            cout << "Exiting Shell." << endl;
        
        else if (command.compare("clear") == 0)
            system ("clear");

        /***    1. File Operations  ***/

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

        /***    2. Statistical Commands  ***/

        else if (command.compare("min") == 0)
        {
            if (argc < 1)
                cout << "Error: Not enough parameter." << endl;
            else if (argc == 1)
                ft_minOne(element);
            else if (argc == 2)
                ft_minTwo(element);
            else if (argc > 2)
                cout << "Error: Too much parameters." << endl;
        }
        
        /***    3. Display commands  ***/
        
        else if (command.compare("show") == 0)
        {
            if (argc < 1)
                cout << "Error: Not enough parameter." << endl;
            else if (argc == 1)
                ft_showOne(element);
            else if (argc == 2)
                ft_showTwo(element);
            else if (argc > 2)
                cout << "Error: Too much parameters." << endl;
        }

        /***    4. Add/Delete commands  ***/

        else if (command.compare("delete") == 0)
        {
            if (argc < 2)
                cout << "Error: Not enough parameter." << endl;
            else if (argc == 3 || argc == 4)
                ft_delete(element);
            else if (argc > 4)
                cout << "Error: Too much parameters." << endl;
        }

        else if (command.compare("insert") == 0)
        {
            if (element == "row")
                cout << "Values are inserted into the memory data." << endl << "Total number of rows is increased by 1." << endl;
            else
                cout << "Invalid command." << endl;
        }

        else if (command.compare("replace") == 0)
        {
            if (argc < 3)
                cout << "Error: Not enough parameters." << endl;
            else if (argc == 3 || argc == 4)
                ft_replace(element);
            else if (argc > 4)
                cout << "Error: Too much parameters." << endl;
        }

    } while (command != "exit");
    
    system("clear");
    return 0;
}