package org.ioopm.calculator.parser;

import org.ioopm.calculator.ast.*;

import java.io.StreamTokenizer;
import java.io.StringReader;
import java.io.IOException;

import java.util.*;

/**
 * Represents the parsing of strings into valid expressions defined in the AST.
 */
public class CalculatorParser {
    private StreamTokenizer st;
    private EnvironmentHandler vars;
    private ArrayList<FunctionDeclaration> functionList;
    private static char MULTIPLY = '*';
    private static char ADDITION = '+';
    private static char SUBTRACTION = '-';
    private static char DIVISION = '/';
    private static String NEG = "Neg";
    private static char NEGATION = '-';
    private static String SIN = "Sin";
    private static String COS = "Cos";
    private static String LOG = "Log";
    private static String EXP = "Exp";
    private static char ASSIGNMENT = '=';
    private static String LESSTHAN = "<";
    private static String LESSOREQUAL = "<=";
    private static String EQUAL = "==";
    private static String GREATERTHAN = ">";
    private static String GREATEROREQUAL = ">=";
    private static String IF = "if";
    private static String ELSE = "else";

    String functionName = "";
    FunctionDeclaration functionDeclaration = null;

    // unallowerdVars is used to check if variabel name that we
    // want to assign new meaning to is a valid name eg 3 = Quit
    // or 10 + x = L is not allowed
    private final ArrayList < String > unallowedVars = new ArrayList < String > (Arrays.asList("Quit",
        "Vars",
        "Clear", "Sin", "if", "else", "Cos", "Log", "Neg", "Exp", "function", "End"));

    /**
     * Used to parse the inputted string by the Calculator program
     * @param inputString the string used to parse
     * @param vars the Environment in which the variables exist
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     */
    public SymbolicExpression parse(String inputString, EnvironmentHandler vars, ArrayList<FunctionDeclaration> functionList) throws IOException {
        this.st = new StreamTokenizer(new StringReader(inputString)); // reads from inputString via stringreader.
        this.vars = vars;
        this.functionList = functionList;
        this.st.ordinaryChar('-');
        this.st.ordinaryChar('/');
        this.st.eolIsSignificant(true);
        SymbolicExpression result = statement(); // calls to statement
        return result; // the final result
    }

    /**
     * Checks wether the token read is a command or an assignment
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a valid expression
     */
    private SymbolicExpression statement() throws IOException {
        SymbolicExpression result = null;
        this.st.nextToken(); //kollar pÃ¥ nÃ¤sta token som ligger pÃ¥ strÃ¶mmen
        if (this.st.ttype == this.st.TT_EOF) {
            throw new SyntaxErrorException("Error: Expected an expression");
        }

        if (this.st.ttype == this.st.TT_WORD) { // vilken typ det senaste tecken vi lÃ¤ste in hade.
            if (this.st.sval.equals("function")) {
                result = functionDeclaration();
            } else if (this.st.sval.equals("Quit") || this.st.sval.equals("Vars") || this.st.sval.equals("Clear") || this.st.sval.equals("End")) { // sval = string Variable
                result = command();
            } else {
                result = assignment(); // gÃ¥r vidare med uttrycket.
            }
        } else {
            result = assignment(); // om inte == word, gÃ¥ till assignment Ã¤ndÃ¥ (kan vara tt_number)
        }

        if (this.st.nextToken() != this.st.TT_EOF) { // token should be an end of stream token if we are done
            if (this.st.ttype == this.st.TT_WORD) {
                throw new SyntaxErrorException("Error: Unexpected '" + this.st.sval + "'");
            } else {
                throw new SyntaxErrorException("Error: Unexpected '" + String.valueOf((char) this.st.ttype) + "'");
            }
        }
        return result;
    }

