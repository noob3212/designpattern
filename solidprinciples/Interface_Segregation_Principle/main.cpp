#include <vector>
#include <string>

/**
 * The problem is that every inherited struct IMachine 
 * has to override all fax, scan and print so 
 * better we seggregate the interfaces.
 */

/** 
struct IMachine{
    virtual void print(std::vector<Document*> docs) = 0;
    virtual void fax(std::vector<Document*> docs) = 0;
    virtual void scan(std::vector<Document*> docs) = 0;

};
*/

struct Document{
    std::string name;
};

struct IPrinter{
    virtual void print(std::vector<Document*> docs) = 0;

};

struct IScanner{
    virtual void scan(std::vector<Document*> docs) = 0;

};

struct IFax{
    virtual void fax(std::vector<Document*> docs) = 0;

};

struct Printer : IPrinter{
    void print(std::vector<Document*> docs) override;

};

struct Scanner : IScanner{
    void scan(std::vector<Document*> docs) override;
};

struct IMachine: IPrinter,IScanner{};

struct Machine : IMachine{
    IPrinter &printer;
    IScanner &scanner;

    Machine(IPrinter &printer, IScanner &scanner):
    printer(printer),scanner(scanner){}

    void print(std::vector<Document*> docs) override{
        printer.print(docs);
    }

    void scan(std::vector<Document*> docs) override{
        scanner.scan(docs);
    }

};