#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"


void user_accept(User *u) {
	//printf("\nUser id: ");
	//scanf("%d", &u->id);
	u->id = get_next_user_id();
	printf("Name: ");
	scanf("%s", u->name);
	printf("Phone no.: ");
	scanf("%s", u->phone);
	printf("Email: ");
	scanf("%s", u->email);
	printf("Password: ");
	scanf("%s", u->pwd);
	//if(strcmp(u->email, EMAIL_OWNER) == 0)
		//strcpy(u->role, ROLE_OWNER);
    //else
	    strcpy(u->role, ROLE_MEMBER);
}

void user_display(User *u) {
	printf("Id:%d\n",u->id);
	printf("Name: %s\n",u->name);
	printf("Email:%s\n",u->email);
	printf("Phone no.:%s\n",u->phone);
	printf("ROLE:%s\n",u->role);
	printf("\n");
}

void book_accept(Book *b) {
	//printf("Book id: ");
	//scanf("%d", &b->bid);
	printf("Book name: ");
	scanf("%s", b->bname);
	printf("Author: ");
	scanf("%s", b->author);
	printf("Book subject: ");
	scanf("%s", b->subject);
	printf("Price: ");
	scanf("%f", &b->price);
	printf("ISBN: ");
	scanf("%s", b->isbn);
}

void book_display(Book *b) {
	printf("Book Info.\n");
	printf("Id:%d\n",b->bid);
	printf("Name:%s\n",b->bname);
	printf("Author:%s\n",b->author);
	printf("Subject:%s\n",b->subject);
	printf("Price:%f\n",b->price);
	printf("ISBN:%s\n",b->isbn);
	printf("\n"); 
}

// bookcopy functions
void bookcopy_accept(BookCopy *c) {
	//printf("Copy id: ");
	//scanf("%d", &c->cid);
	printf("Book id: ");
	scanf("%d", &c->bid);
	printf("Rack no.: ");
	scanf("%d", &c->rack);
	strcpy(c->status, STATUS_AVAIL);
}

void bookcopy_display(BookCopy *c) {
	printf("Copy id:%d\n",c->cid);
	printf("Book id:%d\n",c->bid); 
	printf("Rack no.:%d\n",c->rack); 
	printf("Status:%s\n",c->status);
	printf("\n");
}

// issuerecord functions
void issuerecord_accept(IssueRecord *r) {
	//printf("Issue id: ");
	//scanf("%d", &r->iss_id);
	printf("Copy id: ");
	scanf("%d", &r->cid);
	printf("Member id: ");
	scanf("%d", &r->id);
	printf("Issue ");
	date_accept(&r->iss_date);
	//Take current date as issue date
	//r->issue_date = date_current(); 
	r->r_duedate = date_add(r->iss_date, BOOK_RETURN_DAYS);
	memset(&r->r_date, 0, sizeof(date_t));
	r->f_amount = 0.0;
}

void issuerecord_display(IssueRecord *r) {
	printf("\nIssue id: %d\n",r->iss_id) ;
	printf("Copy id: %d\n", r->cid);
	printf("Member id: %d\n", r->id);
	printf("Fine: %.2d\n",r->f_amount);
	printf("Issue date");
	date_display(&r->iss_date);
	printf("Return due_");
	date_display(&r->r_duedate);
	printf("Return ");
	date_display(&r->r_date);
	printf("\n");
}

// payment functions
void payment_accept(Payment *p) {
	//printf("Payment id: ");
	//scanf("%d", &p->pay_id);
	printf("Member id: ");
	scanf("%d", &p->memberid);
	fflush(stdin);
	//printf("Type (fees/fine): ");
	//scanf("%s", p->pay_type);
	strcpy(p->pay_type,PAY_TYPE_FEES);
	printf("Amount: ");
	scanf("%f", &p->amount);
	p->tran_time = date_current();
	//printf("Enter transaction ");  //manual entry check
    //date_accept(&p->tran_time);
	//if(strcmp(p->pay_type, PAY_TYPE_FEES) == 0)
		p->nextpay_duedate = date_add(p->tran_time, MEMBERSHIP_MONTH_DAYS);
	//else
	//	memset(&p->nextpay_duedate, 0, sizeof(date_t));
}

