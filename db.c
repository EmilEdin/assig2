#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

struct item
{
  char *Name;
  char *Desc;
  int Price;
  char *Shelf;
};

typedef struct item item_t;

void print_item(item_t *a) {
  int pric = a->Price;
  // ge mig punkten som a pekar på och hämta ut fältet Name
  printf("Name: %s\nDesc: %s\nPrice: %d.%d\nShelf: %s\n", a->Name, a->Desc, pric/100, pric % 100, a->Shelf);
}

item_t make_item(char *n, char *d, int p, char *s) {
  item_t t = { .Name = n, .Desc = d, .Price = p, .Shelf = s};
  return t;
}

bool is_shelf(char *str) {
    int length = strlen(str);
    if (length == 1) {
        return false;
    }
    if (isalpha(str[0])) {
        for(int i = 1; i < length; i++) {
            if (isdigit(str[i])) {
            }
            else {
                return false;
            }
        }
    return true;
   
    }
return false; 
}

char *ask_question_shelf(char *question) {
  return ask_question(question, is_shelf, (convert_func) strdup).string_value;
}

item_t input_item(void) {
  char *Name = ask_question_string("Name:");
  int Price = ask_question_int("Write the price:");
  char *Desc = ask_question_string("Description:");
  char *Shelf = ask_question_shelf("Write shelf:");
  return make_item(Name, Desc, Price, Shelf);
}

char *magick(char *arr1[], char *arr2[], char *arr3[], int arr_length) {
  char buf[255];
  int i = 0;
  int j = 0;
  int p = 0;
  char *arr_1 = arr1[rand()% arr_length];
  for (; i < strlen(arr_1); i++) {
    buf[i] = arr_1[i];
  }
  buf[i] = '-';
  i = i + 1;
  char *arr_2 = arr2[rand()% arr_length];
  for (; j < strlen(arr_2); j++, i++) {
    buf[i] = arr_2[j];
  }
  buf[i] = 32;
  i = i + 1;
  char *arr_3 = arr3[rand()% arr_length];
  for (; p < strlen(arr_3); p++, i++) {
    buf[i] = arr_3[p];
  }
  buf[i] = '\0';
  return strdup(buf);
}

void list_db(item_t *items, int no_items) {
  item_t *t = items;
  int j = 0;
  for (int i = 1; i <= no_items; i++, j++) {
    item_t a = t[j];
    printf("%d: %s\n", i, a.Name);
  }
}

void edit_db(item_t *items, int db_siz) {
  bool flag = true;
  while (flag) {
  int tal = ask_question_int("Skriv tal:");
  tal = tal - 1;
    // Tror det är db_siz -1 men oklart!
    if (0 < tal && tal < db_siz - 1) {
      flag = false;
    } else {}
  print_item(&items[tal]);
  item_t new = input_item();
  items[tal] = new;
  }
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

char string_to_char(char *str) {
    return toupper(*str);
}

char ask_question_menu() {
    char *print_menu = "[L]ägga till en vara\n[T]a bort en vara\n[R]edigera en vara\nÅn[g]ra senaste ändringen\nLista [h]ela varukatalogen\n[A]vsluta\n";
    char answer = ask_question(print_menu, check_letter, (convert_func) string_to_char).char_value;
    return answer;
}

int add_item_to_db(item_t *db, int db_siz) {
    item_t new = input_item();
    db[db_siz] = new;
    db_siz = db_siz + 1;
    return db_siz;
}

int remove_item_from_db(item_t *db, int db_siz) {
    list_db(db, db_siz);
    bool flag = true;
    while (flag) {
        int tal = ask_question_int("Skriv tal:");
        tal = tal - 1;
        if (tal > 0 && tal < db_siz) {
            for (int i = tal; i < db_siz; i++) {
                db[i] = db[i + 1];
            }
            db_siz = db_siz - 1;
            flag = false;
            return db_siz;
        } else {
        }
    }
    return db_siz;
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

int main(int argc, char *argv[])
{
  char *array1[] = { "Laser",        "Polka",    "Extra" };
  char *array2[] = { "förnicklad",   "smakande", "ordinär" };
  char *array3[] = { "skruvdragare", "kola",     "uppgift" };

  if (argc < 2)
  {
    printf("Usage: %s number\n", argv[0]);
  }
  else
  {
    item_t db[20]; // Array med plats för 16 varor
    int db_siz = 0; // Antalet varor i arrayen just nu

    int items = atoi(argv[1]); // Antalet varor som skall skapas

    if (items > 0 && items <= 16)
    {
      for (int i = 0; i < items; ++i)
      {
        // Läs in en vara, lägg till den i arrayen, öka storleksräknaren
        item_t item = input_item();
        db[db_siz] = item;
        ++db_siz;
      }
    }
    else
    {
      puts("Sorry, must have [1-16] items in database.");
      return 1; // Avslutar programmet!
    }

    for (int i = db_siz; i < 16; ++i)
      {
        char *name = magick(array1, array2, array3, 3); // TODO: Lägg till storlek
        char *desc = magick(array1, array2, array3, 3); // TODO: Lägg till storlek
        int price = random() % 200000;
        char shelf[] = { random() % ('Z'-'A') + 'A',
                         random() % 10 + '0',
                         random() % 10 + '0',
                         '\0' };
        item_t item = make_item(name, desc, price, shelf);

        db[db_siz] = item;
        ++db_siz;
      }

     // Skriv ut innehållet
    event_loop(db, db_siz);
  }
  return 0;
}