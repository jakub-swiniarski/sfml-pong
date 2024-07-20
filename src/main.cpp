#include "App.hpp"
#include <exception>
#include <iostream>
#include <stdexcept>

int main(void) {
    try {
        App app;
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        throw std::runtime_error("Unknown error");
    }

    return 0;
}
