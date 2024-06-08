package org.ioopm.calculator.ast;

import java.util.ArrayList;

public class FunctionDeclaration extends SymbolicExpression {
    private String name;
    private Sequence body;
    // private FunctionCall functionCall;
    private ArrayList<String> list;

    public FunctionDeclaration(String name) {
        this.name = name;
        this.list = new ArrayList<String>();
        // this.functionCall = functionCall;
    }

    // public void insertFunctionCall(FunctionCall functionCall) {
    //     this.functionCall = functionCall;
    // }

    // public FunctionCall getFunctionCall() {
    //     return this.functionCall;
    // }

    public void addParam(String param) {
        list.add(param);
    }
    public ArrayList<String> getList() {
        return this.list;
    }

    public String getParam(int index) {
        return list.get(index);
    }
    public int getSize() {
        return list.size();
    }

    public void insertBody(Sequence body) {
        this.body = body;
    }
    public String getName() {
        return name;
    }

    public Sequence getBody() {
        return body;
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

// 