C_COMPILER     = gcc
C_OPTIONS      = -Wall -g
C_LINK_OPTIONS = -lm
C_LINK_CUNIT = -lcunit

test_logic: hash_test
	valgrind ./hash_test

hash_test: test.o business_logic.o hash_table.o linked_list.o utils.o
	$(C_COMPILER) $(C_OPTIONS) test.o business_logic.o hash_table.o linked_list.o utils.o -o hash_test $(C_LINK_CUNIT)

assig2: user_interface
	./assig2

assig2_v: user_interface
	valgrind --leak-check=full ./assig2

user_interface: user_interface.o business_logic.o hash_table.o linked_list.o utils.o
	$(C_COMPILER) $(C_OPTIONS) user_interface.o business_logic.o hash_table.o linked_list.o utils.o -o assig2

user_interface.o: user_interface.c 
	$(C_COMPILER) $(C_OPTIONS) -c user_interface.c 

hash_table.o: generic_datastructures/hash_table.c
	$(C_COMPILER) $(C_OPTIONS) -c generic_datastructures/hash_table.c

linked_list.o: generic_datastructures/linked_list.c
	$(C_COMPILER) $(C_OPTIONS) -c generic_datastructures/linked_list.c

utils.o: generic_utils/utils.c
	$(C_COMPILER) $(C_OPTIONS) -c generic_utils/utils.c

test.o: test.c
	$(C_COMPILER) $(C_OPTIONS) -c test.c

business_logic.o: business_logic.c
	$(C_COMPILER) $(C_OPTIONS) -c business_logic.c

clean_test:
	rm test.o business_logic.o hash_table.o linked_list.o utils.o hash_test

clean_assig2:
	rm user_interface.o business_logic.o hash_table.o linked_list.o utils.o assig2

