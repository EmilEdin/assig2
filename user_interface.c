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
#include "business_logic.h"

int string_to_int(elem_t str) {
  return atoi(str.string_value);
}

char string_to_char(char *str) {
    return toupper(*str);
}


void print_menu(void)
{
    char *A = "Add Merchandise [A]\n";
    char *L = "List Merchandise [L]\n";
    char *D = "Remove Merchandise [D]\n";
    char *E = "Edit Merchandise [E]\n";
    char *S = "Show Stock [S]\n";
    char *P = "Replenish [P]\n";
    char *C = "Create Cart [C]\n";
    char *R = "Remove Cart [R]\n";
    char *Ad = "Add To Cart [+]\n";
    char *Su = "Remove From Cart [-]\n";
    char *Ca = "Calculate Cost [=]\n";
    char *O = "Checkout [O]\n";
    char *Q = "Quit [Q]\n";

    printf("%s%s%s%s%s%s%s%s%s%s%s%s%s", A, L, D, E, S, P, C, R, Ad, Su, Ca, O, Q);
}

bool check_letter(char *input_string) {
    if (strlen(input_string) > 1) {
        return false;
    } else if (isdigit(input_string[0])) {
        return false;
    } else if (input_string[0] == 'A' || input_string[0] == 'L' || input_string[0] == 'D' || input_string[0] == 'E' || input_string[0] == 'S' || input_string[0] == 'P' || input_string[0] == 'C' || input_string[0] == 'R' || input_string[0] == 'Q') {
        return true;
    } else {
        return false;
    }
}


char ask_question_menu()
{
    print_menu();
    char answer = ask_question("Select an option", check_letter, (convert_func) string_to_char).char_value;
    return answer;
}


void event_loop(ioopm_hash_table_t *ht_merch, ioopm_hash_table_t *ht_stock)
{
    int cart_id = 0;
    bool flag = true;
    while (flag == true)
    {
        char answer = ask_question_menu();
        if (answer == 'A')
        {
            add_merch(ht_merch, input_merch());
        }
        else if (answer == 'L')
        {
            list_merchandise(ht_merch);
        }
        else if (answer == 'D')
        {
            char *question_remove = ask_question_string("Which item would you genocidealy destroy?");
            char *sure = ask_question_string("Sure?");
            if (remove_merch(ht_merch, ht_stock, sure, question_remove) == false) {
                printf("Merch removal failed!\n");
            }
        }
        else if (answer == 'E')
        {
            char *question_edit = ask_question_string("Which item would you edit?");
            
            if (ioopm_hash_table_has_key(ht_merch, ptr_elem(question_edit)) == true) {
                char *name_edit = ask_question_string("New name");
                char *desc_edit = ask_question_string("New description");
                int new_price = ask_question_int("New price");
                char *really = ask_question_string("Sure?");
                bool new_name = ioopm_hash_table_has_key(ht_merch, ptr_elem(name_edit));
                if (new_name == false) {
                    edit_merchandise(ht_merch, ht_stock, really, question_edit, name_edit, desc_edit, new_price);
                } else {
                    printf("Name already exists!\n");
                }
            } else {
                printf("Name does not exist!\n");
            }
        } else if (answer == 'S') {
            show_stock(ht_merch, ask_question_string("which merch to show stock?"));
        } else if (answer == 'P') {
            char *shelf = ask_question_shelf("Which shelf?");
            char *merch = ask_question_string("Which merch would u wan increase stock for?");
            int items = ask_question_int("Number of items to add? >1");

            if (items < 1) {
                printf("Too few items!");
            } else if (replenish(ht_merch, ht_stock, shelf, merch, items) == false) {
                printf("Error! \n");
            } else {

            }
            
        } else if (answer == 'C') {
            
        } else {
            flag = false;
        }
    }
}

int main()
{   
    ioopm_hash_table_t *ht_merch = ioopm_hash_table_create(string_to_int, NULL);
    ioopm_hash_table_t *ht_stock = ioopm_hash_table_create(string_to_int, NULL);
    ioopm_hash_table_t *ht_carts = ioopm_hash_table_create(NULL, NULL);

    event_loop(ht_merch, ht_stock);

    ioopm_ht_merch_destroy(ht_merch);
    ioopm_hash_stock_destroy(ht_stock);
    hash_table_carts_destroy(ht_carts);

    return 0;
}
