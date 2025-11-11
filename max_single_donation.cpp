#include <iostream>
#include <sstream>
#include <fstream>

int main() {
  std::string filename;
  std::cout << "Enter donation filename: ";
  std::cin >> filename;
  std::ifstream ifs(filename);
  if (!ifs.is_open()) {
    std::cout << "Failed to open file " << filename << "." << std::endl;
    return 1;
  }

  double max_donation = 0.0;
  long long max_collector = 0;
  bool hasWinner = false;
  std::string line;

  while (std::getline(ifs, line)) {
    std::stringstream ss(line);
    long long id;
    if (!(ss >> id)) continue;

    double amount;
    while (true) {
      if (ss >> amount) {
        if (!hasWinner || amount > max_donation) {
          hasWinner = true;
          max_donation = amount;
          max_collector = id;
        }
      } else if (ss.fail() && !ss.eof()) {
        ss.clear();
        std::string bad;
        ss >> bad;
        continue;
      } else {
        break;
      }
    }
  }

  if (hasWinner) {
    std::cout << "Highest single donation: " << max_donation << std::endl;
    std::cout << "-- collected by id: " << max_collector << std::endl;
  } else {
    std::cout << "No winner." << std::endl;
  }

  return 0;
}