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


/// @brief Add a merch
/// @returns returns a merch_t struct
merch_t *input_merch(void);

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

/// @brief Lists the number of merchandise up to 20 and more with input n.
/// @param ht_merch The merch hash_table
void list_merchandise(ioopm_hash_table_t *ht_merch);

/// @brief Destroy the hash table with merch
/// @param ht_merch The merch hash_table
void ioopm_ht_merch_destroy(ioopm_hash_table_t *ht_merch);

/// @brief Removes a merch
/// @param ht_merch The merch hash_table
/// @param ht_stock The ht stock 
/// @param ask_question Give a question
/// @returns returns a boolean
bool remove_merch(ioopm_hash_table_t *ht_merch, ioopm_hash_table_t *ht_stock, char *ask_question_confirm, char *ask_question);

/// @brief edits a merch
/// @param ht_merch The merch hash_table
/// @param ht_stock The ht stock 
/// @param ask_question Give a question
void edit_merchandise(ioopm_hash_table_t *ht_merch ,ioopm_hash_table_t *ht_stock, char *ask_question_confirm, char *item_to_edit, char *new_name, char *new_desc, int new_price);

/// @brief shows stock for merch
/// @param ht_merch The merch hash_table
/// @param ht_stock The ht stock 
/// @param given_merch the given merch to show stock for
void show_stock(ioopm_hash_table_t *ht_merch, char *given_merch);

/// @brief edits a merch
/// @param ht_merch The merch hash_table
/// @param ht_stock The ht stock 
/// @param storage_id the shelf
/// @param given_merch the given merch to show stock for
/// @param items number of items to add
bool replenish(ioopm_hash_table_t *ht_merch ,ioopm_hash_table_t *ht_stock, char *storage_id, char *given_merch, int items);




