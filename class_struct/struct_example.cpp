#include <iostream>

using namespace std;

struct PERSON
{
    int age;
    long ss;
    float weight;
    char name[25];
} family_member;

struct CELL
{
    unsigned short character : 8;
    unsigned short foreground : 3;
    unsigned short intensity : 1;
    unsigned short background : 3;
    unsigned short blink : 1;
} screen[25][80];

int main()
{
    struct PERSON sister;
    PERSON brother;
    sister.age = 13;
    brother.age = 7;

    cout << "sister.age = " << sister.age << '\n';
    cout << "brother.age = " << brother.age << '\n';

    CELL my_cell;
    my_cell.character = 1;
    cout << "my_cell.character = " << my_cell.character << endl;
}