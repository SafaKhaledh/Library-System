//============================================================================
// Name        : LibrarySystem.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;


const int MAX_BOOKS = 10;
const int MAX_USERS = 10;

struct book {
	int id;
	string name;
	int total_quantity;
	int total_borrowed;

	void read() {
		cout << "Enter book info: id & name & total quantity: ";
		cin >> id >> name >> total_quantity;

	}

	bool borrow() {
		if(total_quantity - total_borrowed == 0)
			return false;
		total_borrowed ++;
		return true;
	}

	void return_copy() { // possibilities
		assert(total_borrowed > 0);
		total_borrowed --;
	}

	bool has_prefix(string prefix) {// must have parameter
		if (name.size() < prefix.size())
			return false;
		for(int i = 0; i < (int)prefix.size(); ++i) {
			if(prefix[i] != name[i])
				return false;
		}
		return true;

	}
	void print() {
			cout << "id = " << id << " "<< "name = " << name << " " << "total quantity = " << total_quantity << " "
			     << "total borrowed = " << total_borrowed << " " << "\n";
		}
};

bool compare_id(book &book1, book &book2) {
	return book1.id < book2.id;
}

bool compare_name(book &book1, book &book2) {
	return book1.name < book2.name;
}

struct user {
	int id;
	string name;
	int num_borrowed;
	int borrowed_books_ids[MAX_BOOKS] = { }; // max number of books to borrow is 10! // link with book struct

	void read() {
		cout << "Enter user name & national id: ";
		cin >> name >> id;
	}

	void borrow(int book_id) {
		borrowed_books_ids[num_borrowed++] = book_id; // 2 changes

	}

	void return_copy(int book_id) { // 2 changes
		bool removed = false;
		for (int i = 0; i < num_borrowed; ++i) {
			if (borrowed_books_ids[i] == book_id) {
				for (int j = i + 1; j < num_borrowed ; ++j) // shift left to remove
					borrowed_books_ids[j - 1] = borrowed_books_ids[j];
				--num_borrowed;
				removed = true;
				break;
			}
		}

		if(!removed) // communication
			cout<< "User " << name << " never borrowed book id " << book_id << "\n";

  }

  bool is_borrowed(int book_id) {
	  for(int i = 0; i < num_borrowed; ++i)
		  if(book_id == borrowed_books_ids[i])
			  return true;
	  return false;
  }

  void print_borrowed_books_ids() { //?
  		for (int i = 0; i < num_borrowed; ++i) {
  			cout << borrowed_books_ids[i] << " ";
  		}
  		cout << "\n";
  	}

  	void print() { // will help us later in other methods
  		cout << "user " << name << " " << "id " << id << " "
  				<< "borrowed books ids: ";

  		print_borrowed_books_ids();
  	}
};


struct library_system {
	int total_books;
	book books[MAX_BOOKS];
	int total_users;
	user users[MAX_USERS];


	void run() {
			while(true) {
			int choice = menu();
			if (choice == 1)
				add_book();
			else if (choice == 2)
				search_books_by_prefix();
			else if (choice == 3)
				print_who_borrowed_book_by_name();
			else if (choice == 4)
				print_library_by_id();
			else if (choice == 5)
				print_library_by_name();
			else if (choice == 6)
				add_user();
			else if (choice == 7)
				user_borrow_book();
			else if (choice == 8)
				user_return_book();
			else if (choice == 9)
				print_users();
			else
				break;
		   }
	   }

	int menu() {
		int choice = -1;
		while(choice == -1){
			cout << "\nLibrary Menu;\n";
			cout << "1) add_book\n";
			cout << "2) search_books_by_prefix\n";
			cout << "3) print_who_borrowed_book_by_name\n";
			cout << "4) print_library_by_id\n";
			cout << "5) print_library_by_name\n";
			cout << "6) add_user\n";
			cout << "7) user_borrow_book\n";
			cout << "8) user_return_book\n";
			cout << "9) print_users\n";
			cout << "10) Exit\n";

			cout << "\nEnter your menu choice [1 - 10]: ";
			cin >> choice;
			if(!(1 <= choice && choice <= 10)) {
				cout << "Invalid choice. Try again\n";
				choice = -1;
		    }
		}
		return choice;
	}

	void add_book() {
		books[total_books++].read();
	}

	void search_books_by_prefix() {
		cout << "Enter book name prefix: "; // frontend
		string prefix;
		cin >> prefix;

		int cnt = 0;
		for(int i = 0; i < total_books; ++i) { // Abstraction level
			if(books[i].has_prefix(prefix))
				cout << books[i].name << "\n";
				cnt ++;
		}

		if(!cnt) // communication
			cout << "No books with such prefix\n"
	}

	void add_user() {
		users[total_users++].read();
	}

	int find_book_idx_by_name(string name) {
		for(int i = 0; i < total_books; ++i){
			if(books[i].name == name)
				return i;
		}
		return -1; // no books with such name
	}

	int find_user_idx_by_name(string name) {
		for(int i = 0; i < total_users; ++i){
			if(users[i].name == name)
				return i;
		}
		return -1; // no users with such name
	}

	bool read_user_name_and_book_name(int &user_idx, int &book_idx, int trials = 3){  // common utility
		string user_name, book_name;

		while(trials --) {
		cout << "Enter user name and book name: ";
		cin >> user_name >> book_name;

		user_idx = find_user_idx_by_name(user_name);
		if(user_idx == -1) {
			cout << "Invalid username. Try Again\n";
			continue;
		}

		book_idx = find_book_idx_by_name(user_name);
		if(user_idx == -1) {
			cout << "Invalid bookname. Try Again\n";
			continue;
		}
		return true;
	  }
	  cout << "You did several trials! Try later.";
	  return false;
	}

	void user_borrow_book() {
		int user_idx, book_idx;

		if(!read_user_name_and_book_name(user_idx, book_idx))
			return;

		int book_id = books[book_idx].id;
		int user_id = users[user_idx].id;

		if(!books[book_idx].borrow()) // communication
			cout << "No more copies available right now!\n";
		else
			users[user_idx].borrow(book_id); // for consistency
   }

   void user_return_book() {
	   int user_idx, book_idx;

		if(!read_user_name_and_book_name(user_idx, book_idx))
			return;

		int book_id = books[book_idx].id;
		books[book_idx].return_copy();
		users[user_idx].return_copy(book_id);
	}

	// call print book method many times based on the bookcase array size
	void print_library_by_id() {
		sort(books, books + total_books, compare_id);

		cout << "\n";
		for (int i = 0; i < total_books; ++i) {
			books[i].print();
		}
	}

	void print_library_by_name() {
		sort(books, books + total_books, compare_name);

		cout << "\n";
		for (int i = 0; i < total_books; ++i) {
			books[i].print();
		}
	}

	void print_who_borrowed_book_by_name() {
		string book_name;
		cout << "Enter book name: ";
		cin >> book_name; // frontend

		int book_idx = find_book_idx_by_name(book_name);

		if(book_idx == -1) { // probabilities and communicate the problem
			cout << "Invalid book name\n";
			return;
		}

		int book_id = books[book_idx].id;

		if(books[book_idx].total_borrowed == 0){
			cout << "No borrowed copies\n";
			return;
		}

		for (int i = 0; i < total_users; ++i) {
			if (users[i].is_borrowed(book_id))// fn instead of nested loop
				cout << users[i].name << "\n";

		}

	}

	void print_users() {
		cout << "\n";
		for (int i = 0; i < total_users; ++i)
			users[i].print();
	}

};

	int main() { // hide complexity of the system
		library_system library;
		library.run();
	}

//	return 0;

