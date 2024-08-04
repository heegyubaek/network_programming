#include <iostream>
#include <string>

// Memento
class Memento {
private:
    std::string state_;

public:
    explicit Memento(std::string state) : state_(std::move(state)) {}

    std::string get_state() const {
        return state_;
    }
};

// Originator
class Originator {
private:
    std::string state_;

public:
    void set_state(const std::string& state) {
        state_ = state;
    }

    std::string get_state() const {
        return state_;
    }

    Memento create_memento() const {
        return Memento(state_);
    }

    void restore_from_memento(const Memento& memento) {
        state_ = memento.get_state();
    }
};

// Caretaker
class Caretaker {
private:
    Memento memento_;

public:
    explicit Caretaker(Memento memento) : memento_(std::move(memento)) {}

    Memento get_memento() const {
        return memento_;
    }
};

int main() {
    Originator originator;
    originator.set_state("State1");
    Caretaker caretaker(originator.create_memento());

    originator.set_state("State2");
    std::cout << "Current state: " << originator.get_state() << std::endl;

    originator.restore_from_memento(caretaker.get_memento());
    std::cout << "Restored state: " << originator.get_state() << std::endl;

    return 0;
}
