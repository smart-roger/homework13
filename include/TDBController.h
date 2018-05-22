#ifndef TDBCONTROLLER_H
#define TDBCONTROLLER_H

#include "common_types.h"
#include "TTable.h"
#include <unordered_map>
#include <string>
#include <memory>

class TDBController
{
    using ptrTable = std::shared_ptr<TTable>;
    using typeResult = std::vector<TTable::dataType>;

    public:

        TDBController();
        ~TDBController();

        TOperationResult createTable (std::string name);
        ptrTable getTable (std::string name);

    protected:

        TOperationResult insert(std::string nameTable, int newID, std::string newName);
        TOperationResult truncate(std::string nameTable);

    private:
        std::unordered_map<std::string, ptrTable > _tables;
};

#endif // TDBCONTROLLER_H
