#ifndef HANDLERS_HPP_INCLUDE
#define HANDLERS_HPP_INCLUDE

#include <map>
#include <string>

#include "../server/server.hpp"
#include "src/UTaste.hpp"

class LogoutHandler : public RequestHandler
{
private:
    UTaste *utaste;

public:
    LogoutHandler(UTaste *ut) { utaste = ut; }
    Response *callback(Request *) override;
};

class UserHandler : public RequestHandler
{
public:
    UserHandler(UTaste *ut) { utaste = ut; }
    Response *callback(Request *) override;
    UTaste *utaste;
};

class RestaurantHandler : public RequestHandler
{
public:
    RestaurantHandler(UTaste *ut) { utaste = ut; }
    Response *callback(Request *) override;
    UTaste *utaste;
};

class LoginHandler : public RequestHandler
{
public:
    LoginHandler(UTaste *ut) { utaste = ut; }
    Response *callback(Request *) override;
    UTaste *utaste;
};

class SignupHandler : public RequestHandler
{
public:
    SignupHandler(UTaste *ut) { utaste = ut; }
    Response *callback(Request *) override;
    UTaste *utaste;
};

class UploadHandler : public RequestHandler
{
public:
    Response *callback(Request *) override;
};

class ColorHandler : public TemplateHandler
{
public:
    ColorHandler(const std::string &filePath);
    std::map<std::string, std::string> handle(Request *req) override;
};

Response *UserMainPage(UTaste* ut);
Response *RestaurantDetails(UTaste* ut);
string find_exeption(runtime_error e);

#endif // HANDLERS_HPP_INCLUDE
