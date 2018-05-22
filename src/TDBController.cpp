#include "TDBController.h"

TDBController::TDBController():_tables()
{
    //ctor
}

TDBController::~TDBController()
{
    //dtor
}

TOperationResult TDBController::createTable (std::string name){
    if(0==_tables.count(name)){
        _tables[name] = std::make_shared<TTable>();
        return TOperationResult::Result::OK;
    } else {
        return TOperationResult::Result::TABLE_EXISTS_ALREADY;
    }
}

TDBController::ptrTable TDBController::getTable (std::string name){
    if (0==_tables.count(name))
        return nullptr;
    return _tables[name];
}

TOperationResult TDBController::intersection (std::string nameLeft, std::string nameRight){
}

TOperationResult TDBController::symmetric_difference (std::string nameLeft, std::string nameRight){
}

TOperationResult TDBController::insert(std::string nameTable, int newID, std::string newName){
    ptrTable table = getTable(nameTable);
    if(nullptr != table){
        return table->valueAdd(newID, newName);
    } else return TOperationResult::Result::UNKNOWN_TABLE;
}

TOperationResult TDBController::truncate(std::string nameTable){
    ptrTable table = getTable(nameTable);
    if(nullptr != table){
        return table->truncate();
    } else return TOperationResult::Result::UNKNOWN_TABLE;
}

