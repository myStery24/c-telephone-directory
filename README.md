
Welcome to a telephone directory program.
===
In this program, you can **add** a new record, **delete** an/ all existing record(s), **sort** the records, **display** the entire phone list or **search** the directory for a specified record.

---
1. This is a **default menu** with **7** options.

					   - You have [number] contact(s) -

					     		MENU

				      		 PhoneBook Options

        [1]	Create new contact
        [2]	Delete contact
        [3]	Sort the contacts list
        [4]	Display contacts
        [5]	Look up for contact's information
        [6]	Delete ALL contacts
        [7]	Exit PhoneBook

		Select an option from the menu [1 - 7]:

2. Select an option from the menu [1 - 7]:

	(i) If you choose `1`:\
      You will be asked to enter the `contact's first name`, `last name` and also the `phone number`.
      This is the display screen for creating a new contact:

        ----------------------------------------------
                          New Contact
        ----------------------------------------------
        Enter first name:

        Enter last name:

        Enter phone.no:

        ----------------------------------------------

		Contact added to PhoneBook successfully. // This sentence is displayed when creating the first contact only

		Creating your first contact...

		 Press any key

	(ii)	 If you choose `2`:\
	You will be asked to enter the `contact's first name` and `contact's last name`. This is the display screen for deleting a contact:

				----------------------------------------
					     Deleting Contact
				----------------------------------------

		Enter the contact's first name:

		Enter the contact's last name:

 After entering the required inputs (the contact (first name and last name) that you want to delete), the program will automatically help you to **delete** the contact.

 This is the message shown on the screen after a contact has been removed. Next, the menu is displayed again on the screen.

		Remove [first name entered][last name entered] from the phonebook...

		Contact deleted successfully.

					    - You have [number - 1] contact(s) -

		     					 MENU

				      		  PhoneBook Options

        [1]	Create new contact
        [2]	Delete contact
        [3]	Sort the contacts list
        [4]	Display contacts
        [5]	Look up for contact's information
        [6]	Delete ALL contacts
        [7]	Exit PhoneBook

		Select an option from the menu [1 - 7]:

	(iii) If you choose `3`:
 	- Whenever the phonebook is *empty*, the message below will be displayed and the program is terminated:

	    	Error!
	    	Your PhoneBook is empty, there is nothing to sort.

 - If the phonebook contains *only one contact*, this message is displayed instead, followed by showing the default menu:

			Sorry, I can't sort the PhoneBook. You have only ONE contact.

 - Else, if the phonebook has stored *more than one contact*, the program will sort the entire contact list and display the following message after sorting:

	    	Sorted contact list successfully.

	                ---------------------------------------
	                               Your Contact
	                ---------------------------------------

	                (1)
	                Name      : xxx xxx
	                Phone no. : 0123456789

	                ---------------------------------------

	                ---------------------------------------
	                               Your Contact
	                ---------------------------------------

	                (2)
	                Name      : xxx xxx
	                Phone no. : 051234567

	                ---------------------------------------

	     Press any key

 (iv) If you choose `4`:\
	You are meant to `display` your contact list. Thus, your contacts are as shown below.

	                ---------------------------------------
	                              Your Contact
	                ---------------------------------------

	                (1)
	                Name      : xxx xxx
	                Phone no. : 0123456789

	                ---------------------------------------

	                ---------------------------------------
	                              Your Contact
	                ---------------------------------------

	                (2)
	                Name      : xxx xxx
	                Phone no. : 051234567

	                ---------------------------------------

	         Press any key

 (v) If you choose `5`:\
There will be **2** options to choose from.

		[1] Search by name
		[2] Search by phone number

	    Enter your choice [1 - 2]:

 - Choosing 1: You will be asked to enter `contact's first name` and `last name` that you want to search. This is the two lines showing on the screen:

	     Enter contact's first name:

	     Enter contact's last name:

  After entering all the details required, the search result will be shown as below, followed by a message after pressing any key and then, a default menu:

		You are looking for [contact's name].

	                    -----------------------------------------
	                               About [contact's name]
	                    -----------------------------------------

	                    Name      : xxx xxx
	                    Phone no. : 0123456789

	                    -----------------------------------------

		 Press any key

		 If contact is found, the contact details will be displayed as above. Otherwise, please try again.

	     -------------------------------------------------------------------------------------------------

	 - Choosing 2 : You will be asked to enter the `phone number` that you want to search. This line is shown on the screen:

	       Enter contact's phone no.:

 After entering the phone number, the search result will be shown as below:

	                    -----------------------------------------
	                               About [contact's name]
	                    -----------------------------------------

	                    Name      :
	                    Phone no. :

	                    -----------------------------------------

	     If contact is found, the contact details will be displayed as above. Otherwise, please try again.

	     Press any key

**NOTE** For the scenario of after *entering any names or any phone numbers that weren't stored/ saved in the phonebook*:

First, you have to `press any key`, then, you will see this message and a default menu.

	If contact is found, the contact details will be displayed as above. Otherwise, please try again.

 (vi) If you choose `6`:\
 You are meant to `delete the entire records`, not just deleting a single contact.

For this choice - number 6, you will be asked a question to confirm that if you wanted to proceed with this process.

This is the question that will be displayed:

	Delete all the contacts? (y/n):

- If you enter **n** or **N**, nothing will be deleted and this message is shown:

      Nothing has been deleted.

        Press any key


- If you enter **y** or **Y**, the program will proceed to delete all the contacts.

 This is the output on the screen:

      [number] contact(s) to be deleted... // Start with the total number of contacts and continue displaying by reducing the number one by one until the total number of contacts is reduced to 0.

      Deleted ALL the contacts successfully.

       Press any key

	 **NOTE** For the scenario of entering y or Y while having an *empty phonebook*:\
	 You will see this message below.

		Sorry, your PhoneBook is empty, there is nothing to be deleted!

	     Press any key

 (vii) If you choose `7`:\
	 A message is displayed:

	 	You have chosen to exit the PhoneBook.

   (viii) If you choose/ enter any `invalid numbers, characters`:\
	 The upper left side of the program will show this message:

	 	Invalid option: [invalid number]

		This designed program can be used to save the names and phone numbers.

---
The linked list data structure is implemented in this C phonebook program. This program contains many functions such as add, delete, sort, display and search. Plus, some utility functions to display coloured word and clear console screen.

By using this program, the usage of pen and paper to record the people's contact detail can be reduced.

This program also helps in reducing the time taken to find out other contact details and also arranging all the contacts information.
