#include <iostream>

class Subsystem1 {
public:
    void operation1() {
        std::cout << "Subsystem1: operation1" << std::endl;
    }
};

class Subsystem2 {
public:
    void operation2() {
        std::cout << "Subsystem2: operation2" << std::endl;
    }
};

class Facade {
private:
    Subsystem1* subsystem1;
    Subsystem2* subsystem2;
public:
    Facade() {
        subsystem1 = new Subsystem1();
        subsystem2 = new Subsystem2();
    }

    ~Facade() {
        delete subsystem1;
        delete subsystem2;
    }

    void operation() {
        subsystem1->operation1();
        subsystem2->operation2();
    }
};

int main() {
    Facade* facade = new Facade();
    facade->operation();
    delete facade;

    return 0;
}
