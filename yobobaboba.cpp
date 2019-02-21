/*Author: Jorge Moreno
  Date: 6/28/18
  Description: Customer reward system for yo boba boba©. */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
using namespace std;

const int SIZE = 5;  //Constant int used for dynamic array re-allocation

class customer  //Class for an individual customer
{
  private:
  string firstName;   //Holds customer's first name
  string lastName;   //Holds customer's last name
  string customerEmail;  //Holds customer's email address
  string phoneNum;  //Holds a customer's phone number
  int rewardsNum;  //Holds the number of customer rewards
  //int sandwhichRewards;
  //int drinkRewards;
  
  public:
  customer()  //constructor for customer class
  {
    rewardsNum = 0;  //Each new customer will have their rewards set to 0 automatically
  }
  string getFN()  //returns the customer's first name
  {
    return this->firstName;
  }
  string getLN()  //returns the customer's last name
  {
    return this->lastName;
  }
  string getEmail()  //returns customer's email address
  {
    return this->customerEmail;
  }
  string getPhoneN()   //returns the customer's phone number
  {
    return this->phoneNum;
  }
  int getRewardsN()  //returns the customer's rewards
  {
    return this->rewardsNum;
  }
  void add_info()  //Add a new customers information
  {
   cout << "Enter the customer's first name." << endl;
   cin >> firstName;
   cout << "Enter the customer's last name." << endl;
   cin >> lastName;
   cout << "Enter the customer's email address." << endl;
   cin >> customerEmail;
   cout << "Enter the customer's phone number." << endl;
   cin >> phoneNum;
  }
  void rewards()  //Increase a customers rewards and check if they have reached the max
  {
   rewardsNum++;
   if(rewardsNum == 5)
   {
     cout << "You win!" << endl;
     rewardsNum = 0;
   }
  }
  void save()  //Save all of the customer data to a file
  {
   ofstream save2;
   save2.open("customer_rewards.txt",ios_base::app);
   if(save2.fail())
   {
    cout << "Unable to save to file!" << endl;
    exit(EXIT_FAILURE);
   }
   save2 << firstName << " " << lastName << " " <<  customerEmail << " " << phoneNum << " " << rewardsNum << endl;
   save2.close();
  }
  void read(unsigned int &fileLine)  //Read in customers data from a file
  {
   ifstream read2;
   read2.open("customer_rewards.txt");
   if(read2.fail())
   {
    cout << "Unable to read file!" << endl;
    exit(EXIT_FAILURE);
   }
   char tempA[256];
   for(int i=0;i<fileLine;i++)
   {
     read2.getline(tempA,256);
     bzero(tempA,256);  //clear array
   }
   read2 >> firstName >> lastName >> customerEmail >> phoneNum >> rewardsNum;
   fileLine++;
   read2.close();
  }
};

class customer_collection  //Class for the collection of all customers
{
  private:
  customer *customers_list;  //Pointer of type customer for dynamic allocation of data
  int customerCount;  //Number of customers in the system
  int customerCap;   //The capacity of customers / size of table that will be increased when there is no free space
  
  public:
  customer_collection(int SIZE)  //constructor
  {
    customerCount = 0;
    customerCap = SIZE;
  }
  
  void addNewC(int size)
  {
    if(customerCount == 0)
    {
      customers_list = new customer[size];
    }
    else if(customerCount == customerCap)
    {
      customer *temp;
      temp = new customer[customerCap+size];
      for(int i=0;i<customerCount;i++)
      {
        temp[i] = customers_list[i];
      }
      delete[] customers_list;
      customers_list = temp;
      customerCap += size;
    }
    customers_list[customerCount].add_info();
    customerCount++;
  }
  void addRewards()
  {
    string tempPhone;
    bool check = false;
    while(check == false)
    {
      cout << "Enter customer's phone number." << endl;
      cin >> tempPhone;
      for(int i=0;i<customerCount;i++)
      {
        if(tempPhone == customers_list[i].getPhoneN())
        {
         customers_list[i].rewards();
         check = true;
         break;
        }
      }
      if(check == false)
      {
        cout << "Phone number is not in system!" << endl;
      }
    }
  }
  void printAll()
  {
    for(int i=0;i<customerCount;i++)
    {
     cout << "Customer's name: " << customers_list[i].getFN() << " " << customers_list[i].getLN() << endl;
     cout << "Customer's email: " << customers_list[i].getEmail() << endl;
     cout << "Customer's phone number: " << customers_list[i].getPhoneN() << endl;
     cout << "Rewards: " << customers_list[i].getRewardsN() << endl;
    }
  }
  
