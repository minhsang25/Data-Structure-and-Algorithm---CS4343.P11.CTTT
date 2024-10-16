#include <iostream>
using namespace std;
class TowerOfHanoi
{
public:
    TowerOfHanoi(int n) : num_disks(n)
    {
        // Initialize the towers with disks on the first tower
        for (int i = n; i >= 1; --i)
        {
            towers[0][top[0]++] = i; // Place disks in the first tower
        }
    }

    void moveDisk(int fromTower, int toTower)
    {
        if (top[fromTower] > 0)
        {
            int disk = towers[fromTower][--top[fromTower]];
            towers[toTower][top[toTower]++] = disk;
            cout << "Move disk " << disk << " from tower " << fromTower + 1 << " to tower " << toTower + 1 << endl;
        }
    }

    void solve(int n, int fromTower, int toTower, int auxTower)
    {
        if (n == 1)
        {
            moveDisk(fromTower, toTower);
            return;
        }
        solve(n - 1, fromTower, auxTower, toTower); // Move n-1 disks to auxiliary tower
        moveDisk(fromTower, toTower);               // Move the nth disk to target tower
        solve(n - 1, auxTower, toTower, fromTower); // Move n-1 disks from auxiliary to target tower
    }

    void start()
    {
        cout << "Initial Towers:" << endl;
        printTowers();
        solve(num_disks, 0, 2, 1); // Solve the puzzle
        cout << "Final Towers:" << endl;
        printTowers();
    }

private:
    static const int MAX_DISKS = 64; // Max number of disks, can be adjusted
    int num_disks;
    int towers[3][MAX_DISKS] = {0}; // Towers represented as arrays
    int top[3] = {0};               // Track the top of each tower

    void printTowers()
    {
        for (int i = 0; i < 3; ++i)
        {
            cout << "Tower " << i + 1 << ": ";
            for (int j = 0; j < top[i]; ++j)
            {
                cout << towers[i][j] << " ";
            }
            cout << std::endl;
        }
    }
};

int main()
{
    int num_disks = 3; // Change this value for different numbers of disks
    TowerOfHanoi hanoi(num_disks);
    hanoi.start();
    return 0;
}
