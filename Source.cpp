#include <iostream>
#include <filesystem>
#include <clocale>
#include <cwctype>
#include <unordered_set>

namespace fs = std::filesystem;

std::string getCategoryFolder(const std::string& extension) {
    static const std::unordered_set<std::string> codeExtensions = { ".cpp", ".h", ".hpp", ".java", ".py", ".cs", ".rb", ".php", ".js", ".html", ".css", ".xml", ".json" };
    if (extension == ".pdf") {
        return "PDF";
    }
    else if (extension == ".docx" || extension == ".doc") {
        return "Documents";
    }
    else if (extension == ".jpg" || extension == ".png" || extension == ".gif") {
        return "Images";
    }
    else if (extension == ".mp4" || extension == ".avi" || extension == ".mkv") {
        return "Videos";
    }
    else if (codeExtensions.find(extension) != codeExtensions.end()) {
        return "Code";
    }
    else {
        return "Other"; 
    }
}

int main() {
    std::cout << "   __ _ _                                 _            " << std::endl;
    std::cout << "  / _(_) |___ ___  ___ _ _ __ _ __ _ _ _ (_)______ _ _ " << std::endl;
    std::cout << " |  _| | / -_|_-< / _ \\ '_/ _` / _` | ' \\| |_ / -_) '_|" << std::endl;
    std::cout << " |_| |_|_\\___/__/ \\___/_| \\__, \\__,_|_||_|_/__\\___|_|  " << std::endl;
    std::cout << "                          |___/                        " << std::endl;
    
    
    // Specify the path to the directory you want to access
    std::cout << "Enter the path to your Download folder: ";
    std::cout << std::endl;

    fs::path folderPath = R"(D:\Downloads)";
    
    std::unordered_set<std::wstring> extensionsType;
    int count = 0;

    try {
        // Iterate through the contents of the directory
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            // Check if the entry is a regular file
            if (fs::is_regular_file(entry)) {
                // Extract the file extension
                std::wstring extension = entry.path().extension();
                // Print the file extension
                if (extensionsType.find(extension) == extensionsType.end())
                {
                    extensionsType.insert(extension);
                    std::wcout << L"File extension: " << extension << std::endl;
                }
            }
            count++;
        }
    }
    catch (const std::filesystem::filesystem_error& ex) {
        // Handle filesystem error
        std::cerr << "Error accessing directory: " << ex.what() << std::endl;
    }
    catch (const std::exception& ex) {
        // Handle other exceptions
        std::cerr << "An error occurred: " << ex.what() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "There are " << extensionsType.size() << " types of file" << std::endl;
    

    return 0;
}
