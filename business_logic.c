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


// Destroy ht_stock
/*
static void entry_stock_destroy(entry_t *entry) {
  // Cache the next pointer
    entry_t *next = entry->next;
    free(entry);
  while (next != NULL) {
   
    free(next->value.string_value);
    free(next);
    next = next->next;
  }
}
*/
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
  // TODO 
  for (int i = 0; i < No_Buckets; i++) {
    entry_stock_destroy(ht->buckets[i]);
  }
  free(ht);
}

// Destroy ht_merch
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

static void ioopm_linked_merch_destroy(ioopm_list_t *list) {
    if (list->first == NULL && list->last == NULL) {
        free(list);
    } else {
        merch_links_destroy(list->first);
        free(list);
    }
}

static void merch_linked_destroy(ioopm_hash_table_t *ht_merch) {
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


merch_t *make_merch(char *name, char *description, int price, ioopm_list_t *list) {
  merch_t *merch = calloc(1, sizeof(merch_t));
  merch->name = name;
  merch->description = description;
  merch->price = price;
  merch->list = list;
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


bool remove_merch(ioopm_hash_table_t *ht_merch, ioopm_hash_table_t *ht_stock, char *ask_question_confirm, char *ask_question)
{
    if (ask_question_confirm[0] == 'y' || ask_question_confirm[0] == 'Y') {
        ioopm_option_t t_merch = ioopm_hash_table_remove(ht_merch, ptr_elem(ask_question));

        if ((t_merch.success) == false) {
            free(ask_question);
            free(ask_question_confirm);
            return false;
        } else {
            ioopm_link_t *merch_stock_list = t_merch.value.merch->list->first;
            while (merch_stock_list != NULL) {
                ioopm_hash_table_remove(ht_stock, ptr_elem(merch_stock_list->element.string_value));
                merch_stock_list = merch_stock_list->next;
            }
            ioopm_linked_list_destroy(t_merch.value.merch->list);
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
            ioopm_hash_table_insert(ht_stock, ptr_elem(stock_keys[i]), ptr_elem(name_edit));
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