    /**
     * Checks that the functiondeclaration is correct and returns one if correct structure and syntax
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a valid expression
     */
    private SymbolicExpression functionDeclaration() throws IOException {
        this.st.nextToken();
                
        if (this.st.ttype != this.st.TT_WORD) {
            throw new SyntaxErrorException("Expected function name [function, Parser]");
        }
        functionName = this.st.sval;
        
        functionDeclaration = new FunctionDeclaration(functionName);
        this.st.nextToken();
        if (this.st.ttype == '(') {
            this.st.nextToken();
            while (this.st.ttype != this.st.TT_EOL) { 
                int current = this.st.ttype;
                String param = this.st.sval;
                int next = this.st.nextToken();
                if (current == ')') {
                    break;
                } else if (current == this.st.TT_WORD && next == ',') {
                    functionDeclaration.addParam(param);
                    this.st.nextToken();
                } else if (current == this.st.TT_WORD && next == ')') {
                    functionDeclaration.addParam(param);
                    break;
                } else {
                    throw new SyntaxErrorException("Expected argument 97 [function, Parser]");
                }
            }
        } else {
            throw new SyntaxErrorException("expected '(' [Function 93, Parser]");
        }
        return functionDeclaration;
    }

    /**
     * Checks that the function call has correct structure and syntax and that the function is defined.
     * @return a SymbolicExpression to be evaluated. 
     * @throws IOException
     * @throws SyntaxErrorException if the token parsed cannot be turned into a valid expression for a function
     *                              declaration.
     */
    private SymbolicExpression functionCall() throws IOException {
        FunctionDeclaration ourFunction = null;
        String name = "";
        if (this.st.sval.equals(functionDeclaration.getName())) {
            ourFunction = functionDeclaration;
            name = functionDeclaration.getName();
        }
        for (FunctionDeclaration function: functionList) {
            if (this.st.sval.equals(function.getName())) {
                ourFunction = function;
                name = function.getName();
            };
        }
            this.st.nextToken();
            if (this.st.ttype == '(') {
                this.st.nextToken();
                ArrayList<SymbolicExpression> paramList = new ArrayList<SymbolicExpression>(); 
                while (this.st.ttype != this.st.TT_EOL) {
                    int current = this.st.ttype;
                    String paramStr = this.st.sval;
                    double paramInt = this.st.nval;
                    int next = this.st.nextToken();
                    if (current == ')') {
                        break;
                    } else if (current == this.st.TT_WORD && next == ',') {
                        paramList.add(new Variable(paramStr));
                        this.st.nextToken();
                    } else if (current == this.st.TT_NUMBER && next == ',') {
                        paramList.add(new Constant(paramInt));
                        this.st.nextToken();
                    } else if (current == this.st.TT_WORD && next == ')') {
                        paramList.add(new Variable(paramStr));
                        break;
                    } else if (current == this.st.TT_NUMBER && next == ')') {
                        paramList.add(new Constant(paramInt));
                        break;
                    } else {
                        throw new SyntaxErrorException("Expected argument 168 [function, Parser]");
                    }
                }  
                if (ourFunction.getSize() == paramList.size()) {
                    FunctionCall newFun = new FunctionCall(name);
                    newFun.addArgList(paramList);
                    return new Scope(newFun);
                    
                } 
            } else {
                throw new SyntaxErrorException("expected '(' [Function 152, Parser]");
            }
            return null;
    }

    /**
     * Checks what kind of command that should be returned
     * @return an instance of Quit, Clear or Vars depending on the token parsed
     * @throws IOException by nextToken() if it reads invalid input
     */
    private SymbolicExpression command() throws IOException {
        if (this.st.sval.equals("Quit")) {
            return Quit.instance();
        } else if (this.st.sval.equals("Clear")) {
            return Clear.instance();
        } else if (this.st.sval.equals("End")) {
            return End.instance();
        } else {
            return Vars.instance();
        }
    }


