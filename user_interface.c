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
    } else if (input_string[0] == 'L' || input_string[0] == 'l' || input_string[0] == 'T' || input_string[0] == 't' || input_string[0] == 'R' || input_string[0] == 'r' || input_string[0] == 'G' || input_string[0] == 'g' || input_string[0] == 'H' || input_string[0] == 'h' || input_string[0] == 'A'|| input_string[0] == 'a') {
        return true;
    } else {
        return false;
    }
}


char ask_question_menu()
{
    print_menu();
    char answer = ask_question("Select an option", check_letter (convert_func), string_to_char).char_value;
    return answer;
}

void event_loop(item_t *db, int db_siz)
{
    bool flag = true;
    while (flag)
    {
        char answer = ask_question_menu();
        if (answer == 'L')
        {
            db_siz = add_item_to_db(db, db_siz);
        }
        else if (answer == 'T')
        {
            db_siz = remove_item_from_db(db, db_siz);
        }
        else if (answer == 'R')
        {
            edit_db(db, db_siz);
        }
        else if (answer == 'H')
        {
            list_db(db, db_siz);
        }
        else if (answer == 'G')
        {
            printf("Not yet implemented!\n");
        }
        else
        {
            flag = false;
        }
    }
}

int main()
{
    event_loop();
}
