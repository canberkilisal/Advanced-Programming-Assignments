// lutfi canberk ilisal

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Coordinate {
    unsigned int x;
    unsigned int y;
};

/* Begin: code taken from strutils.cpp CS201 */
/* converts string to integer */
int atoi(const string & s)
{
    return atoi(s.c_str());
}
/* End: code taken from strutils.cpp CS201 */

/* checks input from txt returns true or false and matrixSize for create matrix */
bool txtCheck ( ifstream & inputFile, vector<int>& matrixSize )
{
    string line;

    inputFile.clear();
    inputFile.seekg(0);

    unsigned int rowNum=0;
    while (getline(inputFile,line))
    {
        matrixSize.push_back(0);
        for ( int i=0; i < line.size(); i++)
        {
            if ( line[i] != '-' &&  line[i] != '#' ) // checks what txt file contains
            {
                return false;
            }
            else
            {
                matrixSize[rowNum] ++; // determines column number of matrix
            }
        }
        rowNum ++; // determines row number of matrix
    }

    if ( matrixSize.size() != 1 ) // checks number of elements of rows are equal
    {
        for (int j = 0; j < matrixSize.size()-1; j++)
        {
            if (matrixSize[j] != matrixSize[j+1])
            {
                return false;
            }
        }
    }

    return true;
}

/* converts txt file to matrix */
vector<vector<char>> txtToMatrix ( ifstream & inputFile, const vector<int>& matrixSize )
{
    string line;
    vector<vector<char>> matrix(matrixSize.size(), vector<char> (matrixSize[0]));

    inputFile.clear();
    inputFile.seekg(0);

    unsigned int count=0;
    while (getline(inputFile,line))
    {
        for ( int i=0; i < line.size(); i++)
        {
            matrix[count][i] = line[i];
        }
        count ++;
    }

    return matrix;
}

void printMatrix( const vector<vector<char>>& matrix )
{
    for ( unsigned int i=0; i<matrix.size(); i++ )
    {
        for ( unsigned int j=0; j<matrix[i].size(); j++)
        {
            cout << matrix[i][j];
        }
        cout << endl;
    }
}

/* converts string query to vector query */
void queryOrganizer( string query, vector<string>& querySplit)
{
    string queryLine, pair;
    int index, digitOfPair;
    querySplit.clear(); // sometimes function needed to use more than once therefore vector needed to clear

    index = query.find('/');
    while ( index != string::npos )  // string to vector
    {
        queryLine = query.substr(0,index);
        querySplit.push_back(queryLine);
        query = query.substr(index+1);

        index = query.find('/');
    }
    querySplit.push_back(query);


    for ( unsigned int i=0; i<querySplit.size(); i++)  // organizes query ( i.e 2s1b to ssb )
    {
        string c;
        while ( querySplit[i].size() >= 2 )
        {
            pair = querySplit[i].substr(0, 2);
            digitOfPair = atoi(pair.substr(0, 1));
            for (unsigned int j=0; j < digitOfPair; j++)
            {
                c += pair[1];
            }
            querySplit[i] = querySplit[i].substr(2);
        }
        querySplit[i] = c;
    }
}

/* checks whether query can fit into matrix, if suitable finds first star's coordinates then appoints all possible placement coordinates to vector */
/* however this placement does not test #-s possibility */
bool queryPlacer ( const vector<string>& querySplit, const vector<vector<char>>& matrix, vector<Coordinate>& match )
{
    if ( querySplit.size() > matrix.size() )
    {
        return false;
    }
    else
    {
        for ( unsigned int i=0; i<querySplit.size(); i++)
        {
            if (querySplit[i].size() > matrix[i].size())
            {
                return false;
            }
        }
        for (  unsigned int j=0; j<matrix.size(); j++)
        {
            for (  unsigned int k=0; k<matrix[j].size(); k++)
            {
                unsigned int count = 0;
                for ( unsigned int l=0; l<querySplit.size(); l++)
                {
                    if (querySplit[l].size() <= matrix[j].size() - k && querySplit.size() <= matrix.size() - j)
                    {
                        count++;
                    }
                }
                if ( count == querySplit.size() )
                {
                    Coordinate xy = {j, k};
                    match.push_back(xy);
                }
            }
        }
    }
    return true;
}

