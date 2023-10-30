#include "generic_datastructures/hash_table.h"
#include "generic_datastructures/linked_list.h"
#include "generic_datastructures/common.h"
#include "generic_utils/utils.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


static void entry_stock_destroy(entry_t *entry) {
    entry_t *current = entry;
    while (current != NULL) {
        entry_t *next = current->next;
        if (current->value.string_value != NULL) {
            free(current->value.string_value);
        }
        free(current);
        current = next;
    }
}

void ioopm_hash_stock_destroy(ioopm_hash_table_t *ht) {
  for (int i = 0; i < No_Buckets; i++) {
    entry_stock_destroy(ht->buckets[i]);
  }
  free(ht);
}

static void merch_links_destroy(ioopm_link_t *link) {
  // Cache the next pointer
  ioopm_link_t *next = link->next;
  free(link->element.shelf->shelf);
  free(link->element.shelf);
  free(link);
  if (next != NULL) {
    merch_links_destroy(next);
  }
}

void ioopm_linked_merch_destroy(ioopm_list_t *list) {
    if (list->first == NULL && list->last == NULL) {
        free(list);
    } else {
        merch_links_destroy(list->first);
        free(list);
    }
}

void merch_linked_destroy(ioopm_hash_table_t *ht_merch) {
    ioopm_list_t *all_merchs = ioopm_hash_table_values(ht_merch);
    ioopm_link_t *t = all_merchs->first;
    while (t != NULL) {
        ioopm_linked_merch_destroy(t->element.merch->list);
        free(t->element.merch->name);
        free(t->element.merch->description);
        free(t->element.merch);
        t = t->next;
    }
    ioopm_linked_list_destroy(all_merchs);
}

void ioopm_ht_merch_destroy(ioopm_hash_table_t *ht_merch) {
    merch_linked_destroy(ht_merch);
    ioopm_hash_table_destroy(ht_merch);
} 

void hash_table_carts_destroy(ioopm_hash_table_t *ht_carts) {
  ioopm_list_t *values = ioopm_hash_table_values(ht_carts);
  ioopm_link_t *cart_ts = values->first;
  while (cart_ts != NULL) {
    ioopm_hash_table_t *ht_cart_items = cart_ts->element.cart->ht_cart_items;
    ioopm_list_t *merch_keys = ioopm_hash_table_keys(ht_cart_items);
    ioopm_link_t *key = merch_keys->first;

    while (key != NULL) {
      free(key->element.string_value);
      key = key->next;
    }
    ioopm_linked_list_destroy(merch_keys);
    ioopm_hash_table_destroy(ht_cart_items);
    cart_t *current_cart_ts = cart_ts->element.cart;
    cart_ts = cart_ts->next;
    free(current_cart_ts);
  }
  ioopm_linked_list_destroy(values);
  ioopm_hash_table_destroy(ht_carts);
}

merch_t *make_merch(char *name, char *description, int price, ioopm_list_t *list) {
  merch_t *merch = calloc(1, sizeof(merch_t));
  merch->name = name;
  merch->description = description;
  merch->price = price;
  merch->list = list;
  merch->items_tracker = 0; // Keep track of items used for carts.
  return merch;
}

merch_t *input_merch(void) {
  char *name = ask_question_string("Name:");
  char *desc = ask_question_string("Description:");
  int price = ask_question_int("Write the price:");

  return make_merch(name, desc, price, ioopm_linked_list_create(NULL));
}

bool add_merch(ioopm_hash_table_t *ht_merch, merch_t *merch)
{

    if (ioopm_hash_table_lookup(ht_merch, ptr_elem(merch->name)).success == false)
    {
        ioopm_hash_table_insert(ht_merch, ptr_elem(merch->name), merch_elem(merch));
        return true;
    }
    else
    {
        // If merch already exists, free the input strings and return false
        free(merch->name);
        free(merch->description);
        ioopm_linked_list_destroy(merch->list);
        free(merch);
        return false;
    }
}
// Should be in interface
void list_merchandise(ioopm_hash_table_t *ht_merch) {
    ioopm_list_t *list_of_merchs = ioopm_hash_table_keys(ht_merch);
    ioopm_link_t *current = list_of_merchs->first;
    int i = 1;
    while (current != NULL && i <= 20) {
        printf("%d: %s\n", i, current->element.string_value);
        current = current->next;
        i = i + 1;
    }
    while (current != NULL) {
        char *answer = ask_question_string("Continue listing?");
        if (answer[0] == 'N' || answer[0] == 'n') {
            free(answer);
            int i = 0;
            while (current != NULL && i < 20) {
                printf("%d: %s\n", i, current->element.string_value);
                current = current->next;
            }
        } else {
            free(answer);
        }
    }
    ioopm_linked_list_destroy(list_of_merchs);
    
}


