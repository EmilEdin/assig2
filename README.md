# assig2


gcc -g -Wall generic_datastructures/hash_table.c generic_datastructures/linked_list.c generic_utils/utils.c  test.c business_logic.c -o hash_test -lcunit


// For trying user interface program game
gcc -g -Wall generic_datastructures/hash_table.c generic_datastructures/linked_list.c generic_utils/utils.c business_logic.c user_interface.c -o assig2

multipass exec primary -- bash            


/* Info om structuren */
Allmänt - Alla inputs av char* från functionerna är strdup eftersom ask_question_string/shelf return strdup
* Add merch skapar så i ht_merch pekar key merch namnet och merch namnet i structen på samma minne
* Ht_stock merch pekar på olika block i minnet och alla values i ht stock skall frigöras separat
* Ht_stock namn och Ht_merch namn är oberoende och pekar INTE på samma block i minnet. 
