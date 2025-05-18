// Please enter your own name and class.
// -------------------------------------------------------------------
#pragma once
#define NAME    "Murtaza Amjed & Yash Desai"
#define CLASS   "CSCI 4547-01"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <utility>
#include <unordered_map>

#include <cmath>
#include <ctime>
#include <cctype>      // for isspace() and isdigit()
#include <span>

//Our Tools
#include <getopt.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <csignal>
#include <pthread.h>
using namespace std;

// -------------------------------------------------------------------
// Macros for debugging.
// -------------------------------------------------------------------
#define DUMPp(p) "\n" <<"    " #p " @ " <<&p <<"    value = " <<p <<"    " #p " --> " <<*p
#define DUMPv(k) "\n" <<"    " #k " @ " <<&k <<"    value = " <<k

// -------------------------------------------------------------------
// I/O Extension.
// -------------------------------------------------------------------
istream& cleanline(istream& is); // discards remainder of line
istream& flush(istream& is);     // Use: cin >> x >> flush;
ostream& general(ostream& os);   // Use: cout <<fixed <<x <<general<<y;

// -------------------------------------------------------------------
// Routine output labeling. ------------------------------------------
// -------------------------------------------------------------------
void     fbanner( ostream& fout );
void     banner();
void     bye( void );

// -------------------------------------------------------------------
// Error handling ----------------------------------------------------
// -------------------------------------------------------------------
void    fatal( const string& msg );

// -------------------------------------------------------------------
// time and date. ----------------------------------------------------
// -------------------------------------------------------------------
void   when( string& date, string& hour );
string today();
string oclock();

// ---------------------------------------------------------------------
//  Menu handling
// ---------------------------------------------------------------------
// Display a menu then read an alphabetic menu choice character.
char menu_c( string title, int n, const string  menu[], const string valid );
int  menu( const char* title, int n, const string menu[] );


//----------------------------------------------------------------------
//Murtaza & Yash Tools
//----------------------------------------------------------------------
bool caseInsensitiveEquals(const string& str1, const string& str2);

//Global variable
inline stringstream ss;