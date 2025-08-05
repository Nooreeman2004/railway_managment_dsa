git init
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <stack>
#include <map>
#include <vector>
#include <sstream>
#include <climits>
#include <regex>

using namespace std;

// Structures
struct Reservation
{
	string trainId;
	int noOfSeats;
	string bookerName;
};

struct train
{
    string trainId, trainName, source, destination;
    int arrivalTime, departureTime, seats, cost, distance;
    train *next = NULL;
};
struct Feedback
{
	string userName;
	int rating;
	string comments;
};

struct TreeNode
{
    int cost;
    string trainId;
    string source; 
	string destination;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val, string id, string sc, string d) : cost(val), trainId(id), source(sc),destination(d), left(nullptr), right(nullptr) {}
};
struct ticket
{
	int ticketNo;
	string bookedTrainId, bookerName;
	int noOfSeats, bookedCost;
	train *bookedTrain = NULL;
	ticket *next = NULL;
};

struct User
{
	string email;
	string password;
	string username;
	User* next =NULL;
	User(const string& e, const string& p, const string& u) : email(e), password(p), username(u), next(nullptr) {}
};

//------------------------------------------------ DIJKSTRA GRAPH ALGORITHM ------------------------------------

int *route;
int *parent;
class Graph
{
public:
	int **edges;
	int n;
	int e;

	Graph()
	{

		this->n = 4;
		this->e = 6;
		edges = new int *[n];

		for (int i = 0; i < n; i++)
		{
			edges[i] = new int[n];
			for (int j = 0; j < n; j++)
			{
				edges[i][j];
			}
		}
	}

	Graph(int n, int e)
	{

		this->n = n;
		this->e = e;
		edges = new int *[n];

		for (int i = 0; i < n; i++)
		{
			edges[i] = new int[n];
			for (int j = 0; j < n; j++)
			{
				edges[i][j];
			}
		}
	}

	void addEdge(int f, int s, int weight)
	{

		edges[f][s] = weight;
	}

	void dijkstra(int srcIndex)
	{

		route = new int[n];
		parent = new int[n];
		bool *visited = new bool[n];

		for (int i = 0; i < n; i++)
		{
			route[i] = INT_MAX;
			visited[i] = false;
			parent[i] = -1;
		}

		route[srcIndex] = 0;
		parent[srcIndex] = -1;

		for (int i = 0; i < n - 1; i++)
		{

			int minVertex = findMinVertex(route, visited);
			visited[minVertex] = true;

			for (int j = 0; j < n; j++)
			{
				if (edges[minVertex][j] != 0 && !visited[j])
				{
					int dist = route[minVertex] + edges[minVertex][j];

					if (dist < route[j])
					{
						route[j] = dist;
						parent[j] = minVertex;
					}
				}
			}
		}
	}

	int findMinVertex(int *route, bool *visited)
	{

		int minVertex = -1;

		for (int i = 0; i < n; i++)
		{

			if (!visited[i] && (minVertex == -1 || route[i] < route[minVertex]))
			{
				minVertex = i;
			}
		}
		return minVertex;
	}
};
//-------------------------------------------------------------------------------------------------
// global variables
string currentUsername = "";
bool feedbackFlag = false;
//feedback stacks 
stack<int> feedbackNumbers;

//min and max
TreeNode* resultMin = nullptr;
TreeNode* resultMax = nullptr;

// user password
User *firstUser =NULL;
User *lastUser =NULL;
string username,password,email;
// VECTOR:
vector<string> cities;
vector<Reservation> reservations;
vector<Feedback> feedbackList;

// STACK:
stack<string> checkLastTrain;
stack<int> checkLastBooking;
// tree
TreeNode *costTree = NULL;

// TRAIN:
train *first = NULL;
train *last = NULL;

string trainId, trainName, source, destination;
int arrivalTime, departureTime, seats, cost, distanc;
bool isFound;

// TICKET:
ticket *ticketFirst = NULL;
ticket *ticketLast = NULL;

int ticketNo;
string bookedTrainId, bookerName;
int noOfSeats, bookedCost;

//-------------------------------------------------------------------------------------------------
// MENUS
void feedbackMenu();
void mainMenu();

void AdminLogin();
void AdminMenu();
void UserMenu();

//-------------------------------------------------------------------------------------------------
// user
void submitFeedback();
void searchByCost(TreeNode *root, int targetCost);
void displayYouTubeLink();
void searchTrainByDepartureTimeRange(train *node, int startTime, int endTime);
void cancelBooking(train *selectedTrain, int seatNumber);
void findAlternativeRoutes(Graph cityGraph, int srcIndex, int destIndex);
void findAlternativeRoutesInput(Graph cityGraph);
void viewFeedback();
string getInput(istream &input, const string &prompt);
bool isEmailTaken(const string &email);
void signUp(istream &input);
bool isValidUser(const string &email, const string &password);
void login(istream &input);
void user();
void readUsersFromFile();
void viewSystemInformation();
//-------------------------------------------------------------------------------------------------
// TRAIN FUNCTIONS:
void insertTrain(string, string, string, string, int, int, int, int, int);
void insertTrainMenu();
void display();
void searchTrainMenu();
train *searchTrainById(string);
void searchTrain(string, string);
void showRouteTrain(string, string);
void updateTrain();
void deleteTrain(string);
void readFromFile();
void writeToFile();

//-------------------------------------------------------------------------------------------------
// TICKET FUNCTIONS:
void insertTicket(int, string, string, int);
void bookTicketMenu();
void displayTickets();
void searchTicket();
void readTicketsFromFile();
void writeTicketsToFile();
void viewLatestBookingAndTrain();
void createGraph();
void minimumDistanceRoute(Graph, int, int);
void printPath(int *, int);
void searchTrainRoute(int *, int);

// -----------------------------------------Admin functions-----------------------------------------
void viewUserDetails();
int calculateTotalRevenue(ticket *ticketFirst);
void viewTransactionHistory();
void viewSystemLogs();
void manageUserAccounts();

//------------------------------------------------ MAIN -------------------------------------------
int main()
{
	cout<< "Hello";
	readFromFile();
	readTicketsFromFile();
	readUsersFromFile();
	// system("PAUSE");
	mainMenu();
}

