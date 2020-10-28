#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

void librarian_area(User *u) {
	int choice,memberid;
	char name[80];
	do {
		printf("\n\n1. Add member\n2. Edit Profile\n3. Change Password\n4. Add Book\n5. Find Book\n6. Edit Book\n7. Check Availability\n8. Add Copy\n9. Change Rack\n10. Issue Copy\n11. Return Copy\n12. Take Payment\n13. Payment History\n14.Display All Members\nEnter choice: ");
		scanf("%d", &choice);
		switch(choice) {
			case 1:
			       add_member();
				   break;
			case 2://Edit Profile
			       edit_profile(u);//func definition in common.c file
				   break;
			case 3://Change password
                   change_password(u);//func definition in common.c file
				   break;
			case 4://Add Book
			       add_book();
				   break;
			case 5:// Find Book
				   printf("Enter book name: ");
				   scanf("%s", name);
				   book_find_by_name(name);//func definition in common.c file
				   break;
			case 6://Edit Book
			       book_edit_by_id();
				   break;
			case 7://Check Availability
			       bookcopy_checkavail_details();//func definition in common.c file
				   break;
			case 8://Add Copy
			       bookcopy_add();
				   break;
			case 9://Change Rack
			       change_rack();//
				   break;
			case 10:// Issue Book Copy
				   bookcopy_issue();
				   break;
			case 11://Return Book Copy
			       bookcopy_return();
				   break;
			case 12://Take payment
			       take_fees_payment();
				   break;
			case 13://Payment History
			       printf("Enter Member Id of the member to search Payment history: ");
				   scanf("%d",&memberid);
			       payment_history(memberid);//func definition in common.c file
				   break;
		    case 14://Display All Members.
			       display_members();
				   break;
		}
		printf("\nPress 1 to Continue \nPress 0 to Sign out\n");
        scanf("%d",&choice);
	}while (choice);		
}

//1.Add Member
void add_member() {
	// input member details
	User u;
	user_accept(&u);
	// add librarian into the users file
	user_add(&u);

}



//4.Add book
void add_book() {
	FILE *fp;
	// input book details
	Book b;
	book_accept(&b);
	b.bid = get_next_book_id();
	// add book into the books file
	// open books file.
	fp = fopen(BOOK_DB, "ab");
	if(fp == NULL) {
		perror("cannot open books file");
		exit(1);
	}
	// append book to the file.
	fwrite(&b, sizeof(Book), 1, fp);
	printf("book added in file.\n");
	// close books file.
	fclose(fp);
}



//6.Edit Book
void book_edit_by_id() {
	int id, found = 0;
	FILE *fp;
	Book b;
	// input book id from user.
	printf("Enter book id: "); 
	scanf("%d", &id);
	// open books file
	fp = fopen(BOOK_DB, "rb+");
	if(fp == NULL) {
		perror("cannot open books file");
		exit(1);
	}
	// read books one by one and check if book with given id is found.
	while(fread(&b, sizeof(Book), 1, fp) > 0) {
		if(id == b.bid) {
			found = 1;
			break;
		}
	}
	// if found
	if(found) {
		// input new book details from user
		long size = sizeof(Book);
		Book nb;
		book_accept(&nb);
		nb.bid = b.bid;
		// take file position one record behind.
		fseek(fp, -size, SEEK_CUR);
		// overwrite book details into the file
		fwrite(&nb, size, 1, fp);
		printf("Book info updated.\n");
	}
	else // if not found
		// show message to user that book not found.
		printf("Book not found.\n");
	// close books file
	fclose(fp);
}







//8.Add BookCopy
void bookcopy_add() {
	FILE *fp;
	// input book copy details
	BookCopy b;
	bookcopy_accept(&b);
	b.cid = get_next_bookcopy_id();
	// add book copy into the books file
	// open book copies file.
	fp = fopen(BOOKCOPY_DB, "ab");
	if(fp == NULL) {
		perror("cannot open book copies file");
		exit(1);
	}
	// append book copy to the file.
	fwrite(&b, sizeof(BookCopy), 1, fp);
	printf("Book copy added in file.\n");
	// close book copies file.
	fclose(fp);
}

//9.Change Rack
void change_rack()
{
	int found = 0;
    BookCopy bc;
    FILE *fp;
	int rackno;
	int copyid;
	printf("Enter Copy Id of book whose rack is to be changed.\n");
	scanf("%d",&copyid);

    fp = fopen(BOOKCOPY_DB, "rb+");
    if (fp == NULL)
    {
        perror("Cannot open users file.\n");
        exit(1);
    }
    while (fread(&bc, sizeof(BookCopy), 1, fp) > 0)
    {
        if (bc.cid == copyid)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        long size = sizeof(BookCopy);

        printf("Enter new rack no. : ");
        scanf("%d",&rackno);
		bc.rack=rackno;
        fseek(fp, -size, SEEK_CUR);
        fwrite(&bc, sizeof(BookCopy), 1, fp);
        printf("Rack no. updated successfully.\n");
    }
    fclose(fp);
}


