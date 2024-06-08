package org.ioopm.calculator.ast;

import java.util.ArrayList;

public class FunctionCall extends SymbolicExpression {
    private String name;
    private ArrayList<SymbolicExpression> argList;

    public FunctionCall(String name) {
        this.name = name;
    }

    public void addArgList(ArrayList<SymbolicExpression> argList) {
        this.argList = argList;
    }

    public ArrayList<SymbolicExpression> getArgList() {
        return argList;
    }

    public String getName() {
        return this.name;
    }

    @Override
    public SymbolicExpression eval(Environment vars) throws IllegalAssignment {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'eval'");
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}
