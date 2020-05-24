#include <stdio.h>
#include <stdlib.h> // system()
#include <conio.h> // getch()
#include <string.h> // strcmp()

//defining the properties of the fields used in the program
#define FST_NAME 20
#define LST_NAME 20
#define PHONE_NO 20
#define MAX 100

struct Contact_Info
{
      char FirstName[FST_NAME];
      char LastName[LST_NAME];
      char PhoneNumber[PHONE_NO];
};

void menu(); // main menu
void addrecord(); // insert new contacts
void deleterecord(); // delete selected contacts
void deleteall(); // delete the PhoneBook
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
      printf("\n\t3.\tEdit Phonebook");
      //printf("\n\t4.\tSort the Contacts List");
      printf("\n\t5.\tDisplay Contacts");
      printf("\n\t6.\tLook Up a Contact's Information");
      //printf("\n\t7.\tDelete ALL Contacts");
      printf("\n\t8.\tExit Phonebook");
      printf("\n\nSelect an option from the menu (1 - 8): ");
      scanf("%d", &choice);

      switch (choice)
      {
        case 1: addrecord(); break;
        case 2: deleterecord(); break;
        case 3: editrecord(); break;
      /*case 4:
                sort();
                break;*/
        case 5: displayrecord(); break;
        case 6: search(); break;
        //case 7: deleteall(); break;
        case 8: exit(0); break;
        default: printf("\n\tInvalid option: %d \a\n", choice); break;
      }
      if (choice == 8)
      {
        printf("\nYou have chosen to exit the Phonebook.\n");
        break;
      }
    }
}

// success
void addrecord()
{
  struct Contact_Info phonebook;
  FILE *PhoneBook;

  // open a text document named PhoneBook, read it and append data
  PhoneBook = fopen("PhoneBook.txt", "a+");
  // open a .bin file named PhoneBook, read it and append data in binary mode // PhoneBook = fopen("PhoneBook.bin", "ab+");

  printf("\nEnter first name: ");
  scanf(" %[^\n]%*c", phonebook.FirstName); // scanf("%s", phonebook.FirstName);
  printf("Enter last name: ");
  scanf(" %[^\n]%*c", phonebook.LastName); //scanf("%s", phonebook.LastName);
  printf("Enter phone no.: ");
  scanf("%s", phonebook.PhoneNumber);

  // write the contact's info into PhoneBook
  fprintf(PhoneBook, "%s %s %s \t", phonebook.FirstName, phonebook.LastName, phonebook.PhoneNumber);
  // write to a binary file // fwrite(&phonebook, sizeof(phonebook), 1, PhoneBook);

  printf("\n\tContact added to PhoneBook successfully.\n");
  fclose(PhoneBook); // close file

  printf("\nEnter any key");
  getch(); // get input from user's keyboard
  system("cls"); // clear screen

  menu(); // function call menu()
}

// error - whole record is deleted
void deleterecord()
{
  char delFirstName[20];
  char delLastName[20];
  int flag = 0;
  struct Contact_Info phonebook;
  FILE *PhoneBook;
  FILE *temprec;

  // open for reading
  if((PhoneBook = fopen("PhoneBook.txt", "r")) == NULL)
  {
    printf("\nYour PhoneBook is empty.\n");
  }
  else
  {
     // w+ means open for both reading and writing
     // if the file exists, its contents are overwritten
     // if the file does not exist, it will be created
    temprec = fopen("temp.txt", "w+");
    if(temprec == NULL)
    {
      printf("\nFile opening error.");
    }
    else
    {
      printf("\nEnter contact's first name: ");
      scanf("%s", &delFirstName);
      printf("Enter contact's last name: ");
      scanf("%s", &delLastName);

      // feof() returns the value zero when end of the file has not occurred, otherwise it returns 1
      // look into the text file for info if the PhoneBook isn't empty
      while(!feof(PhoneBook))
      {
        fscanf(PhoneBook, "%s %s %s \t", phonebook.FirstName, phonebook.LastName, phonebook.PhoneNumber);
        if (feof(PhoneBook))
        {
          break;
        }
        // compare the first name and last name entered by user and the info stored in PhoneBook
        if (strcmp(delFirstName, phonebook.FirstName) != 0)
          if(strcmp(delLastName, phonebook.LastName) != 0)
            fprintf(temprec, "%s %s %s \t", phonebook.FirstName, phonebook.LastName, phonebook.PhoneNumber);
        else
        {
          // set flag to 1 if the input not matched with the info stored in PhoneBook
          flag = 1;
        }
      } // end while
      if (flag == 1)
      {
        printf("\nNo such contact's record to delete./ Contact not found in PhoneBook.");
        remove("temp.txt");
      }
      printf("\nContact deleted successfully.\n");
      fclose(PhoneBook);
      fclose(temprec);
      remove("PhoneBook.txt");
      rename("temp.txt", "PhoneBook1.txt");
    } // end innner else statement
  } // end outer else statement
  system("pause");
  system("cls");
  menu();
}

