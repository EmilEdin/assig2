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
    char *quantity;
};

merch_t *make_merch(char *name, char *description, int price, ioopm_list_t *list) {
  merch_t merch = { .name = name, .description = description, .price = price, .list = list};
  return merch;
}

merch_t *input_merch(void) {
  char *name = ask_question_string("Name:");
  char *desc = ask_question_string("Description:");
  int price = ask_question_int("Write the price:");

  return make_merch(name, desc, price, ioopm_linked_list_create(NULL));
}

void add_merch(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{
    merch_t *merch = input_merch();

    if (ioopm_hash_table_lookup(ht, ptr_elem(merch->name)) == false)
    {
        ioopm_hash_table_insert(ht, ptr_elem(merch->name), merch_elem(merch));
    }
    else
    {
        printf("This merchandice aleady exists");
    }
}

void remove_merch(ioopm_hash_table_t *ht, elem_t key, int stock)
{
    ioopm_hash_table_remove(ht, key);
    stock--;
    return stock;
}
// Sidalol
