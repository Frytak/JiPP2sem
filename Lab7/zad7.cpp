#include <algorithm>
#include <compare>
#include <iostream>
#include <vector>

struct Student {
    int grade;

    friend std::strong_ordering operator<=>(const Student& lhs, const Student& rhs) { return lhs.grade <=> rhs.grade; }
};

int main() {
    std::vector<Student> studenci = { Student(5), Student(4), Student(5), Student(2), Student(3) };
    std::sort(studenci.begin(), studenci.end());

    for (auto student : studenci) {
        std::cout << student.grade << " ";
    }
    std::cout << std::endl;
}
