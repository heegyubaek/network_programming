#include <iostream>

class AbstractClass {
public:
    void templateMethod() const {
        baseOperation1();
        requiredOperation1();
        baseOperation2();
        requiredOperation2();
    }

protected:
    void baseOperation1() const {
        std::cout << "AbstractClass: Base operation 1\n";
    }

    void baseOperation2() const {
        std::cout << "AbstractClass: Base operation 2\n";
    }

    virtual void requiredOperation1() const = 0;
    virtual void requiredOperation2() const = 0;
};

class ConcreteClass1 : public AbstractClass {
protected:
    void requiredOperation1() const override {
        std::cout << "ConcreteClass1: Implemented Operation1\n";
    }

    void requiredOperation2() const override {
        std::cout << "ConcreteClass1: Implemented Operation2\n";
    }
};

class ConcreteClass2 : public AbstractClass {
protected:
    void requiredOperation1() const override {
        std::cout << "ConcreteClass2: Implemented Operation1\n";
    }

    void requiredOperation2() const override {
        std::cout << "ConcreteClass2: Implemented Operation2\n";
    }
};

int main() {
    std::cout << "Same client code can work with different subclasses:\n";
    ConcreteClass1 concreteClass1;
    concreteClass1.templateMethod();

    std::cout << "\n";
    ConcreteClass2 concreteClass2;
    concreteClass2.templateMethod();

    return 0;
}
