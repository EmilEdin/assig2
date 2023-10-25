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

void list_merchandise(ioopm_hash_table_t *ht_merch) {
    ioopm_list_t *list_of_merchs = ioopm_hash_table_keys(ht_merch);
    ioopm_link_t *current = list_of_merchs->first;
    int i = 1;
    while (current != NULL && i <= 20) {
        printf("%d: %s\n", i, current->element.string_value);
        current = current->next;
    }
    while (current != NULL) {
        char *answer = ask_question_string("Continue listing?");
        if (answer[0] == 'N' || answer[0] == 'n') {
            free(answer);
            int i = 0;
            while (current != NULL && i < 20) {
                printf("%d: %s", i, current->element.string_value);
                current = current->next;
            }
        } else {
            free(answer);
        }
    }
    ioopm_linked_list_destroy(list_of_merchs);
    
}

static void merch_linked_destroy(ioopm_hash_table_t *ht_merch) {
    ioopm_list_t *all_merchs = ioopm_hash_table_values(ht_merch);
    ioopm_link_t *t = all_merchs->first;
    while (t != NULL) {
        ioopm_linked_list_destroy(t->element.merch->list);
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


bool remove_merch(ioopm_hash_table_t *ht_merch, ioopm_hash_table_t *ht_stock, char *ask_question_confirm, char *ask_question)
{
    if (ask_question_confirm[0] == 'y' || ask_question_confirm[0] == 'Y') {
        ioopm_option_t t_merch = ioopm_hash_table_remove(ht_merch, ptr_elem(ask_question));
        ioopm_option_t t_stock = ioopm_hash_table_remove(ht_stock, ptr_elem(ask_question));

        if ((t_merch.success) == false && (t_stock.success) == false) {
            free(ask_question);
            free(ask_question_confirm);
            return false;
        } else {
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





