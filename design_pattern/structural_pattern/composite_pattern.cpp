#include <iostream>
#include <vector>
#include <algorithm>

class Component {
public:
    virtual void operation() throw() = 0;
    virtual void add(Component* component) throw() {}
    virtual void remove(Component* component) throw() {}
    virtual ~Component() = default;
};

class Leaf : public Component {
public:
    void operation() throw() override {
        std::cout << "Leaf operation" << std::endl;
    }
};

class Composite : public Component {
private:
    std::vector<Component*> children;
public:
    void operation() throw() override {
        std::cout << "Composite operation" << std::endl;
        for (auto& child : children) {
            child->operation();
        }
    }

    void add(Component* component) throw() override {
        children.push_back(component);
    }

    void remove(Component* component) throw() override {
        children.erase(std::remove(children.begin(), children.end(), component), children.end());
    }
};

int main() {
    Composite* root = new Composite();
    Leaf* leaf1 = new Leaf();
    Leaf* leaf2 = new Leaf();

    root->add(leaf1);
    root->add(leaf2);

    root->operation();

    delete root;
    delete leaf1;
    delete leaf2;

    return 0;
}
