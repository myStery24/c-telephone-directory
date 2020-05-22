#include <stdio.h>
#include <stdlib.h> // system()
#include <conio.h> // getch()

//defining the properties of the fields used in the program
#define FST_NAME 20
#define LST_NAME 20
#define PHONE_NO 20

struct Contact_Info
{
      char FirstName[FST_NAME];
      char LastName[LST_NAME];
      char PhoneNumber[PHONE_NO];
};

struct Contact_Info phonebook;

FILE *PhoneBook;

void menu(); // main menu
void addrecord(); // insert new contacts
void deleterecord(); // delete contacts
void deleteall(); // delete all contacts
void editrecord(); // edit contacts
void sort();
void displayrecord(); // display contacts
void search();

// main function
int main()
{
    menu();
    return 0;
}

void menu()
{
    int choice = 0;

    // infinite loop
    for (;;)
    {
      printf("\n\n\t\t\t\t  MENU\t\t\n\n");
      printf("\n\t\t\tPhonebook Options");
      printf("\n\n\t1.\tNew Contact");
      printf("\n\t2.\tDelete Contact");
      printf("\n\t3.\tEdit Phonebook ");
      printf("\n\t4.\tDisplay Phonebook ");
      printf("\n\t5.\tLook Up a Contacts Phone Number");
      printf("\n\t6.\tDelete ALL Contacts");
      printf("\n\t7.\tExit Phonebook");
      printf("\n\nSelect an option from the menu (1 - 8): ");
      scanf("%d", &choice);

      switch (choice)
      {
        case 1:
                addrecord();
                break;
        case 2:
                deleterecord();
                break;
        case 3:
                editrecord();
                break;
        case 4:
                displayrecord();
                break;
        case 5:
                search();
                break;
        case 6:
                random1();
                break;
        case 7:
                deleteall();
                break;
        case 8:
                fprintf(stdout, "\nYou have chosen to exit the Phonebook.\n");
                getchar();
                break;
        default:
                fprintf(stdout, "\n\tI don't know the option : %d \a\n", choice);
                break;
      }
      if (choice == 8) break;
    }
}

void addrecord()
{
  // open PhoneBook, read it and append data
  // PhoneBook = fopen("PhoneBook.txt", "a+");
  // open PhoneBook, read it and append data in binary mode
  PhoneBook = fopen("PhoneBook.bin", "ab+");

  printf("\nEnter First Name: ");
  scanf(" %[^\n]%*c", phonebook.FirstName);
  printf("Enter Last Name: ");
  scanf(" %[^\n]%*c", phonebook.LastName);
  printf("Enter Phone Number: ");
  scanf("%s", phonebook.PhoneNumber);

  // write to a text file
  // fprintf(phonebook, "%s %s %s ", phonebook.FirstName, phonebook.LastName, phonebook.PhoneNumber); // not working
  // write to a binary file
  fwrite(&phonebook, sizeof(phonebook), 1, PhoneBook);

  fflush(stdin);
  printf("\n\tContact successfully added to Phonebook\n");
  fclose(PhoneBook);

  printf("\n\nEnter any key");
  getch();
  system("cls");

  menu();
}

void displayrecord()
{
  int x;
  // open PhoneBook and read it
  // PhoneBook = fopen("PhoneBook.txt", "r");
  // open PhoneBook and read in binary mode
  PhoneBook = fopen("PhoneBook.bin", "rb");

  if (PhoneBook == NULL)
  {
    printf("\nThe PhoneBook is Empty");
    // program exits if the file pointer returns NULL
    exit(1);
  }

  while (fread(&phonebook, sizeof(phonebook), 1, PhoneBook) == 1)
  {
      printf("\n(%d)\n", x+1);
      printf("\nYour Contact List\n\n");
      printf("Name: %s %s\n", phonebook.FirstName, phonebook.LastName);
      printf("Number: %s\n", phonebook.PhoneNumber);
      x++;

      printf("\nPress any key to view the next contacts");
      // waiting for user's input
      getch();
      // clear screen and show the next contacts (one by one)
      system("cls");
  }

  fclose(PhoneBook);

  printf("\n Enter any key");
  getch();
  system("cls");

  menu();
}

void cls()
{
	system("cls");
}
