package org.ioopm.calculator.ast;


public class Addition extends Binary {

    public Addition(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
    }

    public String getName() {
        return "+";
    }

    public int getPriority() {
        return 50;
    }

    public String toString() {
        return String.valueOf(getLhs()) + " " + this.getName() + " " + String.valueOf(getRhs());
    }

    public boolean equals(Object other) {
        if (other instanceof Addition) {
            return this.equals((Addition) other);
        } else {
            return false;
        }
    }
    
    public boolean equals(Addition other) {
        /// access a private field of other!
        return getLhs().equals(other.getLhs()) && getRhs().equals(other.getRhs());
    }

    public SymbolicExpression eval(Environment vars) throws IllegalAssignment {
        SymbolicExpression leftEvaluated = getLhs().eval(vars);
        SymbolicExpression rightEvaluated = getRhs().eval(vars);

        if (leftEvaluated.isConstant() && rightEvaluated.isConstant()) {
            // Both sides are constants, perform addition
            double lhs = leftEvaluated.getValue() + rightEvaluated.getValue();
            return new Constant(lhs);
        } else {
            // Either side or both are not constants, return a new Addition expression
            return new Addition(leftEvaluated, rightEvaluated);
        }
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}
