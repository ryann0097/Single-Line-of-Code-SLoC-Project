#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  std::ifstream ifs{ "test.cpp" };
  std::string line;

  if (ifs.is_open()) {
    while (std::getline(ifs, line)) {
      std::cout << ">>> Line: " << std::quoted(line) << "\n";
    }
    ifs.close();
  }

  return 0;
}
