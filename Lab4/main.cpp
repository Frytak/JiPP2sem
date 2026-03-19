#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

template <typename T>
T maxValue(T a, T b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

template <typename T>
void swapValues(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
void printArray(T arr[], int size) {
    std::cout << "[";
    for (int i = 0; i < size - 1; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[size-1] << "]";
}

template<typename T>
class Box {
private:
    T value;
public:
    Box(T v) : value(v) {};

    void set(T v) {
        this->value = v;
    }

    T get() const {
        return this->value;
    }

    void print() const {
        std::cout << "Box[" << this->value << "]";
    }
};

template<typename T>
class Pair {
private:
    T first;
    T second;
public:
    Pair(T a, T b) : first(a), second(b) {};

    T sum() const {
        return first + second;
    };
};

template<typename T>
class Vector2D {
public:
    T x;
    T y;

    Vector2D(T x, T y) : x(x), y(y) {};

    T lengthSquared() const {
        return std::pow(x, 2) + std::pow(y, 2);
    }
};

template<typename T>
T dotProduct(const Vector2D<T>& a, const Vector2D<T>& b) {
    return (a.x * b.x) + (a.y * b.y);
}

template<typename T>
void printVector(const std::vector<T>& v) {
    printArray(v.data(), v.size());
}

int main() {
    std::printf("\x1b[1m\x1b[34m=== Zad 1 ===\x1b[0m\n");
    std::printf("Przykład: %d\n", maxValue<int>(4, 8));
    std::printf("Przykład: %lf\n", maxValue<double>(4., 8.));
    std::printf("Przykład: %c\n", maxValue<char>('d', 'a'));
    std::printf("\n");

    int a1 = 4, b1 = 8;
    float a2 = 4., b2 = 8.;
    std::string a3 = "A3", b3 = "B3";

    std::printf("\x1b[1m\x1b[34m=== Zad 2 ===\x1b[0m\n");
    swapValues<int>(a1, b1);
    std::printf("Przykład: %d, %d\n", a1, b1);
    swapValues<float>(a2, b2);
    std::printf("Przykład: %lf, %lf\n", a2, b2);
    swapValues<std::string>(a3, b3);
    std::printf("Przykład: %s, %s\n", a3.c_str(), b3.c_str());
    std::printf("\n");

    int arr1[3] = {1, 2, 3};
    std::string arr2[5] = {"A", "B", "C", "D", "E"};

    std::printf("\x1b[1m\x1b[34m=== Zad 3 ===\x1b[0m\n");
    printArray(arr1, 3);
    std::printf("\n");
    printArray(arr2, 5);
    std::printf("\n\n");

    Box<int> boxed_int(42);
    Box<std::string> boxed_str("Kot");

    std::printf("\x1b[1m\x1b[34m=== Zad 4 ===\x1b[0m\n");
    std::printf("Wartość: %d\n", boxed_int.get());
    std::printf("Wartość: %s\n", boxed_str.get().c_str());
    boxed_int.set(13);
    boxed_int.print();
    std::printf("\n");
    boxed_str.print();
    std::printf("\n\n");

    Pair<int> pair_int(13, 42);
    Pair<std::string> pair_str("Kot", "Pies");

    // sum() działa dla std::string, bo std::string ma implementację dla operaotra '+'
    std::printf("\x1b[1m\x1b[34m=== Zad 5 ===\x1b[0m\n");
    std::printf("Suma: %d\n", pair_int.sum());
    std::printf("Suma: %s\n", pair_str.sum().c_str());
    std::printf("\n");

    Vector2D<int> vec2_int(3, 4);
    Vector2D<double> vec2_double(3., 4.);

    std::printf("\x1b[1m\x1b[34m=== Zad 6 ===\x1b[0m\n");
    std::printf("Długość do kwadratu: %d\n", vec2_int.lengthSquared());
    std::printf("Długość do kwadratu: %lf\n", vec2_double.lengthSquared());
    std::printf("o: %d\n", dotProduct(vec2_int, Vector2D(1, 2)));
    std::printf("\n");

    std::vector<int> vec_int;
    vec_int.push_back(1);
    vec_int.push_back(2);
    vec_int.push_back(3);
    vec_int.push_back(4);

    std::printf("\x1b[1m\x1b[34m=== Zad 7 ===\x1b[0m\n");
    printVector(vec_int);
    std::printf("\n\n");

    std::vector<int> v = {7, 2, 9, 1, 5, 2};

    std::printf("\x1b[1m\x1b[34m=== Zad 8 ===\x1b[0m\n");
    std::sort(v.begin(), v.end());
    std::printf("Największy element: %d\n", *std::max_element(v.begin(), v.end()));
    std::printf("Suma: %d\n", std::accumulate(v.begin(), v.end(), 0));
}
