// search and sort not done yet
// search functions : error in searching

#include <stdio.h>
#include <stdlib.h> // system() , exit()
#include <conio.h> // getch()
#include <string.h> // strcmp() , stricmp()
#include <windows.h>

//defining the properties of the fields used in the program
#define FSTNAME 20
#define LSTNAME 20
#define PHONE_NO 20

// for colour
void color(short x) {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x); // windows.h
}

// functions
void menu(); // main menu
void addrecord(); // add contact
void display(); // show all contacts
void deleterecord(); // delete a single contact by name
void deleteall(); // delete all contacts
void sort(); // not done yet
void searchByName(); // search by name // error, logic error
void searchByPhoneNumber(); // search by entering phone number 
void searchSelection();
int countContacts(); // a.k.a countNodes() , counts total number of contacts in the list
void ClearScreen(); // clear screen

// create a linked list struct
struct Contact_Info {
  char FirstName[FSTNAME]; // data
  char LastName[LSTNAME]; // data
  char PhoneNumber[PHONE_NO]; // data
  struct Contact_Info * next; // address
}*head, *tail;

//struct Contact_Info *head = NULL;
//struct Contact_Info *tail = NULL;

int main() {

  menu();
  return 0;
}

void addrecord() {
  struct Contact_Info *newContact = (struct Contact_Info *) malloc(sizeof(struct Contact_Info));

  // input data of node from user
  printf("\n\t\t-----------------------------------------\n\t\t\t\tNew Contact\n\t\t-----------------------------------------\n");
  printf("\n\t\tEnter first name: ");
  fgets(newContact->FirstName, 20, stdin);
  newContact->FirstName[strlen(newContact->FirstName) - 1] = 0; // printf("%d", newContact->name[strlen(newContact->name) - 1]);
  printf("\n\t\tEnter last name: ");
  fgets(newContact->LastName, 20, stdin);
  newContact->LastName[strlen(newContact-> LastName) - 1] = 0;
  printf("\n\t\tEnter phone no.: ");
  fgets(newContact->PhoneNumber, 11, stdin);
  newContact->PhoneNumber[strlen(newContact->PhoneNumber) - 1] = 0;

  newContact->next = NULL;

  if (head == NULL) {
    printf("\nCreating your first contact...\n");
    head = newContact;
    tail = newContact;
  } else {
    tail->next = newContact;
    tail = newContact;
  }
  printf("\nContact added to PhoneBook successfully.\n");

  printf("\n Press any key");
  getch(); // get input from user's keyboard
  ClearScreen(); // clear screen
}

void display() {
  struct Contact_Info *temp = head;
  int x = 0;

  // return if list is empty
  if (head == NULL) {
    printf("\nSorry, your PhoneBook is empty.\nAdd new contact by choosing 1.\a\n");
    return;
  }

  temp = head;
  
  while (temp != NULL) {
    printf("\n\t\t---------------------------------------\n\t\t\t\tYour Contact\n\t\t---------------------------------------\n");
    printf("\n\t\t(%d)\n", x + 1);
    printf("\t\tName\t : %s %s\n", temp->FirstName, temp->LastName);
    printf("\t\tPhone no.: %s", temp->PhoneNumber);
    printf("\n\n\t\t--------------------------------------\n\n");
    temp = temp->next; // move to next node
    x++;
	}
	
	printf("\n Press any key");
	getch(); // get input from user's keyboard
	ClearScreen(); // clear screen
}

