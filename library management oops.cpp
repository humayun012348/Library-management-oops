// Online C++ compiler to run C++ program online
#include <algorithm>
#include <iostream>
#include <vector>
// USING C++ STL TO GET CURRENT AND DUE DATE
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;
string current_date() {
  // Get the current time
  std::time_t currentTime = std::time(nullptr);
  // Create a buffer to store the formatted date
  char buffer[80]; // Adjust the size based on your formatting needs
  // Format the date as a string
  std::strftime(buffer, sizeof(buffer), "%d-%m-%Y",
                std::localtime(&currentTime));
  return string(buffer);
}

// USING C++ LIBRARY TO GET NUMBER OF DAYS BETWEEN TWO DATES
int num_days(string date1_str, string date2_str) {
  // Convert strings to tm structures
  std::tm date1 = {};
  std::tm date2 = {};
  std::istringstream date1_stream(date1_str);
  std::istringstream date2_stream(date2_str);
  date1_stream >> std::get_time(&date1, "%d-%m-%Y");
  date2_stream >> std::get_time(&date2, "%d-%m-%Y");
  if (date1_stream.fail() || date2_stream.fail()) {
    std::cerr << "Error parsing dates." << std::endl;
    return 1;
  }
  // Convert tm structures to time_points
  auto time_point1 =
      std::chrono::system_clock::from_time_t(std::mktime(&date1));
  auto time_point2 =
      std::chrono::system_clock::from_time_t(std::mktime(&date2));
  // Calculate duration in days
  auto duration =
      std::chrono::duration_cast<std::chrono::hours>(time_point2 - time_point1);
  // Get the number of days
  int days = duration.count() / 24; // 1 day = 24 hours
  return days;
}

class Books {
public:
  string Title;
  string Author;
  int year_published;
  int available_copies;
  int total_copies;
  bool is_reserved = false;
  Books(string Title, string Author, int year_published, int available_copies,
        int total_copies) {
    this->Title = Title;
    this->Author = Author;
    this->year_published = year_published;
    this->available_copies = available_copies;
    this->total_copies = total_copies;
  }

public:
  void CheckOut(string name) {
    if (available_copies > 0 && is_reserved == false) {
    cout<<"\""<<this->Title <<"\""<< " "<< "Checked Out"<<endl;
      available_copies -= 1;
    } else if (available_copies > 0 && is_reserved == true) {
      cout <<"\""<<this->Title << "\""<<" IS RESERVED, CANNOT CHECK OUT" << endl;
      is_reserved = false;
    } else {
      cout << "Book Not Available" << endl;
    }
  }
  void CheckIn(string name) {
    if (available_copies < total_copies) {
    cout<<"\""<<this->Title <<"\""<<" "<<"CHECKED IN"<<endl;
      available_copies += 1;
    } else {
      cout << "BOOK IN EXCESS" << endl;
    }
  }
};

class LibraryPatron {

public:
  int patron_ID;
  string name;
  vector<pair<Books *, string>> CheckedOutBooks;
  LibraryPatron(int patron_ID, string name) {
    this->patron_ID = patron_ID;
    this->name = name;
  }

public:
  void CheckOutBook(Books *book, string date_CheckOut,string name_) {
    //   book here is pointer
    CheckedOutBooks.push_back({book, date_CheckOut});
    book->CheckOut(name_);
  }
  void CheckInBook(Books *book, string date_checkOut, string date_submission,string name_) {
    pair<Books *, string> target_pair = {book, date_checkOut};
    auto iter =
        std::find(CheckedOutBooks.begin(), CheckedOutBooks.end(), target_pair);
    if (iter != CheckedOutBooks.end()) {
      int days = num_days(date_checkOut, date_submission);
      if (days <= 15) {
        CheckedOutBooks.erase(iter);
        book->CheckIn(name_);
      } else {
        cout <<"\""<< book->Title<<"\""<<" "<<"crossed due date"
             << " : "
             << "IMPOSED FINE = " << (days - 15) * 5 << "$" << endl;
        CheckedOutBooks.erase(iter);
        book->CheckIn(name);
      }
    } else {
      cout << book->Title << " "
           << "WAS NEVER CHECKED OUT" << endl;
    }
  }
  //   in order to check names of book in checkes out list
  void checked_out_BookTitle() {
    for (int i = 0; i < CheckedOutBooks.size(); i++) {
      cout << CheckedOutBooks[i].first->Title << endl;
    }
  }
};

