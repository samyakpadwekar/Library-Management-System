#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

void owner_area(User *u) {
	int choice;

	do {
		printf("\n\n1. Appoint Librarian\n2. Edit Profile\n3. Change Password\n4. Payment Report\n5. Book Availability\nEnter choice: ");
		scanf("%d", &choice);
		switch(choice) {
			case 1:// Appoint Librarian
				   appoint_librarian();
				   break;
			case 2://Edit Profile
			       edit_profile(u);    //func definition in common.c file
				   break;
			case 3://Change password
                   change_password(u); //func definition in common.c file
				   break;
			case 4://Fees/Fine report
			       payment_report();
				   break;
			case 5://Check Availability
			       bookcopy_checkavail_details();//func definition in common.c file
				   break;
		}
		printf("\nPress 1 to Continue \nPress 0 to Sign out\n");
        scanf("%d",&choice);
	}while (choice);	
}

//1.Appoint ibrarian
void appoint_librarian() {
	// input librarian details
	User u;
	user_accept(&u);
	// change user role to librarian
	strcpy(u.role, ROLE_LIBRARIAN);
	// add librarian into the users file
	user_add(&u);
}

//4.Fees/Fine Report
void payment_report()
{
    double total_pay = 0;
    FILE *fp;
    Payment p;
    date_t d1, d2;
	printf("Enter two dates between which you want to know the payment done.\n");
    printf("From ");
    date_accept(&d1);
    printf("To ");
    date_accept(&d2);

    fp = fopen(PAYMENT_DB, "rb");
    if (fp == NULL)
    {
        perror("Cannot open payment file.\n");
        return;
    }

    while (fread(&p, sizeof(Payment), 1, fp) > 0)
    {
        if ((date_cmp(d1, p.tran_time) <= 0) && (date_cmp(p.tran_time, d2) <= 0))
        {
            printf("Type : %s, Amount : %.2f\n", p.pay_type, p.amount);
            total_pay += p.amount;
        }
    }
    fclose(fp);
    printf("Total amount received : %.2lf\n", total_pay);
}
