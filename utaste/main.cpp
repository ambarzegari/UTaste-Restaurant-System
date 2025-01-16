#include <iostream>
#include <string>

#include "../server/server.hpp"
#include "handlers.hpp"
#include "src/UTaste.hpp"

const int PORT = 9090;

void mapServerPaths(Server &server , UTaste *ut)
{
    server.setNotFoundErrPage("static/not_found.html");
    server.get("/not_found",new ShowPage("static/not_found.html"));
    server.get("/ok",new ShowPage("static/ok.html"));
    server.get("/permission_denied",new ShowPage("static/permission_denied.html"));
    server.get("/", new ShowPage("static/home.html"));
    server.get("/signup", new ShowPage("static/signup.html"));
    server.post("/signup", new SignupHandler(ut));
    server.get("/main", new UserHandler(ut));
    server.get("/restaurants-details", new RestaurantHandler(ut));
    server.get("/logout", new LogoutHandler(ut));
    server.get("/ut.png", new ShowImage("static/ut.png"));
    server.get("/login", new ShowPage("static/login.html"));
    server.post("/login", new LoginHandler(ut));
}

int main(int argc, char **argv)
{
    try
    {
        UTaste *utaste = new UTaste();
        utaste->GetDataFromDistrictsFile(argv[2]);
        utaste->GetDataFromResturantsFile(argv[1]);
        utaste->GetDataFromDiscountsFile(argv[3]);

        int port = PORT;
        Server server(port);
        mapServerPaths(server, utaste);
        std::cout << "Server running on port: " << port << std::endl;
        server.run();
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (const Server::Exception &e)
    {
        std::cerr << e.getMessage() << std::endl;
    }
    return 0;
}
