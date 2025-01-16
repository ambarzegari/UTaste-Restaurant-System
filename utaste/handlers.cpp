#include "handlers.hpp"

#include <cstdlib>
#include <iostream>

Response *LogoutHandler::callback(Request *req)
{
    try
    {
        utaste->LogOut();
    }
    catch (const runtime_error &e)
    {
        string exception_url = find_exeption(e);
        if (exception_url == "/ok")
        {
            Response *res = Response::redirect("/");
            return res;
        }
        else
        {
            Response *res = Response::redirect(exception_url);
            return res;
        }
    }
}

Response *UserHandler::callback(Request *req)
{
    try
    {
        return UserMainPage(utaste);
    }
    catch (const runtime_error &e)
    {
        string exception_url = find_exeption(e);
        Response *res = Response::redirect(exception_url);
        return res;
    }
}

Response *RestaurantHandler::callback(Request *)
{
    return RestaurantDetails(utaste);
}

Response *LoginHandler::callback(Request *req)
{
    try
    {
        utaste->LogIn(req->getBodyParam("username"), req->getBodyParam("password"));
    }
    catch (const runtime_error &e)
    {
        string exception_url = find_exeption(e);
        if (exception_url == "/ok")
        {
            Response *res = Response::redirect("/main");
            return res;
        }
        else
        {
            Response *res = Response::redirect(exception_url);
            return res;
        }
    }
}

Response *SignupHandler::callback(Request *req)
{
    try
    {
        utaste->SignUp(req->getBodyParam("username"), req->getBodyParam("password"));
        Response *res = Response::redirect("/main");
        return res;
    }
    catch (const runtime_error &e)
    {
        string exception_url = find_exeption(e);
        Response *res = Response::redirect(exception_url);
        return res;
    }
}

Response *UserMainPage(UTaste *utaste)
{
    try
    {
        User *user = utaste->GetUser();
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
        body += "  <meta charset=\"UTF-8\">\n";
        body += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\\\">\n";
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
        body += "  <div class=\"container\">\n";
        body += "    <h2>Hello, ";
        body += utaste->GetUser()->GetUsername();
        body += "    </h2> \n";
        body += "    <p>What would you like to do today?</p>\n";
        body += "    <div class=\"buttons\">\n";
        body += "      <a href=\"/restaurants-details\">Restaurants Details</a>\n";
        body += "      <a href=\"/reserve\">Reserve a Table</a>\n";
        body += "      <a href=\"/show-reservations\">Show My Reservations</a>\n";
        body += "      <a href=\"/logout\">Logout</a>\n";
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

Response *RestaurantDetails(UTaste *ut)
{
    string s = ut->ShowRestaurantInfo();
    try
    {

        Response *res = new Response();
        res->setHeader("Content-Type", "text/html");

        string body;
        body += "<!DOCTYPE html>";
        body += "<html lang=\"en\">";

        body += "<head>";
        body += "  <meta charset=\"UTF-8\">";
        body += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
        body += "  <title>Restaurant Details - UTaste</title>";
        body += "  <style>";
        body += "    body {";
        body += "      font-family: 'Arial', sans-serif;";
        body += "      margin: 0;";
        body += "      padding: 0;";
        body += "      background-color: #f7f7f7;";
        body += "      display: flex;";
        body += "      flex-direction: column;";
        body += "      align-items: center;";
        body += "      height: auto;";
        body += "      text-align: center;";
        body += "    }";
        body += "    header {";
        body += "      background-color: #d35400;";
        body += "      color: #fff;";
        body += "      padding: 15px 0;";
        body += "      width: 100%;";
        body += "      box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);";
        body += "      text-align: center;";
        body += "    }";
        body += "    header h1 {";
        body += "      margin: 0;";
        body += "      font-size: 2.5rem;";
        body += "    }";
        body += "    .details-container {";
        body += "      background-color: #fff;";
        body += "      padding: 20px;";
        body += "      border-radius: 10px;";
        body += "      box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);";
        body += "      max-width: 700px;";
        body += "      width: 90%;";
        body += "      margin-top: 20px;";
        body += "      height: auto;";
        body += "      text-align: left;";
        body += "      direction: ltr;";
        body += "    }";
        body += "    .back-button {";
        body += "      margin-top: 20px;";
        body += "      padding: 10px 20px;";
        body += "      font-size: 1rem;";
        body += "      color: #fff;";
        body += "      background-color: #d35400;";
        body += "      border: none;";
        body += "      border-radius: 5px;";
        body += "      cursor: pointer;";
        body += "      text-decoration: none;";
        body += "      transition: background-color 0.3s;";
        body += "    }";
        body += "    .back-button:hover {";
        body += "      background-color: #e67e22;";
        body += "    }";
        body += "  </style>";
        body += "</head>";

        body += "<body>";
        body += "  <header>";
        body += "    <h1>Restaurant Details</h1>";
        body += "  </header>";

        body += "  <div class=\"details-container\">";
        body += s;
        body += "  </div>";

        body += "  <a href=\"/main\" class=\"back-button\">Back to Main Page</a>";
        body += "</body>";

        body += "</html>";

        res->setBody(body);
        return res;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}