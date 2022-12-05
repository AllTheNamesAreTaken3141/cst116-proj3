#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

// I stole this from the internet and I have basically no idea how it works,
// but it lets you cout to both the console and a text file at the same time,
// and all you have to do is pass everything to the Tee object instead of cout.
// Very useful since now I don't have to copy-paste the console every time I need to store my output somewhere.
class Tee
{
private:
    std::ostream& os1, & os2;
public:
    Tee(std::ostream& os1, std::ostream& os2) : os1(os1), os2(os2) {}
    template <typename T>
    Tee& operator<<(const T& thing)
    {
        os1 << thing;
        os2 << thing;

        return *this;
    }


    // function that takes a custom stream, and returns it
    typedef Tee& (*TeeManipulator)(Tee&);

    // take in a function with the custom signature
    Tee& operator<<(TeeManipulator manip)
    {
        // call the function, and return it's value
        return manip(*this);
    }

    // define the custom endl for this stream.
    // note how it matches the `TeeManipulator`
    // function signature
    static Tee& endl(Tee& stream)
    {
        // print a new line
        stream << std::endl;

        // do other stuff with the stream
        // std::cout, for example, will flush the stream
        stream << "Called Tee::endl!" << std::endl;

        return stream;
    }

    // this is the type of std::cout
    typedef std::basic_ostream<char, std::char_traits<char> > CoutType;

    // this is the function signature of std::endl
    typedef CoutType& (*StandardEndLine)(CoutType&);

    // define an operator<< to take in std::endl
    Tee& operator<<(StandardEndLine manip)
    {
        // call the function, but we cannot return its value
        manip(std::cout);

        return *this;
    }
};

// Here's how I'm storing each matrix.
vector<vector<int> > m1 = {
    {-57, 82, 43},
    {17, -93, 89},
    {-2, 53, 17}
};
vector<vector<int> > m2 = {
    {-23, 87, -3},
    {-5, 72, 50},
    {59, 29, -35}
};
vector<vector<int>> total = {
    {0,0,0},
    {0,0,0},
    {0,0,0}
};

int dotProduct(vector<int> r1, vector<int> r2);
void displayMenu();
void processMenuChoice(int menuChoice);
vector<vector<int>> getNewMatrix();
vector<vector<int>> addMatrix(vector<vector<int>> m1, vector<vector<int>> m2);
vector<vector<int> > multiplyMatrix(vector<vector<int> > m1, vector<vector<int> > m2);

int main()
{
    // The path to the log file. The ./ makes it a relative path,
    // so it starts at the root folder of the project.
    // If you right-click on the very top file in the Solution Explorer
    // and click "Open folder in File Explorer", it should take you there.
    // IF YOU WANT TO SAVE A SECOND LOG FILE, YOU MUST CHANGE THIS FILENAME.
    // If you don't change it and run the code a second time,
    // it will destroy the first log.
    ofstream logFile("./logs/test-log.txt");
    Tee teeOut(std::cout, logFile); // Creates a new Tee named teeOut. Now all you have to do is use teeOut instead of cout (so, "cout << "Hello, world!" << endl;" becomes "teeOut << "Hello, world!" << endl;").
    cout << "Please input data for the first matrix."<< endl;
    m1 = getNewMatrix();
    cout << endl<< "Please input data for the second matrix."<< endl;
    m2 = getNewMatrix();
    displayMenu();
    int menuChoice = 0;
    while (menuChoice != 0) {

    }
    
    
    logFile.close(); // Closes the log file because you should always close your files. Make sure this is the very last line in main.
}
void displayMenu() {
    cout << "What do you want to do with your matrixes?" << endl
        << "1. Enter a new matrix 1." << endl
        << "2. Enter a new matrix 2." << endl
        << "3. Add matrixes." << endl
        << "4. Multiply matrixes" << endl << endl;
}
vector<vector<int>> getNewMatrix() {
    vector<vector<int>> m3 = {};
    vector<int> row = {};
    int temp;
    for (int r = 0; r < 3; r++)
    {
        row = {};
        for (int c = 0; c < 3; c++)
        {
            cout << "What do you want to put in at spot " << r << " " << c << "?";
            cin >> temp;
            row.push_back(temp);
        }
        m3.push_back(row);
    }
    return m3;
}
void processMenuChoice(int menuChoice) {
    switch (menuChoice) {
    case 1:
        m1 = getNewMatrix();
        break;
    case 2:
        m2 = getNewMatrix();;
        break;
    case 3:
        total=addMatrix(m1,m2);
        printVector(total);
        break;
    case 4:
        total=multiplyMatrix(m1,m2);
        printVector(total);
        break;
    case 5:
        break;
    }
}
void printVector(vector<vector<int>> m) {
    for (int r = 0; r < size(m); r++) {
        for (int c = 0; c < size(m); c++) {
            cout << m[r][c];
        }
    }
}
int dotProduct(vector<int> r1, vector<int> r2)
{
    int p1 = r1[0];
    int p2 = r2[0];
    for (int i = 1; i < size(r1); i++)
    {
        p1 *= r1[i];
    }
    for (int i = 1; i < size(r2); i++)
    {
        p2 *= r2[i];
    }
    return p1 + p2;
}
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