/* checks #-s problem in possible placements vector ( i.e. match ) then appends true placements to new vector */
void hashtagCheck ( const vector<string>& querySplit, const vector<vector<char>>& matrix, const vector<Coordinate>& match, vector<Coordinate>& finalMatch )
{
    unsigned int starNumQuery = 0;
    /* finds # of stars in query */
    for (unsigned int a = 0; a < querySplit.size(); a++)
    {
        for (unsigned int b = 0; b < querySplit[a].size(); b++)
        {
            if ( querySplit[a][b] == 's' )
            {
                starNumQuery++;
            }
        }
    }

    /* finds # of stars in matrix */
    for ( unsigned int k=0; k<match.size(); k++)
    {
        unsigned int starNumMatrix = 0;
        for (unsigned int i = 0; i < querySplit.size(); i++)
        {
            for (unsigned int j = 0; j < querySplit[i].size(); j++)
            {
                if ( matrix[match[k].x + i][match[k].y + j] == '-' && querySplit[i][j] == 's' ) // checks whether stars are matched with '-'
                {
                    starNumMatrix++;
                }
            }
        }
        if ( starNumMatrix == starNumQuery ) // if any star matched with '#' starNumQuery will be greater than starNumMatrix
        {
            finalMatch.push_back(match[k]);
        }
    }
}

/* finds all star coordinates for true placements vector elements then prints every placement */
void starCoordinates ( const vector<string>& querySplit, const vector<Coordinate>& finalMatch)
{
    for ( unsigned int i=0; i<finalMatch.size(); i++)
    {
        cout << "Placement number " << i+1 << ":" << endl;
        for ( unsigned int k=0; k<querySplit.size(); k++)
        {
            for ( unsigned int j=0; j<querySplit[k].size(); j++)
            {
                if ( querySplit[k][j] == 's' )
                {
                    cout << "(" << finalMatch[i].x + k << "," << finalMatch[i].y + j << ")" << " ";
                }
            }
        }
        cout << endl;
    }

}

int main() {

    string filename, query;
    ifstream inputFile;
    vector<vector<char>> matrix;
    vector<int> matrixSize;
    vector<string> querySplit;

    cout << "Please enter the file name:" << endl;
    cin >> filename;
    inputFile.open(filename);
    while (inputFile.fail())
    {
        cout << "Could not open the file. Please enter a valid file name: " << endl;
        cin >> filename;
        inputFile.open(filename);
    }

    if ( !txtCheck (inputFile, matrixSize ) )
    {
        cout << "Erroneous file content. Program terminates." << endl;
        return 0;
    }

    matrix = txtToMatrix (inputFile, matrixSize );
    cout << "The matrix file contains:" << endl;
    printMatrix(matrix);

    cout << "Enter the string query for a shape, or \"Quit\" to terminate the program:" << endl;
    cin >> query;
    while ( query != "Quit" )
    {
        vector<Coordinate> match, finalMatch;
        queryOrganizer( query, querySplit) ;

        if ( !queryPlacer ( querySplit, matrix, match ))
        {
            cout << "No placements found." << endl;
        }
        else
        {
            hashtagCheck ( querySplit, matrix, match, finalMatch );
            if ( finalMatch.size() == 0 )
            {
                cout << "No placements found." << endl;
            }
            else
            {
                starCoordinates( querySplit, finalMatch );
            }
        }
        cout << "Enter the string query for a shape, or \"Quit\" to terminate the program:" << endl;
        cin >> query;
    }

    inputFile.close();

    return 0;
}
