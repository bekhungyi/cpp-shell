#include <iostream>
#include <fstream>

using namespace std;

float** getArray(int rows, int cols)
{
    float **vec;
    vec = new float* [rows];
    for (int i = 0; i < rows; i++)
        vec[i] = new float[cols];
    return vec;
}

void deleteMemory(float** vec, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
        delete[] vec[i];
    delete[] vec;
}

void printCol(float** ptr, int rows, int col)
{
    for (int r = 0; r < rows; r++)
    {
        cout << ptr[r][col] << endl;
    }
}

int main()
{
    float** vec;
    int cols, rows;
    ifstream input;
    input.open("data.csv");

    input >> cols;
    input >> rows;

    vec = getArray(rows, cols);

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            float x;
            input >> x;
            vec[r][c] = x;
            cout << x << " ";
        }
        cout << endl;
    }
    input.close();

    printCol(vec, 6, 2);

    deleteMemory(vec, rows, cols);

    
    return 0;
}