// LIBRARY TRANSACTION CLASS
class LibraryTransaction {
public:
  string patron_name;
  string book_name;
  string date;
  LibraryTransaction(LibraryPatron *patron, Books *book, string date) {
    this->patron_name = patron->name;
    this->book_name = book->Title;
    this->date = date;
  }
  void statement_CheckOut(Books *book) {
    cout <<"\""<< book->Title<<"\"" << " "
         << "was CHECKED OUT on"
         << " " << this->date <<" by "<<" patron "<<"\""<<patron_name<<"\""<< endl;
  }
  void statement_CheckIn(Books *book,string date_) {
    cout <<"\""<<book->Title<<"\""<< " "
         << "is "<<"CHECKED IN on"
         << " " << date_ <<" by "<<" patron "<<"\""<<patron_name<<"\""<< endl;
  }
};

class LibraryBranch {
public:
  Books *book_type;
  LibraryPatron *patron;

public:
  LibraryBranch(Books *book_type, LibraryPatron *patron) {
    this->book_type = book_type;
    this->patron = patron;
  }
};

class reservation_by_patrons {
public:
  Books *book;
  LibraryPatron *patron;

public:
  reservation_by_patrons(Books *book, LibraryPatron *patron) {
    this->book = book;
    this->patron = patron;
  }
  void reserve() {
    if (book->available_copies > 0) {
      cout <<"\""<< book->Title <<"\""<< " IS AVAILABLE, NO NEED TO RESERVE" << endl;
    } else {
      book->is_reserved = true;
      cout <<"\""<< book->Title<<"\""<< " "
           << "IS RESERVED BY " << patron->name << endl;
    }
  }
};
bool check_authenticity(string name,int roll_number){
    vector<pair<int,string>> studentsData = {
        {230000, "Humayun"},
        {230001, "Jane"},
        {230002, "Alice"},
        {230003, "Bob"},
        {230004, "Charlie"},
        {230005, "Emma"},
        {230006, "David"},
        {230007, "Eva"},
        {230008, "Sophia"},
        {230009, "Michael"},
        {230010, "Alex"},
        {230011, "Olivia"},
        {230012, "William"},
        {230013, "Grace"},
        {230014, "Daniel"},
        {230015, "Lily"},
        {230016, "Henry"},
        {230017, "Ava"},
        {230018, "Samuel"},
        {230019, "Sophie"},
        {230020, "Mason"},
        {230021, "Emily"},
        {230022, "Ethan"},
        {230023, "Isabella"},
        {230024, "Liam"},
        {230025, "Mia"},
        {230026, "Alexander"},
        {230027, "Aiden"},
        {230028, "Ella"},
        {230029, "Chloe"},
        {230030, "Logan"},
        {230031, "Grace"},
        {230032, "Sophie"},
        {230033, "Jackson"},
        {230034, "Avery"},
        {230035, "Lucas"},
        {230036, "Layla"},
        {230037, "Benjamin"},
        {230038, "Emma"},
        {230039, "Zoe"},
        {230040, "Caleb"},
        {230041, "Madison"},
        {230042, "Elijah"},
        {230043, "Abigail"},
        {230044, "Gabriel"},
        {230045, "Aria"},
        {230046, "Jackson"},
        {230047, "Scarlett"},
        {230048, "Nathan"},
        {230049, "Hannah"},
        {230050, "Isaac"},
        {230051, "Ava"},
        {230052, "Carter"},
        {230053, "Evelyn"},
        {230054, "Owen"},
        {230055, "Amelia"},
        {230056, "Wyatt"},
        {230057, "Victoria"},
        {230058, "Leo"},
        {230059, "Peyton"},
        {230060, "Mila"}};
    bool presence=false;
    for(int i=0;i<80;i++){
        pair<int ,string> expected_data={roll_number,name};
        if(expected_data==studentsData[i]){
            presence=true;
            break;
        }
    }
    return presence;
}
void check_out_book(LibraryBranch* type, Books* book_,string date){
    int roll_number;
    string name;
    cout<<"PLEASE ENTER YOUR ROLL NO. : ";
    cin>>roll_number;
    cout<<endl;
    cout<<"PLEASE ENTER YOUR NAME : ";
    cin>>name;
    cout<<endl;
    if(check_authenticity(name,roll_number)){
        type->patron->CheckOutBook(book_ , date,name);
        LibraryTransaction transaction(type->patron,book_,date);
        transaction.statement_CheckOut(book_);
    }
    else{
        cout<<"USER IS NOT AUTHENTICATED :("<<endl;
    }
}
void check_in_book(LibraryBranch* type, Books* book_,string date_CheckOut,string date_CheckIn){
    int copies = book_->available_copies;
    int roll_number_;
    string name_;
    cout<<"PLEASE ENTER YOUR ROLL NO. TO CHECK IN: ";
    cin>>roll_number_;
    cout<<endl;
    cout<<"PLEASE ENTER YOUR NAME TO CHECK IN : ";
    cin>>name_;
    cout<<endl;
    if(check_authenticity(name_,roll_number_)){
        type->patron->CheckInBook(book_, date_CheckOut, date_CheckIn,name_);
        if(copies<book_->available_copies){
            LibraryTransaction transaction2(type->patron,book_,date_CheckOut);
            transaction2.statement_CheckIn(book_,date_CheckIn);
        }
        cout<<"THANK YOU "<<name_<<" :)"<<endl;
    }
    else{
        cout<<"USER IS NOT AUTHENTICATED :("<<endl;
    }
}
int main() {
// CREATING BOOKS DATA
  LibraryPatron patron_comedy = {1011, "Alexa"};
Books book_comedy[10] = {
       {"Laugh Out Loud", "Jane Doe", 2010, 30, 50},
       {"Hilarious Times", "John Smith", 2015, 25, 40},
       {"Comic Relief", "Alice Johnson", 2012, 15, 30},
       {"Witty Jokes", "Bob Anderson", 2018, 20, 35},
       {"Giggle Fest", "Emily White", 2009, 10, 20},
       {"Funny Business", "Tom Brown", 2014, 18, 25},
       {"Humor Haven", "Sara Miller", 2017, 22, 40},
       {"Chuckling Charm", "Chris Taylor", 2011, 28, 45},
       {"Comedy Carousel", "David Clark", 2019, 12, 30},
       {"Jovial Tales", "Jessica Davis", 2016, 24, 38}};
  LibraryBranch comedy(book_comedy, &patron_comedy);
  LibraryPatron patron_horror = {1015, "Emily"};
  Books book_horror[10] = {
      {"The Haunting Shadows", "Michael Black", 2013, 15, 25},
      {"Eerie Encounters", "Emily Darkwood", 2016, 20, 30},
      {"Creepy Chronicles", "William Nightfall", 2011, 25, 40},
      {"Dreadful Whispers", "Sophia Graves", 2018, 12, 22},
      {"Chilling Secrets", "Thomas Raven", 2015, 18, 35},
      {"Sinister Silence", "Olivia Nightshade", 2012, 22, 40},
      {"Ghastly Tales", "Christopher Bloodworth", 2017, 10, 15},
      {"Fearful Fables", "Jessica Shadows", 2014, 30, 50},
      {"Nightmare Heights", "Daniel Haunt", 2019, 8, 18},
      {"Macabre Mysteries", "Alexandra Midnight", 2020, 25, 45}};
  LibraryBranch horror(book_horror, &patron_horror);
  LibraryPatron patron_romance = {1013, "Sarah"};
  Books book_romance[10] = {
      {"Love in Bloom", "Emma Rose", 2012, 20, 35},
      {"Hearts Entwined", "David Sparks", 2016, 15, 25},
      {"Passionate Promises", "Sophie Lovejoy", 2010, 25, 40},
      {"Eternal Embrace", "Ryan Evergreen", 2015, 18, 30},
      {"Sweet Serendipity", "Lily Harmony", 2018, 22, 38},
      {"Cupid's Arrow", "Alexandra Bliss", 2013, 12, 20},
      {"Enchanting Moments", "Oliver Moonlight", 2017, 28, 45},
      {"Romantic Rendezvous", "Isabella Dreamer", 2011, 30, 50},
      {"Whispers of Love", "Christopher Rosewood", 2014, 10, 15},
      {"Destined Hearts", "Madison Rivers", 2019, 24, 42}};
  LibraryBranch romance(book_romance, &patron_romance);

// checking if "reservation" is working properly
// ***************************************************************************
  for (int i = 0; i < 30; i++) {
    comedy.patron->CheckOutBook(&book_comedy[0], "10-03-2023","Humayun");
    cout << "AVAILABLE COPIES : " << comedy.book_type[0].available_copies
         << endl;
  }
  reservation_by_patrons reservation_1(&book_comedy[0], &patron_comedy);
  reservation_1.reserve();

  comedy.patron->CheckInBook(&book_comedy[0], "10-03-2023", "15-03-2023","Humayun");

  reservation_by_patrons reservation_2(&book_comedy[7], &patron_comedy);
  reservation_2.reserve();
//   to check it is not checking out a reserved book
  comedy.patron->CheckOutBook(&book_comedy[0], "10-03-2023","Humayun");
// to check it works normally when there is no reservation
  comedy.patron->CheckInBook(&book_comedy[0], "10-03-2023", "15-03-2023","Humayun");
  comedy.patron->CheckOutBook(&book_comedy[0], "10-03-2023","Humayun");


//   EXAMPLES : 
  horror.patron->CheckOutBook(&book_horror[6], "10-05-2023","Humayun");
  romance.patron->CheckOutBook(&book_romance[8], "18-03-2024","Humayun");

  horror.patron->CheckInBook(&book_horror[6], "10-05-2023", "15-03-2024","Humayun");
  romance.patron->CheckInBook(&book_romance[8], "18-03-2024", "15-04-2024","Humayun");
// ***************************************************************************
// THIS METHOD IS QUITE TOUGH TO WRITE EVERY TIME SO FOLLOW BELOW STEPS

// PROPER WAY :

// TO CHECK OUT A BOOK YOU WANT : FOLLOW THE STEPS :
// 1) GET THE "INDEX" OF THE BOOK FROM THE DATA
// 2) WRITE : check_out_book(&branch, &book_branch[index], "date of check out");
// date format example : "23-01-2024"

// TO CHECK IN A BOOK YOU HAVE : FOLLOW THE STEPS :
// 1) GET THE "INDEX" OF THE BOOK FROM THE DATA : INDEX = S.NO - 1
// 2) WRITE : check_in_book(&branch, &book_branch[index], "date of check out", "date of check in",your "name");

  check_out_book(&comedy, &book_comedy[6],"23-01-2024");
  check_out_book(&horror, &book_horror[7],"24-01-2024");
  check_in_book(&comedy, &book_comedy[6],"23-01-2024","30-03-2024");
  check_in_book(&horror, &book_horror[7],"24-01-2024","30-01-2024");
  return 0;
}