bool remove_merch(ioopm_hash_table_t *ht_merch, ioopm_hash_table_t *ht_stock, ioopm_hash_table_t *ht_carts, char *ask_question_confirm, char *ask_question)
{
    ioopm_list_t *carts = ioopm_hash_table_values(ht_carts);
    ioopm_link_t *cart = carts->first;
    while (cart != NULL) {
        ioopm_list_t *cart_merchs = ioopm_hash_table_keys(cart->element.cart->ht_cart_items);
        ioopm_link_t *cart_m = cart_merchs->first;
        while (cart_m != NULL) {
            if (strcmp(ask_question, cart_m->element.string_value) == 0) {
                printf("Trying to remove a merch which a shopping cart has, Error!\n");
                free(ask_question_confirm);
                free(ask_question);
                ioopm_linked_list_destroy(carts);
                ioopm_linked_list_destroy(cart_merchs);

                return false;
            }
        }
        ioopm_linked_list_destroy(cart_merchs);
    }
    ioopm_linked_list_destroy(carts);
    
    if (ask_question_confirm[0] == 'y' || ask_question_confirm[0] == 'Y') {
        ioopm_option_t t_merch = ioopm_hash_table_remove(ht_merch, ptr_elem(ask_question));

        if ((t_merch.success) == false) {
            free(ask_question);
            free(ask_question_confirm);
            return false;
        } else {
            ioopm_link_t *merch_stock_list = t_merch.value.merch->list->first;
            while (merch_stock_list != NULL) {
                // När man tar bort ett ht_stock entry måste man frigöra namnet merch då det är independent pekare på minnet
                // Medan shelf i ht_stock och i ht_merch delar samma minne så då behöver vi inte nu frigöra
                ioopm_option_t t = ioopm_hash_table_remove(ht_stock, ptr_elem(merch_stock_list->element.shelf->shelf));
                assert(t.success == true);
                free(t.value.string_value);
                merch_stock_list = merch_stock_list->next;
            }
            // Här frigörs även shelf från ht_stock då både det och i ht_merch shelf delar på samma minne
            ioopm_linked_merch_destroy(t_merch.value.merch->list);
            free(t_merch.value.merch->name);
            free(t_merch.value.merch->description);
            free(t_merch.value.merch);
            
            free(ask_question);
            free(ask_question_confirm);
            return true;
        }
    } else {
        free(ask_question);
        free(ask_question_confirm);
        return false;
    }
}

void edit_merchandise(ioopm_hash_table_t *ht_merch ,ioopm_hash_table_t *ht_stock, char *ask_question_confirm, char *question_edit, char *name_edit, char *desc_edit, int new_price) {
    // We presupose that the given merch does exist and the new name does not already exist in ht
    if (ask_question_confirm[0] == 'y' || ask_question_confirm[0] == 'Y') {
        // Here we use remove, free the name and desc and reinsert the merch with new name etc
        ioopm_option_t merch_edit = ioopm_hash_table_remove(ht_merch, ptr_elem(question_edit));
        
        // Before changing name and desc, free the original name and desc
        free(merch_edit.value.merch->name);
        free(merch_edit.value.merch->description);

        merch_edit.value.merch->name = name_edit;
        merch_edit.value.merch->description = desc_edit;
        merch_edit.value.merch->price = new_price;
        ioopm_hash_table_insert(ht_merch, ptr_elem(name_edit), merch_elem(merch_edit.value.merch));
        
        // Put all the shelf_t stocks from list into the key_stocks char ** to find it in ht_stock
        ioopm_list_t *merch_list = merch_edit.value.merch->list;
        char **stock_keys = calloc(1, sizeof(char *) * ioopm_linked_list_size(merch_list));
        int counter = 0;
        ioopm_link_t *merch_link = merch_list->first;
        // Get all stocks from merch linked_list to stock_keys string array
        while (merch_link != NULL) {
            stock_keys[counter] = merch_link->element.shelf->shelf;
            counter = counter + 1;
            merch_link = merch_link->next;
        }
        // Now update the new name for every stock the merch is in
        for (int i = 0; i < counter; i++) {
            // But first we need to free the previous value name, and in our structure our value names in ht stock
            // All points to different memory, so we need to keep that promise and for each storage we need to strdup name.
            ioopm_option_t t = ioopm_hash_table_lookup(ht_stock, ptr_elem(stock_keys[i]));
            assert(t.success == true);
            free(t.value.string_value);
            char *same_name_but_different_memory_block = strdup(name_edit);
            ioopm_hash_table_insert(ht_stock, ptr_elem(stock_keys[i]), ptr_elem(same_name_but_different_memory_block));
        }
        free(stock_keys);
        free(ask_question_confirm);
        free(question_edit);
        

    } else {
        free(ask_question_confirm);
        free(question_edit);
        free(name_edit);
        free(desc_edit);
    }
}

