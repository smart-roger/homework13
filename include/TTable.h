#ifndef TTABLE_H
#define TTABLE_H

#include <algorithm>
#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <map>
#include "TOperationResult.h"



class TTable
{
    public:
        struct dataType {
            dataType(int newId, std::string newName):id(newId), name(newName){};
            int id;
            std::string name;
        };

        TTable();
        virtual ~TTable();

        TOperationResult valueAdd(int id, std::string name);
        TOperationResult truncate();

        TOperationResult intersection(std::shared_ptr<TTable> right);
        TOperationResult symmetric_difference(std::shared_ptr<TTable> right);

    protected:
        int getIndex(int id);


    private:
        std::vector<dataType>   _rows;
        std::map<int, int>      _indexForId;

        std::mutex  _mutexTransaction;
};

#endif // TTABLE_H