void payment_display(Payment *p) {
	printf("\nPayment id: %d\n",p->pay_id);
	printf("Member id: %d\n",p->memberid);
	printf("Amount: %f\n",p->amount);
	printf("Payment type(fees/fine): %s\n",p->pay_type);
	printf("Payment ");
	date_display(&p->tran_time);
	printf("Nextpayment_due");
	date_display(&p->nextpay_duedate);
	printf("\n");
}

int get_next_user_id() {
	FILE *fp;
	int max = 0;
	int size = sizeof(User);
	User u;
	// open the file
	fp = fopen(USER_DB, "rb");
	if(fp == NULL)
		return max + 1;
	// change file pos to the last record
	fseek(fp, -size, SEEK_END);
	// read the record from the file
	if(fread(&u, size, 1, fp) > 0)
		// if read is successful, get max (its) id
		max = u.id;
	// close the file
	fclose(fp);
	// return max + 1
	return max + 1;
}

int get_next_book_id() {
	FILE *fp;
	int max = 0;
	int size = sizeof(Book);
	Book u;
	// open the file
	fp = fopen(BOOK_DB, "rb");
	if(fp == NULL)
		return max + 1;
	// change file pos to the last record
	fseek(fp, -size, SEEK_END);
	// read the record from the file
	if(fread(&u, size, 1, fp) > 0)
		// if read is successful, get max (its) id
		max = u.bid;
	// close the file
	fclose(fp);
	// return max + 1
	return max + 1;
}

int get_next_bookcopy_id() {
	FILE *fp;
	int max = 0;
	int size = sizeof(BookCopy);
	BookCopy u;
	// open the file
	fp = fopen(BOOKCOPY_DB, "rb");
	if(fp == NULL)
		return max + 1;
	// change file pos to the last record
	fseek(fp, -size, SEEK_END);
	// read the record from the file
	if(fread(&u, size, 1, fp) > 0)
		// if read is successful, get max (its) id
		max = u.cid;
	// close the file
	fclose(fp);
	// return max + 1
	return max + 1;
}

int get_next_issuerecord_id() {
	FILE *fp;
	int max = 0;
	int size = sizeof(IssueRecord);
	IssueRecord u;
	// open the file
	fp = fopen(ISSUERECORD_DB, "rb");
	if(fp == NULL)
		return max + 1;
	// change file pos to the last record
	fseek(fp, -size, SEEK_END);
	// read the record from the file
	if(fread(&u, size, 1, fp) > 0)
		// if read is successful, get max (its) id
		max = u.id;
	// close the file
	fclose(fp);
	// return max + 1
	return max + 1;
}

int get_next_payment_id()
{
	FILE *fp;
	int max = 0;
	Payment p;
	int size = sizeof(Payment);
	// open the file
	fp = fopen(PAYMENT_DB, "rb");
	if(fp == NULL)
		return max + 1;
	// change file pos to the last record
	fseek(fp, -size, SEEK_END);
	// read the record from the file
	if(fread(&p, size, 1, fp) > 0)
		// if read is successful, get its max id
		max = p.pay_id;
	// close the file
	fclose(fp);
	// return max + 1
	return max + 1;
}


void user_add(User *u) {
	// open the file for appending the data
	FILE *fp;
	fp = fopen(USER_DB, "ab");
	if(fp == NULL) {
		perror("failed to open users file");
		return;
	}
	
	// write user data into the file
	fwrite(u, sizeof(User), 1, fp);
	printf("user added into file.\n");
	
	// close the file
	fclose(fp);
}

//librarian & member function
void book_find_by_name(char name[]) {
	FILE *fp;
	int found = 0;
	Book b;
	// open the file for reading the data
	fp = fopen(BOOK_DB, "rb");
	if(fp == NULL) {
		perror("failed to open books file");
		return;
	}
	// read all books one by one
	while(fread(&b, sizeof(Book), 1, fp) > 0) {
		// if book name is matching partially, found 1
		if(strstr(b.bname, name) != NULL) {
			found = 1;
			book_display(&b);
		}
	}
	// close file
	fclose(fp);
	if(!found)
		printf("No such book found.\n");
}


