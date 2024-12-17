#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

const string PUT = "PUT";
const string GET = "GET";
const string POST = "POST";
const string DELETE = "DELETE";

const string OK = "OK";
const string PERMISSION_DENIED = "Permission Denied";
const string EMPTY = "Empty";
const string BAD_REQUEST = "Bad Request";
const string NOT_FOUND = "Not Found";

vector<string> StringSplitter(string line);

#endif