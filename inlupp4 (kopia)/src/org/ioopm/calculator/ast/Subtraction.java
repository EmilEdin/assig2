package org.ioopm.calculator.ast;

public class Subtraction extends Binary {

    public Subtraction(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
    }

    public String getName() {
        return "-";
    }

    public int getPriority() {
        return 50;
    }

    public String toString() {
        if (getRhs().getPriority() == this.getPriority()) {
            return String.valueOf(getLhs()) +  " " + this.getName() + " " + "(" + String.valueOf(getRhs()) + ")";
        } else {
            return String.valueOf(getLhs()) +  " " + this.getName() + " " + String.valueOf(getRhs());
        }
    }

    public boolean equals(Object other) {
        if (other instanceof Subtraction) {
            return this.equals((Subtraction) other);
        } else {
            return false;
        }
    }
    public boolean equals(Subtraction other) {
        /// access a private field of other!
        // return this.getName().compareTo(other.getName()) == 0 && getLhs().equals(other) && getRhs().equals(other);
        return getLhs().equals(other.getLhs()) && getRhs().equals(other.getRhs());
    }

    public SymbolicExpression eval(Environment vars) throws IllegalAssignment {
        SymbolicExpression leftEvaluated = this.getLhs().eval(vars);
        SymbolicExpression rightEvaluated = this.getRhs().eval(vars);

        if (leftEvaluated.isConstant() && rightEvaluated.isConstant()) {
            // Both sides are constants, perform addition
            double lhs = leftEvaluated.getValue() - rightEvaluated.getValue();
            return new Constant(lhs);
        } else {
            // Either side or both are not constants, return a new Addition expression
            return new Subtraction(leftEvaluated, rightEvaluated);
        }
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}
