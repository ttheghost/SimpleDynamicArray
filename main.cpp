#include "DynamicArray.hpp"

int main() {
  std::cout << "=== Creating array1 ===\n";
  DynamicArray<std::string> array1;
  array1.push_back("Hello");
  array1.push_back("World");

  std::cout << "\n=== Copy construction (array2) ===\n";
  DynamicArray<std::string> array2 = array1;

  std::cout << "\n=== Move construction (array3) ===\n";
  DynamicArray<std::string> array3 = std::move(array1);

  std::cout << "\n=== Creating array4 for assignment ===\n";
  DynamicArray<std::string> array4;

  std::cout << "\n=== Copy assignment ===\n";
  array4 = array2;

  std::cout << "\n=== Move assignment ===\n";
  array4 = std::move(array3);

  std::cout << "\n=== Function returning by value ===\n";
  auto make_array = []() -> DynamicArray<std::string> {
    DynamicArray<std::string> temp;
    temp.push_back("Temporary");
    return temp;
  };

  DynamicArray<std::string> array5 = make_array();

  std::cout << "\n=== Destructors will be called ===\n";
  return 0;
}
