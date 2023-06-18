#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>

using namespace std;

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
string getRemaining(string command)     // This function takes the "command" and returns everything after the first space character.
{                                       // Main usage of this is to retrieve the parameters that come after the command.
        int position = command.find(' ');   // This line is to find the position of first space character

        if (position != command.length())   // If space character was found, it would return a substring that begins from the character after the space.
        {
            return command.substr(position + 1);
        }
        else                                // If no space character was found, it would just return an empty string.
        {
            return "";
        }
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
            count++;                            // if any space detected,word count is incremented
    }

    return count;
}

string trimStr(string str)
{
    string nstr;

    nstr = str.substr(0, str.find(","));
    if (nstr.at(0) == '\n'||nstr.at(0)==' ')
        nstr = nstr.substr(1);

    return (nstr);
}

float trimNum(string str)
{
    float nnum;

    str = str.substr(0, str.find(","));
    nnum = stof(str);
    return (nnum);
}

void checktitlenum(vector<string> titles, vector<string> types,string colInput)
{
     int index = 0;
    for (int i = 0; i < titles.size(); i++)
    {
        if (titles[i] != colInput && types[i] == "number")
            index++;
        else if (titles[i] == colInput && types[i] == "number")
        {
           break;
        }
    }
}

void checktitlestr(vector<string> titles, vector<string> types,string colInput)
{
     int index = 0;
    for (int i = 0; i < titles.size(); i++)
    {
        if (titles[i] != colInput && types[i] == "string")
            index++;
        else if (titles[i] == colInput && types[i] == "string")
        {
           break;
        }
    }
}
int ft_load(string filename, int &cols, int &rows, vector<string> &titles, vector<string> &types, vector<vector<string>> &sdata, vector<vector<float>> &ndata)
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
        string str;
        int c = 0, c1 = 0, c2 = 0;
        while (c < cols)
        {
            if (types[c] == "number")
            {
                file >> str;
                num = stof(trimStr(str));
                ndata[r][c1] = num;
                // cout << "n" << ndata[r][c1] << " ";
                c1++;
            }
            else if (types[c] == "string")
            {

                if (c < cols - 1)
                    getline(file, str, ',');
                else
                    file >> str;
                str = trimStr(str);
                // cout << str << endl;
                sdata[r][c2] = str;
                // cout << "s" << sdata[r][c2];
                c2++;
            }
            c++;
            // cout << endl;
        }
    }
    file.close();
    return (1);
}



bool isNumeric(int cols, vector<string> titles, vector<string> types, string colName)
{
    int thisCol;
    bool numeric = false;
    for (int c = 0; c < cols; c++)
    {
        if (colName == titles[c])
        {
            thisCol = c;
            break;
        }
    }
    if (types[thisCol] == "number")
        numeric = true;
    return numeric;
}

bool findTitle(vector<string> titles, string colInput)
{
    bool tfound = false;

    for (int i = 0; i < titles.size(); i++)
    {
        if (titles[i] == colInput)
        {
            tfound = true;
            break;
        }
    }
    return tfound;
}


void searchNumber(vector<string> titles, vector<string> types, string colInput, int &index)
{
    for (int i = 0; i < titles.size(); i++)
    {
        if (titles[i] != colInput && types[i] == "number")
            index++;
        else if (titles[i] == colInput && types[i] == "number")
        {
            break;
        }
    }
}

void searchString(vector<string> titles, vector<string> types, string colInput, int &index)
{
    for (int i = 0; i < titles.size(); i++)
    {
        if (titles[i] != colInput && types[i] == "string")
            index++;
        else if (titles[i] == colInput && types[i] == "string")
        {
            break;
        }
    }
}
void printTitles(vector<string>titles,int cols)
{
    for(int i = 0; i < cols; i++)
	{   
         cout << titles[i] << " ";
    }
    cout<<endl;
}

void show(vector<string> titles, vector<string> types, vector<vector<float>> ndata, vector<vector<string>> sdata,int cols,int rows)
{
        printTitles(titles,cols);
        for(int i=0;i<rows;i++)
        {
             for(int c=0; c<cols; c++)
            {
               bool numeric = isNumeric(titles.size(), titles, types, titles[c]);
               if (numeric)
               {
                 int index = 0;
                 searchNumber(titles, types, titles[c], index);
                 cout << setw(20) << ndata[i][index] <<" ";
               }
        
              else
              {
               int index = 0;
               searchString(titles, types, titles[c], index);
               cout << setw(20)<<sdata[i][index] <<" ";
              }
            }
         cout<<endl;
        }
}

