#include <iostream>
#include <string>
#include <unordered_map>

class Flyweight {
public:
    virtual void operation(int extrinsicState) = 0;
    virtual ~Flyweight() = default;
};

class ConcreteFlyweight : public Flyweight {
private:
    std::string intrinsicState;
public:
    ConcreteFlyweight(const std::string& state) : intrinsicState(state) {}
    void operation(int extrinsicState) override {
        std::cout << "Intrinsic State: " << intrinsicState
                  << ", Extrinsic State: " << extrinsicState << std::endl;
    }
};

class FlyweightFactory {
private:
    std::unordered_map<std::string, Flyweight*> flyweights;
public:
    Flyweight* getFlyweight(const std::string& key) {
        if (flyweights.find(key) == flyweights.end()) {
            flyweights[key] = new ConcreteFlyweight(key);
        }
        return flyweights[key];
    }

    ~FlyweightFactory() {
        for (auto pair : flyweights) {
            delete pair.second;
        }
    }
};

int main() {
    FlyweightFactory* factory = new FlyweightFactory();

    Flyweight* fw1 = factory->getFlyweight("state1");
    Flyweight* fw2 = factory->getFlyweight("state1");
    Flyweight* fw3 = factory->getFlyweight("state2");

    fw1->operation(10);
    fw2->operation(20);
    fw3->operation(30);

    delete factory;

    return 0;
}
