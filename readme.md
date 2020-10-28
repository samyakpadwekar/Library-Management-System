This Library Management System has three type of users:
o Owner
o Librarian
o User

#Owner
a.Owner owns library.
b.He is interested into tracking assets and revenue.
c.Owner Functionalities:
1. Appoint Librarian
2. Edit Profile
3. Change Password
4. Payment Report
5. Book Availability

#Librarian
a.Owner appoints a librarian for library management.
b.He handles all tasks including data entry, book issue, Payment Collection etc.
c.librarian Functionalities:
1. Add member
2. Edit Profile
3. Change Password
4. Add Book
5. Find Book
6. Edit Book
7. Check Availability
8. Add Copy
9. Change Rack
10. Issue Copy
11. Return Copy
12. Take Payment
13. Payment History
14.Display All Members

#Member
a.Members (reader) can find books and check availability.
b.Member Functionalities
1. Find Book
2. Edit Profile
3. Change Password
4. Book Availability
5. Issue Record.
6. Payment History


1.Each book can have multiple copies and organized into multiple racks.

2.Issue/return of individual copy is expected. For example, if “C Programming Language (by Ritchie)” (1 book id)have 10 copies(hence 10 copy id), each copy can be issued and returned independently.

3.Book can be issued if and only if user is paid user. Otherwise error message will be displayed. Payment of each user will be collected by Librarian on monthly basis.

4.Book is expected to return in 7 days. If delayed, fine of Rs. 5/- is applicable and should be taken by Librarian while returning book.