#include <iostream>

using namespace std;

int main() {
    int rows, cols;
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;

  
    int arr[rows][cols] = {0};

    cout<<"Enter the values in the array:" << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j  < cols; j++){
            cin>>arr[i][j];
        }
    }

    cout << "\nUpdated 2D Array:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
