#include <iostream>
#include <fstream>
#include <vector>
#include <thread>

using namespace std;

/*  ---------------------------------------------------------
            G L O B A L        V A R I A B L E S
    2D Vectors to represent first, second and result Matrix
    r-> for rows                            c-> for columns
    ---------------------------------------------------------  */
vector<vector<int>> firstMatrix,secondMatrix,resultMatrix;
                int first_r, first_c, second_r, second_c;

/*  ---------------------------------------------------------
           R    E   A   D       I   N   P   U   T
    This function uses pointer to a FILE "input file" and i
    declared a variable to get element by element, store
    row in a vector, then push this vector into the matrix.
    ---------------------------------------------------------  */

void readInput()
{
    FILE* input;
    input = freopen("input.txt","r",stdin);


    int tmp;
    vector<int> temp;

    cin >> first_r >> first_c;

    for(int i = 0; i < first_r; i++)
    {
        for(int j = 0; j < first_c; j++)
        {
            cin >> tmp;
            temp.push_back(tmp);
        }
        firstMatrix.push_back(temp);
        temp.clear();
    }

    cin >> second_r >> second_c;

    for(int i = 0; i < second_r; i++)
    {
        for(int j = 0; j < second_c; j++)
        {
            cin >> tmp;
            temp.push_back(tmp);
        }
        secondMatrix.push_back(temp);
        temp.clear();
    }
    fclose(input);
}

/*  ---------------------------------------------------------
           E L E M E N T   *    E L E M E N T
    First we initialize our result matrix with zeros, then we
    create threads = number of elements in the result matrix
    = rows in matrix 1 * cols in matrix 2, then we calculate.
    ---------------------------------------------------------  */

vector<vector<int>> matrixMultiplyByElement()
{
    vector<vector<int>> resultMatrix(first_r, vector<int> (second_c, 0));
    vector<thread> threads(firstMatrix.size() * secondMatrix[0].size());

    int t = 0;

    for(int i = 0; i < firstMatrix.size(); i++)
        for(int j = 0; j < secondMatrix[0].size(); j++)
        {
            threads[t] = thread{[&]()
            {
                for(int k = 0; k < firstMatrix[0].size(); k++)
                    resultMatrix[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }};
            threads[t].join();
            t++;
        }
    return resultMatrix;
}

/*  ---------------------------------------------------------
                    T H R E A D S = R O W S
    First we initialize our result matrix with zeros, then we
    create threads = number of matrix 1 rows, then we calculate
    using threads class.
    ---------------------------------------------------------  */

vector<vector<int>> matrixMultiplyByRow()
{
    vector<vector<int>> resultMatrix(first_r, vector<int> (second_c, 0));
    vector<thread> threads(firstMatrix.size());
    int t = 0;

    for(int i = 0; i < firstMatrix.size(); i++){
        threads[t] = thread{[&](){
            for(int j = 0; j < secondMatrix[0].size(); j++){
                for(int k = 0; k < firstMatrix[0].size(); k++){
                    resultMatrix[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
                }
            }
        }};
        threads[t].join();
        t++;
    }
    return resultMatrix;
}

/*  ---------------------------------------------------------
                P   R   I   N   T   I   N   G
    ---------------------------------------------------------  */

void writeOutput(vector<vector<int>> byElement, auto byElementTime, vector<vector<int>> byRow, auto byRowTime)
{
    ofstream output;
    output.open("output.txt");

    for(int i = 0; i < byElement.size(); i++)
    {
        for(int j = 0; j < byElement[0].size(); j++)
            output << byElement[i][j] << " ";
        output << "\n";
    }
   output << chrono::duration <double, micro> (byElementTime).count() << " ms" << endl;

    for(int i = 0; i < byRow.size(); i++)
    {
        for(int j = 0; j < byRow[0].size(); j++)
            output << byRow[i][j] << " ";
        output << "\n";
    }
   output << chrono::duration <double, micro> (byRowTime).count() << " ms" << endl;

    output.close();
}

int main()
{
    readInput();

    vector<vector<int>> byElement,byRow;

    auto start = chrono::steady_clock::now();
    byElement = matrixMultiplyByElement();
    auto end = chrono::steady_clock::now();
    auto byElementTime = end - start;

    start = chrono::steady_clock::now();
    byRow = matrixMultiplyByRow();
    end = chrono::steady_clock::now();
    auto byRowTime = end - start;

    writeOutput(byElement, byElementTime, byRow, byRowTime);
    return 0;
}
