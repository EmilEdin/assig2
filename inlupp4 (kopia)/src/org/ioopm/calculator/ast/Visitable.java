package org.ioopm.calculator.ast;

interface Visitable {

    public double accept(Visitor v);
    
}
