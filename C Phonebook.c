// Project: C phonebook
// Fantastic 5
// lee Zi Hui
// AI190244
// Last modified: 6/12/20 @ 6:36 PM

#include <stdio.h>
#include <stdlib.h> // system() , exit()
#include <conio.h> // getch()
#include <string.h> // strcmp() , stricmp()
#include <windows.h>

/* Defining the properties of the fields used in the program */
#define FSTNAME 20
#define LSTNAME 20
#define PHONE_NO 11

/* For colour */
void color(short x) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x); // windows.h
}

/* Functions */
void menu(); // main menu
void addrecord(); // add contact
void display(); // show all contacts
void deleterecord(); // delete a single contact by name
void deleteall(); // delete all contacts
void sort(); // sort by first name alphabetically
int searchByName(); // search by first name and last name
void show(char *FirstName, char *LastName, char *PhoneNumber); // display the contact details after searching
int searchByPhoneNumber(); // search by entering phone number 
void searchSelection(); // choose between 1 (search by name) or 2 (search by phone no)
int countContacts(); // a.k.a countNodes() , counts total number of contacts in the list
void ClearScreen(); // clear screen

/* Create a linked list node structure */
struct Contact_Info {
 char FirstName[FSTNAME]; // data
 char LastName[LSTNAME]; // data
 char PhoneNumber[PHONE_NO]; // data
 struct Contact_Info * next; // address
}*head, *tail;

int main() {
	menu();
	return 0;
}

/*
 * Create a list of n contacts (nodes)
 */
void addrecord() {
  // create new contact (node)
  struct Contact_Info *newContact = (struct Contact_Info*) malloc(sizeof(struct Contact_Info));
  	
  // input data of node from the user
  printf("\n\t\t-----------------------------------------\n\t\t\t\tNew Contact\n\t\t-----------------------------------------\n");
  printf("\n\t\tEnter first name: ");
  fgets(newContact->FirstName, FSTNAME, stdin); // FSTNAME = 20
  newContact->FirstName[strlen(newContact->FirstName) - 1] = 0; // printf("%d", newContact->name[strlen(newContact->name) - 1]);
  printf("\n\t\tEnter last name: ");
  fgets(newContact->LastName, LSTNAME, stdin); // LSTNAME = 20
  newContact->LastName[strlen(newContact-> LastName) - 1] = 0;
  printf("\n\t\tEnter phone no.: ");
  fgets(newContact->PhoneNumber, PHONE_NO, stdin); // PHONE_NO = 11
  printf("\n\t\t-----------------------------------------\n");
  newContact->PhoneNumber[strlen(newContact->PhoneNumber) - 1] = 0;

  newContact->next = NULL; // link address field to NULL

  // if the list is empty
  if (head == NULL) {
    printf("\nCreating your first contact...\n");
    head = newContact;
    tail = newContact;
  } else {
    tail->next = newContact; // link previous node with newContact
    tail = newContact;
  }
  printf("\nContact added to PhoneBook successfully.\n");

  printf("\n Press any key");
  getch(); // get input from user's keyboard
  ClearScreen(); // clear screen
}

/*
 * Display entire list
 */
void display() {
  struct Contact_Info *temp = head;
  int x = 0;

  // return if the list is empty
  if (head == NULL) {
    printf("\nSorry, your PhoneBook is empty.\nAdd new contact by choosing 1.\a\n");
    return;
  }

  temp = head;
  
  while (temp != NULL) {
    printf("\n\t\t---------------------------------------\n\t\t\t\tYour Contact\n\t\t---------------------------------------\n");
    printf("\n\t\t(%d)\n", x + 1); // print index of current node, ie. first contact in the list = 1
    printf("\t\tName\t : %s %s\n", temp->FirstName, temp->LastName); // print first name and last name of current node
    printf("\t\tPhone no.: %s", temp->PhoneNumber); // print phone no. of current node
    printf("\n\n\t\t--------------------------------------\n\n");
    temp = temp->next; // move to next node
    x++;
  }
  printf("\n Press any key");
  getch(); // get input from user's keyboard
  ClearScreen(); // clear screen
}

