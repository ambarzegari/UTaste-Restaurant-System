#include "handlers.hpp"

#include <cstdlib>
#include <iostream>

Response *RandomNumberHandler::callback(Request *req)
{
    Response *res = new Response();
    res->setHeader("Content-Type", "text/html");

    std::string randomNumber = std::to_string(std::rand() % 10 + 1);
    std::string body;

    body += "<!DOCTYPE html>";
    body += "<html lang=\"en\">";

    body += "<head>";
    body += "  <title>Random Number Page</title>";
    body += "</head>";

    body += "<body style=\"text-align: center;\">";
    body += "  <h1>AP HTTP</h1>";
    body += "  <p>A random number in [1, 10] is: " + randomNumber + "</p>";
    body += "  <p>SessionId: " + req->getSessionId() + "</p>";
    body += "</body>";

    body += "</html>";
    res->setBody(body);
    return res;
}

Response *LoginHandler::callback(Request *req)
{
    std::string username = req->getBodyParam("username");
    std::string password = req->getBodyParam("password");
    if (username == "root")
    {
        throw Server::Exception("Remote root access has been disabled.");
    }
    std::cout << "username: " << username << ",\tpassword: " << password << std::endl;
    Response *res = Response::redirect("/");
    res->setSessionId("SID");
    return res;
}

Response *SignupHandler::callback(Request *req)
{
    try
    {
        utaste.SignUp(req->getBodyParam("username"), req->getBodyParam("password"));
        return UserMainPage(utaste);
    }
    catch (const runtime_error &e)
    {
        string exception_url = find_exeption(e);
        Response *res = Response::redirect(exception_url);
        return res;
    }
}

Response *UploadHandler::callback(Request *req)
{
    std::string name = req->getBodyParam("file_name");
    std::string file = req->getBodyParam("file");
    utils::writeToFile(file, name);
    Response *res = Response::redirect("/");
    return res;
}

ColorHandler::ColorHandler(const std::string &filePath)
    : TemplateHandler(filePath) {}

std::map<std::string, std::string> ColorHandler::handle(Request *req)
{
    std::string newName = "I am " + req->getQueryParam("name");
    std::map<std::string, std::string> context;
    context["name"] = newName;
    context["color"] = req->getQueryParam("color");
    return context;
}

Response *UserMainPage(UTaste utaste)
{
    try
    {
        User *user = utaste.GetUser();
        if (user == nullptr)
        {
            throw runtime_error(PERMISSION_DENIED);
        }

        Response *res = new Response();
        res->setHeader("Content-Type", "text/html");

        string body;
        body += "<!DOCTYPE html>\n";
        body += "<html lang=\"en\">\n";

        body += "<head>\n";
        body += "  <meta charset=\\\"UTF-8\\\">\n";
        body += "  <meta name=\\\"viewport\\\" content=\\\"width=device-width, initial-scale=1.0\\\">\n";
        body += "  <title>User Main Page - UTaste</title>\n";
        body += "  <style>\n";
        body += "    body {\n";
        body += "      font-family: 'Arial', sans-serif;\n";
        body += "      margin: 0;\n";
        body += "      padding: 0;\n";
        body += "      background-color: #f7f7f7;\n";
        body += "      text-align: center;\n";
        body += "    }\n";
        body += "    header {\n";
        body += "      background-color: #d35400;\n";
        body += "      color: #fff;\n";
        body += "      padding: 15px 0;\n";
        body += "      box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);\n";
        body += "    }\n";
        body += "    header h1 {\n";
        body += "      margin: 0;\n";
        body += "      font-size: 2.5rem;\n";
        body += "    }\n";
        body += "    .container {\n";
        body += "      max-width: 600px;\n";
        body += "      margin: 50px auto;\n";
        body += "      background-color: #fff;\n";
        body += "      padding: 20px;\n";
        body += "      border-radius: 10px;\n";
        body += "      box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);\n";
        body += "    }\n";
        body += "    h2 {\n";
        body += "      margin-bottom: 20px;\n";
        body += "      font-size: 1.8rem;\n";
        body += "      color: #333;\n";
        body += "    }\n";
        body += "    .buttons {\n";
        body += "      display: flex;\n";
        body += "      flex-direction: column;\n";
        body += "      gap: 15px;\n";
        body += "      margin-top: 20px;\n";
        body += "    }\n";
        body += "    .buttons a {\n";
        body += "      display: inline-block;\n";
        body += "      padding: 10px 20px;\n";
        body += "      font-size: 1rem;\n";
        body += "      color: #fff;\n";
        body += "      background-color: #d35400;\n";
        body += "      border-radius: 5px;\n";
        body += "      text-decoration: none;\n";
        body += "      text-align: center;\n";
        body += "      transition: background-color 0.3s;\n";
        body += "    }\n";
        body += "    .buttons a:hover {\n";
        body += "      background-color: #e67e22;\n";
        body += "    }\n";
        body += "  </style>\n";
        body += "</head>\n";
        
        body += "<body>\n";
        body += "  <header>\n";
        body += "    <h1>Welcome to UTaste</h1>\n";
        body += "  </header>\n";
        body += "  <div class=\\\"container\\\">\n";
        body += "    <h2>Hello, ";
        body += utaste.GetUser()->GetUsername();
        body += "    </h2> \n";
        body += "    <p>What would you like to do today?</p>\n";
        body += "    <div class=\\\"buttons\\\">\n";
        body += "      <a href=\\\"/restaurants-details\\\">Restaurants Details</a>\n";
        body += "      <a href=\\\"/reserve\\\">Reserve a Table</a>\n";
        body += "      <a href=\\\"/show-reservations\\\">Show My Reservations</a>\n";
        body += "      <a href=\\\"/logout\\\">Logout</a>\n";
        body += "    </div>\n";
        body += "  </div>\n";
        body += "</body>\n";
        body += "</html>\n";

        res->setBody(body);
        return res;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

string find_exeption(runtime_error e)
{
    string exp = e.what();
    if (exp == OK)
    {
        return "/ok";
    }
    else if (exp == NOT_FOUND)
    {
        return "/not_found";
    }
    else if (exp == PERMISSION_DENIED)
    {
        return "/permission_denied";
    }
    else if (exp == EMPTY)
    {
        return "/empty";
    }
    else
    {
        return "/bad_request";
    }
}