//10.Issue Book Copy
void bookcopy_issue() {
	int valid;
	IssueRecord rec;
	FILE *fp;
	// accept issuerecord details from user
	issuerecord_accept(&rec);
	// generate & assign new id for the issuerecord
	rec.iss_id = get_next_issuerecord_id();
	
	//TODO: if user is not paid, give error & return.
    valid = valid_member(rec.id, rec.iss_date);
    if (!valid)
	{
		printf("Membership not found.Please take the membership.");
        return;
	}
    
	// open issuerecord file
	fp = fopen(ISSUERECORD_DB, "ab");
	if(fp == NULL) {
		perror("Issuerecord file cannot be opened");
		exit(1);
	}
	// append record into the file
	fwrite(&rec, sizeof(IssueRecord), 1, fp);
	// close the file
	printf("Book copy issued.");
	fclose(fp);
	
	// mark the copy as issued
	bookcopy_changestatus(rec.cid, STATUS_ISSUED);
}
int valid_member(int member_id, date_t d)
{
    int found = 0;
    Payment p;
    FILE *fp;
	int i;
    fp = fopen(PAYMENT_DB, "rb");
    if (fp == NULL)
    {
        perror("Cannot open payment file.\n");
        return found;
    }
    while (fread(&p, sizeof(Payment), 1, fp) > 0)
    {   
		i=date_cmp(d,p.tran_time);            //Debug purpose(can be ignored)
		printf("Pay mem id:%d\n",p.memberid); //Debug prpose(can be ignored)
        printf("date diff:%d\n",i);           //Debug pupose(can be ignored)
        if (member_id == p.memberid && (i < MEMBERSHIP_MONTH_DAYS))
        {
            //printf("Please opt for membership, Cannot issue book.\n");
            found=1;
			return found;
        }		
    }
    //found = 1;
    return found;
}
void bookcopy_changestatus(int bookcopy_id, char status[]) {
	BookCopy bc;
	FILE *fp;
	long size = sizeof(BookCopy);
	// open book copies file
	fp = fopen(BOOKCOPY_DB, "rb+");
	if(fp == NULL) {
		perror("cannot open book copies file");
		return;
	}

	// read book copies one by one
	while(fread(&bc, sizeof(BookCopy), 1, fp) > 0) {
		// if bookcopy id is matching
		if(bookcopy_id == bc.cid) {
			// modify its status
			strcpy(bc.status, status);
			// go one record back
			fseek(fp, -size, SEEK_CUR);
			// overwrite the record into the file
			fwrite(&bc, sizeof(BookCopy), 1, fp);
			break;
		}
	}
	
	// close the file

	fclose(fp);

}



//11.Return Book Copy
void bookcopy_return() {
	int member_id, record_id;
	FILE *fp;
	IssueRecord rec;
	int diff_days, found = 0;
	long size = sizeof(IssueRecord);
	// input member id
	printf("Enter member id: ");
	scanf("%d", &member_id);
	// print all issued books (not returned yet)
	display_issued_bookcopies(member_id);
	// input issue record id to be returned.
	printf("\nEnter issue record id (to return): ");
	scanf("%d", &record_id);
	// open issuerecord file
	fp = fopen(ISSUERECORD_DB, "rb+");
	if(fp==NULL) {
		perror("cannot open issue record file");
		return;
	}
	// read records one by one
	while(fread(&rec, sizeof(IssueRecord), 1, fp) > 0) {
		// find issuerecord id
		if(record_id == rec.iss_id) {
			found = 1;
			// initialize return date
			//rec.r_date = date_current();
			printf("Enter return");
			date_accept(&rec.r_date);
			// check for the fine amount
			diff_days = date_cmp(rec.r_date, rec.r_duedate);
			// update fine amount if any
			if(diff_days > 0){
				rec.f_amount = diff_days * FINE_PER_DAY;
				fine_payment_add(rec.id, rec.f_amount);
				printf("Fine amount Rs. %d/- is applied.\n", rec.f_amount);
			}
			break;
		}
	}
	if(found) {
		// go one record back
		fseek(fp, -size, SEEK_CUR);
		// overwrite the issue record
		fwrite(&rec, sizeof(IssueRecord), 1, fp);
		// print updated issue record.
		printf("\nUpdated issue record after returning book(Bill for returned book):\n");
		issuerecord_display(&rec);
		// update copy status to available 
		bookcopy_changestatus(rec.cid, STATUS_AVAIL);
	}
	
	// close the file.
	fclose(fp);
}
void fine_payment_add(int memberid, float fine_amount) {
	FILE *fp;
	// initialize fine payment
	Payment pay;
	pay.pay_id = get_next_payment_id();
	pay.memberid = memberid;
	pay.amount = fine_amount;
	strcpy(pay.pay_type, PAY_TYPE_FINE);
	pay.tran_time = date_current();
	memset(&pay.nextpay_duedate, 0, sizeof(date_t));
	// open the file
	fp = fopen(PAYMENT_DB, "ab");
	if(fp == NULL) {
		perror("cannot open payment file");
		exit(1);
	}
	// append payment data at the end of file
	fwrite(&pay, sizeof(Payment), 1, fp);
	// close the file
	fclose(fp);
}



//12.Take payment
void take_fees_payment()
{
	FILE *fp;
	// input book details
	//Book b;
	Payment p;
	payment_accept(&p);
	//book_accept(&b);

	p.pay_id = get_next_payment_id();
	payment_display(&p);

	// add book into the books file
	// open books file.
	fp = fopen(PAYMENT_DB, "ab");
	if(fp == NULL) {
		perror("Payment File cannot be opened.");
		exit(1);
	}
	// append book to the file.
	fwrite(&p, sizeof(Payment), 1, fp);
	printf("Payment done successfully.\n");
	// close books file.
	fclose(fp);
}




//14.Display All Members.
void display_members()
{
	FILE *fp;
	int found = 0;
	User nu ;
	// open the file for reading the data
	fp = fopen(USER_DB, "rb");
	if(fp == NULL) {
		perror("Failed to open user file");
		return;
	}
	// read all books one by one
	while(fread(&nu, sizeof(User), 1, fp) > 0) 
		user_display(&nu);
	
	// close file
	fclose(fp);

}
