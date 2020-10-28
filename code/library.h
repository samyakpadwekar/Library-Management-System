#ifndef _LIBRARY_H
#define _LIBRARY_H
#include <time.h>
#include "date.h"
 
#define USER_DB		    "users.db"
#define BOOK_DB         "books.db"
#define BOOKCOPY_DB	    "bookcopies.db"
#define ISSUERECORD_DB	"issuerecord.db"
#define PAYMENT_DB      "payment.db"

#define ROLE_OWNER 		"owner"
#define ROLE_LIBRARIAN 	"librarian"
#define ROLE_MEMBER 	"member"

#define STATUS_AVAIL	"available"
#define STATUS_ISSUED	"issued"

#define PAY_TYPE_FEES	"fees"
#define PAY_TYPE_FINE	"fine"

#define FINE_PER_DAY			5
#define BOOK_RETURN_DAYS		7
#define MEMBERSHIP_MONTH_DAYS	30

#define EMAIL_OWNER		"samyak@gmail.com"

typedef struct user {
    int id;
    char name[20];
    char email[30];
    char phone[15];
    char pwd[15];
    char role[10];
}User;

typedef struct book {
    int bid;
    char bname[30];
    char author[30];
    char subject[20];
    float price;
    char isbn[16];
}Book;

typedef struct bookcopy {
    int cid;
    int bid;
    int rack;
    char status[10];
}BookCopy;

typedef struct issuerecord {
    int iss_id;
    int cid;
    int id;
    date_t iss_date;
    date_t r_duedate;
    date_t r_date;
    int f_amount;
}IssueRecord;

typedef struct payment {
    int pay_id;
    int memberid;
    float amount;
    char pay_type[10];
    date_t tran_time;
    date_t nextpay_duedate;

}Payment;

// user functions
void user_accept(User *u);
void user_display(User *u);

// book functions
void book_accept(Book *b);
void book_display(Book *b);

// owner functions
void owner_area(User *u);
void appoint_librarian();
void payment_report();

// librarian functions
void librarian_area(User *u);
void add_member();
void add_book();
void book_edit_by_id();
void bookcopy_add();
void bookcopy_checkavail_details();
void bookcopy_issue();
int valid_member(int member_id, date_t d);
void bookcopy_changestatus(int bookcopy_id, char status[]);
void display_issued_bookcopies(int member_id);
void bookcopy_return();
void fine_payment_add(int memberid, float fine_amount);
void take_fees_payment();
int get_next_payment_id();
void payment_history(int memberid);
void display_members();
void change_rack();

// member functions
void member_area(User *u);
void bookcopy_checkavail();

// bookcopy functions
void bookcopy_accept(BookCopy *c);
void bookcopy_display(BookCopy *c);

// issuerecord functions
void issuerecord_accept(IssueRecord *r);
void issuerecord_display(IssueRecord *r);

// payment functions
void payment_accept(Payment *p);
void payment_display(Payment *p);

// common functions
void sign_in();
void sign_up();
void edit_profile(User *u);
void change_password(User *u);
int get_next_user_id();
int get_next_book_id();
int get_next_bookcopy_id();
int get_next_issuerecord_id();

void user_add(User *u);
int user_find_by_email(User *u, char email[]);
void book_find_by_name(char name[]);

void edit_profile(User *u);
void change_password(User *u);

void payment_history(int memberid);
void display_issued_bookcopies(int member_id);
void bookcopy_checkavail_details();
#endif

