#include "hash_table.h"
#include "linked_list.h"
#include "common.h"
#include "utils.h"
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
    char *+ = "Add To Cart [+]\n";
    char *- = "Remove From Cart [-]\n";
    char *= = "Calculate Cost [=]\n";
    char *O = "Checkout [O]\n";
    char *Q = "Quit [Q]\n";

    printf("%s%s%s%s%s%s%s%s%s%s%s%s%s", A, L, D, E, S, P, C, R, +, -, =, O, Q);
}

char ask_question_menu() {
    print_menu()
    char answer = ask_question("Select an option" check_letter, (convert_func) string_to_char).char_value;
    return answer;
}

void event_loop(item_t *db, int db_siz) {
    bool flag = true;
    while (flag) {
        char answer = ask_question_menu();
        if (answer == 'L') {
            db_siz = add_item_to_db(db, db_siz);
        } else if (answer == 'T') {
            db_siz = remove_item_from_db(db, db_siz);
        } else if (answer == 'R') {
            edit_db(db, db_siz);
        } else if (answer == 'H') {
            list_db(db, db_siz);
        } else if (answer == 'G') {
            printf("Not yet implemented!\n");
        } else {
            flag = false;
        }
    }
}

int main() {
    event_loop();
}
