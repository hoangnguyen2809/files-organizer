#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int main() {
    // Specify the path to the directory you want to access
    fs::path folderPath = R"(D:\Downloads\Users\vieth\Desktop\Gaming)";

    // Iterate through the contents of the directory
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        // Print the name of each file or directory in the folder
        std::cout << entry.path().filename() << std::endl;
    }

    return 0;
}
