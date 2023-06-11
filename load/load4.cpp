#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <string>
#include <cstring>

using namespace std;

void printCol(vector<vector<float> >& ptr, int col)
{
    for (int r = 0; r < ptr.size(); r++)
    {
        cout << ptr[r][col] << endl;
    }
}

void printAll(vector<vector<float> >& ptr, const vector<string>& names)
{
    for (int i = 0; i < names.size(); i++)
        cout << setw(15) << names[i] << " ";
    cout << endl;

    for (int r = 0; r < ptr.size(); r++)
    {
        for (int c = 0; c < ptr[r].size(); c++)
            cout << setw(15) << ptr[r][c] << "  ";
        cout << endl;
    }
}

float Average(const vector<vector<float> >& ptr, int col)
{
    float sum = 0;
    for (int r = 0; r < ptr.size(); r++)
    {
        sum += ptr[r][col];
    }
    return sum / ptr.size();
}

float Minimum(const vector<vector<float> >& ptr, int col)
{
    float min = ptr[0][col];
    for (int r = 0; r < ptr.size(); r++)
    {
        if (min > ptr[r][col])
            min = ptr[r][col];
    }
    return min;
}

int main()
{
    vector<string> names;
    vector<string> types;
    vector<int>    index;

    vector<vector<float> > vec;  // two dimensional array

    int cols, rows;
    ifstream input;
    input.open("data.csv");

    input >> cols;
    input >> rows;

    string str;
    for (int i = 0; i < cols; i++)
    {
        input >> str;
        names.push_back(str);
    }

    for (int i = 0; i < cols; i++)
    {
        input >> str;
        types.push_back(str);
    }

    for (int i = 0; i < cols; i++)
    {
        index.push_back(i);
    }

    for (int r = 0; r < rows; r++)
    {
        vector<float> line;
        for (int c = 0; c < cols; c++)
        {
            float x;
            input >> x;
            line.push_back(x);
        }
        vec.push_back(line);
    }
    input.close();

    printAll(vec, names);

    int idx = -1;
    string colName = "Malay";
    for (int i = 0; i < names.size(); i++)
        if (colName == names[i])
        {
            idx = i;
            break;
        }

    if (idx != -1)
    {
        cout << names[idx] << endl;
        printCol(vec, index[idx]);
        cout << "Avg = " << Average(vec, index[idx]) << endl;
        cout << "Min = " << Minimum(vec, index[idx]) << endl;
    }
    return 0;
}
