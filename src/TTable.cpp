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

    if (0!=_indexForId.count(id)){
		TOperationResult result(TOperationResult::Result::DUPLICATE_KEY, {std::to_string(id)});
        return result;
	}

    _rows.push_back(dataType(id, name));
    _indexForId[id] = _rows.size()-1;
    return TOperationResult::Result::OK;
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

    for( auto iterIndex: _indexForId){
        int id (iterIndex.first);
        int rightIndex (right->getIndex(id));

        if(-1 != rightIndex){
            result.push_back(std::to_string(id)+","+_rows.at(iterIndex.second).name+","+right->_rows.at(rightIndex).name);
        }
    }

    return TOperationResult(TOperationResult::Result::OK, result);
}

TOperationResult TTable::symmetric_difference(std::shared_ptr<TTable> right){
    std::lock_guard<std::mutex> lockThis(_mutexTransaction);
    std::lock_guard<std::mutex> lockRight(right->_mutexTransaction);

    std::vector<std::string>    result;

    auto iterLeft (_indexForId.cbegin());
    auto leftEnd (_indexForId.cend());
    auto iterRight(right->_indexForId.cbegin());
    auto rightEnd (right->_indexForId.cend());

    while ( ( iterLeft != leftEnd ) && ( iterRight != rightEnd) ){
        if ( iterLeft->first == iterRight->first){
            ++iterLeft;
            ++iterRight;
        }
        else if ( iterLeft->first < iterRight->first){
            result.push_back(std::to_string(iterLeft->first)+","+_rows.at(iterLeft->second).name+",");
            ++iterLeft;
        } else {
            result.push_back(std::to_string(iterRight->first)+",,"+right->_rows.at(iterRight->second).name);
            ++iterRight;
        }

    }

    if (iterLeft != leftEnd){
        std::for_each(iterLeft, leftEnd,
            [&result, this](auto index){
                result.push_back(std::to_string(index.first)+","+_rows.at(index.second).name+",");
        });
    } else {
        std::for_each(iterRight, rightEnd,
            [&result, right](auto index){
                result.push_back(std::to_string(index.first)+",,"+right->_rows.at(index.second).name);
        });
    }

    return TOperationResult(TOperationResult::Result::OK, result);

}