int show_stock(ioopm_hash_table_t *ht_merch, char *given_merch) {
    ioopm_option_t merch = ioopm_hash_table_lookup(ht_merch, ptr_elem(given_merch));
    int counter = 0;
    if (merch.success == false) {
        printf("Error\n");
    } else {
        ioopm_link_t *merch_shelf = merch.value.merch->list->first;
        while (merch_shelf != NULL) {
            char *shelf = merch_shelf->element.shelf->shelf;
            int quantity = merch_shelf->element.shelf->quantity;
            counter = counter + quantity;
            printf("Shelf: %s, Quantity: %d\n", shelf, quantity);
            merch_shelf = merch_shelf->next;
        }
    }
    free(given_merch);
    return counter;
}

bool replenish(ioopm_hash_table_t *ht_merch, ioopm_hash_table_t *ht_stock, char *storage_id, char *given_merch, int items) {
    ioopm_option_t shelf = ioopm_hash_table_lookup(ht_stock, ptr_elem(storage_id));
    if (shelf.success == true) {
        if (strcmp(shelf.value.string_value, given_merch) == 0) {
            ioopm_option_t merch = ioopm_hash_table_lookup(ht_merch, ptr_elem(given_merch));
            
            ioopm_link_t *merch_list = merch.value.merch->list->first;
            while (merch_list != NULL) {
                if (strcmp(merch_list->element.shelf->shelf, storage_id) == 0) {
                    merch_list->element.shelf->quantity = merch_list->element.shelf->quantity + items;
                    // Add the struct for carts to
                    merch.value.merch->items_tracker = merch.value.merch->items_tracker + items;
                    
                    // Free storage id
                    free(storage_id);
                    free(given_merch);
                    return true;
                }
                merch_list = merch_list->next;
            }
        free(storage_id);
        free(given_merch);
            
        } else {
            free(given_merch);
            free(storage_id);
            return false;
        } 
    } else {
        ioopm_option_t merch_2 = ioopm_hash_table_lookup(ht_merch, ptr_elem(given_merch));
        

        if (merch_2.success == true) {
    
            
            ioopm_hash_table_insert(ht_stock, ptr_elem(storage_id), ptr_elem(given_merch));
            
            ioopm_list_t *merch_list_2 = merch_2.value.merch->list;
                   
            // Nu har vi hittat slutet på listan, lägg till ny shelf
            shelf_t *new_shelf = calloc(1, sizeof(shelf_t));
            new_shelf->quantity = items;
            new_shelf->shelf = storage_id;
            ioopm_linked_list_append(merch_list_2, shelf_elem(new_shelf));
            
            // Add items to cart struct too
            merch_2.value.merch->items_tracker = merch_2.value.merch->items_tracker + items;
            
            return true;

        } else {
            free(given_merch);
            free(storage_id);
            return false;
        }

    }
    free(given_merch);
    free(storage_id);
    return false;
}

static int string_to_int(elem_t str) {
  int counter = 0;
  int value = 0;
  char *st = str.string_value;
  while (st[counter] != '\0') {
    value = value + st[counter];
    counter = counter + 1;
  }
  return value;
}

void create_cart(ioopm_hash_table_t *ht_carts, int cart_id) {
    cart_t  *cart = calloc(1, sizeof(cart_t));
    cart->ht_cart_items = ioopm_hash_table_create(string_to_int, NULL);
    cart->total_cost = 0;
    ioopm_hash_table_insert(ht_carts, int_elem(cart_id), cart_elem(cart));
}

