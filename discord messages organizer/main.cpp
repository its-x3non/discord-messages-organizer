// Last Updated: 8:25 PM PST - 6/2/2024

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

// Message Struct
struct Message {
    string text;
    string timestamp;
};

// Functions
string extractTimestamp(const string&);
void sortDate(const string&, const string&, const string&, const int&);
void directoryCheck(const string&);

// Main :3
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

    // Sorting Time
    sortDate(path, outputFile, targetFile, totalCount);
    
    // Completion
    cout << "Open " << outputFile << " for your organized messages :3 " << endl;
    cout << "I recommend using notepad++ since big file lol" << endl;
    cout << "Thank u for using! Please Like and Subscribe -x3non" << endl;
    system("pause");
}

// Extract Timestamp
string extractTimestamp(const string& line) {
    regex timestamp_regex("\"Timestamp\":\\s*\"([^\"]+)\"");
    smatch match;

    if (regex_search(line, match, timestamp_regex) && match.size() > 1)
        return match.str(1);

    return "";
}

// Log Messages by Date
void sortDate(const string& directory, const string& output, const string& target, const int& totalCount) {
    // Completed Count
    int completed = 0;

    // Check for valid directory
    directoryCheck(directory);

    // Creates a Vector for Messages
    vector<Message> messages;

    // Iterate over the directory and print items
    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        // Progression Text
        cout << "IN PROGRESS [SORTING BY DATE]" << endl;
        cout << completed << " / " << totalCount << endl;

        // Start Reading the Lines
        if (fs::is_regular_file(entry.path()) && entry.path().filename() == target) {
            cout << "[FILE] " << entry.path() << endl;
            ifstream input_file(entry.path());
            if (input_file.is_open()) {
                string line;

                // Read File Lines
                while (getline(input_file, line)) {
                    string timestamp = extractTimestamp(line);

                    // If lines are empty
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

    // Sort messages by timestamp
    sort(messages.begin(), messages.end(), [](const Message& a, const Message& b) { 
        return a.timestamp < b.timestamp; 
        });

    // Open the output file
    ofstream output_file(output);
    if (!output_file.is_open()) {
        cerr << "Failed to open output file: " << output << endl;
        return;
    }

    // Write sorted messages to output file
    for (const auto& entry : messages){ 
        output_file << entry.text << endl; 
    }

    // Close file
    output_file.close();
}

// Checks for Valid Directory
void directoryCheck(const string& directory) {
    if (!fs::exists(directory)) {
        cerr << "Directory does not exist." << endl;
        return;
    }

    if (!fs::is_directory(directory)) {
        cerr << "Path is not a directory." << endl;
        return;
    }
}