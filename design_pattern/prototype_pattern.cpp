#include <iostream>

class Prototype {
public:
    virtual Prototype* clone() const = 0;
    virtual void use() = 0;
    virtual ~Prototype() = default;
};

class ConcretePrototype1 : public Prototype {
public:
    Prototype* clone() const override {
        return new ConcretePrototype1(*this);
    }

    void use() override {
        std::cout << "Using ConcretePrototype1" << std::endl;
    }
};

class ConcretePrototype2 : public Prototype {
public:
    Prototype* clone() const override {
        return new ConcretePrototype2(*this);
    }

    void use() override {
        std::cout << "Using ConcretePrototype2" << std::endl;
    }
};

int main() {
    Prototype* prototype1 = new ConcretePrototype1();
    Prototype* clone1 = prototype1->clone();
    clone1->use();

    Prototype* prototype2 = new ConcretePrototype2();
    Prototype* clone2 = prototype2->clone();
    clone2->use();

    delete prototype1;
    delete clone1;
    delete prototype2;
    delete clone2;

    return 0;
}