/*
 * Delete a single contact from the list
 */
void deleterecord() {
  char delFirstName[20], delLastName[20]; // array to store the inputs from user
  struct Contact_Info *prev, *curr;
  int flag;
	
  if (head == NULL) {
    printf("\nSorry, your PhoneBook is empty.\a\n");
    return; // exit(1)
  }

  printf("\n\t\t-----------------------------------------\n\t\t\t\tDeleting Contact\n\t\t-----------------------------------------\n");
  printf("\nEnter the contact's first name: ");
  /* no need '&' operator for string
  in case of a string (character array), the variable itself points to the first element of the array in question*/
  scanf(" %[^\n]%*c", delFirstName);
  printf("\nEnter the contact's last name: ");
  scanf(" %[^\n]%*c", delLastName);
  printf("\n-------------------------------------------------------------------------\n");
  ClearScreen();
  
  // check if head node contains a contact
  while (head != NULL && !strcmp(head->FirstName, delFirstName) && !strcmp(head->LastName, delLastName)) {
    // get reference of head node
    prev = head;

    // adjust head node link
    head = head->next;

    printf("\nRemove %s %s from the phonebook...", delFirstName, delLastName);
    printf("\n\nContact deleted successfully.\n");

    // delete prev since it contains reference to head node
    free(prev);

    // no need to delete further
    return;
  }
  flag = 0; // if the condition is wrong, set flag to 0

  curr = head; // use curr to traverse the list, head as reference to the list's first element
  prev = NULL; // use prev to point to the previous element when iterating through the list

  // for each contact (node) in the list
  while (curr != NULL) {
    // current node contains (pointed) name to be deleted
    if (!strcmp(curr->FirstName, delFirstName) && !strcmp(curr->LastName, delLastName)) {
      // current node is the last element (tail)
      if (!curr->next) {
        tail = prev; // copy reference of tail node to prev node
      }
      // adjust links for previous node
      if (prev != NULL) {
        prev->next = curr->next;
      } else {
        head = curr->next;
      }
      printf("\nRemove %s %s from the phonebook...", delFirstName, delLastName);
      printf("\n\nContact deleted successfully.\n");
      free(curr); // delete current node
      return; // no need to delete further
    }
    flag = 0;
    prev = curr; // assign current node to previous node
    curr = curr-> next; // move current node to next
  }
  
  // if there is no matching
  if (!flag) {
    printf("\nContact %s %s not found.\a\n", delFirstName, delLastName);
  }

  printf("\n Press any key");
  getch(); // get input from user's keyboard
}

/*
 * Delete all the contacts from the list
 */
void deleteall() {
  struct Contact_Info *temp;
  int countToDelete = 0; // initialize count

  if (head == NULL) {
    printf("\nSorry, your PhoneBook is empty, there is nothing to be deleted!\a\n");
  } else {
    countToDelete = countContacts(); // count the number of contacts to be deleted
    while (head != NULL) {
      printf("\n%d contact(s) to be deleted...\n", countToDelete);

      temp = head; // copy the address of head node to temp variable
      head = head-> next; // move head node to the second node

      countToDelete--;

      free(temp); // clears the memory occupied by first node
    }
    printf("\nDeleted ALL the contacts successfully.\n");
  }
  printf("\n Press any key");
  getch(); // get input from user's keyboard
  ClearScreen(); // clear screen
}

/*
 * Sort contact list by first name alphabetically
 */