//--------------------------------------------Main Menu---------------------------------------------
void mainMenu()
{
    char opt;

	system("CLS");
    do
    {
        system("Color 4F");
        int center = 50;
        cout << "\n";
        cout << setw(50) << "WELCOME TO RAILWAY MANAGEMENT SYSTEM\n\n\n";
        cout << setw(50) << "----------------------------------------------\n";
        cout << setw(50) << "| 1.  ADMIN                                   |\n";
        cout << setw(50) << "| 2.  USER                                    |\n";
        cout << setw(50) << "| 0.  EXIT                                    |\n";
        cout << setw(50) << "----------------------------------------------\n";
        cout << setw(50) << "\nEnter your choice: ";
        cin >> opt;
        cout << "\n";

        switch (opt)
        {
        case '1':
            AdminLogin();
            break;
        case '2':
            user();
            break;
        case '0':
            cout << "\nExiting Program byebye :)!";
			system("start explorer.exe Thank You.png");
            exit(0);
            break;
        default:
			system("CLS");
            cout << setw(45) << "Please Enter Correct Choice \n";
            break;
        }
    } while (opt != '0');
}


//--------------------------------------------admin ---------------------------------------------
void AdminLogin()
{
	string password;
	char x;

	cout << "Enter Password: ";
	cin >> password;

	if (password != "admin123")
	{
		cout << "\n";
		cout << setw(50) << "--------------------------------------\n";
		cout << setw(50) << "|  Wrong Password                    |\n";
		cout << setw(50) << "|  Do you want to try again (y/n)?   |\n";
		cout << setw(50) << "--------------------------------------\n";
		cin >> x;
		cout << "\n";

		if (x == 'y' || x == 'Y')
		{
			AdminLogin();
		}
		else
		{
			mainMenu();
		}
	}
	AdminMenu();
}
int calculateTotalRevenue(ticket *ticketFirst)
{
    int totalRevenue = 0;

    ticket *currentTicket = ticketFirst;
    while (currentTicket != NULL)
    {
        totalRevenue += currentTicket->bookedCost;
        currentTicket = currentTicket->next;
    }

    return totalRevenue;
}

void AdminMenu()
{
	int opt;
	system("CLS");
	system("Color 0A");

	int center = 50;
	cout << setw(center) << "____________ADMIN MENU_______________\n";
	cout << setw(center) << "_____________________________________\n";
	cout << setw(center) << "| 1. Insert Train                   |\n";
	cout << setw(center) << "| 2. View All Trains                |\n";
	cout << setw(center) << "| 3. Search Specific Train          |\n";
	cout << setw(center) << "| 4. Update Train DATA              |\n";
	cout << setw(center) << "| 5. Delete Specific Train          |\n";
	cout << setw(center) << "| 6. View All Tickets               |\n";
	cout << setw(center) << "| 7. Search Specific Ticket         |\n";
	cout << setw(center) << "| 8. View Recent Tickets And Trains |\n";	
	cout << setw(center) << "| 9. BackUp data to File            |\n";
	cout << setw(center) << "| 10. Calculate Revenue             |\n";
	cout << setw(center) << "| 0. LOG-OUT                        |\n";
	cout << setw(center) << "_____________________________________\n";
	cout << setw(15) << " "
		 << "Enter your choice: ";

	cin >> opt;
	cout << "\n";

	switch (opt)
	{
	case 1:
		insertTrainMenu();
		break;
	case 2:
		display();
		break;
	case 3:
		searchTrainMenu();
		system("PAUSE");
		break;
	case 4:
		updateTrain();
		break;
	case 5:
	{
		cout << "\n Enter Train number to delete: ";
		string del_val;
		cin >> del_val;
		deleteTrain(del_val);
		break;
	}
	case 6:
	{
		displayTickets();
		break;
	}
	case 7:
	{
		searchTicket();
		break;
	}
	case 8:
		viewLatestBookingAndTrain();
		break;
	case 9:
	{
		writeToFile();
		writeTicketsToFile();
		break;
	}
	case 10:
	{
	int totalRevenue = calculateTotalRevenue(ticketFirst);
    cout << "Total Revenue: " << totalRevenue << endl;
     system("pause");
		break;
	}
	case 0:
		cout << "\n\n";
		// cout << "Goodbye! Click the link below to view an image:\n";
		mainMenu();
		break;
	default:
		cout << "\n Please Enter Correct Choice ";
		AdminMenu();
		break;
	}
	AdminMenu();
}

string getInput(istream &input, const string &prompt)
{
	cout << prompt;
	string value;
	getline(input, value);
	return value;
}
string idTrack;
void insertTrain(string id, string name, string source, string destination, int arr, int dep, int seats, int cost, int distanc)
{

	train *curr = new train;

	curr->trainId = id;
	idTrack = id;
	curr->trainName = name;
	curr->source = source;
	curr->destination = destination;
	curr->arrivalTime = arr;
	curr->departureTime = dep;
	curr->seats = seats;
	curr->cost = cost;
	curr->distance = distanc;

	if (first == NULL)
	{
		first = last = curr;
	}
	else
	{
		last->next = curr;
		last = curr;
	}
}
//-----------------------insert train--------------------------------------
void insertTrainMenu()
{
	system("CLS");
	system("Color B5");

	cout << "\nEnter Train Id:";
	cin >> trainId;

	cout << "\nEnter Train Name:";
	cin >> trainName;

	cout << "\nEnter Train source:";
	cin >> source;

	cout << "\nEnter Train destination:";
	cin >> destination;

	cout << "\nEnter Train arrivalTime:";
	cin >> arrivalTime;

	cout << "\nEnter Train departureTime:";
	cin >> departureTime;

	cout << "\nEnter Train Available Seats:";
	cin >> seats;

	cout << "\nEnter Cost of a seat:";
	cin >> cost;

	cout << "\nEnter Distance between Cities(KM):";
	cin >> distanc;

	insertTrain(trainId, trainName, source, destination, arrivalTime, departureTime, seats, cost, distanc);
	cout << "\nInserted Train no:" << trainId << "\n\n";

	checkLastTrain.push(trainId);
	writeToFile();

	system("PAUSE");
}
void user()
{
	system("CLS");
	char choice;

	do
	{
		cout << "\n---------------------- ----\n";
		cout << "| 1. Sign Up                |\n";
		cout << "| 2. Login                  |\n";
		cout << "| 0. Exit                   |\n";
		cout << "-----------------------------\n";
		cout << "\nEnter your choice: ";
		cin >> choice;
		cin.ignore();

		switch (choice)
		{
		case '1':
			signUp(cin);
			break;
		case '2':
			login(cin);
			break;
		case '0':
			cout << "Exiting the program.\n";
			mainMenu();
		default:
			cout << "Invalid choice. Try again.\n";
			system("CLS");
		}
	} while (choice != '0');
}