// success
void editrecord()
{
    int c;
    struct Contact_Info phonebook, edit;
    FILE *PhoneBook;
    int flag = 0;
    char name[20];

    PhoneBook = fopen("PhoneBook.txt", "r+");
	  if(PhoneBook == NULL)
		{
			printf("\nContact not added yet.\n");
		}
    else
	  {
      printf("\nEnter contact's first name: ");
      scanf("%s", &edit.FirstName);
      printf("Enter contact's last name: ");
      scanf("%s", &edit.LastName);

      while(!feof(PhoneBook))
      {
        if(strcmp(phonebook.FirstName, edit.FirstName) && strcmp(phonebook.LastName, edit.LastName) != 0)
        {
            printf("\nEditing...\n");
            printf("\n Enter first name: ");
            scanf(" %[^\n]%*c", &edit.FirstName);
            printf("\n Enter last name: ");
            scanf(" %[^\n]%*c", &edit.LastName);
            printf("\n Enter phone no: ");
            scanf("%s", &edit.PhoneNumber);
            fseek(PhoneBook, -sizeof(phonebook), SEEK_CUR);
            fprintf(PhoneBook, "%s %s %s \t", edit.FirstName, edit.LastName, edit.PhoneNumber);
            flag = 1;
            break;
        }

      }
      if(flag == 1)
      {
        printf("\n Your contact info is modified.\n");
      }
      else
      {
        printf(" \n Data is not found.\n");
      }
      fclose(PhoneBook);
	}
  system("pause");
  system("cls");
	menu();
}

// success
void displayrecord()
{
  struct Contact_Info phonebook;
  FILE *PhoneBook;
  int x = 0;

  // open PhoneBook and read it
  PhoneBook = fopen("PhoneBook.txt", "r");
  // open PhoneBook and read in binary mode // PhoneBook = fopen("PhoneBook.bin", "rb");
  if (PhoneBook == NULL)
  {
    printf("\nSorry, the PhoneBook is empty.\n");
  }
  else
  {
    // feof() returns the value 1 if file pointer is at the end of file, otherwise it will return 0
    // !feof() means "until we have not reached end of file"
    while (!feof(PhoneBook))
    {
     printf("\nYour Contact\n");
     fscanf(PhoneBook, "%s %s %s \t", phonebook.FirstName, phonebook.LastName, phonebook.PhoneNumber);
     printf("\n(%d)\n", x+1);
     printf("Name: %s %s\n", phonebook.FirstName, phonebook.LastName);
     printf("Phone no.: %s\n", phonebook.PhoneNumber);
     x++;
     // view contact one by one
     // printf("\nPress any key to view the next contacts");
     // getch(); // waiting for user's input
     // system("cls"); // clear screen (include menu) and show the next contacts
   }
  }
  fclose(PhoneBook);
  printf("\n");
  system("pause");
  menu(); // function call menu()
}

// no idea where to put printf("\nContact not found.); in void search()
// error when reading the the second contact and above from the PhoneBook.txt, return x number "contact not found" follow by contacts info
void search()
{
  struct Contact_Info phonebook;
  FILE *PhoneBook;
  char searchFirstName[20], searchLastName[20], searchPhoneNumber[20];
  int choice1, flag = 1;

  PhoneBook = fopen("PhoneBook.txt", "r");
  if(PhoneBook == NULL)
  {
    printf("\nError in opening\a\a\a\a");
    exit(1);
  }

  printf("\n1. Search by first name and last name");
  printf("\n2. Search by phone number");
  printf("\n\nEnter your choice (1 / 2): ");
  scanf("%d", &choice1);

  if(choice1 == 1)
  {
    printf("\nEnter contact's first name: ");
    scanf("%s", &searchFirstName);
    printf("Enter contact's last name: ");
    scanf("%s", &searchLastName);
  }
  if(choice1 == 2)
  {
    printf("Enter contact's phone no.: ");
    scanf("%s", &searchPhoneNumber);
  }
  while(!feof(PhoneBook))
  {
    fscanf(PhoneBook, "%s %s %s \t", phonebook.FirstName, phonebook.LastName, phonebook.PhoneNumber);
    if(choice1 == 1)
    {
      if(strcmp(phonebook.FirstName, searchFirstName) == 0)
      {
        if(strcmp(phonebook.LastName, searchLastName) == 0)
        {
          printf("\n\tDetail Information About %s %s\n", searchFirstName, searchLastName);
          printf("\nName: %s %s\nPhone no: %s \n", phonebook.FirstName, phonebook.LastName, phonebook.PhoneNumber);
        }
      }
    }
    if(choice1 == 2)
    {
      if(strcmp(phonebook.PhoneNumber, searchPhoneNumber) == 0)
      {
        printf("\n\tContact found.\n");
        printf("\nName: %s %s\nPhone no: %s \n", phonebook.FirstName, phonebook.LastName, phonebook.PhoneNumber);
      }
    }
  }
  fclose(PhoneBook);
  printf("\n");
  system("pause");
  system("cls");
  menu();
}
