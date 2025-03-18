#include <stdlib.h>
#include <iostream>


#include <SFML/Graphics.hpp>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

#define SERVER "127.0.0.1:3306"
#define USERNAME "root"
#define PASSWORD ""
#define DATABASE "videogame"

void ConnectDatabase(sql::Driver*& driver, sql::Connection*& con) {


    try {

        driver = get_driver_instance();
        con = driver->connect(SERVER, USERNAME, PASSWORD);
        con->setSchema(DATABASE);
        std::cout << "Connection done. " << std::endl;


    }
    catch (sql::SQLException e) {

        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;



    }



}

void GetAllUsers(sql::Connection* con) {

    try {

        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT user FROM users");

        std::cout << "Users in the database: " << std::endl;
        while (res->next()) {
            std::cout << res->getString("user") << std::endl;
        }

        delete res;
        delete stmt;

    }
    catch (sql::SQLException& e) {

        std::cout << "Error while fetching users: " << e.what() << std::endl;


    }



}

void UpdatePassword(sql::Connection* con, std::string user, std::string newPassword) {

    try {

        sql::Statement* stmt = con->createStatement();
        std::string query = "UPDATE users SET password = '" + newPassword + "' WHERE user = '" + user + "'";

        int affected_rows = stmt->executeUpdate(query);
        std::cout << "Number of rows affected: " << affected_rows << std::endl;

        delete stmt;
    }
    catch (sql::SQLException& e) {

        std::cout << "Error while updating password: " << e.what() << std::endl;

    }


}

void DeleteByUser(sql::Connection* con, std::string user) {

    try {

        sql::Statement* stmt = con->createStatement();
        std::string query = "DELETE FROM users WHERE user = '" + user + "'";

        int affected_rows = stmt->executeUpdate(query);
        std::cout << "Number of users deleted: " << affected_rows << std::endl;

        delete stmt;

    }
    catch (sql::SQLException& e) {
        std::cout << "Error while deleting user: " << e.what() << std::endl;
    }

}

void CreateUsers(sql::Connection* con, std::string user, std::string password) {

    try {

        sql::Statement* stmt = con->createStatement();
        std::string query = "INSERT INTO users (user,password) VALUES ('"+user+"','"+password+"')";

        int affected_rows = stmt->executeUpdate(query);
        if (affected_rows > 0) {
            std::cout << "User created successfully. " << std::endl;
        }
      

        delete stmt;

    }
    catch (sql::SQLException& e) {
        std::cout << "Error while creating user: " << e.what() << std::endl;
    }


}


void DisconnectDatabase(sql::Connection*& con) {

    con->close();

    if (con->isClosed()) {

        std::cout << "Connection close. " << std::endl;
        delete con;
    }


}


int main()
{

    sql::Driver* driver;
    sql::Connection* con;

    ConnectDatabase(driver, con);
   // GetAllUsers(con);
   // UpdatePassword(con, "Radev", "suspenderAlumnos");
    //DeleteByUser(con,"Edu");
    //CreateUsers(con, "Edu", "123");
    DisconnectDatabase(con);

    system("pause");
    // exit(1);



    /*sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }*/
}