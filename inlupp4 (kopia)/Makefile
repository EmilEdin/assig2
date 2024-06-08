all: classes

classes:
	javac -d classes -sourcepath src src/org/ioopm/calculator/Calculator.java

run: all
	java -cp classes org.ioopm.calculator.Calculator

classes_test:
	javac -d classes -sourcepath src -cp junit-platform-console-standalone-1.8.1.jar src/org/ioopm/calculator/CalculatorTests.java   

test: classes_test
	java -jar junit-platform-console-standalone-1.8.1.jar -cp classes -c org.ioopm.calculator.CalculatorTests

clean:
	rm -rf classes
	rm -rf classes_test

.PHONY: all classes clean run

