package org.ioopm.calculator.ast;

public class Multiplication extends Binary {

    public Multiplication(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
    }

    public String getName() {
        return "*";
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
        if (other instanceof Multiplication) {
            return this.equals((Multiplication) other);
        } else {
            return false;
        }
    }
    public boolean equals(Multiplication other) {
        /// access a private field of other!
        return this.getLhs().equals(other.getLhs()) && this.getRhs().equals(other.getRhs());
    }

    public SymbolicExpression eval(Environment vars) throws IllegalAssignment {
        SymbolicExpression leftEvaluated = this.getLhs().eval(vars);
        SymbolicExpression rightEvaluated = this.getRhs().eval(vars);

        if (leftEvaluated.isConstant() && rightEvaluated.isConstant()) {
            // Both sides are constants, perform addition
            double lhs = leftEvaluated.getValue() * rightEvaluated.getValue();
            return new Constant(lhs);
        } else {
            // Either side or both are not constants, return a new Addition expression
            return new Multiplication(leftEvaluated, rightEvaluated);
        }
    }
    
    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }
}

