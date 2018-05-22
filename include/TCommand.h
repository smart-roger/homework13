#ifndef TCOMMAND_H
#define TCOMMAND_H

#include "TDBController.h"
#include "TOperationResult.h"
#include <sstream>

class TCommand
{
    public:
        TCommand()=delete;
        TCommand(std::string name):_name(name){};
        TCommand(const TCommand& other):_name(other._name){}
        TCommand(TCommand&& other):_name(other._name){}
        virtual ~TCommand(){};

        TOperationResult exec(std::shared_ptr<TDBController> controller, std::stringstream& args)
        { return execute(controller, args);}
        std::string usage(){return getUsageString();}
        std::string command(){return _name;}
    protected:
        virtual TOperationResult execute (std::shared_ptr<TDBController> controller, std::stringstream& args) =0;
        virtual std::string getUsageString() = 0;
    private:
        std::string _name;
};

class TCommandCreate : public TCommand{
    public:
    TCommandCreate():TCommand("create"){};
    TCommandCreate(const TCommandCreate& other):TCommand(other){};
    TCommandCreate(TCommandCreate&& other):TCommand(std::move(other)) {};
    ~TCommandCreate(){};

    protected:
        virtual TOperationResult execute (std::shared_ptr<TDBController> controller, std::stringstream& args) override;
        virtual std::string getUsageString() override;
};

class TCommandInsert : public TCommand{
    public:
    TCommandInsert():TCommand("INSERT"){};
    TCommandInsert(const TCommandInsert& other):TCommand(other){};
    TCommandInsert(TCommandInsert&& other):TCommand(std::move(other)) {};
    ~TCommandInsert(){};

    protected:
        virtual TOperationResult execute (std::shared_ptr<TDBController> controller, std::stringstream& args) override;
        virtual std::string getUsageString() override;
};

class TCommandTruncate : public TCommand{
    public:
    TCommandTruncate():TCommand("TRUNCATE"){};
    TCommandTruncate(const TCommandTruncate& other):TCommand(other){};
    TCommandTruncate(TCommandTruncate&& other):TCommand(std::move(other)) {};
    ~TCommandTruncate(){};

    protected:
        virtual TOperationResult execute (std::shared_ptr<TDBController> controller, std::stringstream& args) override;
        virtual std::string getUsageString() override;
};

class TCommandIntersection : public TCommand{
    public:
    TCommandIntersection():TCommand("INTERSECTION"){};
    TCommandIntersection(const TCommandInsert& other):TCommand(other){};
    TCommandIntersection(TCommandInsert&& other):TCommand(std::move(other)) {};
    ~TCommandIntersection(){};

    protected:
        virtual TOperationResult execute (std::shared_ptr<TDBController> controller, std::stringstream& args) override;
        virtual std::string getUsageString() override;
};

class TCommandDifference : public TCommand{
    public:
    TCommandDifference():TCommand("SYMMETRIC_DIFFERENCE"){};
    TCommandDifference(const TCommandInsert& other):TCommand(other){};
    TCommandDifference(TCommandInsert&& other):TCommand(std::move(other)) {};
    ~TCommandDifference(){};

    protected:
        virtual TOperationResult execute (std::shared_ptr<TDBController> controller, std::stringstream& args) override;
        virtual std::string getUsageString() override;
};

#endif // TCOMMAND_H
