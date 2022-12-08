#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// Here's how I'm storing each matrix.
vector<vector<int> > m1 = {};
vector<vector<int> > m2 = {};
vector<vector<int>> total = {};

int dotProduct(vector<int> r1, vector<int> r2);
void displayMenu();
void processMenuChoice(int menuChoice);
void printVector(vector<vector<int>> m);
vector<vector<int> > getNewMatrix();
vector<vector<int> > addMatrix(vector<vector<int>> m1, vector<vector<int>> m2);
vector<vector<int> > multiplyMatrix(vector<vector<int> > m1, vector<vector<int> > m2);

int main()
{
    cout << "Please input data for the first matrix."<< endl;
    m1 = getNewMatrix();
    cout << endl<< "Please input data for the second matrix."<< endl;
    m2 = getNewMatrix();
    cout << endl;
    int menuChoice = 0;
    while (menuChoice != 5) {
        displayMenu();
        cin >> menuChoice;
        processMenuChoice(menuChoice);
        cout << endl;
    }
    return 0;
}

//Prints out all menu options for the user to choose from
void displayMenu() {
    cout << "What do you want to do with your matrices?" << endl
        << "1. Enter a new matrix 1." << endl
        << "2. Enter a new matrix 2." << endl
        << "3. Add matrices." << endl
        << "4. Multiply matrices" << endl
        << "5. End program."<< endl;
}

// It took me two hours and a ton of spaghetti code
// just to let the user input an entire row at once.
// Worth it, though.
vector<vector<int>> getNewMatrix() {
    vector<vector<int>> matrix = {};
    vector<int> row = {};
    string temp = "";
    string rowString = "";
    int cell;
    bool errorFlag = false; // Used to break (actually to not break) a loop from inside another loop.
    for (int r = 0; r < 3; r++)
    {
        while (true)
        {
            errorFlag = false;
            cout << "Enter the " << (r == 0 ? "first" : r == 1 ? "second" : "third") << " row of your matrix. Separate numbers with spaces: ";
            row = {};

            // I still don't like that it takes this much code
            // just to get input that includes whitespace.
            cin >> rowString;
            getline(cin, temp);
            rowString += temp;
            
            // At least 90% of my pain writing this was trying to get cin to loop
            // until it runs out of input, but it turns out that that's kind of impossible.
            // I think it's because when cin is empty it just waits for more input
            // instead of setting eof() to true, but either way it causes an infinite loop.
            // Thankfully, putting the input into a different stringstream seems to solve the problem.
            istringstream stream(rowString);
            while (!stream.eof())
            {
                stream >> cell;

                // If stream >> cell fails (because the user didn't input a number)
                // then stream sets its failbit to true.
                if (stream.fail())
                {
                    cout << "You need to enter numbers!" << endl;
                    errorFlag = true;
                    break;
                }
                else
                {
                    row.push_back(cell);
                }
            }

            // errorFlag is set to true if the user didn't enter numbers,
            // so all of this can be skipped.
            if (!errorFlag)
            {
                // Makes sure the user entered at least 3 numbers
                if (size(row) < 3)
                {
                    cout << "You need to enter 3 numbers!" << endl;

                }
                else
                {
                    // Truncate the row to 3 numbers in case the user entered more than 3.
                    // If the user only entered 3, it does nothing and leaves the row unchanged.
                    row.resize(3);
                    matrix.push_back(row);
                    break;
                }
            }
        }
    }
    return matrix;
}

// Takes the menu choice given by the user and
// either assigns new values for each matrix,
// adds the matrices and assigns the sum to total,
// multiplies the matrices and assigns the product to total 
// or breaks the while loop to end the program.
void processMenuChoice(int menuChoice) {
    switch (menuChoice) {
    case 1:
        m1 = getNewMatrix();
        break;
    case 2:
        m2 = getNewMatrix();
        break;
    case 3:
        total=addMatrix(m1,m2);
        cout << "Adding Matrices:" << endl;
        printVector(total);
        break;
    case 4:
        total=multiplyMatrix(m1,m2);
        cout << "Multiplying Matrices:" << endl;
        printVector(total);
        break;
    case 5:
        break;
    }
}

// Prints the matrix in a 3x3 format, used to nicely show products and sums.
void printVector(vector<vector<int>> m) {
    for (int r = 0; r < size(m); r++) {
        for (int c = 0; c < size(m); c++) {
            cout << setw(7) << right << (to_string(m[r][c]) + ", ");
        }
        cout << endl;
    }
}

// Part of the multiplying matrices step. Gets the row of the first matrix
// and the corresponding column of the second matrix and returns the dot product
int dotProduct(vector<int> r, vector<int> c)
{
    int p = 0;
    for (int i = 0; (i < size(r) && i < size(c)); i++)
    {
        p += r[i]* c[i];
    }
    return p;
}

// Just as the name suggests, this function adds the two matrices together into a newly defined matrix and returns the matrix.
vector<vector<int>> addMatrix(vector<vector<int>> m1, vector<vector<int>> m2) {
    
    vector<vector<int>> m3 = {};
    vector<int> row = {};
    for (int r = 0; r < size(m1); r++)
    {
        row = {};
        for (int c = 0; c < size(m1); c++)
        {
            row.push_back(m1[r][c] + m2[r][c]);
        }
        m3.push_back(row);
    }
    return m3;
}

// Multiplies two matrices together.
// Takes the two matrices to be multiplied
// and returns the product.
vector<vector<int> > multiplyMatrix(vector<vector<int> > m1, vector<vector<int> > m2)
{
    vector<vector<int> > rows = { m1[0], m1[1], m1[2] };

    // To multiply the matrices you have to divide one into rows and one into columns.
    // Rows are easy since that's how the matrices are stored. Columns are...less easy.
    vector<vector<int> > columns = {
        {m2[0][0], m2[1][0], m2[2][0]},
        {m2[0][1], m2[1][1], m2[2][1]},
        {m2[0][2], m2[1][2], m2[2][2]},
    };

    vector<vector<int> > m3 = {};
    vector<int> row = {};
    for (int r = 0; r < 3; r++)
    {
        row = {};
        for (int c = 0; c < 3; c++)
        {
            row.push_back(dotProduct(rows[r], columns[c]));
        }
        m3.push_back(row);
    }
    return m3;
}