void remove_cart(ioopm_hash_table_t *ht_carts, ioopm_hash_table_t *ht_merch, int cart_id, char *ask_question_confirm) {
    if (ask_question_confirm[0] == 'y' || ask_question_confirm[0] == 'Y') {
        ioopm_option_t value_to_remove = ioopm_hash_table_remove(ht_carts, int_elem(cart_id));
        cart_t *cart_to_remove = value_to_remove.value.cart;
        ioopm_list_t *merch_list = ioopm_hash_table_keys(cart_to_remove->ht_cart_items);
        for(int i = 0; i < ioopm_linked_list_size(merch_list); i++) {
            ioopm_option_t option_to_restore = ioopm_hash_table_lookup(ht_merch, ioopm_linked_list_get(merch_list, i));
            merch_t *merch_to_restore = option_to_restore.value.merch;
            ioopm_option_t lookup_result = ioopm_hash_table_lookup(cart_to_remove->ht_cart_items, ptr_elem(merch_to_restore->name));
            merch_to_restore->items_tracker = merch_to_restore->items_tracker + lookup_result.value.int_value;
            
        }
        ioopm_link_t *merch_link = merch_list->first;
        while (merch_link != NULL) {
            free(merch_link->element.string_value);
            merch_link = merch_link->next;
        }
        ioopm_linked_list_destroy(merch_list);
        ioopm_hash_table_destroy(cart_to_remove->ht_cart_items);
        free(cart_to_remove);
        free(ask_question_confirm);
    }
    else {
        free(ask_question_confirm);
    }
}

bool add_to_cart(ioopm_hash_table_t *ht_merch, ioopm_hash_table_t *ht_carts, int cart_id, char *given_merch, int num_of_items) {
    ioopm_option_t merch = ioopm_hash_table_lookup(ht_merch, ptr_elem(given_merch));
    ioopm_option_t cart = ioopm_hash_table_lookup(ht_carts, int_elem(cart_id));
    
    if (cart.success == false) {
        printf("Cart does not exist!\n");
        free(given_merch);
        return false;
    } 
    if (merch.success == false) {
        printf("Merch does not exist!\n");
        free(given_merch);
        return false;
    }  
    
    int merch_stock = merch.value.merch->items_tracker;
    if (merch_stock < num_of_items) {
        printf("Not enough items to add to cart!\n");
        free(given_merch);
        return false;
    }

    ioopm_hash_table_t *cart_varukorg = cart.value.cart->ht_cart_items;
    
    ioopm_option_t varukorg = ioopm_hash_table_lookup(cart_varukorg, ptr_elem(given_merch));
    if (varukorg.success == false) {
        // First time insert of that given merch
        ioopm_hash_table_insert(cart_varukorg, ptr_elem(given_merch), int_elem(num_of_items));
        merch.value.merch->items_tracker = merch.value.merch->items_tracker - num_of_items;

        // Add the total cost
        cart.value.cart->total_cost = cart.value.cart->total_cost + num_of_items * merch.value.merch->price;

        return true;  
    } else {
        merch.value.merch->items_tracker = merch.value.merch->items_tracker - num_of_items;
        num_of_items = num_of_items + varukorg.value.int_value;
        // Second time, we need to first free the strdup given merch in prev instance before we insert again
        // Since given merch is key, we need to remove the entry first and reinsert
        ioopm_list_t *list_of_keys = ioopm_hash_table_keys(cart_varukorg);
        // Remove it then after we insert it again. Necessary in order to free the key of prev given_merch
        ioopm_hash_table_remove(cart_varukorg, ptr_elem(given_merch));
        ioopm_link_t *link_keys = list_of_keys->first;
        while (link_keys != NULL) {
            if (strcmp(link_keys->element.string_value, given_merch) == 0) {
                free(link_keys->element.string_value);
                break;
            }
            link_keys = link_keys->next;
        }
        ioopm_linked_list_destroy(list_of_keys);
        // Add the total cost
        cart.value.cart->total_cost = cart.value.cart->total_cost + num_of_items * merch.value.merch->price;

        ioopm_hash_table_insert(cart_varukorg, ptr_elem(given_merch), int_elem(num_of_items));
        return true;   
    }
}