    /**
     * Checks wether the token read is an assignment between 2 expression and 
     * descend into the right hand side of '='
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a valid expression,
     *         the variable on rhs of '=' is a number or invalid variable
     */
    private SymbolicExpression assignment() throws IOException {
        SymbolicExpression result = expression();
        this.st.nextToken();
        while (this.st.ttype == ASSIGNMENT) {
            this.st.nextToken();
            if (this.st.ttype == this.st.TT_NUMBER) {
                throw new SyntaxErrorException("Error: Numbers cannot be used as a variable name");
            } else if (this.st.ttype != this.st.TT_WORD) {
                throw new SyntaxErrorException("Error: Not a valid assignment of a variable"); //this handles faulty inputs after the equal sign eg. 1 = (x etc
            } else {
                if (this.st.sval.equals("ans")) {
                    throw new SyntaxErrorException("Error: ans cannot be redefined");
                }
                SymbolicExpression key = identifier();
                result = new Assignment(result, key);
            }
            this.st.nextToken();
        }
        this.st.pushBack();
        return result;
    }

    /**
     * Check if valid identifier for variable and return that if so
     * @return a SymbolicExpression that is either a named constant or a new variable
     * @throws IOException by nextToken() if it reads invalid input
     * @throws IllegalExpressionException if you try to redefine a string that isn't allowed
     */
    private SymbolicExpression identifier() throws IOException {
        SymbolicExpression result;

        if (this.unallowedVars.contains(this.st.sval)) {
            throw new IllegalExpressionException("cannot redefine a constant " + this.st.sval);
        }
        
        if (Constants.namedConstants.containsKey(this.st.sval)) {
            result = new NamedConstant(st.sval, Constants.namedConstants.get(st.sval));
        } else {
            result = new Variable(this.st.sval);
        }
        return result;
    }


    /**
     * Checks wether the token read is an addition or subtraction
     * and then continue on with the right hand side of operator
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     */
    private SymbolicExpression expression() throws IOException {
        SymbolicExpression result = term();
        this.st.nextToken();
        while (this.st.ttype == ADDITION || this.st.ttype == SUBTRACTION) {
            int operation = st.ttype;
            this.st.nextToken();
            if (operation == ADDITION) {
                result = new Addition(result, term());
            } else {
                result = new Subtraction(result, term());
            }
            this.st.nextToken();
        }
        this.st.pushBack();
        return result;
    }

    /**
     * Checks wether the token read is an Multiplication or
     * Division and then continue on with the right hand side of
     * operator
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     */
    private SymbolicExpression term() throws IOException {
        SymbolicExpression result = primary();
        this.st.nextToken();
        while (this.st.ttype == MULTIPLY || this.st.ttype == DIVISION) {
            int operation = st.ttype;
            this.st.nextToken();

            if (operation == MULTIPLY) {
                result = new Multiplication(result, primary());
            } else {
                result = new Division(result, primary());
            }
            this.st.nextToken();
        }
        this.st.pushBack();
        return result;
    }

    /**
     * Checks wether the token read is a parantheses and then
     * continue on with the expression inside of it or if the
     * operation is an unary operation and then continue on with
     * the right hand side of that operator else if it's a
     * number/identifier
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a valid expression,
     *         missing right parantheses
     */
    private SymbolicExpression primary() throws IOException {
        SymbolicExpression result;
        if (this.st.ttype == '(') {
            this.st.nextToken();
            result = assignment();
            /// This captures unbalanced parentheses!
            if (this.st.nextToken() != ')') {
                throw new SyntaxErrorException("expected ')'");
            }
        } else if (this.st.ttype == '{') {
            this.st.nextToken();
            // Handle the scope
            result = new Scope(assignment());
    
            // This captures unbalanced curly braces!
            if (this.st.nextToken() != '}') {
                throw new SyntaxErrorException("expected '}'");
            }
    
        } else if (this.st.ttype == NEGATION) {
        
            result = unary();
        } else if (this.st.ttype == this.st.TT_WORD) {
            if (checkFuncName()) {
                result = functionCall(); }
            else if (st.sval.equals(SIN) ||
            st.sval.equals(COS) ||
            st.sval.equals(EXP) ||
            st.sval.equals(NEG) ||
            st.sval.equals(LOG)) {
                
                result = unary();
            } else if (this.st.sval.equals("if")) {
                result = conditional();
            } else {
                result = identifier();
            }
        } else {
            this.st.pushBack();
            result = number();
        }
        return result;
    }

