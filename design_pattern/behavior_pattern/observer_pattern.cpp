#include <iostream>
#include <vector>
#include <memory>

// 옵저버 인터페이스
class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() = default;
};

// 구체적인 옵저버
class ConcreteObserver : public Observer {
public:
    void update(const std::string& message) override {
        std::cout << "ConcreteObserver received: " << message << std::endl;
    }
};

// 주체 인터페이스
class Subject {
public:
    virtual void add_observer(std::shared_ptr<Observer> observer) = 0;
    virtual void remove_observer(std::shared_ptr<Observer> observer) = 0;
    virtual void notify_observers() = 0;
    virtual ~Subject() = default;
};

// 구체적인 주체
class ConcreteSubject : public Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers_;
    std::string state_;

public:
    void add_observer(std::shared_ptr<Observer> observer) override {
        observers_.push_back(observer);
    }

    void remove_observer(std::shared_ptr<Observer> observer) override {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
    }

    void set_state(const std::string& state) {
        state_ = state;
        notify_observers();
    }

    void notify_observers() override {
        for (const auto& observer : observers_) {
            observer->update(state_);
        }
    }
};

int main() {
    std::shared_ptr<ConcreteSubject> subject = std::make_shared<ConcreteSubject>();
    std::shared_ptr<ConcreteObserver> observer1 = std::make_shared<ConcreteObserver>();
    std::shared_ptr<ConcreteObserver> observer2 = std::make_shared<ConcreteObserver>();

    subject->add_observer(observer1);
    subject->add_observer(observer2);

    subject->set_state("New State 1");
    subject->set_state("New State 2");

    return 0;
}
