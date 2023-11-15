#include <iostream>
#include <fstream>
#include <optional>
#include <string>

// Define the Maybe monad using std::optional
template <typename T>
using Maybe = std::optional<T>;

// Lambda function to read the contents of a file
auto readFile = [](const std::string &filename) -> Maybe<std::string>
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return Maybe<std::string>(); // Return empty Maybe if file cannot be opened
    }

    std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return Maybe<std::string>(fileContent);
};

// Lambda function to check if the file content is ASCII
auto isASCII = [](const std::string &content) -> bool
{
    for (char c : content)
    {
        if (c < 0 || c > 127)
        {
            return false;
        }
    }
    return true;
};

// Lambda function to process the file content
auto processFileContent = [](const Maybe<std::string> &maybeContent)
{
    if (maybeContent.has_value())
    {
        std::string content = maybeContent.value();

        if (isASCII(content))
        {
            std::cout << "File content is in ASCII format:\n"
                      << content << "\n";
        }
        else
        {
            std::cout << "File content is not in ASCII format.\n";
        }
    }
    else
    {
        std::cout << "Failed to read file or file does not exist.\n";
    }
};

int main()
{
    const std::string filenameNonAscii = "example-non-ascii.txt";

    // Call the processFileContent lambda function to handle the file content
    Maybe<std::string> maybeContentNonAscii = readFile(filenameNonAscii);
    processFileContent(maybeContentNonAscii);

    const std::string filename = "example.txt";

    // again
    Maybe<std::string> maybeContent = readFile(filename);
    processFileContent(maybeContent);
    return 0;
}