void sort() {
	struct Contact_Info *node1, *node2, *temp, t;
	
	if (head == NULL) {
		printf("\nError!\nYour PhoneBook is empty, there is nothing to sort.\n");
		exit(1); // exit because of error occurs
	} else if (head != NULL && head->next == NULL) {
		printf("\nSorry, I can't sort the PhoneBook. You have only ONE contact.\n");
		return; // call menu()
	} else {
		for(node1 = head; node1; node1 = node1->next) {
			for(node2 = node1->next; node2; node2 = node2->next ) { 
				// if the first value is bigger than the second value
				if(strcmp(node1->FirstName, node2->FirstName) > 0) {
					t = *node1; // store the value of the node1 pointer in t
					*node1 = *node2; // swap the two values
					*node2 = t; // the value that is initially stored by node1 pointer is passed to node2 pointer
					
					// swap node1 and node2 by swapping their next node links
					temp = node1->next; 
					node1->next = node2->next;
					node2->next = temp;
				}
			}
		}
		ClearScreen(); // clear screen
		printf("\nSorted contact list successfully.\n");
		display();	// display sorted list
	}
}

/*
 * Search a contact with given first name and last name in linked list.
 * It returns a positive integer specifying index of the contact found in the linked list on success,
 * otherwise returns -1.
 */
int searchByName() {
  int index, flag;
  char searchFirstName[20], searchLastName[20]; // array to store the inputs from user
  struct Contact_Info *curNode;

  index = 0;
  curNode = head;

  if (curNode == NULL) {
    printf("\nSorry, there is nothing to search, your PhoneBook is EMPTY.\a\n");
  } else {
    printf("\nEnter contact's first name: ");
    scanf(" %[^\n]%*c", searchFirstName);
    printf("\nEnter contact's last name: ");
    scanf(" %[^\n]%*c", searchLastName);
    ClearScreen(); // clear screen
	
    // iterate till last element until contact's name is not matched
    while (curNode != NULL && curNode->FirstName != searchFirstName && curNode->LastName != searchLastName) {
    	flag = 1;
		index++; // increment the index if not matched
		if (strcmp(curNode->FirstName, searchFirstName) == 0 && strcmp(curNode->LastName, searchLastName) == 0) {
			printf("\nContact found at position %d!\n", index);
			printf("\nYou are looking for %s %s.\n", searchFirstName, searchLastName);
			show(curNode->FirstName, curNode->LastName, curNode->PhoneNumber);
		}
		curNode = curNode->next; // move to next node
	}
	printf("\n Press any key\n");
  	getch(); // get input from user's keyboard
  	printf("\n If contact is found, the contact details will be displayed as above. Otherwise, please try again.\n"); //printf("\nSorry, I can't find anything. There is no such contact (%s %s) in your PhoneBook.\n", searchFirstName, searchLastName);
  	printf("\n -------------------------------------------------------------------------------------------------\n");
	return (curNode != NULL) ? index : -1; // if curNode is not NULL, and contact not found, return -1
  }
}

/*
 * Display the details of contact after the searching functions.
 * It prints out the name and phone no.
 */
void show(char *FirstName, char *LastName, char *PhoneNumber) {
    printf("\n\n\t\t--------------------------------------");
    printf("\n\t\t\t  About %s %s", FirstName, LastName);
    printf("\n\t\t--------------------------------------\n\n");
    printf("\t\tName\t : %s %s\n", FirstName, LastName);
    printf("\t\tPhone no.: %s", PhoneNumber);
    printf("\n\n\t\t--------------------------------------\n\n");
}

/*
 * Search a contact with given phone no. in linked list.
 * It returns a positive integer specifying index of the contact found in the linked list on success,
 * otherwise returns -1.
 */
int searchByPhoneNumber() {
	int index;
	char searchPhoneNumber[20]; // array to store the input from user
	struct Contact_Info *curNode;
	
	index = 0;
	curNode = head;
	
	if(curNode == NULL) {
		printf("\nSorry, there is nothing to search, your PhoneBook is EMPTY.\a\n");
	}
	else {
		printf("\nEnter contact's phone no.: ");
		scanf("%11s", &searchPhoneNumber); // read only 11 digits
		ClearScreen(); // clear screen
		
		// iterate till the last element until the phone number is not matched
		while(curNode != NULL && curNode->PhoneNumber != searchPhoneNumber) {
			index++; // increment the index if not matched
			if(strcmp(curNode->PhoneNumber, searchPhoneNumber) == 0) {
				printf("\nFound at position %d", index);
				show(curNode->FirstName, curNode->LastName, curNode->PhoneNumber);
			}
			curNode = curNode->next; // move to next node
		}
		printf("\n If contact is found, the contact details will be displayed as above. Otherwise, please try again.\n");
		printf("\n Press any key\n");
  		getch(); // get input from user's keyboard
		printf("\n --------------------------------------------------------------------------------------------\n");
		return (curNode != NULL) ? index : -1; // if curNode is not NULL, and contact not found, return -1
	}
}

