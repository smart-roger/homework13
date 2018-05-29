#ifndef TOPERATIONRESULT_H
#define TOPERATIONRESULT_H

#include <vector>
#include <string>

#include "common_types.h"

static const char err_header [] = "ERR ";

class TOperationResult
{
    public:
        enum class Result{OK, WRONG_ARGUMENTS, TABLE_EXISTS_ALREADY, UNKNOWN_TABLE, DUPLICATE_KEY};


        TOperationResult() = delete;
        TOperationResult(Result  code):_code(code), _data(){};
        TOperationResult(Result  code, std::vector<std::string> data):
            _code(code), _data(data){};
        ~TOperationResult(){};

        Result   getCode(){return _code;}
        std::vector<std::string>    data(){return _data;}

        std::string toString() const {
            std::string result(err_header);

            auto append_string_to_result = [&result](std::string row){result += row; result += "\r\n";};

            switch(_code){
                case Result::OK: {
                    result = "";
                    if(!_data.empty())
                        std::for_each(_data.begin(), _data.end(), append_string_to_result);

                    result+= "OK";
                    break;
                }
                case Result::WRONG_ARGUMENTS: {
                    result+= "Wrong command Arguments ";
                    break;
                }

                case Result::TABLE_EXISTS_ALREADY: {
                    result += "This table exists ";
                    break;
                }

                case Result::UNKNOWN_TABLE:{
                    result +=  "This table doesn't exist ";
                    break;
                }

                case Result::DUPLICATE_KEY:{
                    result += "duplicate ";
                    break;
                }
                default: result += "Unknown Error ";
            };

            if(!_data.empty() && _code!=Result::OK)
                std::for_each(_data.begin(), _data.end(), append_string_to_result);
            else
                result += "\r\n";

            return result;
        }
    protected:

    private:
        Result   _code;
        std::vector<std::string>    _data;
};

#endif // TOPERATIONRESULT_H
