//
//  main.cpp
//  bounded_enum
//

#include "bounded_enum.hpp"
#include <iostream>

int
  main(int argc, const char* argv[]) {
    std::cout << "Hello, world. This is an example.\n";
    enum class chip_config { low_power, high_power, off, uninitialised };
    using chip_config_bt = bounded_enum<chip_config, chip_config::low_power, chip_config::uninitialised>;
    chip_config_bt from_spi;

    std::cout << "The possible chip configurations are ";
    for (const auto& i : from_spi) {
        std::cout << i << ", ";
    }
    std::cout << "\n";

    std::cout << "Which configuration do you want?\n> ";
    std::cin >> from_spi;

    return 0;
}