void showSubject(vector<string> titles,vector<string> types, string commandLine, vector<vector<float>>ndata,vector<vector<string>>sdata,int rows,int cols)
{
    string colInput =getRemaining(commandLine);
    findTitle(titles, colInput);
     for(int i=0;i<types.size();i++)
     {
      if(types[i]=="number")
         checktitlenum(titles, types,colInput);
      else if(types[i]=="string")
          checktitlestr(titles, types,colInput);
     }
    
     for (int c = 0; c < cols; c++)
    {
        for(int r=0; r < rows; r++)
        {
          if (colInput == titles[c]&&types[c]=="number")
             cout << ndata[r][c] <<endl;
          else if (colInput == titles[c]&&types[c]=="string")
             cout << sdata[r][c]<<endl;
        }      
    }
}
void totalRow(vector<vector<float>>& ndata, int &cols,int& rows)
{
    int count=0;
    for (int r = 0; r < rows; r++)
    {
        ndata[r][cols];
        count++;
    }
    cout<< "Total rows loaded = " << count;
    cout<< endl;
}

void totalCol(vector<vector<float>>& ndata,int cols,int rows)
{
    int count=0;
    for (int c = 0; c < cols; c++)
    {
        ndata[rows][c];
        count++;
    }
    cout<< "Total columns loaded = " << count;
    cout<< endl;
}



void printEvenrow(int cols, int rows, vector<string> titles, vector<string> types,vector<vector<float>>& ndata,vector<vector<string>>& sdata)
{
    printTitles(titles,cols);
    for(int i=0;i<rows;i++)
    {
        for(int c=0; c<cols; c++)
        if(i%2==1)
        {
            bool numeric = isNumeric(titles.size(), titles, types, titles[c]);
            if (numeric)
           {
            int index = 0;
            searchNumber(titles, types, titles[c], index);
             cout << setw(20) << ndata[i][index] <<" ";
           }
        
        else
           {
            int index = 0;
            searchString(titles, types, titles[c], index);
            cout << setw(20)<<sdata[i][index] <<" ";
            }
       }
       cout<<endl;
    }
}	

void Oddrows(int cols, int rows, vector<string> titles, vector<string> types,vector<vector<float>>& ndata,vector<vector<string>>& sdata)
{
    printTitles(titles,cols);
    for(int i=0;i<rows;i++)
    {
        for(int c=0; c<cols; c++)
        if(i%2==0)
        {
            bool numeric = isNumeric(titles.size(), titles, types, titles[c]);
            if (numeric)
           {
            int index = 0;
            searchNumber(titles, types, titles[c], index);
              cout << setw(20) << ndata[i][index] <<" ";
           }
        
        else
           {
            int index = 0;
            searchString(titles, types, titles[c], index);
            cout << setw(20)<<sdata[i][index] <<" ";
            }
       }
       cout<<endl;
    }
}	

//void prime(int cols, int rows, vector<string> titles, vector<string> types,vector<vector<float>>& ndata,vector<vector<string>>& sdata)




   

int main()
{
    int num_parameter;
    string command, commandLine,colInput;
    system("cls");

    cout << "Shell running..." << endl;

    do
    {
        cout << "$ ";
        getline(cin, commandLine);
        command = getFirstParameter(commandLine);
        num_parameter = wordCounter(commandLine);
        colInput =getRemaining(commandLine);

        int i = 1;
        string comList;
        if (command == "exit")
        {
            cout << "Exiting" << endl;
            break;
        }
        else if (command == "load")
        {
            int cols, rows;
            string filename;
            vector<string> titles;
            vector<string> types;
            vector<vector<string>> sdata;
            vector<vector<float>> ndata;

            filename = commandLine.substr(commandLine.find(" ") + 1);
            if (ft_load(filename, cols, rows, titles, types, sdata, ndata))
            {
                printf("%s loaded\n", filename.c_str());

                do
                {
                    cout << "$ ";
                    getline(cin, commandLine);
                    command = getFirstParameter(commandLine);
                    num_parameter = wordCounter(commandLine);
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
                        for (i = 0; i < cols; i++)
                            cout << titles[i] << " ";
                    }
                    else if (command == "Rows")
                    {
                        totalRow(ndata,cols,rows);
                    }
                    else if (command == "show" && num_parameter == 1)
                    {
                        cout << "here" << endl;
                        show(titles, types, ndata, sdata,cols,rows);
                    }
                    else if (command == "show" && num_parameter == 2)
                    {
                        cout << "here" << endl;
                        showSubject(titles,types, commandLine, ndata, sdata,rows,cols);
                    }
                    else if (command =="Columns")
                    {
                        totalCol(ndata,cols,rows);
                    }
                    else if (command == "Titles")
                    {
                        printTitles(titles,cols);
                    }
                    else if(command == "Evenrows")
                    {
                        printEvenrow(cols, rows, titles, types,ndata,sdata);
                    }
                    else if (command == "Oddrows")
                    {
                        Oddrows(cols, rows, titles, types, ndata, sdata);
                    }
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
                // comList = get<1>(CommandList[i]);
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