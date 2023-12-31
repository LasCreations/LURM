#ifndef INSTITUTION_H
#define INSTITUTION_H

#include "degree.h"
#include "database.h"

class INSTITUTION
{
private:
    std::unordered_map<std::string, DEGREE> degrees;
    std::string name, code;

public:
    INSTITUTION()
    {}

    INSTITUTION(std::string name, std::string code, std::unordered_map<std::string, DEGREE> degrees)
    {
        this->code = code;
        this->name = name;
        this->degrees = degrees;
    }

    INSTITUTION(INSTITUTION *institution)
    {
        this->code = institution->code;
        this->name = institution->name;
        this->degrees = institution->degrees;
    }

    void setInstitutionName(std::string code)
    {
        this->code = code;
    }

    void setInstitutionCode(std::string name)
    {
        this->name = name;
    }

    void setInstitutionDegrees(std::unordered_map<std::string, DEGREE> degrees)
    {
        this->degrees = degrees;
    }

    std::string getInstitutionName() const
    {
        return this->name;
    }

    std::string getInstitutionCode() const
    {
        return this->code;
    }

    std::unordered_map<std::string, DEGREE> getInstitutionDegrees() const
    {
        return this->degrees;
    }

    std::unordered_map<std::string, INSTITUTION> getAll()
    {
        sql::Statement *stmt  = nullptr;
        sql::ResultSet *res  = nullptr;
        std::unordered_map<std::string, INSTITUTION> mapData;
        DATABASEMANAGER &dbMan = DATABASEMANAGER::getInstance();
        try
        {
            stmt = dbMan.getConnection()->createStatement();
            res = stmt->executeQuery("SELECT name, code FROM institutions");
            while (res->next())
            {
                mapData[res->getString("name")] = INSTITUTION(res->getString("name"), res->getString("code"), DEGREE().getAll(res->getString("code")));
            }
        }
        catch (const sql::SQLException &e)
        {
            std::cerr << "SQLException: " << e.what() << std::endl;
        }
        delete stmt;
        delete res;
        return mapData;
    }
};

#endif