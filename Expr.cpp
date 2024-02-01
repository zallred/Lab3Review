//
// Created by Zach Allred on 1/16/24.
//

#include "Expr.h"
#include "catch.h"
#include <stdexcept>

/**Constructor to create Num objects
 *
 * @param val - integer value to store
 */

Num::Num(int val) {
    this->val = val;
}

/** method to test if two Num objects are equal
 *
 * @param number - number object
 * @return - boolean of if Num objects are equal
 */

bool Num::equals(Expr *expression) {
    auto *typeCheck = dynamic_cast<Num *>(expression);
    return typeCheck != nullptr && this->val == typeCheck->val;
}

/**Method to return the value from an expression
 *
 * @return  - value from expression
 */

int Num::interp(){
    return this->val;
}

/**Method to check if expression contains a variable
 *
 * @return  - true if contains variable/false otherwise.
 */

bool Num::has_variable(){
return false;
}

/**Method to substitute all specified string values (ie x) with an expression value
 *
 * @param findValue - Variable to search for.
 * @param e - Expression to replace found variable with
 * @return - new expression with replaced value
 */

Expr* Num::subst(std::string findValue, Expr *e){return this;}

/**Constructor for add objects
 *
 * @param lhs - left side of equation
 * @param rhs  -right side of equation
 */

