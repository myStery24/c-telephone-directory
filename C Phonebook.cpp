#include <stdio.h>
#include <stdlib.h> // system()
#include <conio.h> // getch()
#include <string.h> // strcmp()

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
FILE *temprec;

void menu(); // main menu
void addrecord(); // insert new contacts
int searchret(char FirstName[], char LastName[]);
void deleterecord(); // delete contacts
void deleteall(); // delete all contacts
void editrecord(); // edit contacts
void sort();
void displayrecord(); // display contacts
void search();

// main function
int main()
{
    system("cls"); // clear screen
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
      printf("\n\t4.\tDisplay Contacts");
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
        /*case 3:
                editrecord();
                break;*/
        case 4:
                displayrecord();
                break;
        /*case 5:
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
                break;*/
        default:
                fprintf(stdout, "\n\tInvalid option: %d \a\n", choice);
                break;
      }
      if (choice == 8)
      {
        break;
      }
    }
}

void addrecord()
{
  // open a text document named PhoneBook, read it and append data
  PhoneBook = fopen("PhoneBook.txt", "a+");
  // open a .bin file named PhoneBook, read it and append data in binary mode // PhoneBook = fopen("PhoneBook.bin", "ab+");

  printf("\nEnter First Name: ");
  scanf("%s", phonebook.FirstName); // scanf(" %[^\n]%*c", phonebook.FirstName);
  printf("Enter Last Name: ");
  scanf("%s", phonebook.LastName); // scanf(" %[^\n]%*c", phonebook.LastName);
  printf("Enter Phone Number: ");
  scanf("%s", phonebook.PhoneNumber);

  // write the info into PhoneBook
  fprintf(PhoneBook, "%s %s %s \t", phonebook.FirstName, phonebook.LastName, phonebook.PhoneNumber);
  // write to a binary file // fwrite(&phonebook, sizeof(phonebook), 1, PhoneBook);

  fflush(stdin);
  printf("\n\tContact added to PhoneBook successfully.\n");
  fclose(PhoneBook); // close file

  printf("\nEnter any key");
  getch(); // get input from user's keyboard
  system("cls"); // clear screen

  menu(); // function call menu()
}

// after delete, everything display out is a messed
void deleterecord()
{
   int counter, x;
   char deleteFirstName[20];
   char deleteLastName[20];

   // open for reading
   PhoneBook = fopen("PhoneBook.txt", "r");
   // open for reading in binary mode // PhoneBook = fopen("PhoneBook.bin", "rb");

   if (PhoneBook == NULL)
   {
     printf("\nYour contacts list is empty.\n");
   }
   else
   {
     // w+ means open for both reading and writing
     // if the file exists, its contents are overwritten
     // if the file does not exist, it will be created
     temprec = fopen("temp.txt", "w+");

     if (temprec == NULL)
     {
       printf("File opening error");
     }
     else
     {
       printf("\nEnter Contact's First Name: ");
       scanf("%s", deleteFirstName);
       printf("Enter Contact's Last Name: ");
       scanf("%s", deleteLastName);

       fflush(stdin);

       // feof() returns the value zero when end of the file has not occurred, otherwise it returns 1
       // look into the text file for info if the PhoneBook isn't empty
       while(!feof(PhoneBook)) // for binary file // while(fread(&phonebook, sizeof(phonebook), 1, PhoneBook) == 1)
   		 {
         fscanf(PhoneBook,"%s %s %s", phonebook.FirstName, phonebook.LastName, phonebook.PhoneNumber);
         if(feof(PhoneBook))
         {
           break;
         }
         // compare the first name and last name entered by user and the info stored in PhoneBook
   			 if(strcmp(phonebook.FirstName, deleteFirstName) && (strcmp(phonebook.LastName, deleteLastName)) != 0)
         {
   				  fprintf(temprec, "%s %s %s \n", phonebook.FirstName, phonebook.LastName, phonebook.PhoneNumber); // write in binary // fwrite(&phonebook, sizeof(phonebook), 1, temprec);
         }
   			 else
         {
           // counter set to 1 if the input not matched with the info stored in PhoneBook
           counter = 1;
         }
       } // end while
       fclose(PhoneBook); // close PhoneBook
       fclose(temprec); // close temprec

       if(counter != 1)
       {
         printf("\nNo such contact's record to delete./ Contact not found in PhoneBook.");
         remove("temp.txt");
       }
       else
       {
         // delete the old text document named PhoneBook
         remove("PhoneBook.txt");
         // rename the text document named temp to PhoneBook
         rename("temp.txt","PhoneBook.txt");
         printf("Record deleted from the Phonebook successfully.");
       }
     } // end inner else statement - line 147
   } // end outer else statement - line 136
    printf("\n Enter any key");
    getch(); // get input from user's keyboard
    system("cls"); // clear screen
    menu(); // function call menu()
}

void displayrecord()
{
  int x = 0;

  // open PhoneBook and read it
  PhoneBook = fopen("PhoneBook.txt", "r");
  // open PhoneBook and read in binary mode // PhoneBook = fopen("PhoneBook.bin", "rb");

  if (PhoneBook == NULL)
  {
    printf("\nSorry, the PhoneBook is empty.");
    // program exits if the file pointer returns NULL
    exit(1);
  }

  printf("\nYour Contact List\n");
  // !feof() means "until we have not reached end of file"
  while (!feof(PhoneBook)) // for binary file // while (fread(&phonebook, sizeof(phonebook), 1, PhoneBook) == 1)
  {
    fscanf(PhoneBook, "%s %s %s ", phonebook.FirstName, phonebook.LastName, phonebook.PhoneNumber);
    printf("\n(%d)\n", x+1);
    printf("First Name: %s \nLast Name: %s\n", phonebook.FirstName, phonebook.LastName);
    printf("Number: %s\n", phonebook.PhoneNumber);
    x++;

    // view contact one by one
    // printf("\nPress any key to view the next contacts");
    // getch(); // waiting for user's input
    // system("cls"); // clear screen (include menu) and show the next contacts
  }
  fclose(PhoneBook); // close PhoneBook
  printf("\n Enter any key");
  getch(); // get input from user's keyboard
  menu(); // function call menu()
}

void cls()
{
	system("cls");
}