/*
 * Ask the selection from user
 * [1] Search by name or [2] Search by phone number
 */
void searchSelection() {
  int choice;

  color(15); printf("\n[1]");
  color(7); printf(" Search by name");
  color(15); printf("\n[2]");
  color(7); printf(" Search by phone number");
  color(7); printf("\n\nEnter your choice");
  color(15); printf(" [1 - 2]");
  color(7); printf(": ");
  scanf("%1d", &choice); // read only 1 digit
  switch (choice) {
  case 1:
    searchByName();
    break;
  case 2:
    searchByPhoneNumber();
    break;
  default:
    printf("\nInvalid option: %d \n", choice);
    break;
  }
}

/*
 * Counts total number of contacts (nodes) in the list
 */
int countContacts() {
  int count = 0;
  struct Contact_Info *temp = head;

  while (temp != NULL) {
    count++;
    temp = temp->next;
  }

  return count;
}

/*
 * The menu for this program
 */
void menu() {
  int choice, ch, total;
  char toConvert[20];

  // infinite loop
  for (;;) {
    color(7); printf("\n\t\t\t\t - You have"); // 7 = light gray
    color(15); printf(" %d", countContacts()); // 15 = white
    color(7); printf(" contact(s) -\n");
    color(11); printf("\n\n\t\t\t\t\t  MENU\t\t\n\n"); // 11 = light cyan
    color(14); printf("\n\t\t\t\t   PhoneBook Options"); // 14 = yellow
	color(15); printf("\n\n\t[1]\t");
	color(7); printf("Create new contact");
	color(15); printf("\n\t[2]\t");
    color(7); printf("Delete contact");
    color(15); printf("\n\t[3]\t");
    color(7); printf("Sort the contacts list");
    color(15); printf("\n\t[4]\t");
    color(7); printf("Display contacts");
    color(15); printf("\n\t[5]\t");
    color(7); printf("Look up for contact's information");
    color(15); printf("\n\t[6]\t");
    color(7); printf("Delete ALL contacts");
    color(15); printf("\n\t[7]\t");
    color(7); printf("Exit PhoneBook");
    color(7); printf("\n\nSelect an option from the menu");
    color(15); printf(" [1 - 8]");
    color(7); printf(": ");
    choice = atoi(fgets(toConvert, 20, stdin)); // scanf("%1d", &choice);

    switch (choice) {
    case 1:
      ClearScreen();
      addrecord();
      break;
    case 2:
      ClearScreen();
      deleterecord();
      break;
    case 3:
      sort();
      break;
    case 4:
      ClearScreen();
      display();
      break;
    case 5:
      searchSelection();
      break;
    case 6:
      printf("\nDelete all the contacts?");
      color(15); printf(" (y/n)");
      color(7); printf(": ");
      scanf("%1c", &ch);
      if (ch == 'y' || ch == 'Y') {
        deleteall();
      }
      if (ch == 'n' || ch == 'N') {
        printf("\nNothing has been deleted.\n");
        printf("\n Press any key");
        getch(); // get input from user's keyboard
      }
      break;
    case 7:
      printf("\nYou have chosen to exit the PhoneBook.\n");
      break;
    default:
      ClearScreen();
      printf("\nInvalid option: %d \n", choice);
      break;
    }
    if (choice == 7) {
      exit(0); // exit program successfully
      break;
    }
  }
}

/*
 * Utility function
 * Just to clear the screen
 */
void ClearScreen() {
  system("cls");
}
