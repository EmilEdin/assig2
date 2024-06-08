package org.ioopm.calculator;

import org.ioopm.calculator.ast.*;

import org.ioopm.calculator.parser.CalculatorParser;
import org.ioopm.calculator.parser.SyntaxErrorException;

import java.io.StreamTokenizer;
import java.io.StringReader;
import java.io.IOException;

import java.util.*;

public class Calculator {

    public static void main(String[] args) {
        final CalculatorParser program = new CalculatorParser();
        final EnvironmentHandler vars = new EnvironmentHandler();
        boolean functionParsingMode = false;

        int totalExpressionsEntered = 0;
        int successfullyEvaluated = 0;
        int fullyEvaluated = 0;
        Scanner sc = new Scanner(System.in);

        Sequence sequenceHolder = null;
        FunctionDeclaration declarationHolder = null;

        ArrayList<FunctionDeclaration> functionList = new ArrayList<FunctionDeclaration>();

        while (true) {
            try {
                System.out.println("Please enter an expression: ");

                String input = sc.nextLine();
                SymbolicExpression object = program.parse(input, vars, functionList);
                
                EvaluationVisitor evaluator = new EvaluationVisitor();
                totalExpressionsEntered++;

                if (object instanceof FunctionDeclaration) {
                    if (functionParsingMode) {
                        throw new SyntaxErrorException("Nested function definitions are not permitted");
                    } else {
                        functionParsingMode = true;
                        sequenceHolder = new Sequence();
                        declarationHolder = (FunctionDeclaration) object;
                    }
                } 

                if (object.isCommand()) {
                    if (object instanceof Quit) {
                        System.out.println("Exiting the calculator. Goodbye!");
                        System.out.println("Statistics:");
                        System.out.println("Total expressions entered: " + totalExpressionsEntered);
                        System.out.println("Successfully evaluated expressions: " + successfullyEvaluated);
                        System.out.println("Fully evaluated expressions: " + fullyEvaluated);
                        break;
                    } else if (object instanceof Clear) {
                        vars.environmentpeek().clear();
                        
                        System.out.println("Variable list cleared.");
                    } else if (object instanceof Vars) {
                        System.out.println(vars.toString());
                    } else if (object instanceof End) {
                        if (functionParsingMode) {
                            declarationHolder.insertBody(sequenceHolder);
                            sequenceHolder.addNameSeq(declarationHolder.getName());
                            // Remove the existing function if it already exists in the functionList
                            for(int i = 0; i < functionList.size(); i++) {
                                if (declarationHolder.getName().equals(functionList.get(i).getName())) {
                                    functionList.remove(i);
                                };
                            }

                            functionList.add(declarationHolder);
                            functionParsingMode = false;
                        } else {
                            throw new SyntaxErrorException("Cannot call 'End' when not implementing a function");
                        }
                    }
                } else if (functionParsingMode){
                    if (!(object instanceof FunctionDeclaration || object instanceof Command)) {
                        sequenceHolder.insertOrder(object);
                    }
                } else {
                    try {
                        SymbolicExpression result = evaluator.evaluate(object, vars, functionList);
                        vars.put(new Variable("ans"), result);
                        System.out.println("Result: " + result);
                        successfullyEvaluated++;
                        if (result.isConstant()) {
                        fullyEvaluated++;
                        
                        }
                    } catch (IllegalAssignment e) {
                        System.out.println("Error: " + e.getMessage());
                        continue;
                    }
                }
            } catch (IllegalExpressionException e) {
                System.out.println("Error: " + e.getMessage());
                continue;
            } catch (SyntaxErrorException e) {
                System.out.println("Syntax " + e.getMessage());
                continue;
            } catch (IOException e) {
                System.out.println("Error" + e.getMessage());
            }
        }
        sc.close();
    }
}