Add::Add(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

/** method to test if two Add expression objects are equal
 *
 * @param number - Expression object
 * @return - boolean of if objects are equal
 */

bool Add::equals(Expr *expression) {
    auto *typeCheck = dynamic_cast<Add *>(expression);
        return typeCheck!=nullptr && typeCheck->lhs->equals(this->lhs) && typeCheck->rhs->equals( this->rhs);
    }

/**Method to return the value from an expression
*
* @return  - value from expression
*/

int Add::interp(){
    return this->rhs->interp() + this->lhs->interp();
}

/**Method to check if expression contains a variable
 *
 * @return  - true if contains variable/false otherwise.
 */

bool Add::has_variable(){
    return this->rhs->has_variable() || this->lhs->has_variable();
}

/**Method to substitute all specified string values (ie x) with an expression value
 *
 * @param findValue - Variable to search for.
 * @param e - Expression to replace found variable with
 * @return - new expression with replaced value
 */

Expr* Add::subst(std::string findValue, Expr *e){
    return new Add(this->lhs->subst(findValue, e), this->rhs->subst(findValue, e));
}

/**Constructor for Mult objects
 *
 * @param lhs - left side of equation
 * @param rhs -right side of equation
 */

Mult::Mult(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

/** method to test if two Multiply expression objects are equal
 *
 * @param number - Expression object
 * @return - boolean of if objects are equal
 */

bool Mult::equals(Expr *expression) {
    auto *typeCheck = dynamic_cast<Mult *>(expression);
    return typeCheck != nullptr && typeCheck->lhs->equals(this->lhs) && typeCheck->rhs->equals(this->rhs);
}

/**Method to return the value from an expression
 *
 * @return  - value from expression
 */

int Mult::interp(){
    return this->rhs->interp() * this->lhs->interp();
}

/**Method to check if expression contains a variable
 *
 * @return  - true if contains variable/false otherwise.
 */

bool Mult::has_variable(){
    return this->rhs->has_variable() || this->lhs->has_variable();
}

/**Method to substitute all specified string values (ie x) with an expression value
 *
 * @param findValue - Variable to search for.
 * @param e - Expression to replace found variable with
 * @return - new expression with replaced value
 */

Expr* Mult::subst(std::string findValue, Expr *e){
    return new Mult(this->lhs->subst(findValue, e), this->rhs->subst(findValue, e));
}

/** Constructor for Variable objects
 *
 * @param val - String value to create Variable object with
 */

Variable::Variable(std::string val) {
    this->val = val;
}

/** method to test if two Variable objects are equal
 *
 * @param variable - variable object object
 * @return - boolean of if Num objects are equal
 */

bool Variable::equals(Expr *expression) {
    auto *typeCheck = dynamic_cast<Variable *>(expression);
    return typeCheck != nullptr && this->val == typeCheck->val;
}

/**Method to check value of expression. Throws error as variable != numeric value
 *
 * throws error
 */

int Variable::interp(){throw std::runtime_error("Variable is not numeric");}

/**Method to check if expression contains a variable
 *
 * @return  - true if contains variable/false otherwise.
 */

bool Variable::has_variable(){
return true;
}

/**Method to substitute all specified string values (ie x) with an expression value
 *
 * @param findValue - Variable to search for.
 * @param e - Expression to replace found variable with
 * @return - new expression with replaced value
 */

Expr* Variable::subst(std::string findValue, Expr *e){
    if(this->val == findValue) {
        return  e ;
    }
return this;
}
/**
 * Test Cases
 */

TEST_CASE("Add Expressions")
{
    SECTION("0 Values"){
        CHECK((new Add(new Num(0), new Num(0)))->equals(new Add(new Num(0), new Num(0))) == true);
    }

    SECTION("different types test"){
        CHECK((new Add(new Num(1), new Num(2)))->equals(new Variable("x")) == false);
        CHECK((new Add(new Num(1), new Num(2)))->equals(new Mult(new Num(1), new Num(2))) == false);
    }

    SECTION("Class provided Tests") {
        CHECK((new Add(new Num(2), new Num(3)))->equals(new Add(new Num(2), new Num(3))) == true);
        CHECK((new Add(new Num(2), new Num(3)))->equals(new Add(new Num(3), new Num(2))) == false);
    }
    SECTION("Interp") {
        CHECK((new Add(new Add(new Num(10), new Num(15)), new Add(new Num(20), new Num(20))))
                      ->interp() == 65);
        CHECK((new Add(new Add(new Num(0), new Num(0)), new Add(new Num(0), new Num(0))))
                      ->interp() == 0);
        CHECK((new Add(new Num(0), new Num(3)))->interp() == 3);
        CHECK((new Add(new Num(0), new Num(0)))->interp() == 0);
        CHECK((new Add(new Num(100), new Num(100)))->interp() == 200);

    }

    SECTION("has Variable") {
        CHECK((new Add(new Num(2), new Variable("X")))->has_variable() == true);
        CHECK((new Add(new Variable("X"), new Num(2)))->has_variable() == true);
        CHECK((new Add(new Num(2), new Num(2)))->has_variable() == false);
        CHECK((new Add(new Variable("X"), new Variable("X")))->has_variable() == true);
        CHECK((new Add(new Variable("this"), new Num(2)))->has_variable() == true);
    }

    SECTION("subst") {
        CHECK( (new Add(new Variable("x"), new Num(7)))
                       ->subst("x", new Variable("y"))
                       ->equals(new Add(new Variable("y"), new Num(7))) );
        CHECK( (new Variable("x"))
                       ->subst("x", new Add(new Variable("y"),new Num(7)))
                       ->equals(new Add(new Variable("y"),new Num(7))) );
        CHECK( (new Add(new Variable("X"), new Num(7)))
                       ->subst("X", new Variable("y"))
                       ->equals(new Add(new Variable("y"), new Num(7))) );
        CHECK( (new Variable("this"))
                       ->subst("this", new Add(new Variable("y"),new Num(7)))
                       ->equals(new Add(new Variable("y"),new Num(7))) );
    }

}

TEST_CASE("Mult expressions")
{
    SECTION("0 Values"){
        CHECK((new Mult(new Num(0), new Num(0)))->equals(new Mult(new Num(0), new Num(0))) == true);
    }
    SECTION("different types test"){
        CHECK((new Mult(new Num(1), new Num(2)))->equals(new Add(new Num(1), new Num(2))) == false);
        CHECK((new Mult(new Num(1), new Num(2)))->equals(new Variable("x")) == false);
    }
    SECTION("Class provided Tests") {
        CHECK((new Mult(new Num(2), new Num(3)))->equals(new Mult(new Num(2), new Num(3))) == true);
        CHECK((new Mult(new Num(2), new Num(3)))->equals(new Mult(new Num(3), new Num(2))) == false);
    }
    SECTION("Interp") {
        CHECK((new Mult(new Num(2), new Num(3)))->interp() == 6);
        CHECK((new Mult(new Num(0), new Num(3)))->interp() == 0);
        CHECK((new Mult(new Num(0), new Num(0)))->interp() == 0);
        CHECK((new Mult(new Num(100), new Num(100)))->interp() == 10000);
        CHECK( (new Mult(new Num(3), new Num(2)))
                       ->interp()==6 );
    }

    SECTION("has Variable") {
        CHECK((new Mult(new Num(2), new Variable("X")))->has_variable() == true);
        CHECK((new Mult(new Variable("X"), new Num(2)))->has_variable() == true);
        CHECK((new Mult(new Num(0), new Num(2)))->has_variable() == false);
        CHECK((new Mult(new Variable("asda"), new Num(2)))->has_variable() == true);
        CHECK((new Mult(new Num(0), new Variable("X")))->has_variable() == true);
    }

    SECTION("subst") {
    }
    CHECK( (new Mult(new Variable("x"), new Num(7)))
                   ->subst("x", new Variable("y"))
                   ->equals(new Mult(new Variable("y"), new Num(7))) );
    CHECK( (new Variable("x"))
                   ->subst("x", new Mult(new Variable("y"),new Num(7)))
                   ->equals(new Mult(new Variable("y"),new Num(7))) );
    CHECK( (new Mult(new Variable("X"), new Num(7)))
                   ->subst("X", new Variable("y"))
                   ->equals(new Mult(new Variable("y"), new Num(7))) );
    CHECK( (new Variable("this"))
                   ->subst("this", new Mult(new Variable("y"),new Num(7)))
                   ->equals(new Mult(new Variable("y"),new Num(7))) );

}


TEST_CASE("Num expressions")
{
    SECTION("0 Values"){
        CHECK((new Num(0))->equals(new Num(0)) == true);
        CHECK((new Num(0))->val==0);
    }
    SECTION("different types test"){
        CHECK((new Num(9))->equals(new Variable("x")) == false);
    }
    SECTION("long variables test") {
        CHECK((new Num(900342343))->equals(new Num(900342343)) == true);
    }

    SECTION("Class provided Tests") {
        CHECK((new Num(1))->equals(new Variable("x")) == false);
        }

    SECTION("Interp") {
        CHECK((new Num(0))->interp()== 0);
        CHECK((new Num(12))->interp()== 12);
        CHECK((new Num(1))->interp()== 1);
        CHECK((new Num(23123))->interp() == 23123);
        CHECK((new Num(65))->interp() == 65);

    }

    SECTION("has Variable") {
        CHECK((new Num(0))->has_variable()== false);
        CHECK((new Num(12))->has_variable()== false);
        CHECK((new Num(1))->has_variable() == false);
        CHECK((new Num(324234))->has_variable()== false);
        CHECK((new Num(65))->has_variable()== false);
    }

    SECTION("subst") {
        CHECK((new Num(0))->subst("x", new Num(15))->interp() == (new Num(0))->interp());
        CHECK((new Num(32321))->subst("xyzsd", new Num(0))->interp() == (new Num(32321))->interp());
        CHECK((new Num(2))->subst("xadasdas", new Num(90))->interp() == (new Num(2))->interp());
        CHECK((new Num(2))->subst("X", new Num(90))->interp() == (new Num(2))->interp());
        CHECK((new Num(2))->subst("this", new Num(90))->interp() == (new Num(2))->interp());

    }
}

TEST_CASE("Var expressions")
{
    SECTION("long variables test"){
        CHECK((new Variable("xzczxcdasdasdasdasdasd"))->equals(new Variable("xzczxcdasdasdasdasdasd")) == true);
        CHECK((new Variable("xzczxcdasdasdasdasdasd"))->val=="xzczxcdasdasdasdasdasd");
        CHECK((new Variable("0"))->equals(new Variable("0")) == true);
        CHECK((new Variable("0"))->val=="0");
    }

    SECTION("Class provided Tests") {
        CHECK((new Variable("x"))->equals(new Variable("x")) == true);
        CHECK((new Variable("x"))->equals(new Variable("y")) == false);

    }
    SECTION("Interp") {
        CHECK_THROWS_WITH( (new Variable("x"))->interp(), "Variable is not numeric" );
        CHECK_THROWS_WITH( (new Variable("xydasda"))->interp(), "Variable is not numeric" );
        CHECK_THROWS_WITH( (new Variable("0"))->interp(), "Variable is not numeric" );
        CHECK_THROWS_WITH( (new Variable("qwe"))->interp(), "Variable is not numeric" );
        CHECK_THROWS_WITH( (new Variable("X"))->interp(), "Variable is not numeric" );
        CHECK_THROWS_WITH( (new Variable("t"))->interp(), "Variable is not numeric" );

    }

    SECTION("has Variable") {
        CHECK((new Variable("0"))->has_variable() == true);
        CHECK((new Variable("x"))->has_variable() == true);
        CHECK((new Variable("owieopweripw"))->has_variable() == true);
        CHECK((new Variable("X"))->has_variable() == true);
        CHECK((new Variable("T"))->has_variable() == true);

    }

    SECTION("subst") {
        CHECK((new Variable("X"))->subst("X", new Num(90))->interp() == (new Num(90))->interp());
        CHECK((new Variable("X"))->subst("x", new Num(90))->equals(new Variable("X")));
        CHECK((new Variable("asdasd"))->subst("asdasd", new Num(0))->equals(new Num(0)));
        CHECK((new Variable("x"))->subst("x", new Num(90))->equals(new Num(90)));
        CHECK((new Variable("this"))->subst("this", new Num(0))->equals(new Num(0)));

    }
}