// showing demo output:

// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 29
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 28
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 27
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 26
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 25
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 24
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 23
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 22
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 21
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 20
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 19
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 18
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 17
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 16
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 15
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 14
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 13
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 12
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 11
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 10
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 9
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 8
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 7
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 6
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 5
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 4
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 3
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 2
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 1
// "Laugh Out Loud" Checked Out
// AVAILABLE COPIES : 0
// "Laugh Out Loud" IS RESERVED BY Alexa
// "Laugh Out Loud" CHECKED IN
// "Chuckling Charm" IS AVAILABLE, NO NEED TO RESERVE
// "Laugh Out Loud" IS RESERVED, CANNOT CHECK OUT
// "Laugh Out Loud" CHECKED IN
// "Laugh Out Loud" Checked Out
// "Ghastly Tales" Checked Out
// "Whispers of Love" Checked Out
// "Ghastly Tales" crossed due date : IMPOSED FINE = 1475$
// "Ghastly Tales" CHECKED IN
// "Whispers of Love" crossed due date : IMPOSED FINE = 65$
// "Whispers of Love" CHECKED IN
// PLEASE ENTER YOUR ROLL NO. : 230000
// PLEASE ENTER YOUR NAME : Humayun
// "Humor Haven" Checked Out
// "Humor Haven" was CHECKED OUT on 23-01-2024 by  patron "Alexa"
// PLEASE ENTER YOUR ROLL NO. : 230008
// PLEASE ENTER YOUR NAME : Sophia
// "Fearful Fables" Checked Out
// "Fearful Fables" was CHECKED OUT on 24-01-2024 by  patron "Emily"
// PLEASE ENTER YOUR ROLL NO. TO CHECK IN: 230000
// PLEASE ENTER YOUR NAME TO CHECK IN : Humayun
// "Humor Haven" crossed due date : IMPOSED FINE = 260$
// "Humor Haven" CHECKED IN
// "Humor Haven" is CHECKED IN on 30-03-2024 by  patron "Alexa"
// THANK YOU Humayun :)
// PLEASE ENTER YOUR ROLL NO. TO CHECK IN: 230008
// PLEASE ENTER YOUR NAME TO CHECK IN : Sophia
// "Fearful Fables" CHECKED IN
// "Fearful Fables" is CHECKED IN on 30-01-2024 by  patron "Emily"
// THANK YOU Sophia :)
