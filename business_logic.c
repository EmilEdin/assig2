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


struct merch 
{
    char *name;
    char *description;
    int price;
    ioopm_list_t *list;
};

struct shelf
{
    char *shelf;
    int quantity;
};

merch_t *make_merch(char *name, char *description, int price, ioopm_list_t *list) {
  merch_t merch = { .name = name, .description = description, .price = price, .list = list};
  merch_t *t = &merch;
  return t;
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
        return false;
    }
}
/*
void remove_merch(ioopm_hash_table_t *ht_merch, ioopm_hash_table_t *ht_stock, elem_t key)
{
    ask_question_string("Which item would you genocidealy destroy?");
    if (ask_question_string("Are you sure?") == ('y' || 'Y')) {
        if (ioopm_hash_table_remove(ht_merch, key).success == true && ioopm_hash_table_remove(ht_stock, key).success == true) {
            printf("successfully removed");
        } else {
            printf("Merchandice does not exist");        
        }
    } else {}
}
*/