bool remove_from_cart(ioopm_hash_table_t *ht_merch, ioopm_hash_table_t *ht_carts, int cart_id, char *given_merch, int num_of_items) {
    ioopm_option_t the_cart = ioopm_hash_table_lookup(ht_carts, int_elem(cart_id));
    if (the_cart.success == false) {
        printf("Cart not found!\n");
        free(given_merch);
        return false;
    }
    ioopm_hash_table_t *varukorg = the_cart.value.cart->ht_cart_items;
    ioopm_option_t the_merch = ioopm_hash_table_lookup(varukorg, ptr_elem(given_merch));
    if (the_merch.success == false) {
        printf("Given merch not found in cart\n");
        free(given_merch);
        return false;
    }
    if (num_of_items > the_merch.value.int_value) {
        printf("You try to remove too much items\n");
        free(given_merch);
        return false;
    }
    ioopm_option_t merch_t = ioopm_hash_table_lookup(ht_merch, ptr_elem(given_merch));
    if (merch_t.success == false) {
        printf("Merch does not exist ht_merch\n");
        free(given_merch);
        return false;
    }
    // Decreasee in the varukorg quantity by num of items to remove
    the_merch.value.int_value = the_merch.value.int_value - num_of_items;
    // Increase in the merch_t struct the number of items in stock
    merch_t.value.merch->items_tracker =  merch_t.value.merch->items_tracker + num_of_items;

    // Add the total cost
    the_cart.value.cart->total_cost = the_cart.value.cart->total_cost + num_of_items * merch_t.value.merch->price;
    free(given_merch);
    return true;
}

bool checkout(ioopm_hash_table_t *ht_merch, ioopm_hash_table_t *ht_stock, ioopm_hash_table_t *ht_carts, int cart_id) {
    ioopm_option_t cart = ioopm_hash_table_lookup(ht_carts, int_elem(cart_id));
    if (cart.success == false) {
        printf("cart does not exist");
        return false;
    }
    
    ioopm_list_t *list_of_merchs = ioopm_hash_table_keys(cart.value.cart->ht_cart_items);
    ioopm_link_t *link_merchs = list_of_merchs->first;
    while (link_merchs != NULL) {
        ioopm_option_t merch_lookup = ioopm_hash_table_lookup(ht_merch, ptr_elem(link_merchs->element.string_value));
        ioopm_option_t quantity_lookup = ioopm_hash_table_lookup(cart.value.cart->ht_cart_items, ptr_elem(link_merchs->element.string_value));
        // Remove merch items from htstock and htmerch
 
        int index_in_list = 0;
        ioopm_list_t *list_of_shelf = merch_lookup.value.merch->list;
        ioopm_link_t *the_merch_shelfs = list_of_shelf->first;
        while (quantity_lookup.value.int_value > 0 && the_merch_shelfs != NULL) {
            if (quantity_lookup.value.int_value >= the_merch_shelfs->element.shelf->quantity) {
                // We cache the quantity value, make the_merch_shelfs to point to next, then remove current shelf.
                int the_merch_shelf_quantity = the_merch_shelfs->element.shelf->quantity;
                the_merch_shelfs = the_merch_shelfs->next;
                shelf_t *shelf = ioopm_linked_list_remove(list_of_shelf, index_in_list).shelf;
                index_in_list = index_in_list + 1;
                // Here we need to remove it from ht_stock
                ioopm_option_t merch = ioopm_hash_table_remove(ht_stock, ptr_elem(shelf->shelf));
                free(merch.value.string_value);
                free(shelf->shelf);
                free(shelf);
                // Decrease the total quantity by the specific shelf quantity
                quantity_lookup.value.int_value = quantity_lookup.value.int_value - the_merch_shelf_quantity;
                
            } else {
                the_merch_shelfs->element.shelf->quantity = the_merch_shelfs->element.shelf->quantity - quantity_lookup.value.int_value;
                
                // Decrease the total quantity by the specific shelf quantity
                quantity_lookup.value.int_value = quantity_lookup.value.int_value - the_merch_shelfs->element.shelf->quantity;
                the_merch_shelfs = the_merch_shelfs->next;
            }
        }
        link_merchs = link_merchs->next;
        
    }
    ioopm_linked_list_destroy(list_of_merchs);
    remove_cart(ht_carts, ht_merch, cart_id, strdup("y"));
    return true;
}



