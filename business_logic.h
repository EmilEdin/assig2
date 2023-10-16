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
 * @brief Business logic for the webbackend.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @see $CANVAS_OBJECT_REFERENCE$/assignments/gb54499f3b7b264e3af3b68c756090f52
 */


/// @brief Make a merch struct
/// @param name Name of the item
/// @param description The description of the item
/// @param price The price of the item
/// @param list The list struct
merch_t *make_merch(char *name, char *description, int price, ioopm_list_t *list);

/// @brief Add a merch
/// @param ht_merch The merch hash_table
/// @param merch The merch struct to be added.
bool add_merch(ioopm_hash_table_t *ht_merch, merch_t *merch);

/// @brief Destroy the hash table with merch
/// @param ht_merch The merch hash_table
void ioopm_ht_merch_destroy(ioopm_hash_table_t *ht_merch);






