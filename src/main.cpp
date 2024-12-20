#include <fstream>
#include <iostream>

constexpr char PS3 = 0x0F;
constexpr char X360 = 0x0E;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "Usage: " << "mcla_save_converter <save file path>" << std::endl;
        return 1;
    }

    std::fstream file(argv[1], std::ios::in | std::ios::out | std::ios::binary);

    if (!file) {
        std::cerr << "Failed to open file: " << argv[1] << std::endl;
        return 1;
    }

    file.seekg(0x3);
    auto type = file.get();

    if (type == PS3) {
        std::cout << "Converting PS3 save to Xbox 360 save" << std::endl;
        file.seekp(0x3);
        file.put(X360);
    } else if (type == X360) {
        std::cout << "Converting Xbox 360 save to PS3 save" << std::endl;
        file.seekp(0x3);
        file.put(PS3);
    } else {
        std::cerr << "Not a valid MC:LA save file" << std::endl;
        return 1;
    }

    return 0;
}