    /** 
     * Checks whether the token read is a conditional operator and checks if the rest of the syntax
     * for the conditional statement is correct. Throws SyntaxError otherwise.
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a valid expression
     *         for a conditional.
     *         
    */
    private SymbolicExpression conditional() throws IOException {
        SymbolicExpression result = null;
        String name = "";
        this.st.nextToken(); // Move past the 'if' keyword
        SymbolicExpression lhs = expression();
        this.st.nextToken();
        
        if (this.st.ttype == 60) {
            this.st.nextToken();
            if (this.st.ttype == 61) {
                name = "<=";
            } else {
                name = "<";
                this.st.pushBack();
            }
        } else if (this.st.ttype == 61) {
            this.st.nextToken();
            if (this.st.ttype == 61) {
                name = "==";
            } else {
                throw new SyntaxErrorException("expected == but got = [291, Parser]");
            }
        } else if (this.st.ttype == 62) {
            this.st.nextToken();
            if (this.st.ttype == 61) {
                name = ">=";
            } else {
                this.st.pushBack();
                name = ">";
            }
        } else {
            throw new SyntaxErrorException("expected word (operator) [302, Parser]");
        }
        this.st.nextToken();
        SymbolicExpression rhs = expression();
        if (this.st.ttype == '{') {
            this.st.nextToken();
            this.st.nextToken(); 
            SymbolicExpression trueBranch = assignment();
            
            // This captures unbalanced curly braces!
            if (this.st.nextToken() != '}') {
                throw new SyntaxErrorException("expected '}' [312, Parser]");
            }
            
            this.st.nextToken();
            if (this.st.ttype == this.st.TT_WORD) {
                if (!st.sval.equals(ELSE)) {
                    throw new SyntaxErrorException("expected 'else' [318, Parser]");
                }
                this.st.nextToken();
                if (this.st.ttype == '{') {
                    this.st.nextToken();
                    SymbolicExpression falseBranch = assignment();

                    // This captures unbalanced curly braces!
                    if (this.st.nextToken() != '}') {
                        throw new SyntaxErrorException("expected last '}' [327, Parser]");
                    }
                    result = new Conditional(lhs, rhs, name, trueBranch, falseBranch);

                } else {
                    throw new SyntaxErrorException("expected last '{' [332, Parser]");
            }
        } else {
            throw new SyntaxErrorException("expected { [335, Parser]");
        }
        }
        return result;
    }

    /**
     * Checks what type of Unary operation the token read is and
     * then continues with the expression that the operator holds
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     */
    private SymbolicExpression unary() throws IOException {
        SymbolicExpression result;
        int operationNeg = st.ttype;
        String operation = st.sval;
        this.st.nextToken();
        if (operationNeg == NEGATION || operation.equals(NEG)) {
            result = new Negation(primary());
        } else if (operation.equals(SIN)) {
            result = new Sin(primary());
        } else if (operation.equals(COS)) {
            result = new Cos(primary());
        } else if (operation.equals(LOG)) {
            result = new Log(primary());
        } else {
            result = new Exp(primary());
        }
        return result;
    }

    /**
     * Checks if the token read is a number - should always be a number in this method
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a valid expression,
     *         expected a number which is not present
     */
    private SymbolicExpression number() throws IOException {
        this.st.nextToken();
        if (this.st.ttype == this.st.TT_NUMBER) {
            return new Constant(this.st.nval);
        } else {
            throw new SyntaxErrorException("Error: Expected number");
        }
    }

    /**
     * Checks if token is a function name already defined
     * @return a Boolean, true if token read 
     *         is a function name already defined in the list, false otherwise
     */
    private Boolean checkFuncName() {
        if (functionDeclaration != null ) {
            if (this.st.sval.equals(functionDeclaration.getName())) {
                return true;
            }
        }
        for (FunctionDeclaration function: functionList) {
            if (this.st.sval.equals(function.getName())) {
                return true;
            };
        }
        return false;
    }
}