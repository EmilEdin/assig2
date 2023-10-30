#pragma once
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "generic_datastructures/linked_list.h"
#include "generic_datastructures/hash_table.h"
#include "generic_datastructures/common.h"
#include <stdio.h>

/**
 * @file business_logic.h
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

/// @brief Destroy the stock hash table.
///
/// This function destroys the stock hash table and releases associated resources.
///
/// @param ht_stock The stock hash table to be destroyed.
void ioopm_hash_stock_destroy(ioopm_hash_table_t *ht_stock);

/// @brief Destroy a linked list of merchandise.
///
/// This function destroys a linked list containing merchandise structures and
/// releases associated resources.
///
/// @param list The linked list of merchandise to be destroyed.
void ioopm_linked_merch_destroy(ioopm_list_t *list);

/// @brief Destroy the merchandise hash table.
///
/// This function destroys the merchandise hash table and releases associated resources.
///
/// @param ht_merch The merchandise hash table to be destroyed.
void ioopm_ht_merch_destroy(ioopm_hash_table_t *ht_merch);

/// @brief Destroy the shopping cart hash table.
///
/// This function destroys the shopping cart hash table and releases associated resources.
///
/// @param ht_carts The shopping cart hash table to be destroyed.
void ioopm_hash_table_carts_destroy(ioopm_hash_table_t *ht_carts);

/// @brief Make a merchandise structure.
///
/// This function creates and returns a merchandise structure with the provided information.
///
/// @param name The name of the item.
/// @param description The description of the item.
/// @param price The price of the item.
/// @param list The list structure associated with the merchandise.
/// @return A pointer to the created merchandise structure.
merch_t *make_merch(char *name, char *description, int price, ioopm_list_t *list);

/// @brief Add merchandise to the merchandise hash table.
///
/// This function adds a merchandise structure to the merchandise hash table.
///
/// @param ht_merch The merchandise hash table.
/// @param merch The merchandise structure to be added.
/// @return true if the merchandise was successfully added; false otherwise.
bool ioopm_add_merch(ioopm_hash_table_t *ht_merch, merch_t *merch);

/// @brief Remove merchandise from the system.
///
/// This function removes a merchandise item from the merchandise hash table
/// and updates related data structures.
///
/// @param ht_merch The merchandise hash table.
/// @param ht_stock The stock hash table.
/// @param ht_carts The shopping cart hash table.
/// @param ask_question_confirm Confirmation message.
/// @param ask_question Additional question or information.
/// @return true if the merchandise was successfully removed; false otherwise.
bool ioopm_remove_merch(ioopm_hash_table_t *ht_merch, ioopm_hash_table_t *ht_stock, ioopm_hash_table_t *ht_carts, char *ask_question_confirm, char *ask_question);

/// @brief Edit merchandise details.
///
/// This function allows editing merchandise details, including name, description,
/// and price.
///
/// @param ht_merch The merchandise hash table.
/// @param ht_stock The stock hash table.
/// @param ask_question_confirm Confirmation message.
/// @param item_to_edit The name of the merchandise to edit.
/// @param new_name The new name for the merchandise.
/// @param new_desc The new description for the merchandise.
/// @param new_price The new price for the merchandise.
void ioopm_edit_merchandise(ioopm_hash_table_t *ht_merch, ioopm_hash_table_t *ht_stock, char *ask_question_confirm, char *item_to_edit, char *new_name, char *new_desc, int new_price);

/// @brief Display stock information for merchandise.
///
/// This function displays stock information for a specific merchandise item.
///
/// @param ht_merch The merchandise hash table.
/// @param ht_stock The stock hash table.
/// @param given_merch The merchandise item to show stock for.
/// @return The stock quantity for the given merchandise item.
int ioopm_show_stock(ioopm_hash_table_t *ht_merch, char *given_merch);

/// @brief Replenish merchandise stock.
///
/// This function adds items to the stock of a merchandise item.
///
/// @param ht_merch The merchandise hash table.
/// @param ht_stock The stock hash table.
/// @param storage_id The shelf identifier.
/// @param given_merch The merchandise item to add stock to.
/// @param items The number of items to add to stock.
/// @return true if stock replenishment was successful; false otherwise.
bool ioopm_replenish(ioopm_hash_table_t *ht_merch, ioopm_hash_table_t *ht_stock, char *storage_id, char *given_merch, int items);

/// @brief Create a new shopping cart in the system.
///
/// This function creates a new shopping cart with the given identifier.
///
/// @param ht_carts The shopping cart hash table.
/// @param cart_id The identifier for the new cart.
void ioopm_create_cart(ioopm_hash_table_t *ht_carts, int cart_id);

/// @brief Remove a shopping cart from the system.
///
/// This function removes a shopping cart and its contents from the system.
///
/// @param ht_carts The shopping cart hash table.
/// @param ht_merch The merchandise hash table.
/// @param cart_id The identifier of the cart to remove.
/// @param ask_question_confirm Confirmation message.
/// @return true if the cart was successfully removed; false otherwise.
bool ioopm_remove_cart(ioopm_hash_table_t *ht_carts, ioopm_hash_table_t *ht_merch, int cart_id, char *ask_question_confirm);

/// @brief Add merchandise to a shopping cart.
///
/// This function adds a quantity of merchandise to a specific shopping cart.
///
/// @param ht_merch The merchandise hash table.
/// @param ht_carts The shopping cart hash table.
/// @param cart_id The identifier of the cart to which merchandise is added.
/// @param given_merch The name of the merchandise to add to the cart.
/// @param num_of_items The number of items to add to the cart.
/// @return true if the merchandise was successfully added to the cart; false otherwise.
bool ioopm_add_to_cart(ioopm_hash_table_t *ht_merch, ioopm_hash_table_t *ht_carts, int cart_id, char *given_merch, int num_of_items);

/// @brief Remove merchandise from a shopping cart.
///
/// This function removes zero or more items of a merchandise from a particular cart.
///
/// @param ht_merch The merchandise hash table.
/// @param ht_carts The shopping cart hash table.
/// @param cart_id The identifier of the cart from which merchandise is removed.
/// @param given_merch The name of the merchandise to remove from the cart.
/// @param num_of_items The number of items to remove from the cart.
/// @return true if the merchandise was successfully removed from the cart; false otherwise.
bool ioopm_remove_from_cart(ioopm_hash_table_t *ht_merch, ioopm_hash_table_t *ht_carts, int cart_id, char *given_merch, int num_of_items);

/// @brief Perform the checkout process.
///
/// This function simulates the checkout process for a shopping cart, which includes
/// removing merchandise from the stock and the cart.
///
/// @param ht_merch The merchandise hash table.
/// @param ht_stock The stock hash table.
/// @param ht_carts The shopping cart hash table.
/// @param cart_id The identifier of the cart to checkout.
/// @return true if the checkout was successful; false otherwise.
bool ioopm_checkout(ioopm_hash_table_t *ht_merch, ioopm_hash_table_t *ht_stock, ioopm_hash_table_t *ht_carts, int cart_id);
