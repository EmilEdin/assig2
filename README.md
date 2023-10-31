# assig2

# How to run the program
*make test_logic
    Runs the cunit tests in test.c file through valgrind
*make clean_test

*make assig2
    Runs the webstore backend simulation
*make assig2_v
    Runs the webstore backend simulation through valgrind
*make clean_assig2

/* Line and branch coverage using gcov */
* business_logic.c 99.09% 

 # Brief program documentation
 * The program is divided into four modules, the first one is the datastructures used to store data (generic_datastructures)
 * The second one handles the user data in form of inputs (generic_utils)
 * The third one handles the backend logic for the webstore (business_logic)
 * The fourth part is where the main program is and puts everything into a event loop with user interface functions (user_interface)

 * The program uses three main hash tables called ht_merch, ht_stock and ht_carts
 ht_merch
 * Stores the merchandise when adding merchandise to the store
 * The keys are the names of the merchandises as string type
 * The values are a merch_t struct which consists of various fields (name, desc etc) and a list field which has the element
 value of a shelf_t struct containing two fields, one with the storage id name as a string type and the amount of items stored at
 the storage location
* The key name and the name in the merch_t struct of a merchandise both point to the same memory block
ht_stock
* Stores a merchandise in a storage location
* The keys are the names of the storage id's, format one character followed by two numbers (A12, C45..)
* The values are the names of the merchandise stored in the storage
* The storage id keys in the ht_stock and the shelf_t struct storage ids in the merch_t list point to the same memory block
ht_carts
* Stores carts in a hashtable
* A key is the cart id as an integer type.
* A value is a cart_t struct consisting of two fields, total cost which is the total cost of the merchandise items added to the cart
and another hashtable which stores all of the merchandise added to the cart as key and the corresponding value is the quantity added

1. Hash table comes from Thomas’s Assignment 1
2. Linked list comes from Emil’s Assignment 1
3. Utils comes from Eskil’s C bootstrap labs

