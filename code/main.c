#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"
#include "date.h"

void sign_in() {
	char email[30], password[10];
	User u;
	int invalid_user = 0;
	// input email and password from user.
	printf("Email: ");
	scanf("%s", email);
	printf("Password: ");
	scanf("%s", password);
	// find the user in the users file by email.
	if(user_find_by_email(&u, email) == 1) {
		// check input password is correct.
		if(strcmp(password, u.pwd) == 0) {
			// special case: check for owner login
            //if(strcmp(u->email, EMAIL_OWNER) == 0)
		    //strcpy(u->role, ROLE_OWNER);			
			// if correct, call user_area() based on its role.
			if(strcmp(u.role, ROLE_OWNER) == 0)
				owner_area(&u);
			else if(strcmp(u.role, ROLE_LIBRARIAN) == 0)
				librarian_area(&u);
			else if(strcmp(u.role, ROLE_MEMBER) == 0)
				member_area(&u);
			else
				invalid_user = 1;
		}
		else
			invalid_user = 1;
	}
	else
		invalid_user = 1;

	if(invalid_user)
		printf("Invalid email, password or role.\n");

}

void sign_up() {
	// input user details from the user.
	User u;
	user_accept(&u);
	// write user details into the users file.
	user_add(&u);

}



int main() {
	//tester();
	printf("Hello Library!\n");
    
	int choice;
	do {
		printf("\n\n0. Exit\n1. Sign In\n2. Sign Up\nEnter choice: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1: // Sign In
			sign_in();
			break;
		case 2:	// Sign Up
			sign_up();	
			break;
		}
	}while(choice != 0);

	return 0;
}

