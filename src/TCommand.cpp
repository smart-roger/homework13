#include "TCommand.h"

TOperationResult TCommandCreate::execute (std::shared_ptr<TDBController> controller,
                                           std::stringstream& args){
    std::string nameTable;
    args >> nameTable;

    if(nameTable.empty())
        return TOperationResult::Result::WRONG_ARGUMENTS;

    return controller->createTable(nameTable);
}

std::string TCommandCreate::getUsageString(){return "create <table_name>";}

TOperationResult TCommandInsert::execute (std::shared_ptr<TDBController> controller,
                                           std::stringstream& args){
    std::string nameTable;
    args >> nameTable;

    if(nameTable.empty())
        return TOperationResult::Result::WRONG_ARGUMENTS;

    std::shared_ptr<TTable> table = controller->getTable(nameTable);
    if(nullptr == table)
        return TOperationResult::Result::UNKNOWN_TABLE;

    int id;
    args >> id;
    if(args.bad())
        return TOperationResult::Result::WRONG_ARGUMENTS;

    std::string name;
    args >> name;
    if(name.empty())
        return TOperationResult::Result::WRONG_ARGUMENTS;

    return table->valueAdd(id, name);
}

std::string TCommandInsert::getUsageString(){return "INSERT <table_name> <id> <name>";}


TOperationResult TCommandTruncate::execute (std::shared_ptr<TDBController> controller,
                                           std::stringstream& args){

    std::string tablename;
    args >> tablename;
    if(!args.eof())
        return {TOperationResult::Result::WRONG_ARGUMENTS};

    std::shared_ptr<TTable> table = controller->getTable(tablename);

    if(nullptr == table)
        return {TOperationResult::Result::UNKNOWN_TABLE, {tablename}};
    else return table->truncate();
}

std::string TCommandTruncate::getUsageString(){return "TRUNCATE <table_name>";}

TOperationResult TCommandIntersection::execute (std::shared_ptr<TDBController> controller,
                                                std::stringstream& args){

    std::shared_ptr<TTable> tableLeft = controller->getTable("A");
    if(nullptr == tableLeft)
        return {TOperationResult::Result::UNKNOWN_TABLE, {"A"}};

    std::shared_ptr<TTable> tableRight = controller->getTable("B");
    if(nullptr == tableRight)
        return {TOperationResult::Result::UNKNOWN_TABLE,{"B"}};

    return tableLeft->intersection(tableRight);
}

std::string TCommandIntersection::getUsageString(){return "INTERSECTION";}

TOperationResult TCommandDifference::execute (std::shared_ptr<TDBController> controller,
                                                std::stringstream& args){

    std::shared_ptr<TTable> tableLeft = controller->getTable("A");
    if(nullptr == tableLeft)
        return {TOperationResult::Result::UNKNOWN_TABLE, {"A"}};

    std::shared_ptr<TTable> tableRight = controller->getTable("B");
    if(nullptr == tableRight)
        return {TOperationResult::Result::UNKNOWN_TABLE,{"B"}};

    TOperationResult result = tableLeft->symmetric_difference(tableRight);
    return result;
}

std::string TCommandDifference::getUsageString(){return "SYMMETRIC_DIFFERENCE";}

