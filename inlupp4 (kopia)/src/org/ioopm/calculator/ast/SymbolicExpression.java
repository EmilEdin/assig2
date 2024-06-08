package org.ioopm.calculator.ast;

public abstract class SymbolicExpression {

    private String name; 
    private String[] subExpressions;
    /// The second argument allows us to pass in 0 or more arguments
    
    public SymbolicExpression(String name, Object... subExpressions) {
        this.name = name;
        this.subExpressions = new String[subExpressions.length];
        for (int i = 0; i < subExpressions.length; ++i) {
            this.subExpressions[i] = subExpressions[i].toString();
        }
    }
    public SymbolicExpression() {}

    public Boolean isConstant() {
        return false;
    }
    
    public Boolean isCommand() {
        return false;
    }

    public double getValue() {
        throw new RuntimeException("getValue() called on expression that is not constant");
    }

    public String getVariable() {
        throw new RuntimeException("getVariable() called on expression that is not a variable");
    }

    public String getName() {
        throw new RuntimeException("getName() called on expression with no operator");
    }

    public int getPriority() {
        return 100;
    }

    public abstract SymbolicExpression eval(Environment vars) throws IllegalAssignment;
    
    /// Returns e.g., "Constant(42)" if name is "Constant" and subExpressions is ["42"]
    public String toString(String msg) {
        StringBuilder sb = new StringBuilder();
        sb.append(this.name);
        sb.append("(");
        for (int i = 1; i < this.subExpressions.length; ++i) {
            sb.append(this.subExpressions[i]);
            if (i + 1 < subExpressions.length) {
                sb.append(", ");
            }
        }
        sb.append(")");
        return sb.toString(); 
    }

    public abstract SymbolicExpression accept(Visitor v);
}