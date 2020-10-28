#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

void member_area(User *u) {
	int choice;
	char name[80];
	do {
		printf("\n\n1. Find Book\n2. Edit Profile\n3. Change Password\n4. Book Availability\n5. Issue Record.\n6. Payment History\nEnter choice: ");
		scanf("%d", &choice);
		switch(choice) {
			case 1:// Find Book
				   printf("Enter book name: ");
				   scanf("%s", name);
				   book_find_by_name(name);//func definition in common.c file
				   break;
			case 2://Edit Profile
			       edit_profile(u);//func definition in common.c file
				   break;
			case 3://Change password
                   change_password(u);//func definition in common.c file
				   break;
			case 4://Book Availability
			       bookcopy_checkavail();
				   break;
		    case 5://Display Issued books
			       display_issued_bookcopies(u->id);//func definition in common.c file
				   break;
			case 6://Payment History
			       payment_history(u->id);//func definition in common.c file
				   break;
		}
		printf("\nPress 1 to Continue \nPress 0 to Sign out\n");
        scanf("%d",&choice);
	}while (choice);	
}

void bookcopy_checkavail() {
	int book_id;
	FILE *fp;
	BookCopy bc;
	int count = 0;
	// input book id
	printf("enter the book id: ");
	scanf("%d", &book_id);
	// open book copies file
	fp = fopen(BOOKCOPY_DB, "rb");
	if(fp == NULL) {
		perror("cannot open bookcopies file.");
		return;
	}

	// read bookcopy records one by one
	while(fread(&bc, sizeof(BookCopy), 1, fp) > 0) {
		// if book id is matching and status is available, count the copies
		if(bc.bid == book_id && strcmp(bc.status, STATUS_AVAIL)==0) {
		//	bookcopy_display(&bc);
			count++;
		}
	}
	// close book copies file
	fclose(fp);
	// print the message. 
	printf("number of copies availables: %d\n", count);
}
