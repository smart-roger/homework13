#include "TTable.h"

TTable::TTable():
    _rows(),
    _indexForId(),
    _mutexTransaction()
{
    //ctor
}

TTable::~TTable()
{
    //dtor
}

TOperationResult TTable::valueAdd(int id, std::string name){
    std::lock_guard<std::mutex> lock(_mutexTransaction);

    if (0!=_indexForId.count(id))
        return TOperationResult::Result::DUPLICATE_KEY;

    _rows.push_back(dataType(id, name));
    std::sort(_rows. begin(), _rows.end(), [](auto left, auto right){return left.id < right.id;});
    indexUpdate();
    return TOperationResult::Result::OK;
}

void TTable::indexUpdate(){
    _indexForId.clear();

    for(size_t index=0; index<_rows.size();++index){
        _indexForId[_rows[index].id]  = index;
    }
}

int TTable::getIndex(int id){
    if(0 == _indexForId.count(id))
        return -1;
    else return (_indexForId.at(id));
}

TOperationResult TTable::truncate(){
    _rows.clear();
    _indexForId.clear();
    return TOperationResult::Result::OK;
}

TOperationResult TTable::intersection(std::shared_ptr<TTable> right){
    std::lock_guard<std::mutex> lockThis(_mutexTransaction);
    std::lock_guard<std::mutex> lockRight(right->_mutexTransaction);

    std::vector<std::string>    result;

    std::sort(_rows.begin(), _rows.end(),
              [](dataType left, dataType right){
                    return left.id < right.id;
              });
    std::for_each(_rows.begin(), _rows.end(), [&result, right](dataType data){
                    int rightIndex (right->getIndex(data.id));
                    if(-1 != rightIndex){
                        result.push_back(std::to_string(data.id)+","+data.name+","+right->_rows.at(rightIndex).name);
                    }
                  });
    return TOperationResult(TOperationResult::Result::OK, result);
}

TOperationResult TTable::symmetric_difference(std::shared_ptr<TTable> right){
    std::lock_guard<std::mutex> lockThis(_mutexTransaction);
    std::lock_guard<std::mutex> lockRight(right->_mutexTransaction);


    std::vector<std::string>    result;

    std::map<int, std::string> sorted_values;

    std::for_each(_rows.begin(), _rows.end(), [&sorted_values, right](dataType data){
                    int rightIndex (right->getIndex(data.id));
                    if(-1 == rightIndex){
                        sorted_values[data.id] = std::to_string(data.id)+","+data.name+",";
                    }
                  });

    std::for_each(right->_rows.begin(), right->_rows.end(), [&sorted_values, this](dataType data){
                    int thisIndex (this->getIndex(data.id));
                    if(-1 == thisIndex){
                        sorted_values[data.id] = std::to_string(data.id)+","+","+data.name;
                    }
                  });
    for( auto val = sorted_values.begin(); val != sorted_values.end(); ++val)
        result.push_back(val->second);

    return TOperationResult(TOperationResult::Result::OK, result);

}
