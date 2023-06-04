#include <iostream>

using namespace std;

void getArrayData(int numbers[][100], int N) {
    cout << "Enter the values row by row:\n";
    for (int i = 0; i < N; i++) {
        cout << "Input " << (i + 1) << " row: ";
        for (int j = 0; j < N; j++) {
            cin >> numbers[i][j];
        }
    }
}

int sumSecDiag(int numbers[][100], int N) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        if (numbers[i][N - i - 1] % 2 == 0)
            sum += numbers[i][N - i - 1];
    }
    return sum;
}

int main() {
    int numbers[100][100];
    int N;

    cout << "Input N: ";
    cin >> N;

    if (N <= 0) {
        cout << "Invalid input. N should be positive.\n";
        return 0;
    }

    getArrayData(numbers, N);

    int sum = sumSecDiag(numbers, N);

    cout << "Sum of even numbers is equal to " << sum << endl;

    return 0;
}