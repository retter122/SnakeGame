#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
using namespace std;

#define ArrX 20 // Array Size Y
#define ArrY 15 // Array Size X

static char Buffer[ArrY][ArrX + 1];

static unsigned int AplX = rand() % (ArrX - 1);
static unsigned int AplY = rand() % (ArrY - 1);

class Snake {
    unsigned char nar;
    vector <vector <unsigned int>> sp = { {0, 0} };
    int x, y;
public:
    bool live;
    unsigned int score;

    Snake(unsigned int _x, unsigned int _y) : x(_x), y(_y), live(true), nar('r'), score(0) { sp[0][0] = _x, sp[0][1] = _y; }
    Snake() : x(0), y(0), live(true), nar('r'), score(0) {}

    void control() {
        nar = _kbhit() ? _getch() : nar;
        for (unsigned int i = sp.size() - 1; i; --i) sp[i] = sp[i - 1];
        sp[0][0] = x; sp[0][1] = y;
        switch (nar) {
            case('w'): --y; break;
            case('s'): ++y; break;
            case('a'): --x; break;
            case('d'): ++x; break;
            default: break;
        }
        if (x == ArrX) x = 0;
        else if (x == -1) x = ArrX - 1;
        if (y == ArrY) y = 0;
        else if (y == -1) y = ArrY - 1;

        for (auto i : sp) {
            if (x == i[0] && y == i[1] && nar != 'r') {
                live = false;
                return;
            }
        }

        if (x == AplX && y == AplY) {
            sp.push_back(sp[sp.size() - 1]);
            ++score;
            bool f = true;
            while (f) {
                f = false;
                AplX = rand() % (ArrX - 1);
                AplY = rand() % (ArrY - 1);
                if (AplX == x && AplY == y) continue;
                for (auto i : sp) {
                    if (AplX == i[0] && AplY == i[1]) {
                        f = true;
                        break;
                    }
                }
            }
        }
    }

    void view() {
        for (unsigned int i = 0; i < sp.size(); ++i) {
            Buffer[sp[i][1]][sp[i][0]] = '#';
        }
        Buffer[y][x] = 'O';
    }
};

int main() {
    Snake Snk(ArrX / 2, ArrY / 2);
    while (1) {
        if (Snk.live) {
            // Clean Buffer
            for (unsigned int i = 0; i < ArrY; ++i) {
                for (unsigned int j = 0; j < ArrX; ++j) Buffer[i][j] = ' ';
                Buffer[i][ArrX] = '\0';
            }
            // Rendering Image
            Buffer[AplY][AplX] = '@';
            Snk.view();
            // Control snake
            Snk.control();
            // Clean Console
            system("cls");
            // Output Image
            cout << "+";
            for (unsigned int i = ArrX; i; --i) cout << "-";
            cout << "+" << endl;
            for (unsigned int i = 0; i < ArrY; ++i) cout << '|' << Buffer[i] << '|' << endl;
            cout << "+";
            for (unsigned int i = ArrX; i; --i) cout << "-";
            cout << "+" << endl;
            cout << "Score: " << Snk.score << endl;
            // Delay
            Sleep(170);
            continue;
        }
        cout << "You lose with score " << Snk.score << endl;
        cout << "Wanna play again? (Y/N):";
        char ans;
        cin >> ans;
        if (ans == 'Y' || ans == 'y') Snk = Snake(ArrX / 2, ArrY / 2);
        else break;
    }
    return 0;
}
