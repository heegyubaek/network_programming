#include <iostream>
#include <string>
using namespace std;

class dog
{
public:
    dog()
    {
        _legs = 4;
        _bark = true;
    }

    void setDogSize(string dogSize)
    {
        _dogSize = dogSize;
    }
    virtual void setEars(string type)
    {
        _earType = type;
    }

private:
    string _dogSize, _earType;
    int _legs;
    bool _bark;
};

class breed : public dog
{
public:
    breed(string color, string size)
    {
        _color = color;
        setDogSize(size);
    }

    string getColor() { return _color; }
    void setEars(string length, string type)
    {
        _earLenght = length;
        _earType = type;
    }

protected:
    string _color, _earLenght, _earType;
};

int main()
{
    dog mongrel;
    breed labrador("yello", "large");
    mongrel.setEars("pointy");
    labrador.setEars("long", "floppy");

    cout << "Cody is a " << labrador.getColor() << " laborador" << endl;
}