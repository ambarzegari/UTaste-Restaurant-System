#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

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

const string SIGN_UP = "signup";
const string LOG_IN = "login";
const string LOG_OUT = "logout";
const string USER_NAME = "username";
const string PASSWORD = "password";

const string DISTRICTS = "districts";
const string DISTRICT = "district";
const string MY_DISTRICT = "my_district";

const string RESTURANTS = "resturants";
const string FOOD_NAME = "food_name";

vector<string> StringSplitter(string line);

#endif