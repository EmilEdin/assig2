#pragma once
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "generic_datastructures/linked_list.h"
#include "generic_datastructures/hash_table.h"
#include "generic_datastructures/common.h"
#include <stdio.h>

/**
 * @file user_interface.h
 * @author Eskil Lundegårdh och Emil Edin
 * @date 16 Okt 2023
 * @brief user interface functions
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @see $CANVAS_OBJECT_REFERENCE$/assignments/gb54499f3b7b264e3af3b68c756090f52
 */

/// @brief Create a new merchandise structure.
/// This function initializes and returns a new merchandise structure.
/// @return A pointer to the newly created merchandise structure.
merch_t *input_merch(void);

/// @brief prints all merch items in the hash table
/// @param ht_carts The hash_table of merch items
void ioopm_list_merchandise(ioopm_hash_table_t *ht_merch);

/// @brief shows total cost of a cart
/// @param ht_carts The carts hash_table
/// @param cart_id The cart id
void calculate_cost(ioopm_hash_table_t *ht_carts, int cart_id);

/// @brief displays a number of options that the user has and lets them pick from them
/// @param ht_merch The hash_table of merch items
/// @param ht_stock The hash_table of items in stock
/// @param ht_carts The hash_table of carts
void event_loop(ioopm_hash_table_t *ht_merch, ioopm_hash_table_t *ht_stock, ioopm_hash_table_t *ht_carts);