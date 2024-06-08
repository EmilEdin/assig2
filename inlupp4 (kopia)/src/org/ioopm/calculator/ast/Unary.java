package org.ioopm.calculator.ast;

public abstract class Unary extends SymbolicExpression {
    private SymbolicExpression primary;

    public Unary(SymbolicExpression primary) {
        this.primary = primary;
    }

    public SymbolicExpression getPrimary() {
        return this.primary;
    }
}