void searchByCost(TreeNode *root, int targetCost)
{
	if (root == NULL)
	{
		cout << "Train with cost " << targetCost << " not found.\n";
		return;
	}

	if (targetCost == root->cost)
	{
		cout << "Train with cost " << targetCost << " found!\n";
		cout << "Train ID: " << root->trainId << "\n";

		char choice;
		cout << "Do you want to book this train? (y/n): ";
		cin >> choice;

		if (tolower(choice) == 'y')
		{
			bookTicketMenu();

			cout << "Booking confirmed!\n";
		}
		else
		{
			cout << "Booking canceled.\n";
		}
	}
	else if (targetCost < root->cost)
	{
		searchByCost(root->left, targetCost);
	}
	else
	{
		searchByCost(root->right, targetCost);
	}
}
//---------------------------------tree----------------------------------------------------------
void insertTrainIntoBST(TreeNode *&root, int cost, const string& trainID, const string& source, const string& dest)
{
    if (root == nullptr)
    {
        root = new TreeNode(cost, trainID, source, dest);
    }
    else if (cost < root->cost)
    {
        insertTrainIntoBST(root->left, cost, trainID, source, dest);
    }
    else
    {
        insertTrainIntoBST(root->right, cost, trainID, source, dest);
    }
}


TreeNode* findMinCostTrain(TreeNode* root, const string& source,const string& dest, int& minCost)
{
    if (root == nullptr)
    {
        return resultMin;
    }


    if (root->source == source && root->destination == dest && root->cost < minCost)
    {
        resultMin = root;
        minCost = root->cost;
    }

    TreeNode* leftResult = findMinCostTrain(root->left, source,dest, minCost);
    TreeNode* rightResult = findMinCostTrain(root->right, source,dest, minCost);

    if (leftResult != nullptr && leftResult->cost < minCost)
    {
        resultMin = leftResult;
        minCost = leftResult->cost;
    }

    if (rightResult != nullptr && rightResult->cost < minCost)
    {
        resultMin = rightResult;
        minCost = rightResult->cost;
    }

    return resultMin;
}

TreeNode* findMaxCostTrain(TreeNode* root, const string& source, const string& dest, int& maxCost)
{
    if (root == nullptr)
    {
        return resultMax;
    }

    if (root->source == source && root->destination == dest && root->cost > maxCost)
    {
        resultMax = root;
        maxCost = root->cost;
    }

    TreeNode* leftResult = findMaxCostTrain(root->left, source,dest, maxCost);
    TreeNode* rightResult = findMaxCostTrain(root->right, source,dest, maxCost);

    if (leftResult != nullptr && leftResult->cost > maxCost)
    {
        resultMax = leftResult;
        maxCost = leftResult->cost;
    }

    if (rightResult != nullptr && rightResult->cost > maxCost)
    {
        resultMax = rightResult;
        maxCost = rightResult->cost;
    }

    return resultMax;
}

void viewMinimumCostTrain(TreeNode* root)
{
    string source, destination;
    cout << "Enter source station: ";
    cin >> source;
    cout << "Enter destination station: ";
    cin >> destination;

    string route = source + "-" + destination;

    int minCost = INT_MAX;
    TreeNode *minCostTrain = findMinCostTrain(root, source, destination, minCost);
    if (minCostTrain != NULL)
    {
        cout << "Minimum cost train on route " << route << ": Train ID: " << minCostTrain->trainId << ", Cost: " << minCost << endl;
    }
    else
    {
        cout << "No trains available on route " << route << ".\n";
    }
}

void viewMaximumCostTrain(TreeNode* root)
{
    string source, destination;
    cout << "Enter source station: ";
    cin >> source;
    cout << "Enter destination station: ";
    cin >> destination;

    string route = source + "-" + destination;

    int maxCost = numeric_limits<int>::min();
    TreeNode *maxCostTrain = findMaxCostTrain(root, source, destination, maxCost);
    if (maxCostTrain != NULL)
    {
        cout << "Maximum cost train on route " << route << ": Train ID: " << maxCostTrain->trainId << ", Cost: " << maxCost << endl;
    }
    else
    {
        cout << "No trains available on route " << route << ".\n";
    }
}


//---------------------------sorted list-------------------------------------
void inOrderTraversal(TreeNode *root)
{
	if (root != NULL)
	{
		inOrderTraversal(root->left);
		cout << "Train ID: " << root->trainId << ", Cost: " << root->cost << endl;
		inOrderTraversal(root->right);
	}
}
void removeTicket(int ticketNumber)
{
	ticket *currentTicket = ticketFirst;
	ticket *prevTicket = NULL;

	while (currentTicket != NULL && currentTicket->ticketNo != ticketNumber)
	{
		prevTicket = currentTicket;
		currentTicket = currentTicket->next;
	}

	if (currentTicket == NULL)
	{
		cout << "Ticket not found.\n";
		return;
	}

	if (prevTicket == NULL)
	{
		ticketFirst = currentTicket->next;
	}
	else
	{

		prevTicket->next = currentTicket->next;
	}

	delete currentTicket;

	cout << "Ticket No." << ticketNumber << " removed successfully.\n";

}
ticket *searchTicketByNumber(int ticketNumber)
{
	ticket *currentTicket = ticketFirst;
	while (currentTicket != NULL)
	{
		if (currentTicket->ticketNo == ticketNumber)
		{

			cout<<currentTicket->ticketNo;
			system("PAUSE");
			return currentTicket;
		}
		currentTicket = currentTicket->next;
	}

	return NULL;
}

