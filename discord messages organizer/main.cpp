#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <sstream>

using namespace std;
namespace fs = std::filesystem;

// MESSAGE STRUCT
struct Message {
    string text;
    string timestamp;
};

// TIMESTAMP
string extractTimestamp(const string& line) {
    regex timestamp_regex("\"Timestamp\":\\s*\"([^\"]+)\"");
    smatch match;

    if (regex_search(line, match, timestamp_regex) && match.size() > 1) 
        return match.str(1);

    return "";
}

// FUNCTIONS
void sortDate(const string&, const string&, const string&, const int&);
void directoryCheck(const string&);

int main()
{

    // File Stuff
    int totalFiles = 0;
	string path = "messages";
    string targetFile = "messages.json";
    string outputFile = "output.txt";
    int totalCount = 0;

    // Get file Count First
    for (const auto& entry : fs::recursive_directory_iterator(path)) {
        if (fs::is_directory(entry.path())) {
            totalCount++;
        }
    }

    sortDate(path, outputFile, targetFile, totalCount);
    
    cout << "Open " << outputFile << " for your organized messages :3 " << endl;
    cout << "I recommend using notepad++ since big file lol" << endl;
    cout << "Thank u for using please like and subscribe -x3non" << endl;
    system("pause");
}

// LOG MESSAGES BY DATE
void sortDate(const string& directory, const string& output, const string& target, const int& totalCount) {
    // Completed Count
    int completed = 0;

    // Check for valid directory
    directoryCheck(directory);

    vector<Message> messages;

    // Iterate over the directory and print items
    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        cout << "IN PROGRESSs [SORTING BY DATE]" << endl;
        cout << completed << " / " << totalCount << endl;
        if (fs::is_regular_file(entry.path()) && entry.path().filename() == target) {
            // cout << "[FILE] " << entry.path() << endl;
            ifstream input_file(entry.path());
            if (input_file.is_open()) {
                string line;

                // Read File Lines
                while (getline(input_file, line)) {
                    string timestamp = extractTimestamp(line);

                    // IF EMPTY
                    if (!timestamp.empty()) { 
                        messages.push_back({ line, timestamp }); 
                    }
                }
                input_file.close();
            } else {
                cerr << "Failed to open file: " << entry.path() << endl;
            }
        }
        // Complete Directory
        if (fs::is_directory(entry.path())) {
            completed++;
        }
        system("cls");
    }

    // Sort log entries by timestamp
    sort(messages.begin(), messages.end(), [](const Message& a, const Message& b) { 
        return a.timestamp < b.timestamp; 
        });

    // Open the output file
    ofstream output_file(output);
    if (!output_file.is_open()) {
        cerr << "Failed to open output file: " << output << endl;
        return;
    }

    // Write sorted entries to the output file
    for (const auto& entry : messages){ 
        output_file << entry.text << endl; 
    }

    // CLOSE FILE
    output_file.close();
}

// Checks for Directory
void directoryCheck(const string& directory) {
    if (!fs::exists(directory)) {
        std::cerr << "Directory does not exist.\n";
        return;
    }

    if (!fs::is_directory(directory)) {
        std::cerr << "Path is not a directory.\n";
        return;
    }
}