int user_find_by_email(User *u, char email[]) {
	FILE *fp;
	int found = 0;
	// open the file for reading the data
	fp = fopen(USER_DB, "rb");
	if(fp == NULL) {
		perror("failed to open users file");
		return found;
	}
	// read all users one by one
	while(fread(u, sizeof(User), 1, fp) > 0) {
		// if user email is matching, found 1
		if(strcmp(u->email, email) == 0) {
			found = 1;
			break;
		}
	}
	// close file
	fclose(fp);
	// return
	return found;
}


//librarian,owner & member function
void edit_profile(User *u)
{
    int found = 0;
    User o;
    FILE *fp;
    fp = fopen(USER_DB, "rb+");
    if (fp == NULL)
    {
        perror("Cannot open users file.\n");
        exit(1);
    }
    while (fread(&o, sizeof(User), 1, fp) > 0)
    {
        if (u->id == o.id)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        printf("Enter new email : ");
        scanf("%s", u->email);
        printf("Enter new phone no : ");
        scanf("%s", u->phone);
        long size = sizeof(User);
        fseek(fp, -size, SEEK_CUR);
        fwrite(u, sizeof(User), 1, fp);
        printf("Profile updated successfully.\n");
    }
    fclose(fp);
}

//librarian,owner & member function
void change_password(User *u)
{
    int found = 0;
    User o;
    FILE *fp;
    fp = fopen(USER_DB, "rb+");
    if (fp == NULL)
    {
        perror("Cannot open users file.\n");
        exit(1);
    }
    while (fread(&o, sizeof(User), 1, fp) > 0)
    {
        if (u->id == o.id)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        long size = sizeof(User);
        printf("Enter new password : ");
        scanf("%s", u->pwd);
        fseek(fp, -size, SEEK_CUR);
        fwrite(u, sizeof(User), 1, fp);
        printf("Password updated successfully.\n");
    }
    fclose(fp);
}

//librarian & member function
void payment_history(int memberid)
{   
	FILE *fp;
	Payment p;
    // open file
	fp = fopen(PAYMENT_DB, "rb");
	if(fp==NULL) {
		perror("cannot open payment file");
		return;
	}
	// read payment one by one till eof
	while(fread(&p, sizeof(Payment), 1, fp) > 0) {
		if(p.memberid == memberid)
			payment_display(&p);
	}
	// close file	
	fclose(fp);
}

//librarian and member function
void display_issued_bookcopies(int member_id) {
	int found=0;
	FILE *fp;
	IssueRecord rec;
	// open issue records file
	fp = fopen(ISSUERECORD_DB, "rb");
	if(fp==NULL) {
		perror("cannot open issue record file");
		return;
	}

	// read records one by one
	while(fread(&rec, sizeof(IssueRecord), 1, fp) > 0) {
		// if member_id is matching and return date is 0, print it.
		if(rec.id == member_id && rec.r_date.day == 0)
		{	found=1;
			issuerecord_display(&rec);
		}
	}

	if(!found)
	printf("No Book Copies cuurently issued.");
	
    // close the file
	fclose(fp);
}

//librarian & member functions
void bookcopy_checkavail_details() {
	int book_id;
	FILE *fp;
	BookCopy bc;
	int count = 0;
	// input book id
	printf("Enter the book id to check availability: ");
	scanf("%d", &book_id);
	// open book copies file
	fp = fopen(BOOKCOPY_DB, "rb");
	if(fp == NULL) {
		perror("cannot open bookcopies file.");
		return;
	}

	// read bookcopy records one by one
	while(fread(&bc, sizeof(BookCopy), 1, fp) > 0) {
		// if book id is matching and status is available, print copy details
		if(bc.bid == book_id && strcmp(bc.status, STATUS_AVAIL)==0) {
			bookcopy_display(&bc);
			count++;
		}
	}
	// close book copies file
	fclose(fp);
	// if no copy is available, print the message. 
	if(count == 0)
		printf("no copies availables.\n");
}