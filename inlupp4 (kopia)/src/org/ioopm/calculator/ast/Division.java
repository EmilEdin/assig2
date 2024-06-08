package org.ioopm.calculator.ast;

public class Division extends Binary {

    public Division(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
    }

    public String getName() {
        return "/";
    }

    public int getPriority() {
        return 100;
    }

    public String toString() {
        if (getLhs().getPriority() < this.getPriority() && getRhs().getPriority() <= this.getPriority()) {
            return "(" + String.valueOf(getLhs()) + ")" + " " + this.getName() + " " +  "(" + String.valueOf(getRhs()) + ")";
        } else if (getLhs().getPriority() < this.getPriority()) {
            return "(" + String.valueOf(getLhs()) + ")" +  " " + this.getName() + " " + String.valueOf(getRhs());
        } else if (getRhs().getPriority() <= this.getPriority()) {
            return String.valueOf(getLhs()) +  " " + this.getName() + " " + "(" + String.valueOf(getRhs()) + ")";
        } else {
            return String.valueOf(getLhs()) +  " " + this.getName() + " " + String.valueOf(getRhs());
        }
    }

    public boolean equals(Object other) {
        if (other instanceof Division) {
            return this.equals((Division) other);
        } else {
            return false;
        }
    }
    public boolean equals(Division other) {
        /// access a private field of other!
        return getLhs().equals(other.getLhs()) && getRhs().equals(other.getRhs());
    }

    public SymbolicExpression eval(Environment vars) throws IllegalAssignment {
        SymbolicExpression leftEvaluated = getLhs().eval(vars);
        SymbolicExpression rightEvaluated = getRhs().eval(vars);

        if (leftEvaluated.isConstant() && rightEvaluated.isConstant()) {
            // Both sides are constants, perform addition
            double lhs = leftEvaluated.getValue() / rightEvaluated.getValue();
            return new Constant(lhs);
        } else {
            // Either side or both are not constants, return a new Addition expression
            return new Division(leftEvaluated, rightEvaluated);
        }
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}