// File: Printer.hpp
// Name: Murtaza & Yash
// ------------------------------------------------------------
// Singleton class for printing messages to both terminal and file
// ------------------------------------------------------------

#pragma once
#include "tools.hpp"

class Printer {
private:
    ofstream file;                    // Output file stream
    static Printer instance;         // Singleton instance
    Printer();                       // Private constructor
    ~Printer();                      // Private destructor

public:
    // Assign control of output file stream (used if needed externally)
    static void getControl(ofstream&& out) { instance.file = move(out); }

    // Print a message to both the output file and provided output stream
    static void write(const string& message, ostream& out);

    // Print the content of a stringstream and clear it after writing
    static void write(stringstream& stream, ostream& out);

    // Print a line with newline appended
    static void writeln(const string& message, ostream& out);
};