void cancelTicket(int ticketNumber)
{
	ticket *currentTicket = searchTicketByNumber(ticketNo);
	if (currentTicket == NULL)
	{
		cout << "Ticket not found.\n";
		return;
	}
	train *bookedTrain = currentTicket->bookedTrain;
	bookedTrain->seats += currentTicket->noOfSeats;
	
	cout << "\nCancelled Ticket No." << ticketNumber << " for Train " << currentTicket->bookedTrainId << "\n";
	cout << "Refund Amount: $" << currentTicket->bookedCost << "\n";
	removeTicket(ticketNumber);
	writeToFile();
	writeTicketsToFile();

	cout << "\nCancellation successful.\n";
	system("PAUSE");
}
void UserMenu()
{
    Graph graph;
    string optStr;
    int opt;
    system("CLS");
    system("Color F2");

    cout << "\n";
    int center = 65;

    cout << setw(center) << "WELCOME TO RAILWAY MANAGEMENT SYSTEM\n\n\n";
    cout << setw(center + 5) << "__________________USER MENU________________\n";
    cout << setw(center + 5) << "--------------------------------------------\n";
    cout << setw(center + 5) << "| Enter 1 to View Trains                   |\n";
    cout << setw(center + 5) << "| Enter 2 to Book Ticket                   |\n";
    cout << setw(center + 5) << "| Enter 3 to View Minimum Distance and Cost|\n";
    cout << setw(center + 5) << "| Enter 4 to view booking video            |\n";
    cout << setw(center + 5) << "| Enter 5 for feedback                     |\n";
    cout << setw(center + 5) << "| Enter 6 to view ticket                   |\n";
    cout << setw(center + 5) << "| Enter 7 to search by cost                |\n";
    cout << setw(center + 5) << "| Enter 8 to view Minimum Cost Train       |\n";
    cout << setw(center + 5) << "| Enter 9 to view Maximum Cost Train       |\n";
    cout << setw(center + 5) << "| Enter 10 for In-order Traversal          |\n";
    cout << setw(center + 5) << "| Enter 11 to cancel booking               |\n";
    cout << setw(center + 5) << "| Enter 0 to logout                        |\n";
    cout << setw(center + 5) << "-------------------------------------------\n\n";

    cout << setw(20) << " "
         << "Enter your choice: ";
    cin >> opt;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
        opt = 12;
    }
    stringstream(optStr) >> opt;
    cout << "\n";

    switch (opt)
    {
    case 1:
        display();
        break;
    case 2:
        bookTicketMenu();
        break;
    case 3:
        createGraph();
        break;
    case 4:
        displayYouTubeLink();
        break;
    case 5:
        feedbackMenu();
        break;
    case 6:
        displayTickets();
        break;
    case 7:
        int targetCost;
        cout << "\nEnter the amount you want to search for? ";
        cin >> targetCost;
        searchByCost(costTree, targetCost);
        system("PAUSE");
        break;
    case 8:
         viewMinimumCostTrain(costTree);
         system("PAUSE");
        break;
    case 9:
	viewMaximumCostTrain(costTree);
    system("PAUSE");
        break;
    case 10:
        inOrderTraversal(costTree);
        system("PAUSE");
        break;
    case 11:
        int ticketNumber;
        cout << "Enter ticket number?";
        cin >> ticketNumber;
        cancelTicket(ticketNumber);
        break;
     case 0:
        {
            cout << "Are you sure you want to log-out? (yes/no)" << endl;
            string response;
            cin >> response;

            if (response == "yes")
            {
                cout << "\nLogging out! Goodbye :)" << endl;
                return; 
            }
            else if (response == "no")
            {
                cout << "\nReturning to the main menu." << endl;
                return; 
            }
            else
            {
                cout << "\nInvalid response. Please enter 'yes' or 'no'." << endl;
                cin.clear();          
                cin.ignore(100, '\n'); 
            }
        }
        break; 

    default:
        cout << "\n Please enter a correct choice." << endl;
        break;
    }

    UserMenu();
	}

void insertUser(const string& email, const string& password, const string& username) {
        User* newUser = new User(email, password, username);
        newUser->next = firstUser;
        firstUser = newUser;
}


bool isEmailTaken(const string &email)
{
    User* current = firstUser;  
    while (current != nullptr)
    {
        if (current->email == email)
        {
            return true;
        }
        current = current->next;
    }

    return false;
}

void saveNewUsers(const string &filename)
{
    ofstream outputFile(filename);
    if (!outputFile.is_open())
    {
        cerr << "Error opening output file: " << filename << endl;
        return;
    }

    User* current = firstUser;  
	
    while (current != nullptr)
    {
        outputFile << current->email << "\n" << current->password << "\n" << current->username << endl;
        current = current->next;
    }

    outputFile.close();
}

bool isValidEmailFormat(const string &email)
{
    const regex emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return regex_match(email, emailRegex);
}
void signUp(istream &input)
{
	string email = getInput(input, "Enter your Email: ");
	while(!isValidEmailFormat(email)){
		cout<<"Invalid email format. Please enter a valid email address."<<endl;
		email = getInput(input, "Enter your Email (type 'exit' to quit): ");
		if(email == "exit"){
			mainMenu();
		}

	}
	while (isEmailTaken(email) )
	{
		cout << "Email is already taken. Try again.\n";
		email = getInput(input, "Enter your Email (type 'exit' to quit): ");
		if(email == "exit"){
			mainMenu();
		}
	}

	string password = getInput(input, "Create a Password: ");
	string name = getInput(input, "Enter your Name: ");
	insertUser(email,password,name);
	saveNewUsers("userCredentials.txt");

	cout << "Account created successfully!\n";
}


void readUsersFromFile(){
	ifstream inFile;
	inFile.open("userCredentials.txt");

	if (inFile.fail())
	{
		cerr << "Error Opeing File!\n";
		exit(1);
	}

	while (!inFile.eof())
	{
		inFile >> email;
		inFile >> password;
		inFile >> username;
		

		insertUser(email,password,username);
		// cout << "\nUser Inserted\n";
	}
	inFile.close();
}


bool isValidUser(const string& email, const string& password) {
	User* current = firstUser;
	
	while (current) {		
		if (current->email == email && current->password == password) {			

			if(currentUsername == current->username){
				feedbackFlag = true;
			}else{
				feedbackFlag = false;
			}
			currentUsername = current->username;
			return true;
		}
		current = current->next;
	}
	return false;
}
void login(istream &input)
{
	if(currentUsername.empty())
	email = getInput(input, "Enter your Email: ");
	password = getInput(input, "Enter your Password: ");
	
	if (isValidUser(email, password))
	{
		cout << "Logged in successfully as " << email << ".\n";
		
		UserMenu();
	}
	else
	{
		cout << "Invalid credentials. Login failed.\n";
	}
}

void viewSystemLogs()
{
	cout << "System Logs:\n";
}


//-------------------------------------------------FEEDBACK----------------------------------------------------------
void viewFeedback()
{
    system("CLS");
    system("Color B5");
    cout << "Feedback and Ratings:\n";

    while (!feedbackNumbers.empty())
    {
        int feedbackNumber = feedbackNumbers.top();
        feedbackNumbers.pop();

        cout << "Feedback Number: " << feedbackNumber << "\n";
    }

    for (size_t i = 0; i < feedbackList.size(); ++i)
    {
        const Feedback &feedback = feedbackList[i];
        cout << "User: " << feedback.userName << "\n";
        cout << "Rating: " << feedback.rating << "\n";
        cout << "Comments: " << feedback.comments << "\n\n";
    }

    system("PAUSE");
}

