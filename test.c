
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

void test_add_merch(void) {
    ioopm_hash_table_t *ht_merch = ioopm_hash_table_create(string_to_int, NULL);

    // Adding a new merch
    merch_t *merch = make_merch(strdup("Fotboll"), strdup("En boll"), 100, ioopm_linked_list_create(NULL));
    bool new_merch = add_merch(ht_merch, merch);
    // Check that it works to insert a new merch into ht_merch
    CU_ASSERT_TRUE(new_merch);
    CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht_merch, ptr_elem("Fotboll")).success);
    
    ioopm_list_t *list_of_merchs = ioopm_hash_table_values(ht_merch);
    CU_ASSERT_TRUE(strcmp(list_of_merchs->first->element.merch->description, "En boll") == 0);
    CU_ASSERT_TRUE(list_of_merchs->first->element.merch->price == 100);
    ioopm_linked_list_destroy(list_of_merchs);
    
    // Trying to add an existing merch
    merch_t *merch_2 = make_merch(strdup("Fotboll"), strdup("Lol"), 5000, ioopm_linked_list_create(NULL));
    bool same_merch_2 = add_merch(ht_merch, merch_2);
    CU_ASSERT_FALSE(same_merch_2);
    
    ioopm_ht_merch_destroy(ht_merch);
}

void test_remove_merch(void) {
  ioopm_hash_table_t *ht_merch = ioopm_hash_table_create(string_to_int, NULL);
  ioopm_hash_table_t *ht_stock = ioopm_hash_table_create(string_to_int, NULL);

  // Add merchs
  merch_t *merch = make_merch(strdup("Fotboll"), strdup("En boll"), 100, ioopm_linked_list_create(NULL));
  merch_t *merch_2 = make_merch(strdup("Klubba"), strdup("Klubba"), 420, ioopm_linked_list_create(NULL));
  add_merch(ht_merch, merch);
  add_merch(ht_merch, merch_2);
  
  // Remove merchs
  bool removed = remove_merch(ht_merch, ht_stock, strdup("y"), strdup("Klubba"));
  bool removed_2 = remove_merch(ht_merch, ht_stock, strdup("y"), strdup("Fotboll"));
  bool removed_3 = remove_merch(ht_merch, ht_stock, strdup("y"), strdup("Fotboll"));
  bool removed_4 = remove_merch(ht_merch, ht_stock, strdup("y"), strdup("Hejsan"));
  CU_ASSERT_TRUE(removed);
  CU_ASSERT_TRUE(removed_2);
  CU_ASSERT_FALSE(removed_3);
  CU_ASSERT_FALSE(removed_4);
  
  ioopm_ht_merch_destroy(ht_merch);
  ioopm_hash_stock_destroy(ht_stock);

}

void test_edit_merch(void) {
  ioopm_hash_table_t *ht_merch = ioopm_hash_table_create(string_to_int, NULL);
  ioopm_hash_table_t *ht_stock = ioopm_hash_table_create(string_to_int, NULL);

  // Add merchs
  merch_t *merch = make_merch(strdup("Fotboll"), strdup("En boll"), 100, ioopm_linked_list_create(NULL));
  merch_t *merch_2 = make_merch(strdup("Klubba"), strdup("Klubba"), 420, ioopm_linked_list_create(NULL));
  merch_t *merch_3 = make_merch(strdup("David"), strdup("Människa"), 1, ioopm_linked_list_create(NULL));
  add_merch(ht_merch, merch);
  add_merch(ht_merch, merch_2);
  add_merch(ht_merch, merch_3);
  
  edit_merchandise(ht_merch, ht_stock, strdup("y"), strdup("Fotboll"), strdup("Kvarg"), strdup("Mat"), 369696);
  bool kvarg_removed = remove_merch(ht_merch, ht_stock, strdup("y"), strdup("Kvarg"));
  bool try_to_remove_prev_name = remove_merch(ht_merch, ht_stock, strdup("y"), strdup("Fotboll"));
  CU_ASSERT_TRUE(kvarg_removed);
  CU_ASSERT_FALSE(try_to_remove_prev_name);

  edit_merchandise(ht_merch, ht_stock, strdup("y"), strdup("David"), strdup("Fot"), strdup("Mat"), 369696);
  
  edit_merchandise(ht_merch, ht_stock, strdup("y"), strdup("Fot"), strdup("Arm"), strdup("Mat"), 369696);
  edit_merchandise(ht_merch, ht_stock, strdup("y"), strdup("Arm"), strdup("Banan"), strdup("Mat"), 369696);
  // Try to add a merch that exists
  
  merch_t *merch_same = make_merch(strdup("Banan"), strdup("Lol"), 5000, ioopm_linked_list_create(NULL));
  bool same_merch = add_merch(ht_merch, merch_same);
  CU_ASSERT_FALSE(same_merch);
  bool banan_removed = remove_merch(ht_merch, ht_stock, strdup("y"), strdup("Banan"));
  CU_ASSERT_TRUE(banan_removed);
  
  
  ioopm_ht_merch_destroy(ht_merch);
  ioopm_hash_stock_destroy(ht_stock);
}