void deleterecord() {
  char delFirstName[20], delLastName[20];
  struct Contact_Info *prev, *curr;
  int flag;

  if (head == NULL) {
    printf("\nSorry, your PhoneBook is empty.\a\n");
    return; // exit(1)
  }

  printf("\n\t\t-------------------------------------------\n\t\t\t\tDeleting Contact\n\t\t-------------------------------------------\n");
  printf("\nEnter the contact's first name: ");
  /* no need '&' operator for string
  in case of a string (character array), the variable itself points to the first element of the array in question*/
  scanf(" %[^\n]%*c", delFirstName);
  printf("\nEnter the contact's last name: ");
  scanf(" %[^\n]%*c", delLastName);

  /* check if head node contains key*/
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

  /* for each node in the list */
  while (curr != NULL) {
    // current node contains (pointed) name to be deleted
    if (!strcmp(curr->FirstName, delFirstName) && !strcmp(curr-> LastName, delLastName)) {
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

  if (!flag) {
    printf("\nContact %s %s not found.\a\n", delFirstName, delLastName);
  }

  printf("\n Press any key");
  getch(); // get input from user's keyboard
  ClearScreen(); // clear screen
}

void deleteall() {
  struct Contact_Info * temp;
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

void sort() {

}

void searchByName() {
  int index;
  char searchFirstName[20], searchLastName[20];
  struct Contact_Info * curNode;

  index = 0;
  curNode = head;

  if (curNode == NULL) {
    printf("\nSorry, there is nothing to search, your PhoneBook is EMPTY.\a\n");
  } else {
    printf("\nEnter contact's first name: ");
    scanf(" %[^\n]%*c", searchFirstName);
    printf("\nEnter contact's last name: ");
    scanf(" %[^\n]%*c", searchLastName);

    // iterate till last element until contact's name is not matched
    while (curNode != NULL && (curNode->FirstName != searchFirstName) && (curNode->LastName != searchLastName)) {
      // found contact
      if (!stricmp(curNode->FirstName, searchFirstName) && !stricmp(curNode->LastName, searchLastName)) // == 1
      {
        curNode = curNode->next;
        printf("first:  %s", curNode);
        printf("\nContact found!\n");
        printf("\n\t\t\t  About %s %s", curNode->FirstName, curNode->LastName);
        printf("\n\n\t\t--------------------------------------\n\n");
        printf("\t\tName\t : %s %s\n", curNode->FirstName, curNode->LastName);
        printf("\t\tPhone no.: %s", curNode->PhoneNumber);
        printf("\n\n\t\t--------------------------------------\n\n");
        index++;
        curNode = curNode-> next; // move to next node
        return;
      } else {
        printf("\nSorry, I can't find anything. There is no such contact (%s %s) in your PhoneBook.\n", searchFirstName, searchLastName);
        printf("\nMay be you are looking for %s %s?\n", curNode-> FirstName, curNode->LastName);
        break;
      }
    }
  }

  printf("\n Press any key");
  getch(); // get input from user's keyboard
  ClearScreen(); // clear screen
}

void searchByPhoneNumber() {
  int index;
  char searchPhoneNumber[20];
  struct Contact_Info * curNode;

  index = 0;
  curNode = head;

  if (curNode == NULL) {
    printf("\nSorry, there is nothing to search, your PhoneBook is EMPTY.\a\n");
  } else {
    printf("\nEnter contact's phone no.: ");
    scanf("%11s", & searchPhoneNumber);

    // iterate till last element until contact's phone no. is not matched
    while (curNode != NULL && (curNode-> PhoneNumber != searchPhoneNumber)) {
      // found contact
      if (!stricmp(curNode->PhoneNumber, searchPhoneNumber)) // == 1
      {
        printf("\nContact found!\n");
        printf("\n\t\t\t  About %s %s", curNode->FirstName, curNode->LastName);
        printf("\n\n\t\t--------------------------------------\n\n");
        printf("\t\tName\t : %s %s\n", curNode->FirstName, curNode->LastName);
        printf("\t\tPhone no.: %s", curNode->PhoneNumber);
        printf("\n\n\t\t--------------------------------------\n\n");
        index++; // printf("%d", index);
        curNode = curNode->next; // move to next node
      } else {
        printf("\nSorry, I can't find anything. \n%s hasn't added to your PhoneBook.\n", searchPhoneNumber);
        break;
      }
    }
  }

  printf("\n Press any key");
  getch(); // get input from user's keyboard
  ClearScreen(); // clear screen
}

void searchSelection() {
  int choice;

  printf("\n1. Search by name");
  printf("\n2. Search by phone number");
  printf("\n\nEnter your choice (1 - 2): ");
  scanf("%1d", & choice);
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

// done
int countContacts() {
  int count = 0;
  struct Contact_Info * temp = head;

  while (temp != NULL) {
    count++;
    temp = temp->next;
  }

  return count;

}

void menu() {
  int choice, ch, total;
  char toConvert[20];

  // infinite loop
  for (;;) {
    printf("\n\t\t\t\t You have %d contact(s)\n", countContacts());
    printf("\n\n\t\t\t\t\t MENU\t\t\n\n");
    printf("\n\t\t\t\tPhoneBook Options");
    printf("\n\n\t1.\tCreate new contact");
    printf("\n\t2.\tDelete contact");
    printf("\n\t3.\tSort the contacts list");
    printf("\n\t4.\tDisplay contacts");
    printf("\n\t5.\tLook up for contact's information");
    printf("\n\t6.\tDelete ALL contacts");
    printf("\n\t7.\tExit PhoneBook");
    printf("\n\nSelect an option from the menu (1 - 8): ");
    // scanf("%1d", &choice);
    choice = atoi(fgets(toConvert, 20, stdin));

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
      printf("\nDelete all the contacts? (y/n): ");
      scanf("%1c", & ch);
      if (ch == 'y' || ch == 'Y') {
        deleteall();
      }
      if (ch == 'n' || ch == 'N') {
        printf("\nNothing has been deleted.\n");
        printf("\n Press any key");
        getch();
      }
      break;
    case 7:
      printf("\nYou have chosen to exit the PhoneBook.\n");
      break;
    default:
      printf("\nInvalid option: %d \n", choice);
      break;
    }
    if (choice == 7) {
      exit(0);
      break;
    }
  }
}

void ClearScreen() {
  system("cls");
}
