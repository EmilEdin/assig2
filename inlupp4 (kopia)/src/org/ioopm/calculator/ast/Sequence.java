package org.ioopm.calculator.ast;

import java.util.ArrayList;

public class Sequence extends SymbolicExpression{
    private ArrayList<SymbolicExpression> orders;
    private ArrayList<SymbolicExpression> assignments;
    private String name;

    public Sequence() {
        this.orders = new ArrayList<SymbolicExpression>();
        this.assignments = new ArrayList<SymbolicExpression>();
    }

    public void addNameSeq(String name) {
        this.name = name;
    }

    public String getNameSeq() {
        return this.name;
    }
    
    public ArrayList<SymbolicExpression> getList() {
        return orders;
    }

    public void insertOrder(SymbolicExpression order) {
        orders.add(order);
    }

    public void insertOrderFirst(SymbolicExpression order) {
        orders.add(0, order);
    }

    public ArrayList<SymbolicExpression> getAssignmentList() {
        return assignments;
    }

    public void createAssignmentList() {
        assignments = new ArrayList<SymbolicExpression>();
    }

    public void insertAssignment(SymbolicExpression order) {
        assignments.add(order);
    }

    public void insertAssignmentFirst(SymbolicExpression order) {
        assignments.add(0, order);
    }

    @Override
    public SymbolicExpression eval(Environment vars) throws IllegalAssignment {
        throw new UnsupportedOperationException("Unimplemented method 'eval'");
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }

    // Debugging purpose
    public String toString() {
        String list_of_orders = "";
        int i = 0;
        for (SymbolicExpression e: orders) {
            i = i + 1;
            list_of_orders = list_of_orders + " " + i + ": " + e.toString();
        }
        return list_of_orders;
    }
}
