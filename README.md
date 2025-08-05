# 🚆 Railway Management System (DSA Project)

A console-based railway management system in C++ that manages train routes, ticket booking, cost estimation, and user/admin operations — powered by core Data Structures & Algorithms.


## 🎯 Objective

To build a fully functional railway management system using DSA concepts like:
- Linked Lists
- Graphs (Dijkstra, Prim)
- Binary Search Trees (BST)
- Stacks
- Arrays & Vectors
- File Handling
- Console-based GUI



## 🔐 Roles

### 👤 Admin
> Login with: `admin123`

**Features:**
- Add, view, update, delete trains
- Search specific train
- View & search all tickets
- View recent train/ticket additions (via stack)
- Backup data (file handling)
- Revenue calculation


### 🙋‍♂️ User
**Features:**
- Sign up & login (user authentication)
- View trains
- Book tickets
- View ticket
- View min distance & min cost between stations (Dijkstra + Prim)
- View min/max cost train (BST)
- Search by cost
- Cancel ticket
- View sorted train prices (inorder)
- Feedback system
- Watch booking tutorial video



## 🧠 Core DSA Concepts Used

| Concept             | Use Case                                           |
|---------------------|----------------------------------------------------|
| Linked List         | Managing train records                             |
| Stack               | Recent train/ticket additions                      |
| Binary Search Tree  | Searching & sorting train costs                    |
| Graphs              | Route cost/distance calculations                   |
| File Handling       | Persistent storage (users, trains, tickets)       |
| Vectors/Arrays      | Storing & processing collections of items          |
| Loops/Switches      | Menu navigation + CLI interactions                 |
| Error Handling      | Catching invalid input, edge cases                 |



## 💻 Console GUI Overview

- Menu-driven interface with login/register system
- Admin & User options displayed based on authentication
- All data stored in `.txt` files for persistence
- Clean CLI flow for booking, searching, and data visualization
