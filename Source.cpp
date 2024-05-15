#include <iostream>
#include <filesystem>
#include <cwctype>
#include <locale>
#include <codecvt>
#include <unordered_set>
#include <Windows.h>

namespace fs = std::filesystem;
static const std::unordered_set<std::string> codeExtensions = { ".cpp", ".h", ".hpp", ".java", ".py", ".cs", ".rb", ".php", ".js", ".html", ".css", ".xml", ".json", ".ipynb" };
static const std::unordered_set<std::string> docExtensions = { ".docx", ".doc" };
static const std::unordered_set<std::string> imgExtensions = { ".jpg", ".png", ".gif"};
static const std::unordered_set<std::string> videoExtensions = { ".mp4", ".avi", ".mkv" };

std::string getCategoryFolder(const std::string& extension) {
    if (extension == ".pdf") {
        return "PDF";
    }
    else if (docExtensions.find(extension) != docExtensions.end()) {
        return "Documents";
    }
    else if (imgExtensions.find(extension) != imgExtensions.end()) {
        return "Images";
    }
    else if (videoExtensions.find(extension) != videoExtensions.end()) {
        return "Videos";
    }
    else if (codeExtensions.find(extension) != codeExtensions.end()) {
        return "Code";
    }
    else {
        return "Other";
    }
}

std::string convertToString(const std::wstring& wstr) {
    // Calculate the length of the required buffer
    int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    // Allocate buffer
    std::string str(bufferSize - 1, '\0');
    // Convert wide string to narrow string
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], bufferSize, nullptr, nullptr);
    return str;
}

void validPath(std::string& input)
{
    std::string path;
    for (auto c : input)
    {
        if (c != '"')
            path += c;
    }
    input = path;
}

int main() {
    std::cout << "   __ _ _                                 _            " << std::endl;
    std::cout << "  / _(_) |___ ___  ___ _ _ __ _ __ _ _ _ (_)______ _ _ " << std::endl;
    std::cout << " |  _| | / -_|_-< / _ \\ '_/ _` / _` | ' \\| |_ / -_) '_|" << std::endl;
    std::cout << " |_| |_|_\\___/__/ \\___/_| \\__, \\__,_|_||_|_/__\\___|_|  " << std::endl;
    std::cout << "                          |___/                        " << std::endl;
    
    
    // Specify the path to the directory you want to access
    std::string input;
    std::cout << "Enter the path to the folder you want to organize: ";
    std::getline(std::cin, input);
    std::cout << std::endl;
    validPath(input);
    
    fs::path folderPath = input;
    
    int count = 0;

    try {
        // Iterate through the contents of the directory
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            // Check if the entry is a regular file
            if (fs::is_regular_file(entry)) {
                // Extract the file extension
                std::wstring extensionWide = entry.path().extension();

                std::string extension = convertToString(extensionWide);
                std::cout << extension << "\t";
                std::string categoryFolder = getCategoryFolder(extension);

                std::cout << categoryFolder << std::endl;
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
    std::cout << count;
    

    return 0;
}
