package org.ioopm.calculator;

import static org.junit.jupiter.api.Assertions.*;

import org.ioopm.calculator.parser.Constants;

import java.beans.Transient;
import java.io.IOException;
import java.util.*;
import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.CalculatorParser;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;

// import ast.Addition;

public class CalculatorTests {

    // Binary
    private static Addition addition;
    private static Subtraction subtraction;
    private static Multiplication multiplication;
    private static Division division;
    private static Assignment assignment;
    // Unary
    private static Sin sin;
    private static Cos cos;
    private static Exp exp;
    private static Log log;
    private static Negation negation;
    // Atom
    private static SymbolicExpression constant;
    private static SymbolicExpression constant2;
    private static Variable variable;
    // Command
    private static Vars vars;
    private static Quit quit;
    private static Clear clear;
    // Enviroment
    final EnvironmentHandler environment = new EnvironmentHandler();
    private static EvaluationVisitor eval;
    ArrayList<FunctionDeclaration> functionList = new ArrayList<FunctionDeclaration>();

    @BeforeAll
    static void initAll() {
        // Atom
        constant = new Constant(2);
        constant2 = new Constant(4);
        variable = new Variable("x");
        // Binary
        addition = new Addition(constant, constant2);
        subtraction = new Subtraction(constant, constant2);
        multiplication = new Multiplication(constant, constant2);
        division = new Division(constant, constant2);
        assignment = new Assignment(constant, variable); // The constructor Assignment(Constant, Variable) is undefined
        // Unary
        sin = new Sin(constant);
        cos = new Cos(constant);
        exp = new Exp(constant);
        log = new Log(constant);
        negation = new Negation(constant); // The constructor Assignment(Constant, Variable) is undefined
        vars = Vars.instance();
        quit = Quit.instance();
        clear = Clear.instance();
        // environment = new Environment();
        eval = new EvaluationVisitor();
        // FunctionList
        ArrayList<FunctionDeclaration> functionList = new ArrayList<FunctionDeclaration>();
        

    }

    @BeforeEach
    void init() {
    }


    // --------------------------------------------
    // Unary Tests
    // --------------------------------------------
    @Test
    void GetValueTest() {
        // Binary
        assertThrows(RuntimeException.class, () -> addition.getValue());
        assertThrows(RuntimeException.class, () -> subtraction.getValue());
        assertThrows(RuntimeException.class, () -> multiplication.getValue());
        assertThrows(RuntimeException.class, () -> division.getValue());
        assertThrows(RuntimeException.class, () -> assignment.getValue());
        // Unary
        assertThrows(RuntimeException.class, () -> cos.getValue());
        assertThrows(RuntimeException.class, () -> sin.getValue());
        assertThrows(RuntimeException.class, () -> log.getValue());
        assertThrows(RuntimeException.class, () -> exp.getValue());
        assertThrows(RuntimeException.class, () -> negation.getValue());
        // Atom
        assertThrows(RuntimeException.class, () -> variable.getValue());
        assertEquals(constant.getValue(), 2);
        // Command
        assertThrows(RuntimeException.class, () -> quit.getValue());
        assertThrows(RuntimeException.class, () -> vars.getValue());
        assertThrows(RuntimeException.class, () -> clear.getValue());
    }

    @Test
    void IsConstantTest() {
        // Binary 
        assertFalse(addition.isConstant());
        assertFalse(subtraction.isConstant());
        assertFalse(multiplication.isConstant());
        assertFalse(division.isConstant());
        assertFalse(assignment.isConstant());
        // Unary
        assertFalse(cos.isConstant());
        assertFalse(sin.isConstant());
        assertFalse(log.isConstant());
        assertFalse(exp.isConstant());
        assertFalse(negation.isConstant());
        // Atom
        assertFalse(variable.isConstant());
        assertTrue(constant.isConstant());
        // Command
        assertFalse(quit.isConstant());
        assertFalse(vars.isConstant());
        assertFalse(clear.isConstant());
    }