void feedbackMenu()
{
	char choice;
	system("CLS");
	system("Color 4B");

	do
	{
		cout << setw(20) << "Option" << setw(40) << "Menu"
			 << "\n";
		cout << setw(20) << "1" << setw(40) << "Submit Feedback"
			 << "\n";
		cout << setw(20) << "2" << setw(40) << "View Feedback"
			 << "\n";
		cout << setw(20) << "0" << setw(40) << "Exit"
			 << "\n";
		cout <<setw(20)<< "Enter your choice:\n ";

		cin >> choice;

		switch (choice)
		{
		case '1':
			submitFeedback();
			break;
		case '2':
			viewFeedback();
			break;
		case '0':
			cout << "Exiting the program.\n";
			break;
		default:
			system("CLS");
			cout << setw(20) << "Invalid choice. Try again.\n";
		}
		system("CLS");
	} while (choice != '0');
}
void submitFeedback()
{
	if(feedbackFlag){
		cout << "You have already submitted feedback. Thank you!\n";
		system("PAUSE");
        return;
	}
	Feedback newFeedback;
	system("CLS");
	system("Color 2B");

	cin.ignore();

	newFeedback.userName = currentUsername;
	cout<<setw(20)<<currentUsername<<" drop your Valueable Feedback:";
	cout << "Rate the service (1 to 5): ";

	do {
		cin >> newFeedback.rating;

		if (cin.fail() || newFeedback.rating < 1 || newFeedback.rating > 5) {
			cout << "Invalid rating. Please enter a rating between 1 and 5:\n";
			cin.clear();
			cin.ignore();

			newFeedback.rating = 0; 
		}
	} while (newFeedback.rating < 1 || newFeedback.rating > 5);

	cin.ignore();
	cout << "Enter your comments: ";
	getline(cin, newFeedback.comments);
	 feedbackNumbers.push(feedbackList.size());

	feedbackList.push_back(newFeedback);
	feedbackFlag = true;

	cout << "Thank you for your feedback!\n";
	system("PAUSE");

}

void displayYouTubeLink()
{
	cout << "\nWould you like to watch a video about booking? (y/n): ";
	char choice;
	cin >> choice;

	if (choice == 'y' || choice == 'Y')
	{
		cout << "\nOpening YouTube video...\n";

		const char *youtubeLink = "https://youtu.be/6qBTWBd7TGM?si=NyuiIj7JaWJx9n2L";

#ifdef _WIN32
		system(("start " + string(youtubeLink)).c_str());
#elif __APPLE__
		system(("open " + string(youtubeLink)).c_str());
#elif __linux__
		system(("xdg-open " + string(youtubeLink)).c_str());
#else
		cout << "Opening links not supported on this platform.\n";
#endif
	}
	else
	{
		cout << "\nYou chose not to watch the video.\n";
			system("PAUSE");
	}
}
void display()
{

	train *p;

	p = first;

	cout << setw(10) << "Train Id" << setw(20) << " Train Name" << setw(20) << "Train Source" << setw(20) << "Train Destination" << setw(20) << "Arrival Time" << setw(20) << "Departure Time" << setw(20) << "Available Seats" << setw(10) << "Cost" << setw(20) << "Distance";
	cout << "\n"
		 << setw(10) << "---------" << setw(20) << "-----------" << setw(20) << "-------------" << setw(20) << "------------------" << setw(20) << "-------------" << setw(20) << "---------------" << setw(20) << "----------------" << setw(10) << "------" << setw(20) << "------";

	if (first != NULL)
	{

		while (p != NULL)
		{

			cout << "\n\n";
			cout << setw(10) << p->trainId;
			cout << setw(20) << p->trainName;
			cout << setw(20) << p->source;
			cout << setw(20) << p->destination;
			cout << setw(20) << p->arrivalTime;
			cout << setw(20) << p->departureTime;
			cout << setw(15) << p->seats;
			cout << setw(15) << p->cost;
			cout << setw(15) << p->distance;

			p = p->next;
		}
		cout << "\n\n\n\n";
		system("PAUSE");
	}
	else
	{
		cout << "\n The list is EMPTY!\n\n";
		system("PAUSE");
	}
}

void searchTrainMenu()
{
	system("CLS");
	train *p1;
	p1 = first;
	cout<<setw(20)<<"Source"<<setw(30)<<"Destination\n\n";
	while(p1 != NULL){

		cout<<setw(20)<<p1->source<<setw(20)<<p1->destination<<endl;
		p1 = p1->next;
	}

	cout << "\nEnter Train source:";
	cin >> source;

	cout << "\nEnter Train destination:";
	cin >> destination;

	searchTrain(source, destination);
}

train *searchTrainById(string srchId)
{

	train *p;

	p = first;

	while (p != NULL)
	{

		if (p->trainId == srchId)
		{
			return p;
		}

		p = p->next;
	}
	return NULL;
}

void searchTrain(string trSource, string trDestination)
{

	train *p;
	p = first;

	isFound = false;

	cout << "\n";
	cout << setw(10) << "Train Id" << setw(20) << " Train Name" << setw(20) << "Train Source" << setw(20) << "Train Destination" << setw(20) << "Arrival Time" << setw(20) << "Departure Time" << setw(20) << "Available Seats" << setw(10) << "Cost" << setw(20) << "Distance";
	cout << "\n"
		 << setw(10) << "---------" << setw(20) << "-----------" << setw(20) << "-------------" << setw(20) << "------------------" << setw(20) << "-------------" << setw(20) << "---------------" << setw(20) << "----------------" << setw(10) << "------" << setw(20) << "------";

	if (first != NULL)
	{

		while (p != NULL)
		{

			if (p->source == trSource && p->destination == trDestination)
			{

				isFound = true;

				cout << "\n";
				cout << setw(10) << p->trainId;
				cout << setw(20) << p->trainName;
				cout << setw(20) << p->source;
				cout << setw(20) << p->destination;
				cout << setw(20) << p->arrivalTime;
				cout << setw(20) << p->departureTime;
				cout << setw(15) << p->seats;
				cout << setw(15) << p->cost;
				cout << setw(15) << p->distance;
			}

			p = p->next;
		}
		if (!isFound)
		{
			cout << "\n\nNO TRAIN AVAILABLE ON THIS SPECIFIC ROUTE!!";
		}
		cout << "\n\n";
	}
	else
	{
		cout << "\n The list is EMPTY!\n\n";
	}
}

