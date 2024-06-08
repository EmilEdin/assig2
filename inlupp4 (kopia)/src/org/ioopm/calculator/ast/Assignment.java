package org.ioopm.calculator.ast;

import org.ioopm.calculator.parser.Constants;


public class Assignment extends Binary {

    public Assignment(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
    }

    public String getName() {
        return "=";
    }

    public int getPriority() {
        return 50;
    }

    public String toString() {
        return String.valueOf(getLhs()) + " " + this.getName() + " " + String.valueOf(getRhs());
    }

    public boolean equals(Object other) {
        if (other instanceof Assignment) {
            return this.equals((Assignment) other);
        } else {
            return false;
        }
    }

    public boolean equals(Assignment other) {
        /// access a private field of other!
        return getLhs().equals(other.getLhs()) && getRhs().equals(other.getRhs());
    }

    public SymbolicExpression eval(Environment vars) throws IllegalAssignment {
        SymbolicExpression leftEvaluated = getLhs().eval(vars);
        if (Constants.namedConstants.containsKey(getRhs().getVariable())) {
            throw new IllegalAssignment("cannot redefine named constant");
        } 
        if (leftEvaluated.isConstant()) {
            vars.put((Variable) getRhs(), leftEvaluated);
            return new Constant(leftEvaluated.getValue());
        } else {
            vars.put((Variable) getRhs(), leftEvaluated);
            return leftEvaluated;
        }
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}
