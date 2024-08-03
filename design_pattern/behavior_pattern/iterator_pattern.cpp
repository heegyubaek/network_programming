#include <iostream>
#include <vector>

class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual int next() = 0;
    virtual ~Iterator() = default;
};

class ConcreteIterator : public Iterator {
private:
    std::vector<int>::iterator current_;
    std::vector<int>::iterator end_;

public:
    ConcreteIterator(std::vector<int>::iterator start, std::vector<int>::iterator end)
        : current_(start), end_(end) {}

    bool hasNext() override {
        return current_ != end_;
    }

    int next() override {
        return *current_++;
    }
};

class IterableCollection {
private:
    std::vector<int> items_;

public:
    void add(int item) {
        items_.push_back(item);
    }

    Iterator* createIterator() {
        return new ConcreteIterator(items_.begin(), items_.end());
    }
};

int main() {
    IterableCollection collection;
    collection.add(1);
    collection.add(2);
    collection.add(3);

    Iterator* iterator = collection.createIterator();
    while (iterator->hasNext()) {
        std::cout << "Item: " << iterator->next() << std::endl;
    }
    delete iterator;

    return 0;
}
