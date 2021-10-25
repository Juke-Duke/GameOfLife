#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

//Check a cell and all bordering cells
//If its >1 && <=3, then it lives
//If an empty cell has EXACTLY 3 neighbors, it comes to life

//Surrounding Cells:
//Cells: Up to 8
//Border: Up to 5 -> Border Cells: (0,1-7) (1-19,0) (20,1-7) (1-19,8)
//Corner: Up to 3 -> Corner Cells: (0,0) (0,8) (20,0) (20,8)

//Ex. (3,1) -> (2,0) (3,0) (4,0)         (1,0) -> (0,0) (1,0) (2,0)
//			   (2,1) (3,1) (4,1)                  (0,1) (1,1) (2,1)
//             (2,2) (3,2) (4,2)

vector<vector<char>> NextGeneration(vector<vector<char>> world);
int Surrounding(vector<vector<char>> world, int row, int col);
bool isAlive(vector<vector<char>> world, int row, int col);
void Display(vector<vector<char>> world);

int main()
{
    vector<vector<char>> world;
    vector<char> top;
    vector<char> bot;

    for (int i = 0; i < 22; ++i)
    {
        top.push_back('-');
        bot.push_back('-');
    }

    world.push_back(top);

	string line;

	ifstream file("life.txt");

    while (getline(file, line))
    {
        vector<char> row;

        row.push_back('-');
        for (char c : line)
            row.push_back(c);
        row.push_back('-');

        world.push_back(row);
    }

    world.pop_back();
    world.push_back(bot);

    cout << "Initial World" << endl;

    for (int i = 1; i < world.size() - 1; ++i)
    {
        for (int j = 1; j < world[i].size() - 1; ++j)
            cout << world[i][j];

        cout << endl;
    }

    cout << endl;
    cout << "Generation Simulation Limit: ";
    int gen = 0;
    cin >> gen;

    cout << endl;

    for (int i = 1; i < gen + 1; ++i)
    {
        cout << "Generation " << i << endl;
        Display(NextGeneration(world));
        world = NextGeneration(world);

        cout << endl;
    }

    return 0;
}

bool isAlive(vector<vector<char>> world, int row, int col)
{
    if (world[row][col] == '*')
        return true;

    return false;
}

int Surrounding(vector<vector<char>> world, int row, int col)
{
    int mob = 0;
    
    if (isAlive(world, row - 1, col - 1) == true) mob++;

    if (isAlive(world, row, col - 1) == true) mob++;

    if (isAlive(world, row + 1, col - 1) == true) mob++;

    if (isAlive(world, row - 1, col) == true) mob++;

    if (isAlive(world, row + 1, col) == true) mob++;

    if (isAlive(world, row - 1, col + 1) == true) mob++;

    if (isAlive(world, row, col + 1) == true) mob++;

    if (isAlive(world, row + 1, col + 1) == true) mob++;

    return mob;
}

void Display(vector<vector<char>> world)
{
    for (int i = 1; i < world.size() - 1; ++i)
    {
        for (int j = 1; j < world[i].size() - 1; ++j)
            cout << world[i][j];

        cout << endl;
    }
}

vector<vector<char>> NextGeneration(vector<vector<char>> world)
{
    vector<vector<char>> newWorld = world;

    for (int i = 1; i < world.size()-1; ++i)
    {
        for (int j = 1; j < world[i].size()-1; ++j)
        {
            if ((isAlive(world, i, j) == false && Surrounding(world, i, j) == 3) || (isAlive(world, i, j) == true && Surrounding(world, i, j) > 1 && Surrounding(world, i, j) < 4))
                newWorld[i][j] = '*';
            else newWorld[i][j] = '-';
        }
    }

    return newWorld;
}