  int getCount()
  {
    return(customerCount);
  }
  int getCap()
  {
    return(customerCap);
  }
  void readCounts(unsigned int &fileLine)
  {
   ifstream read2;
   read2.open("customer_rewards.txt");
   read2 >> customerCount;
   cout << "Customer Count: " << customerCount << endl;
   read2 >> customerCap;
   cout << "Customer Cap: " << customerCap << endl;
   fileLine+=2;
   read2.close();
  }
  void allocate()
  {
    customers_list = new customer[customerCap];
  }
  void readInfo(unsigned int &fileLine)
  {
    for(int i=0;i<customerCount;i++)
    {
      customers_list[i].read(fileLine);
    }
  }
  void save_data()
  {
    for(int i=0;i<customerCount;i++)
    {
      customers_list[i].save();
    }
  }
  ~customer_collection()  //deconstructor
  {
    if(customerCount > 0)
    {
      delete[] customers_list;
    }
  }
};
int main()
{
  string fileCount;   //reads in the first information in customer_rewards file
  string fileCap;   //reads in the second information in customer_rewards file
  string fileFirstN;   //reads in the third information in customer_rewards file
  string fileLastN;
  string fileEmail;
  string filePhone;
  int fileRewards;   //reads in the fourth information in customer_rewards file
  int menuChoice;
  unsigned int fileLine = 0;
  
  customer_collection info(SIZE);
  ifstream read;  //to read in rewards file
  ofstream save;  //to save to rewards file
  
  read.open("customer_rewards.txt");  //open customer_rewards file
  if(read.fail())
  {
    cout << "Unable to open customer_rewards file!" << endl;
    exit(EXIT_FAILURE);
  }
  info.readCounts(fileLine);  //reads the customer count and capacity in file
  info.allocate();  //allocate dynamic memory with size of customer capacity
  cout << "Im here";
  info.readInfo(fileLine);  //read each of the customer's information and store
  while(1)
  {
    cout << "============================================" << endl;
    cout << "Please choose a menu option." << endl;
    cout << "1. Add a customer." << endl;
    cout << "2. Add rewards to a customer." << endl;
    cout << "3. Print a customer's information." << endl;
    cout << "4. Print a list of all customers." << endl;
    cout << "5. Exit program." << endl;
    cin >> menuChoice;
    cin.clear();
    cin.ignore(100,'\n');
    
    switch(menuChoice)
    {
      case 1:
        {
          info.addNewC(SIZE);
        }
      break;
      case 2:
        {
          info.addRewards();
        }
      break;
      case 3:
        {
         // info->printC();
        }
      break;
      case 4:
        {
         info.printAll();
        }
      break;
      case 5:
        {
         int count = info.getCount();
         int cap = info.getCap();
         save.open("customer_rewards.txt");
         if(save.fail())
         {
           cout << "Unable to save to file!" << endl;
           exit(EXIT_FAILURE);
         }
         save << count << endl;
         save << cap << endl;
         info.save_data();     
         cout << endl << "=======================" << endl;
         cout << "Have a nice day!" << endl;
         cout << "=======================" << endl;
         exit(1);
        }
      break;
      default:  //If something not on the menu is pressed.
        break;
    }
  }
  //close files here
  
  
  
  
  return 0;
}