    @Test 
    void GetName() {
        // Binary
        assertTrue(addition.getName().equals("+"));
        assertTrue(subtraction.getName().equals("-"));
        assertTrue(multiplication.getName().equals("*"));
        assertTrue(division.getName().equals("/"));
        assertTrue(assignment.getName().equals("="));
        // Unary
        assertTrue(cos.getName().equals("Cos"));
        assertTrue(sin.getName().equals("Sin"));
        assertTrue(log.getName().equals("Log"));
        assertTrue(exp.getName().equals("Exp"));
        assertTrue(negation.getName().equals("Neg"));
        // Atom
        assertThrows(RuntimeException.class, () -> variable.getName());
        assertThrows(RuntimeException.class, () -> constant.getName());
        // Command
        assertThrows(RuntimeException.class, () -> quit.getName());
        assertThrows(RuntimeException.class, () -> vars.getName());
        assertThrows(RuntimeException.class, () -> clear.getName());
    }

    @Test
    void IsCommandTest() {
        // Binary 
        assertFalse(addition.isCommand());
        assertFalse(subtraction.isCommand());
        assertFalse(multiplication.isCommand());
        assertFalse(division.isCommand());
        assertFalse(assignment.isCommand());
        // Unary
        assertFalse(cos.isCommand());
        assertFalse(sin.isCommand());
        assertFalse(log.isCommand());
        assertFalse(exp.isCommand());
        assertFalse(negation.isCommand());
        // Atom
        assertFalse(variable.isCommand());
        assertFalse(constant.isCommand());
        // Command
        assertTrue(quit.isCommand());
        assertTrue(vars.isCommand());
        assertTrue(clear.isCommand());
    }

    @Test
    void GetPriorityTest() {
        // Binary
        assertEquals(addition.getPriority(), 50);
        assertEquals(subtraction.getPriority(), 50);
        assertEquals(multiplication.getPriority(), 100);
        assertEquals(division.getPriority(), 100);
        assertEquals(assignment.getPriority(), 50);
        // Unary
        assertEquals(cos.getPriority(), 100);
        assertEquals(sin.getPriority(), 100);
        assertEquals(log.getPriority(), 100);
        assertEquals(exp.getPriority(), 100);
        assertEquals(negation.getPriority(), 100);
        // Atom
        assertEquals(variable.getPriority(), 100);
        assertEquals(constant.getPriority(), 100);
        // Command
        assertEquals(quit.getPriority(), 100);
        assertEquals(vars.getPriority(), 100);
        assertEquals(clear.getPriority(), 100);
    }

    // --------------------------------------------
    // Integration Tests
    // --------------------------------------------
    
    @Test
    void ToStringTest() {
        
    }

    @Test
    void EqualsTest() {
        assertTrue(new Multiplication(new Addition(constant, 
                                                   new Variable("y")), 
                                      new Subtraction(constant, 
                                                      constant2)).equals(new Multiplication(new Addition(constant, 
                                                                                                         new Variable("y")), 
                                                                                            new Subtraction(constant, 
                                                                                                            constant2))));
        assertTrue(new Division(new Constant(8), 
                                new Addition(new Negation(new Constant(4)),
                                             new Constant(4))).equals(new Division(new Constant(8), 
                                                                                   new Addition(new Negation(new Constant(4)), 
                                                                                                new Constant(4)))));
        assertTrue(new Cos(new Exp(new Sin(new Constant(7)))).equals(new Cos(new Exp(new Sin(new Constant(7))))));
        assertFalse(new Cos(new Exp(new Sin(new Constant(7)))).equals(new Cos(new Exp(new Sin(new Constant(1))))));
        assertFalse(new Sin(new Exp(new Sin(new Constant(7)))).equals(new Cos(new Exp(new Sin(new Constant(7))))));
    }
    
    @Test
    void EvalTest() {
        try {
            // 5 + 4 * 10
            
            assertTrue(eval.evaluate(new Addition(new Constant(5), 
                                    new Multiplication(new Constant(4),
                                                    new Constant(10))), environment, functionList).equals(new Constant(45.0)));
            
            // 1 / 0
            assertTrue(eval.evaluate(new Division(new Constant(1),
                                    new Constant(0)), environment, functionList).equals(new Constant(Double.POSITIVE_INFINITY)));
            
            // 1 + 2 + 3 + x
            assertTrue(eval.evaluate(new Addition(new Addition(new Addition(new Constant(1), 
                                                                            new Constant(2)),
                                                               new Constant(3)),
                                                  new Variable("x")), environment, functionList).equals(new Addition(new Constant(6),
                                                                                                                  new Variable("x"))));
            // 5 = x
            // 12 - 30 / x
            
            eval.evaluate(new Assignment(new Constant(5), new Variable("x")), environment, functionList);
            
            assertTrue(eval.evaluate(new Subtraction(new Constant(13), 
                                       new Division(new Constant(30) ,
                                                    new Variable("x"))), environment, functionList).equals(new Constant(7)));
            
            
        } catch (IllegalAssignment e) {

        }
    }   

