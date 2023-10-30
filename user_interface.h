#pragma once
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "generic_datastructures/linked_list.h"
#include "generic_datastructures/hash_table.h"
#include "generic_datastructures/common.h"
#include <stdio.h>

/**
 * @file hash_table.h
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


/// @brief Make a merch struct
/// @param input_string the input string
/// @return returns a boolean
bool check_letter(char *input_string);

/// @brief shows total cost of a cart
/// @param ht_carts The carts hash_table
/// @param cart_id The cart id
void calculate_cost(ioopm_hash_table_t *ht_carts, int cart_id);
