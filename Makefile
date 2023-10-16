main: hash_test
    valgrind --leak-check=full ./hash_test

C_COMPILER     = gcc
C_OPTIONS      = -Wall -pedantic -g -I /usr/include/CUnit
C_LINK_OPTIONS = -lm  
C_LINK_CUNIT = -lcunit

%.o:  generic_datastructures/%.c
    $(C_COMPILER) $(C_OPTIONS) $^ -c

%.o:  generic_utils/%.c
    $(C_COMPILER) $(C_OPTIONS) $^ -c

%.o:  %.c
    $(C_COMPILER) $(C_OPTIONS) $^ -c

hash_test: test.o business_logic.o hash_table.o linked_list.o utils.o
    $(C_COMPILER) $(C_LINK_OPTIONS) $^ -o $@ $(C_LINK_CUNIT)

hash_test.final: test.o business_logic.o hash_table.o linked_list.o utils.o


clean:
    rm -f *.o hash_test