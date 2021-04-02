#include <iostream>
#include <vector>

class X {
private:
    int value1;
    int value2;
public:
    X(const int value1, const int value2) : value1{value1}, value2{value2} {}

    friend std::ostream &operator<<(std::ostream &out, const X &x) {
        return out << x.value1 << " " << x.value2 << std::endl;
    }
};

class A {
private:
    int value1;
    int value2;
public:
    A(const int value1, const int value2) : value1{value1}, value2{value2} {
        std::cout << "KONSTRUKTOR ARGUMENTOWY" << std::endl;
    }

    A(const A &a) : value1{a.value1}, value2{a.value2} {
        std::cout << "KONSTRUKTOR KOPIUJACY" << std::endl;
    }

    A(A &&a) : value1{a.value1}, value2{a.value2} {
        std::cout << "KONSTRUKTOR PRZENOSZACY" << std::endl;
    }

    virtual ~A() {
        std::cout << "DESTRUKTOR" << std::endl;
    };

    friend std::ostream &operator<<(std::ostream &out, const A &a) {
        return out << a.value1 << " " << a.value2 << std::endl;
    }
};


int main() {

    // Jaka jest roznica pomiedzy funkcja push_back oraz emplace_back?

    // 1
    // push_back jest funkcja ktora pozwala dodawac element na koniec std::vector
    // od samego poczatku, podczas gdy funkcja emplace_back zostala dodana w C++11

    // 2
    // Metoda emplace_back umozliwia podawanie tylko argumentow konstruktora obiektu,
    // ktory chcesz dodac do std::vector
    // Metoda push_back wymaga podania calego obiektu
    // Przedstawilem to na przykladzie klasy X

    // std::vector<X> x;
    // x.push_back(X(10, 20));
    // x.emplace_back(X(10, 20));
    // x.emplace_back(10, 20);
    // x.push_back(10, 20); // BLAD

    // 3
    // Kiedy typem std::vector jest typ wbudowany wtedy nie ma roznicy pomiedzy stosowaniem
    // push_back oraz emplace_back
    // Kiedy typem wbudowanym std::vector jest user defined type wtedy emplace_back jest
    // znacznie bardziej wydajny niz push_back

    // Co sie dzieje kiedy jako argument push_back podajemy obiekt tymczasowy?
    // a. wywolany jest konstruktor ktory pozwala inicjalizowac obiekt tymczasowy
    // b. w std::vector tworzona jest kopia obiektu tymczasowego
    // c. wywolany jest destruktor, ktory sprzata po obiekcie tymczasowym

    // Co sie dzieje kiedy jako argument emplace_back podajemy argumenty na podstawie ktorych stworzytmy obiekt?
    // a. po prostu nie jest tworzony zaden obiekt tymczasowy tylko podany obiekt jest
    // od razu osadzany w std::vector

    std::vector<A> a;
    // a.push_back(A(10, 20));
    // a.emplace_back(A(10, 20)); // TUTAJ ZADZIALA TAK SAMO JAK DLA push_back
    // a.emplace_back(10, 20);

    A element{11, 22};
    // a.push_back(element);
    // a.emplace_back(element);

    for (const auto &v : a) {
        std::cout << v << std::endl;
    }

    return 0;
}