void showRouteTrain(string trSource, string trDestination)
{

	train *p;

	p = first;

	if (first != NULL)
	{
		while (p != NULL)
		{

			if (p->source == trSource && p->destination == trDestination)
			{

				cout << "\n";
				cout << setw(10) << p->trainId;
				cout << setw(20) << p->trainName;
				cout << setw(20) << p->source;
				cout << setw(20) << p->destination;
				cout << setw(20) << p->arrivalTime;
				cout << setw(20) << p->departureTime;
				cout << setw(15) << p->seats;
				cout << setw(15) << p->cost;
				cout << setw(15) << p->distance;
			}

			p = p->next;
		}
		cout << "\n";
	}
	else
	{
		cout << "\n The list is EMPTY!\n\n";
	}
}

void updateTrain()
{
    string searchTrainId;
    cout << "\nEnter Train Id: ";
    cin >> searchTrainId;

    train* currTrain = searchTrainById(searchTrainId);

    if (currTrain == nullptr)
    {
        cout << "\nTrain Doesn't Exist!\n\n";
        system("PAUSE");
        return;
    }

    cin.ignore(); 

    cout << "\nEnter Train Name: ";
    getline(cin, trainName);

    cout << "\nEnter Train Source: ";
    getline(cin, source);

    cout << "\nEnter Train Destination: ";
    getline(cin, destination);

    cout << "\nEnter Train Arrival Time: ";
    cin >> arrivalTime;
	while(cin.fail()){
		cin.clear();
		cin.ignore();
		cout << "\nEnter Train Arrival Time: ";
    	cin >> arrivalTime;
	}

    cout << "\nEnter Train Departure Time: ";
	cin >> departureTime;
    while(cin.fail()){
		cin.clear();
		cin.ignore();
		cout << "\nEnter Train Departure Time: ";
    	cin >> departureTime;
	}

    cout << "\nEnter Train Available Seats: ";
    cin >> seats;
	while(cin.fail()){
		cin.clear();
		cin.ignore();
		cout << "\nEnter Train Available Seats: ";

    	cin >> seats;
	}
    cout << "\nEnter Cost of a Seat: ";
    cin >> cost;
	while(cin.fail()){
		cin.clear();
		cin.ignore();
		cout << "\nEnter Cost of a Seat: ";
    	cin >> cost;
	}
    cout << "\nEnter Distance between Cities (KM): ";
    cin >> distanc;
	while(cin.fail()){
		cin.clear();
		cin.ignore();
		cout << "\nEnter Distance between Cities (KM): ";
    	cin >> distanc;
	}
    currTrain->trainName = trainName;
    currTrain->source = source;
    currTrain->destination = destination;
    currTrain->arrivalTime = arrivalTime;
    currTrain->departureTime = departureTime;
    currTrain->seats = seats;
    currTrain->cost = cost;
    currTrain->distance = distanc;

    checkLastTrain.push(currTrain->trainId);

    writeToFile();
    cout << "\nTrain Updated Successfully!\n";
    system("PAUSE");
}


void deleteTrain(string val)
{

	train *p = first;
	train *p1;

	while (p != NULL && p->trainId != val)
	{
		p1 = p;
		p = p->next;
	}

	if (p == NULL)
	{
		cout << "\n Train No. " << val << " Doestnot Exists!\n\n";
		system("PAUSE");
		return;
	}

	p1->next = p->next;

	cout << "\n"
		 << p->trainId << " Deleted\n";

	delete p;

	system("PAUSE");
}


