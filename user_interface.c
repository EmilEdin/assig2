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

static char string_to_char(char *str)
{
    return toupper(*str);
}

static void print_menu(void)
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

static bool check_letter(char *input_string)
{
    if (strlen(input_string) > 1)
    {
        return false;
    }
    else if (isdigit(input_string[0]))
    {
        return false;
    }
    else if (input_string[0] == 'A' || input_string[0] == 'L' || input_string[0] == 'D')
    {
        return true;
    }
    else if (input_string[0] == 'E' || input_string[0] == 'S' || input_string[0] == 'P')
    {
        return true;
    }
    else if (input_string[0] == 'C' || input_string[0] == 'R' || input_string[0] == '+')
    {
        return true;
    }
    else if (input_string[0] == '-' || input_string[0] == '=' || input_string[0] == 'O' || input_string[0] == 'Q')
    {
        return true;
    }
    else
    {
        return false;
    }
}

static char ask_question_menu()
{
    print_menu();
    char answer = ask_question("Select an option", check_letter, (convert_func)string_to_char).char_value;
    return answer;
}

merch_t *input_merch(void) {
  char *name = ask_question_string("Name:");
  char *desc = ask_question_string("Description:");
  int price = ask_question_int("Write the price:");

  return make_merch(name, desc, price, ioopm_linked_list_create(NULL));
}

void ioopm_list_merchandise(ioopm_hash_table_t *ht_merch) {
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
            break;
        }
    }
    ioopm_linked_list_destroy(list_of_merchs);
    
}

void calculate_cost(ioopm_hash_table_t *ht_carts, int cart_id)
{
    ioopm_option_t cost = ioopm_hash_table_lookup(ht_carts, int_elem(cart_id));
    if (cost.success == false)
    {
        printf("Cart not found!\n");
    }
    else
    {
        printf("Total cost: %d\n", cost.value.cart->total_cost);
    }
}

void event_loop(ioopm_hash_table_t *ht_merch, ioopm_hash_table_t *ht_stock, ioopm_hash_table_t *ht_carts)
{
    int cart_id = 0;
    bool flag = true;
    while (flag == true)
    {
        char answer = ask_question_menu();
        if (answer == 'A')
        {
            ioopm_add_merch(ht_merch, input_merch());
        }
        else if (answer == 'L')
        {
            ioopm_list_merchandise(ht_merch);
        }
        else if (answer == 'D')
        {
            char *question_remove = ask_question_string("Which item would you genocidealy destroy?");
            char *sure = ask_question_string("Sure?");
            if (ioopm_remove_merch(ht_merch, ht_stock, ht_carts, sure, question_remove) == false)
            {
                printf("Merch removal failed!\n");
            }
        }
        else if (answer == 'E')
        {
            char *question_edit = ask_question_string("Which item would you edit?");

            if (ioopm_hash_table_has_key(ht_merch, ptr_elem(question_edit)) == true)
            {
                char *name_edit = ask_question_string("New name");
                char *desc_edit = ask_question_string("New description");
                int new_price = ask_question_int("New price");
                char *really = ask_question_string("Sure?");
                bool new_name = ioopm_hash_table_has_key(ht_merch, ptr_elem(name_edit));
                if (new_name == false)
                {
                    ioopm_edit_merchandise(ht_merch, ht_stock, really, question_edit, name_edit, desc_edit, new_price);
                }
                else
                {
                    printf("Name already exists!\n");
                    free(question_edit);
                    free(name_edit);
                    free(desc_edit);
                    free(really);
                }
            }
            else
            {
                printf("Name does not exist!\n");
                free(question_edit);
            }
        }
        else if (answer == 'S')
        {
            ioopm_show_stock(ht_merch, ask_question_string("which merch to show stock?"));
        }
        else if (answer == 'P')
        {
            char *shelf = ask_question_shelf("Which shelf?");
            char *merch = ask_question_string("Which merch would u wan increase stock for?");
            int items = ask_question_int("Number of items to add? >1");

            if (items < 1)
            {
                printf("Too few items!");
            }
            else if (ioopm_replenish(ht_merch, ht_stock, shelf, merch, items) == false)
            {
                printf("Error! \n");
            }
            else
            {
            }
        }
        else if (answer == 'C')
        {
            ioopm_create_cart(ht_carts, cart_id);
            cart_id = cart_id + 1;
            printf("Created cart with id: %d\n", cart_id);
            
        }
        else if (answer == 'R')
        {
            char *confirm = ask_question_string("Sure?");
            int id = ask_question_int("Cart id?");
            bool success = ioopm_remove_cart(ht_carts, ht_merch, id, confirm);
            if (success == true)
            {
                cart_id = cart_id - 1;
            }
            else
            {
                printf("Cart does not exist!\n");
            }
        }
        else if (answer == '+')
        {
            int id = ask_question_int("Cart id?");
            char *given_merch = ask_question_string("Which merch to add?");
            int num_items = ask_question_int("Number of items?");
            ioopm_add_to_cart(ht_merch, ht_carts, id, given_merch, num_items);
        }
        else if (answer == '-')
        {
            int id = ask_question_int("Cart id?");
            char *given_merch = ask_question_string("Which merch to add?");
            int num_items = ask_question_int("Number of items?");
            ioopm_remove_from_cart(ht_merch, ht_carts, id, given_merch, num_items);
        }
        else if (answer == '=')
        {
            int id = ask_question_int("Cart id?");
            calculate_cost(ht_carts, id);
        }
        else if (answer == 'O')
        {
            int id = ask_question_int("Cart id?");
            ioopm_checkout(ht_merch, ht_stock, ht_carts, id);
        }
        else if (answer == 'Q')
        {
            flag = false;
            printf("Goodbye, Thank you coming by!\n");
        }
    }
}

int main()
{
    ioopm_hash_table_t *ht_merch = ioopm_hash_table_create(string_to_int, NULL);
    ioopm_hash_table_t *ht_stock = ioopm_hash_table_create(string_to_int, NULL);
    ioopm_hash_table_t *ht_carts = ioopm_hash_table_create(NULL, NULL);

    event_loop(ht_merch, ht_stock, ht_carts);

    ioopm_ht_merch_destroy(ht_merch);
    ioopm_hash_stock_destroy(ht_stock);
    ioopm_hash_table_carts_destroy(ht_carts);

    return 0;
}
