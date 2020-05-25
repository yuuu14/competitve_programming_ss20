#include <iostream>
#include <string>
#include <vector>

int main() {
    unsigned int length;
    std::cin >> length;
    std::vector<std::string> names;
    std::string name;
    for (unsigned i = 0; i < length; ++i) {
        std::cin >> name;
        names.push_back(name);
    }
    for (std::vector<std::string>::iterator it = names.begin(); it != names.end(); ++it)
        std::cout << "Hello " << *it << "!" <<  std::endl;

    return 0;
}