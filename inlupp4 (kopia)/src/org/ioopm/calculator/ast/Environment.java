package org.ioopm.calculator.ast;
import java.util.*;

public class Environment extends HashMap<Variable, SymbolicExpression> {

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Variables: \n");
        
        Set<Variable> vars = new TreeSet<>(this.keySet());
        for (Variable v : vars) {
            sb.append(v.getVariable());
            sb.append(" = ");
            sb.append(this.get(v));
            sb.append("\n ");
        }

        // Remove the trailing comma and space
        if (sb.length() > 0) {
            sb.setLength(sb.length() - 2);
        }

        return sb.toString();
    }
}