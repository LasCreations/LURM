#ifndef USER_H
#define USER_H


#include "database.h"

class USER
{
private:
    std::string SID, username, password, avatar, fName, lName;
    uint16_t yearStart, yearEnd, rank;

public:
    USER() {}
    USER(std::string SID, std::string username, std::string password, std::string avatar, 
            std::string fName, std::string lName, uint16_t yearStart, uint16_t yearEnd, uint16_t rank)
    {
        this->SID = SID;
        this->password = password;
        this->username = username;
        this->avatar = avatar;
        this->fName = fName;
        this->lName = lName;
        this->yearStart = yearStart;
        this->yearEnd = yearEnd;
        this->rank = rank;
    }

    USER(USER *user)
    {
        this->SID = user->SID;
        this->username = user->username;
        this->password = user->password;
        this->avatar = user->avatar;
        this->fName = user->fName;
        this->lName = user->lName;
        this->yearStart = user->yearStart;
        this->yearEnd = user->yearEnd;
        this->rank = user->rank;
    }

    void setSID(std::string SID)
    {
        this->SID = SID;
    }

    void setUsername(std::string username)
    {
        this->username = username;
    }

    void setPassword(std::string password)
    {
        this->password = password;
    }

    void setAvatar(std::string avatar)
    {
        this->avatar = avatar;
    }

    void setFirstName(std::string fName)
    {
        this->fName = fName;
    }

    void setLastName(std::string lName)
    {
        this->lName = lName;
    }

    void setYearStart(uint16_t yearStart)
    {
        this->yearStart = yearStart;
    }

    void setYearEnd(uint16_t yearEnd)
    {
        this->yearEnd = yearEnd;
    }

    void setRank(uint16_t rank)
    {
        this->rank = rank;
    }

    std::string getSID()
    {
        return this->SID;
    }

    std::string getUsername()
    {
        return this->username;
    }

    std::string getPassword()
    {
        return this->password;
    }

    std::string getAvatar()
    {
        return this->avatar;
    }

    std::string getFirstName()
    {
        return this->fName;
    }

    std::string getLastName()
    {
        return this->lName;
    }

    uint16_t getYearStart()
    {
        return this->yearStart;
    }

    uint16_t getYearEnd()
    {
        return this->yearEnd;
    }

    uint16_t getRank()
    {
        return this->rank;
    }

    bool create(USER user)
    {
        sql::PreparedStatement *prep_stmt = nullptr;
        DATABASEMANAGER &dbMan = DATABASEMANAGER::getInstance();
        try
        {   
            prep_stmt = dbMan.getConnection()->prepareStatement("INSERT INTO users(SID, username, avatar, first_name, last_name, password, year_start, year_end, rank_value) VALUES(?,?,?,?,?,?,?,?,?)");
            prep_stmt->setString(1, user.getSID());
            prep_stmt->setString(2, user.getUsername());
            prep_stmt->setString(3, user.getAvatar());
            prep_stmt->setString(4, user.getFirstName());
            prep_stmt->setString(5, user.getLastName());
            prep_stmt->setString(6, user.getPassword());
            prep_stmt->setInt(7, user.getYearStart());
            prep_stmt->setInt(8, user.getYearEnd());
            prep_stmt->setInt(9, user.getRank());
            prep_stmt->executeUpdate();
            delete prep_stmt;
            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error adding user: " << e.what() << std::endl;
            delete prep_stmt;
        }
        return false;
    }

    void addUserInstitution(std::string institutionCode, std::string username)
    {
        std::cout << "Arrived in User Inst" << std::endl;
        sql::PreparedStatement *prep_stmt = nullptr;
        DATABASEMANAGER &dbMan = DATABASEMANAGER::getInstance();
        try
        {   
            prep_stmt = dbMan.getConnection()->prepareStatement("INSERT INTO user_institution(username, institution_code) VALUES(?,?)");
            prep_stmt->setString(1, username);
            prep_stmt->setString(2, institutionCode);
            prep_stmt->executeUpdate();
            delete prep_stmt;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error adding user: " << e.what() << std::endl;
            delete prep_stmt;
        }
        std::cout << "Left User Inst" << std::endl;
    }

    void addUserDegree(std::string degreeCode, std::string username)
    {
        sql::PreparedStatement *prep_stmt = nullptr;
        DATABASEMANAGER &dbMan = DATABASEMANAGER::getInstance();
        try
        {   
            prep_stmt = dbMan.getConnection()->prepareStatement("INSERT INTO user_degrees(username, degree_code) VALUES(?,?)");
            prep_stmt->setString(1, username);
            prep_stmt->setString(2, degreeCode);
            prep_stmt->executeUpdate();
            delete prep_stmt;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error adding user: " << e.what() << std::endl;
            delete prep_stmt;
        }
    }

    void addUserCourse(std::string courseCode, std::string username)
    {
        sql::PreparedStatement *prep_stmt = nullptr;
        DATABASEMANAGER &dbMan = DATABASEMANAGER::getInstance();
        try
        {   
            prep_stmt = dbMan.getConnection()->prepareStatement("INSERT INTO user_courses(username, course_code) VALUES(?,?)");
            prep_stmt->setString(1, username);
            prep_stmt->setString(2, courseCode);
            prep_stmt->executeUpdate();
            delete prep_stmt;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error adding user: " << e.what() << std::endl;
            delete prep_stmt;
        }
    }

    USER read()
    {
        return NULL;
    }

    bool update(std::string uid)
    {
        return false;
    }

    bool deleteUser()
    {
        return false;
    }

    std::vector<USER> *selectAll()
    {
        return nullptr;
    }
};

#endif