// TRAIN FILE READING:
void readFromFile()
{
	
	ifstream inFile;
	inFile.open("trains.txt");
	if (inFile.fail())
	{
		perror("Error Opening File");
		exit(1);
	}
	
    while (inFile >> trainId) {
        cout << "Reading trainId: " << trainId << endl;
		
        if (trainId == idTrack) {
            inFile.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
		inFile >> trainName;
		inFile >> source;
		inFile >> destination;
		inFile >> arrivalTime;
		inFile >> departureTime;
		inFile >> seats;
		inFile >> cost;
		inFile >> distanc;
		cout << "Inserted Train no:" << trainId << endl;
			insertTrainIntoBST(costTree, cost,trainId,source,destination);

		insertTrain(trainId, trainName, source, destination, arrivalTime, departureTime, seats, cost, distanc);
	
	}

	inFile.close();
}

// TRAIN FILE WRITING:
void writeToFile()
{

	train *p;
	p = first;

	ofstream outFile;
	outFile.open("t.txt");

	if (first != NULL)
	{
		while (p != NULL)
		{

			outFile << p->trainId << "\n";
			outFile << p->trainName << "\n";
			outFile << p->source << "\n";
			outFile << p->destination << "\n";
			outFile << p->arrivalTime << "\n";
			outFile << p->departureTime << "\n";
			outFile << p->seats << "\n";
			outFile << p->cost << "\n";
			outFile << p->distance << "\n\n";

			p = p->next;
		}
		cout << "\n DATA SAVED!\n\n";
	}
	else
	{
		cout << "\n The list is EMPTY!\n\n";
	}

	outFile.close();
}

//---------------------------------------------- TICKET FUNCTIONS ------------------------------------

void insertTicket(int srcTicketNo, string srcBookedTrainId, string srcBookerName, int srcNoOfSeats)
{

	ticket *curr = new ticket;

	curr->ticketNo = srcTicketNo;
	curr->bookedTrainId = srcBookedTrainId;
	curr->bookerName = srcBookerName;
	curr->noOfSeats = srcNoOfSeats;
	curr->bookedTrain = searchTrainById(srcBookedTrainId);
	curr->bookedCost = curr->bookedTrain->cost * curr->noOfSeats;

	if (ticketFirst == NULL)
	{
		ticketFirst = ticketLast = curr;
	}
	else
	{
		ticketLast->next = curr;
		ticketLast = curr;
	}
}
void displayReservations()
{
	cout << "Reservations:" << endl;
	for (size_t i = 0; i < reservations.size(); ++i)
	{
		const Reservation &reservation = reservations[i];
		cout << "Train ID: " << reservation.trainId << ", Seats: " << reservation.noOfSeats
			 << ", Booker Name: " << reservation.bookerName << endl;
	}
}

// check seat availability
bool checkSeatAvailability(train *selectedTrain, int requestedSeats)
{
	if (selectedTrain->seats >= requestedSeats)
	{
		cout << "\nSeats are available for booking.\n";
		return true;
	}
	else
	{
		cout << "\nSorry, there are not enough seats available for booking.\n";
		return false;
	}
}

void bookTicketMenu()
{
	searchTrainMenu();

	if (!isFound)
	{
		char idChoice;
		cout << "\n\nDo you want to search again (y/n): ";
		cin >> idChoice;

		if (idChoice != 'y' && idChoice != 'Y')
		{
			UserMenu();
		}
		else
		{
			bookTicketMenu();
		}
	}

	train *selectedTrain = NULL;
	do
	{
		cout << "\nEnter Train Id to Book: ";
		cin >> bookedTrainId;

		selectedTrain = searchTrainById(bookedTrainId);

		if (selectedTrain == NULL)
		{
			char idChoice;
			cout << "\nTrain Id does not exist.\n";
			cout << "\nDo you want to enter ID again (y/n): ";
			cin >> idChoice;

			if (idChoice != 'y' && idChoice != 'Y')
			{
				UserMenu();
			}
		}
	} while (selectedTrain == NULL);

	cout << "\n\n Booking " << selectedTrain->trainName << " From " << selectedTrain->source << " To " << selectedTrain->destination << "\n";

	cout << "\nEnter Number of Seats: ";
	cin >> noOfSeats;

	if (!checkSeatAvailability(selectedTrain, noOfSeats))
	{
		UserMenu();
	}

	cout << "\nEnter Booker Name: ";
	cin.ignore();
	getline(cin,bookerName);
	cout << "\nCONFIRM TICKET!\n";

	bookedCost = selectedTrain->cost * noOfSeats;

	char confirm;
	cout << "\nDo you confirm the ticket? (y/n): ";
	cin >> confirm;

	switch (confirm)
	{
	case 'y':
	{

		break;
	}
	case 'n':
	{
		UserMenu();
		break;
	}
	default:
	{
		mainMenu();
		break;
	}
	}

	if (ticketLast == NULL)
	{
		ticketNo = 1;
	}
	else
	{
		ticketNo = ticketLast->ticketNo + 1;
	}

	insertTicket(ticketNo, bookedTrainId, bookerName, noOfSeats);
	selectedTrain->seats -= noOfSeats;

	cout << "\n\nSuccessfully Booked Ticket No." << ticketNo << "\n\n";

	checkLastBooking.push(ticketNo);

	writeToFile();
	writeTicketsToFile();

	system("PAUSE");
}

// display ticket
void displayTickets()
{

	ticket *p;

	p = ticketFirst;

	if (first != NULL)
	{

		while (p != NULL)
		{

			cout << "\n";
			cout << setw(10) << "Ticket No.: " << p->ticketNo;
			cout << setw(30) << "Train No.: " << p->bookedTrainId;
			cout << setw(30) << "Train Name: " << p->bookedTrain->trainName;
			cout << setw(30) << "\n-------------------------------------------------------------------------------------------------------------------------";
			cout << setw(30) << "\nBookerName: " << p->bookerName;
			cout << setw(30) << "No. Of Seats: " << p->noOfSeats;
			cout << setw(30) << "Booked Cost: " << p->bookedCost;
			cout << setw(30) << "\nSource: " << p->bookedTrain->source;
			cout << setw(30) << "Destination: " << p->bookedTrain->destination;
			cout << setw(30) << "Arrival Time: " << p->bookedTrain->arrivalTime;
			cout << setw(30) << "Departure Time: " << p->bookedTrain->departureTime;

			p = p->next;
			cout << "\n\n";
		}
		cout << "\n\n\n\n";
		system("PAUSE");
	}
	else
	{
		cout << "\n No Tickets Booked Yet! \n\n";
		system("PAUSE");
	}
}

// search ticket
void searchTicket()
{

	int searchNo;

	cout << setw(10) << "Enter Ticket No.: ";
	cin >> searchNo;

	ticket *p;
	p = ticketFirst;

	bool found = false;

	if (first != NULL)
	{

		while (p != NULL)
		{
			if (p->ticketNo == searchNo)
			{

				cout << "\n";
				cout << setw(10) << "Ticket No.: " << p->ticketNo;
				cout << setw(30) << "Train No.: " << p->bookedTrainId;
				cout << setw(30) << "Train Name: " << p->bookedTrain->trainName;
				cout << setw(30) << "\n-------------------------------------------------------------------------------------------------------------------------";
				cout << setw(30) << "\nBookerName: " << p->bookerName;
				cout << setw(30) << "No. Of Seats: " << p->noOfSeats;
				cout << setw(30) << "Booked Cost: " << p->bookedCost;
				cout << setw(30) << "\nSource: " << p->bookedTrain->source;
				cout << setw(30) << "Destination: " << p->bookedTrain->destination;
				cout << setw(30) << "Arrival Time: " << p->bookedTrain->arrivalTime;
				cout << setw(30) << "Departure Time: " << p->bookedTrain->departureTime;
				cout << "\n\n";

				found = true;
				break;
			}

			p = p->next;
		}
		if (found == false)
		{
			cout << "\n No TICKET FOUND WITH THIS NUMBER!\n\n";
		}
		cout << "\n\n\n\n";
		system("PAUSE");
	}
	else
	{
		cout << "\n No Tickets Booked Yet! \n\n";
		system("PAUSE");
	}
}

// TICKET FILE READING:
void readTicketsFromFile()
{

	ifstream inFile;
	inFile.open("tickets.txt");

	if (inFile.fail())
	{
		cerr << "Error Opeing File!\n";
		exit(1);
	}

	while (!inFile.eof())
	{
		inFile >> ticketNo;
		inFile >> bookedTrainId;
		getline(inFile >> ws, bookerName);
		inFile >> noOfSeats;

		if (inFile.eof())
		{
			break;
		}

		insertTicket(ticketNo, bookedTrainId, bookerName, noOfSeats);
		// cout << "\nInserted ticketNo no:" << ticketNo << "\n";
	}

	inFile.close();
}

// TICKET FILE WRITING:
void writeTicketsToFile()
{

	ticket *p;

	p = ticketFirst;

	ofstream outFile;
	outFile.open("tickets.txt");

	if (first != NULL)
	{

		while (p != NULL)
		{
			outFile << p->ticketNo << "\n";
			outFile << p->bookedTrainId << "\n";
			outFile << p->bookerName << "\n";
			outFile << p->noOfSeats << "\n\n";

			p = p->next;
		}
		cout << "\n DATA SAVED!\n\n";
	}
	else
	{
		cout << "\n The list is EMPTY!\n\n";
	}

	outFile.close();
}

//------------------------------------------------GRAPH FUNCTIONS------------------------------------

void viewLatestBookingAndTrain()
{

	if (checkLastBooking.empty())
	{
		cout << "\nNo Recent Booking";
	}
	else
	{
		cout << "\nRecent Booking ID is: " << checkLastBooking.top();
	}

	cout << "\n";

	if (checkLastTrain.empty())
	{
		cout << "\nNo recent train inserted";
	}
	else
	{
		cout << "\nRecent Inserted Train: " << checkLastTrain.top();
	}

	cout << "\n\n";
	system("PAUSE");
}

bool isCityExists(string srcCity)
{

	for (int i = 0; i < cities.size(); i++)
	{
		if (cities[i] == srcCity)
		{
			return true;
		}
	}
	return false;
}

int returnCityIndex(string srcCity)
{

	for (int i = 0; i < cities.size(); i++)
	{
		if (cities[i] == srcCity)
		{
			return i;
		}
	}
	return -1;
}

// graph
void createGraph()
{

	int noOfEdges = 0;
	int noOfCities = 0;

	train *curr = first;

	while (curr != NULL)
	{

		if (curr == first)
		{
			cities.push_back(curr->source);
			cities.push_back(curr->destination);
		}
		else
		{
			if (!isCityExists(curr->source))
			{
				cities.push_back(curr->source);
			}
			if (!isCityExists(curr->destination))
			{
				cities.push_back(curr->destination);
			}
		}

		noOfEdges += 1;
		curr = curr->next;
	}

	noOfCities = cities.size();

	cout << "\n Current Cities are: ";
	for (int i = 0; i < noOfCities; i++)
	{
		cout << "(" << i << ") " << cities[i] << ", ";
	}

	curr = first;

	Graph distGraph(noOfCities, noOfEdges);
	Graph costGraph(noOfCities, noOfEdges);

	while (curr != NULL)
	{

		int src = returnCityIndex(curr->source);
		int dest = returnCityIndex(curr->destination);
		int routeDist = curr->distance;
		int routeCost = curr->cost;

		distGraph.addEdge(src, dest, routeDist);
		costGraph.addEdge(src, dest, routeCost);

		curr = curr->next;
	}

	int srcIndex;
	char choice;

	cout << "\n Enter Source station(Number): ";
	cin >> srcIndex;

	cout << "\n View Minimum Distance(d) / Cost(c): ";
	cin >> choice;

	if (choice == 'd' || choice == 'D')
	{
		cout << "\n\n";
		minimumDistanceRoute(distGraph, srcIndex, 1);
	}
	else if (choice == 'c' || choice == 'C')
	{
		cout << "\n\n";
		minimumDistanceRoute(costGraph, srcIndex, 2);
	}
	else
	{
		cout << "\nInvalid View Choice....\n";
	}

	cities.clear();
	system("PAUSE");
}

void printPath(int parentArray[], int j)
{

	if (parent[j] == -1)
	{
		return;
	}

	printPath(parentArray, parent[j]);
	cout << " -> " << cities[j];
}

void searchTrainRoute(int parentArray[], int j)
{

	string currCity = cities[j];
	if (parent[j] == -1)
	{
		return;
	}

	string pCity = cities[parent[j]];

	searchTrainRoute(parentArray, parent[j]);

	showRouteTrain(pCity, currCity);
}

// minimum distance of the route
void minimumDistanceRoute(Graph cityGraph, int srcIndex, int graphtype)
{

	cityGraph.dijkstra(srcIndex);

	cout << setw(20) << " "
		 << "**************************************************************\n";

	if (graphtype == 1)
	{
		cout << setw(20) << " "
			 << "The Minimum distance from " << cities[srcIndex] << " to different cities is:\n";
	}
	else
	{
		cout << setw(20) << " "
			 << "The Minimum Cost from " << cities[srcIndex] << " to different cities is:\n";
	}

	cout << setw(20) << " "
		 << "**************************************************************\n\n";

	for (int i = 0; i < cityGraph.n; i++)
	{

		if (srcIndex == i)
		{
			continue;
		}

		if (graphtype == 1)
		{

			cout << setw(20) << " " << cities[srcIndex] << " -> " << cities[i] << " ====> " << route[i] << " KM" << endl;

			cout << setw(20) << " "
				 << "Minimum Route is: " << cities[srcIndex];
			printPath(parent, i);

			cout << "\n\n";

			cout << setw(20) << " "
				 << "AVAILABLE TRAINS ON ROUTE: \n\n";

			cout << setw(5) << "Train Id" << setw(20) << " Train Name" << setw(20) << "Train Source" << setw(20) << "Train Destination" << setw(20) << "Arrival Time" << setw(20) << "Departure Time" << setw(20) << "Available Seats" << setw(10) << "Cost" << setw(15) << "Distance";
			cout << "\n"
				 << setw(10) << "---------" << setw(20) << "-----------" << setw(20) << "-------------" << setw(20) << "------------------" << setw(20) << "-------------" << setw(20) << "---------------" << setw(20) << "----------------" << setw(10) << "------" << setw(15) << "---------";

			searchTrainRoute(parent, i);

			cout << "\n\n\n";
		}
		else
		{

			cout << setw(20) << " " << cities[srcIndex] << " -> " << cities[i] << " ====> " << route[i] << " RS" << endl;

			cout << setw(20) << " "
				 << "Cheapest Route is: " << cities[srcIndex];
			printPath(parent, i);

			cout << "\n\n";

			cout << setw(20) << " "
				 << "AVAILABLE TRAINS ON ROUTE: \n\n";
			cout << setw(10) << "Train Id" << setw(20) << " Train Name" << setw(20) << "Train Source" << setw(20) << "Train Destination" << setw(20) << "Arrival Time" << setw(20) << "Departure Time" << setw(20) << "Available Seats" << setw(10) << "Cost" << setw(15) << "Distance";
			cout << "\n"
				 << setw(10) << "---------" << setw(20) << "-----------" << setw(20) << "-------------" << setw(20) << "------------------" << setw(20) << "-------------" << setw(20) << "---------------" << setw(20) << "----------------" << setw(10) << "------" << setw(15) << "---------";

			searchTrainRoute(parent, i);

			cout << "\n\n\n";
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------  END  ------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