void test_replenish_stock(void) {
  ioopm_hash_table_t *ht_merch = ioopm_hash_table_create(string_to_int, NULL);
  ioopm_hash_table_t *ht_stock = ioopm_hash_table_create(string_to_int, NULL);
  
  CU_ASSERT_EQUAL(show_stock(ht_merch, strdup("Fotboll")), 0);
  // Add merchs
  merch_t *merch = make_merch(strdup("Fotboll"), strdup("En boll"), 100, ioopm_linked_list_create(NULL));
  merch_t *merch_2 = make_merch(strdup("Klubba"), strdup("Klubba"), 420, ioopm_linked_list_create(NULL));
  merch_t *merch_3 = make_merch(strdup("David"), strdup("Människa"), 1, ioopm_linked_list_create(NULL));
  add_merch(ht_merch, merch);
  add_merch(ht_merch, merch_2);
  add_merch(ht_merch, merch_3);



  replenish(ht_merch, ht_stock, strdup("A10"), strdup("Klubba"), 1);
  //replenish(ht_merch, ht_stock, strdup("C16"), strdup("Klubba"), 1);
  //replenish(ht_merch, ht_stock, strdup("P16"), strdup("Klubba"), 1);
  //replenish(ht_merch, ht_stock, strdup("A10"), strdup("Klubba"), 1);
  CU_ASSERT_EQUAL(show_stock(ht_merch, strdup("Klubba")), 4);
  
  /* Här har vi problem, När vi försöker edit_merch på en vara som vi har lagt till i ht_stock med replenish */
  // Så får vi minnesläcka
  edit_merchandise(ht_merch, ht_stock, strdup("y"), strdup("Klubba"), strdup("TV"), strdup("En teve"), 120);


  // Test so if storage id exist but another merch is already there it returns false
  CU_ASSERT_FALSE(replenish(ht_merch, ht_stock, strdup("A10"), strdup("Fotboll"), 2));
  // Test so that the merch exists
  CU_ASSERT_FALSE(replenish(ht_merch, ht_stock, strdup("A10"), strdup("spökdata"), 2));
  CU_ASSERT_FALSE(replenish(ht_merch, ht_stock, strdup("G50"), strdup("spökdataa"), 2));

  // Now edge cases done, regular tests
  
  for (int i = 0; i < 10; i++) {
    bool check = replenish(ht_merch, ht_stock, strdup("B10"), strdup("Fotboll"), 5);
    CU_ASSERT_TRUE(check);
  }
  
  CU_ASSERT_EQUAL(show_stock(ht_merch, strdup("Fotboll")), 50);
  
  replenish(ht_merch, ht_stock, strdup("L5"), strdup("Fotboll"), 5);
  replenish(ht_merch, ht_stock, strdup("L5"), strdup("Fotboll"), 5);
  
  replenish(ht_merch, ht_stock, strdup("A5"), strdup("Fotboll"), 10);
  CU_ASSERT_EQUAL(show_stock(ht_merch, strdup("Fotboll")), 70);
  
  // Test so edit and show stock will show the edited one.
  //edit_merchandise(ht_merch, ht_stock, strdup("y"), strdup("Fotboll"), strdup("TV"), strdup("En teve"), 120);
  // Test so with changed name Fotboll does not exist as merch or have stock
  /*
  CU_ASSERT_EQUAL(show_stock(ht_merch, strdup("Fotboll")), 0);
  // But TV will have the fotboll stocks
  CU_ASSERT_EQUAL(show_stock(ht_merch, strdup("TV")), 70);
  */
  ioopm_ht_merch_destroy(ht_merch);
  ioopm_hash_stock_destroy(ht_stock);

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
    (CU_add_test(my_test_suite, "Test remove_merch", test_remove_merch) == NULL) || 
    (CU_add_test(my_test_suite, "Test edit_merch", test_edit_merch) == NULL) || 
    (CU_add_test(my_test_suite, "Test replenish_and_show_stock", test_replenish_stock) == NULL) || 
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