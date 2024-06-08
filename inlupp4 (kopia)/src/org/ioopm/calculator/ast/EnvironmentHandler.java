package org.ioopm.calculator.ast;

import java.util.ArrayDeque;

public class EnvironmentHandler extends Environment{
    private ArrayDeque<Environment> stack = new ArrayDeque<>();

    public EnvironmentHandler() {
        Environmentpush(new Environment());
    }

    @Override
    public SymbolicExpression put(Variable var1, SymbolicExpression var2) {
        Environment thisScope = stack.getFirst();
        return thisScope.put(var1, var2);
   }

    @Override
    public SymbolicExpression get(Object var1) {
        for (Environment scope : stack) {
            SymbolicExpression result = scope.get(var1);
            if (result != null) {
                return result;
            }
         }
        return null;
   }


   public void Environmentpush(Environment E) {
      stack.push(E);
   }

   public Environment Environmentpop() {
      return stack.pop();
   }

   public Environment environmentpeek() {
    return stack.peek();
   }

   // Skriv ut alla scopes och variabler
   public String toString() {
    String tmp = "";
    for (Environment scope : stack) {
        tmp = tmp + scope.toString();
    }
    return tmp;
   }
}
