#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <sstream>
#include <vector>

int setMonitorType(std::string) {
    
}

std::vector<std::string> findExternal() {
    std::array<char, 128> buffer;
    std::string result;

    const auto closePipe = [](FILE* stream) { pclose(stream); };
    std::unique_ptr<FILE, decltype(closePipe)> pipe(
        popen("grep -Hw '^connected$' /sys/class/drm/*/status | cut -d'/' -f5", "r"),
        closePipe);

    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // Parse each line
    std::vector<std::string> lines;
    std::stringstream ss(result);
    std::string line;

    while (std::getline(ss, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        lines.push_back(line);
    }

    return lines;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string arg = argv[1];

        if (arg == "--findExternal" or arg == "-f") {
            try {
                for (const auto& display : findExternal()) {
                    std::cout << display << '\n';
                }
            } catch (const std::exception& error) {
                std::cerr << "Failed to detect displays: " << error.what() << '\n';
                 return 1;
            }
        }

        if (arg == "--set" or arg == "-s") {
            
        }

    }

}
