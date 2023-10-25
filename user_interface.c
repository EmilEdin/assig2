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
    } else if (input_string[0] == 'A' || input_string[0] == 'L' || input_string[0] == 'D') {
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
            remove_merch(ht_merch, ht_stock, ask_question_string("Sure?"), ask_question_string("Which item would you genocidealy destroy?"));
        }
        else if (answer == 'C')
        {
            printf("here");
            flag = false;

        } else {
            flag = false;
        }
    }
}

int main()
{   
    ioopm_hash_table_t *ht_merch = ioopm_hash_table_create(string_to_int, NULL);
    ioopm_hash_table_t *ht_stock = ioopm_hash_table_create(string_to_int, NULL);

    event_loop(ht_merch, ht_stock);
    return 0;
}
