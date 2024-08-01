#include <iostream>

class Product {
public:
    void setPartA(const std::string& part) { partA = part; }
    void setPartB(const std::string& part) { partB = part; }
    void setPartC(const std::string& part) { partC = part; }
    void show() {
        std::cout << "Product parts: " << partA << ", " << partB << ", " << partC << std::endl;
    }
private:
    std::string partA;
    std::string partB;
    std::string partC;
};

class Builder {
public:
    virtual void buildPartA() = 0;
    virtual void buildPartB() = 0;
    virtual void buildPartC() = 0;
    virtual Product* getResult() = 0;
    virtual ~Builder() = default;
};

class ConcreteBuilder : public Builder {
public:
    ConcreteBuilder() { product = new Product(); }

    void buildPartA() override { product->setPartA("PartA"); }
    void buildPartB() override { product->setPartB("PartB"); }
    void buildPartC() override { product->setPartC("PartC"); }

    Product* getResult() override { return product; }

private:
    Product* product;
};

class Director {
public:
    void setBuilder(Builder* builder) { this->builder = builder; }

    void construct() {
        builder->buildPartA();
        builder->buildPartB();
        builder->buildPartC();
    }

private:
    Builder* builder;
};

int main() {
    Director director;
    Builder* builder = new ConcreteBuilder();
    director.setBuilder(builder);
    director.construct();

    Product* product = builder->getResult();
    product->show();

    delete builder;
    delete product;

    return 0;
}
