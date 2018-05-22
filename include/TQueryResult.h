#ifndef TQUERYRESULT_H
#define TQUERYRESULT_H

#include <vector>
#include <string>

#include "common_types.h"

class TQueryResult
{
    public:
        TQueryResult();
        virtual ~TQueryResult();

    protected:

    private:
        TOperationResult::Result   _code;
        std::vector<std::string>    _result;
};

#endif // TQUERYRESULT_H
