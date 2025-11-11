#include <iostream>
#include <string>
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

double max_total_donation = 0.0;
long long max_collector = 0;
bool hasWinner = false;
std::string line;

while (std::getline(ifs, line)) {
  std::stringstream ss(line);
  long long id;
if (!(ss >> id)) continue;

double total = 0.0;
int count = 0;
double amount;

while (true) {
  if (ss >> amount) {
    total += amount;
    count++;
} else if (ss.fail() && !ss.eof()) {
  ss.clear();
  std::string bad;
  ss >> bad;
  continue;
} else {
  break;
}
}

if (count >= 2) {
  if (!hasWinner || total > max_total_donation) {
    hasWinner = true;
    max_total_donation = total;
    max_collector = id;
}
}
}

if (hasWinner) {
  std::cout << "Highest donation total: " << max_total_donation << std::endl;
  std::cout << "-- collected by id: " << max_collector << std::endl;
} else {
  std::cout << "No winner." << std::endl;
}

return 0;
}