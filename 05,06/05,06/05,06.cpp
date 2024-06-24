#include <iostream>

using namespace std;

class Animal {
protected:
    string name;
    int kg;

public:
    Animal() = default;
    Animal(string n, int k) : name(n), kg(k) {}
    virtual void Print() = 0;
    virtual void Accept(class IVisitor& visitor) = 0;
};

struct IAnimal {
    virtual void Eat() = 0;
    virtual void Move() = 0;
};

struct IBird {
    virtual void Fly() = 0;
};

struct ISwim {
    virtual void Swim() = 0;
};

class IVisitor {
public:
    virtual void Visit(class Cat& cat) = 0;
    virtual void Visit(class Parrot& parrot) = 0;
};

class DrawVisitor : public IVisitor {
public:
    void Visit(Cat& cat) override {
        cout << "Drawing Cat" << endl;
    }

    void Visit(Parrot& parrot) override {
        cout << "Drawing Parrot" << endl;
    }
};

class Cat : public Animal, public IAnimal {
    string color;

public:
    Cat(string n, int k, string c) : Animal(n, k), color(c) {}

    void Print() {
        cout << "Name: " << name << endl;
        cout << "Kg: " << kg << endl;
        cout << "Color: " << color << endl;
    }

    void Eat() {
        cout << "Cat eats" << endl;
    }

    void Move() {
        cout << "Cat moves" << endl;
    }

    void Accept(IVisitor& visitor) override {
        visitor.Visit(*this);
    }
};

class Parrot : public Animal, public IAnimal, public IBird {
public:
    Parrot(string n, int k) : Animal(n, k) {}

    void Print() {
        cout << "Name: " << name << endl;
        cout << "Kg: " << kg << endl;
    }

    void Eat() {
        cout << "Parrot eats" << endl;
    }

    void Move() {
        cout << "Parrot moves" << endl;
    }

    void Fly() {
        cout << "Parrot flies" << endl;
    }

    void Accept(IVisitor& visitor) override {
        visitor.Visit(*this);
    }
};

int main() {
    IAnimal* ref = new Cat("Cat", 3, "white");
    ref->Eat();
    ref->Move();

    ref = new Parrot("Ara", 2);
    ref->Eat();
    ref->Move();

    IBird* f = new Parrot("Ara", 3);
    f->Fly();

    DrawVisitor drawVisitor;
    Cat cat("Cat", 3, "white");
    Parrot parrot("Ara", 2);

    cat.Accept(drawVisitor);
    parrot.Accept(drawVisitor);

    delete ref;
    delete f;
}