    @Test
    void ParserTest() {
        final CalculatorParser program = new CalculatorParser();

        try {
        // 5 + 4 * 10
        Addition test1 = new Addition(new Constant(5), 
                                    new Multiplication(new Constant(4),
                                                    new Constant(10)));
        SymbolicExpression object1 = program.parse(test1.toString(), environment, functionList);
        assertTrue(test1.equals(object1));

        // - - - 5
        Negation test2 = new Negation(new Negation(new Negation(new Constant(5))));
        SymbolicExpression object2 = program.parse(test2.toString(), environment, functionList);
        assertTrue(test2.equals(object2));

        // (15 - 3) / 2
        Division test3 = new Division(new Subtraction(new Constant(15), new Constant(3)), new Constant(2));
        SymbolicExpression object3 = program.parse(test3.toString(), environment, functionList);
        assertTrue(test3.equals(object3));

        // 20 - (3 + 6)
        Subtraction test4 = new Subtraction(new Constant(20), new Addition(new Constant(3), new Constant(6)));
        SymbolicExpression object4 = program.parse(test4.toString(), environment, functionList);
        assertTrue(test4.equals(object4));

        // Cos(Sin(x))
        Cos test5 = new Cos(new Sin(new Variable("x")));
        SymbolicExpression object5 = program.parse(test5.toString(), environment, functionList);
        assertTrue(test5.equals(object5));

        // Exp(Log(25))
        Exp test6 = new Exp(new Log(new Constant(25)));
        SymbolicExpression object6 = program.parse(test6.toString(), environment, functionList);
        assertTrue(test6.equals(object6));

        // (2+5) * (10/5) - Sin(Exp(Log(3*(1+5))))
        Subtraction test7 = new Subtraction(new Multiplication(new Addition(new Constant(2), 
                                                                            new Constant(5)),
                                                               new Division(new Constant(10), 
                                                                            new Constant(5))),
                                            new Sin(new Exp(new Log(new Multiplication(new Constant(3), 
                                                                                       new Addition(new Constant(1), 
                                                                                                    new Constant(5)))))));
        SymbolicExpression object7 = program.parse(test7.toString(), environment, functionList);
        assertTrue(test7.equals(object7));


        // Skall skrivas tester för namedconstants

        // System.out.println(test5.toString());
        // System.out.println(object5.toString());
        // System.out.println(test5.accept(eval).toString());
        // System.out.println(object5.accept(eval).toString());
        } 
        catch (IOException e) {

        }
        // catch (IllegalAssignment a) {

        // }
    }

    @Test
    void ScopeTest() {
        final CalculatorParser program = new CalculatorParser();
        try {
        // Parser tests
        // 3 + {2 + 5} eller {2 + 5} + 3 Det ska bli 10
        Addition test11 = new Addition(new Constant(3),
                 new Scope(new Addition(new Constant(2), new Constant(5))));
        SymbolicExpression object1 = program.parse(test11.toString(), environment, functionList);
        assertTrue(test11.equals(object1));
        // {3 + {1 = x}}
        Scope test12 = new Scope(new Addition(new Constant(3), 
                        new Scope(new Assignment(new Constant(1), new Variable("x")))));
        SymbolicExpression object2 = program.parse(test12.toString(), environment, functionList);
        assertTrue(test12.equals(object2));
        

        // Eval tests
        // {{1 = x} = x}
        assertTrue(eval.evaluate(new Scope(new Assignment(new Scope(
            new Assignment(new Constant(1), 
                        new Variable("x"))), new Variable("x"))), environment, functionList).equals(new Constant(1)));
            // {(1=x) + (3=x)} Reassignment error
        assertFalse(eval.evaluate(new Scope(new Addition(
                        new Assignment(new Constant(1), new Variable("x")), 
                        new Assignment(new Constant(3), new Variable("x")))), environment, functionList).equals(new Constant(4)));
        
    } catch (IOException e) {

    } 
}

