
#include <CUnit/Basic.h>
#include "generic_datastructures/common.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "business_logic.h"
#include "generic_datastructures/hash_table.h"
#include "generic_datastructures/linked_list.h"
#include "generic_utils/utils.h"
#include "business_logic.h"




bool string_eq(elem_t arg1, elem_t arg2) {
  return strcmp(arg1.string_value, arg2.string_value);
}

int string_to_int(elem_t str) {
  int counter = 0;
  int value = 0;
  char *st = str.string_value;
  while (st[counter] != '\0') {
    value = value + st[counter];
    counter = counter + 1;
  }
  return value;
}


/*
// Uses the DJB2 algorithm to hash the string
int string_to_int(elem_t str) {
    int hash = 5381;
    unsigned char *ptr = (unsigned char *)str.string_value;

    while (*ptr) {
        hash = ((hash << 5) + hash) + *ptr; // hash * 33 + c
        ptr++;
    }

    return hash;
}
// Adds the ASCII values of each letter
int string_to_int(elem_t str) {
  int counter = 0;
  int value = 0;
  char *st = str.string_value;
  while (st[counter] != '\0') {
    value = value + st[counter];
    counter = counter + 1;
  }
  return value;
}
*/



int init_suite(void) {
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void) {
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

void test_add_merch() {
    ioopm_hash_table_t *ht_merch = ioopm_hash_table_create(string_to_int, NULL);
    ioopm_hash_table_t *ht_stock = ioopm_hash_table_create(string_to_int, NULL);
    // Adding a new merch
    merch_t *merch = make_merch("Fotboll", "En boll", 100, ioopm_linked_list_create(NULL));
    bool new_merch = add_merch(ht_merch, merch);
    CU_ASSERT_TRUE(new_merch);
    /*
    CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht_merch, ptr_elem("Fotboll")).success);
    CU_ASSERT_EQUAL(ioopm_hash_table_values(ht_merch)->first->element.merch->price, 100);
    CU_ASSERT_TRUE(strcmp(ioopm_hash_table_values(ht_merch)->first->element.merch->description, "En boll"));
    // Trying to add an existing merch
    bool same_merch = add_merch(ht_merch, merch);
    CU_ASSERT_FALSE(same_merch);
    merch_t *merch_2 = make_merch("Fotboll", "Lol", 5000, ioopm_linked_list_create(NULL));
    bool same_merch_2 = add_merch(ht_merch, merch_2);
    CU_ASSERT_FALSE(same_merch_2);
    CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht_merch, ptr_elem("Fotboll")).success);
    */
    ioopm_linked_list_destroy(merch->list);
    free(merch);
    ioopm_hash_table_destroy(ht_merch);
    ioopm_hash_table_destroy(ht_stock);
}

int main() {

  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
  if (my_test_suite == NULL) {
      // If the test suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
    (CU_add_test(my_test_suite, "Test add_merch", test_add_merch) == NULL) || 
    0
  )
    {
      // If adding any of the tests fails, we tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
} 