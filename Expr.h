//
// Created by Zach Allred on 1/18/24.
//

#ifndef PROJECT_EXPR_H
#define PROJECT_EXPR_H


#include <string>

/**
 *Expression Class with equals interface
 */

class Expr {
public:
    virtual bool equals(Expr *e) = 0;
    virtual int interp() = 0;
    virtual bool has_variable() =0;
    virtual Expr* subst(std::string findValue, Expr *e)=0;
};

/**
 * Number Class extending expression class
 */
class Num : public Expr {
public:
    int val;

    Num(int val);

    bool equals(Expr *number);
    int interp();
    bool has_variable();
    Expr* subst(std::string findValue, Expr *e);
};

/**
 * Add Class extending expression class
 */

class Add : public Expr {
public:
    Expr *lhs;
    Expr *rhs;

    Add(Expr *lhs, Expr *rhs);

    bool equals(Expr *number);
    int interp();
    bool has_variable();
    Expr* subst(std::string findValue, Expr *e);
};

/**
 * Mult class extending Expression class
 */
class Mult : public Expr {
public:
    Expr *lhs;
    Expr *rhs;

    Mult(Expr *lhs, Expr *rhs);

    bool equals(Expr *number);
    int interp();
    bool has_variable();
    Expr* subst(std::string findValue, Expr *e);
};

/**
 * Variable class extending Expression class
 */
class Variable : public Expr {
public:
    std::string val;

    Variable(std::string val);

    bool equals(Expr *variable);
    int interp();
    bool has_variable();
    Expr* subst(std::string findValue, Expr *e);

};



#endif //PROJECT_EXPR_H