    @Test
    void ConditionalTest() {
        final CalculatorParser program = new CalculatorParser();
        try {
            // Parser Tests
            // if 3 > 2 { 42 } else { 10 }
            Conditional condition1 = new Conditional(new Constant(3), new Constant(2), ">", new Constant(42), new Constant(10));
            SymbolicExpression object1 = program.parse(condition1.toString(), environment, functionList);
            assertEquals(condition1, object1);
            assertTrue(condition1.equals(object1));

            // if 3 == 2 { 42 } else { 10 }
            Conditional condition2 = new Conditional(new Constant(3), new Constant(2), "==", new Constant(42), new Constant(10));
            SymbolicExpression object2 = program.parse(condition2.toString(), environment, functionList);
            assertTrue(condition2.equals(object2));
            
            // if x > 2 { 42 } else { y }
            Conditional condition3 = new Conditional(new Variable("x"), new Constant(2), ">", new Constant(42), new Variable("y"));
            SymbolicExpression object3 = program.parse(condition3.toString(), environment, functionList);
            assertTrue(condition3.equals(object3));

            // if 5 >= 5 { 10 } else { y }
            Conditional condition4 = new Conditional(new Constant(5), new Constant(5), ">=", new Constant(10), new Variable("y"));
            SymbolicExpression object4 = program.parse(condition4.toString(), environment, functionList);
            assertTrue(condition4.equals(object4));

            // Eval Tests
            assertTrue(eval.evaluate(object1, environment, functionList).equals(new Constant(42)));
            assertTrue(eval.evaluate(object2, environment, functionList).equals(new Constant(10)));
            assertTrue(eval.evaluate(object4, environment, functionList).equals(new Constant(10)));
            // x = 1, y = 1337
            eval.evaluate(new Assignment(new Constant(1), new Variable("x")), environment, functionList);          
            eval.evaluate(new Assignment(new Constant(1337), new Variable("y")), environment, functionList);
            // if x > 2 { 42 } else { y }
            assertTrue(eval.evaluate(object3, environment, functionList).equals(new Constant(1337)));
        
        } catch (IOException e) {

        }

    }

    @Test 
    void functionDeclarationTest() {
        Calculator program = new Calculator();
    }

    @AfterEach
    void tearDown() {
        environment.clear();
    }

    @AfterAll
    static void tearDownAll() {
    }
}















// For test
/*
 * 
 * Welcome to the Symbolic Calculator!
 * ? 2*(5-2)
 * 6.0 [All numeric operations use floating point arithmetic (double)]
 * 
 * ? 1/(2+8) = a [Assign values to variables -- variable names to the right!]
 * 0.1 [Assignments return the value of the variable.]
 * 
 * ? 2 = x = y [Multiple assignments are supported.]
 * 2.0
 * 
 * ? (x+y=z) - (z-1)*(1=x) [Assignments are allowed inside expressions.
 * Evaluation from left to right.]
 * 1.0
 * 
 * ? -sin(exp(a*a*10)) [Elementary functions.]
 * -0.8935409432921488
 * 
 * ? ans [This is a built-in variable that stores the value of the last
 * expression evaluated.]
 * -0.8935409432921488
 * 
 * ? -ans+2 [Ans can be used as a normal variable.]
 * 2.8935409432921488
 * 
 * ? - - -x
 * -1.0
 */
/*
 * 
 * ? b [Undefined variables evaluate to themselves]
 * b
 * 
 * ? 1 = a
 * 1.0
 * 
 * ? a + b [Sometimes evaluation results in an expression]
 * 1.0 + b
 * 
 * 
 * ? b + a = c [Values can be expressions]
 * b + 1.0
 * 
 * ? 2 = b [Assigning a value to b does not change previous expressions
 * containing b]
 * 2.0
 * 
 * ? c [Evaluation only happens once -- values are not evaluated!]
 * b + 1.0
 * 
 * ? 2*x = y
 * 2.0*x
 * 
 * ? vars [Built-in command to list all existing variables and their values.]
 * 2 {ans=1.0, a=0.1, x=1.0, y=2.0, z=4.0}
 * 
 * ? 3**5 ++ x [Failure handling -- no crashing.]
 *** Syntax Error: Unexpected: *
 * 
 * ? foo(x+y)
 *** Syntax Error: Unexpected: (
 * 
 * ? 1/0 [Some errors can be left to Java to handle.]
 * Infinity
 */