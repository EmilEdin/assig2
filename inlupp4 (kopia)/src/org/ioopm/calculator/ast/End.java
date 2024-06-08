package org.ioopm.calculator.ast;


public class End extends Command {

    private static final End theInstance = new End();
    private End() {}
    public static End instance() {
        return theInstance;
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }

}
