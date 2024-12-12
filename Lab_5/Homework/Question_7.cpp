//STT: 25
//Full name: Le Minh Sang
//Homework

//Question 7. Design an organizational chart using a tree structure where each node represents an employee
//and its children represent subordinates. Implement methods for adding/removing employees
//and displaying hierarchy.

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// Class to represent an employee node
class Employee {
public:
    string name;
    vector<Employee*> subordinates;

    Employee(string name) : name(name) {}
};

// Class for the organizational chart
class OrgChart {
private:
    Employee* root;
    unordered_map<string, Employee*> employeeMap;

    // Helper function to display the hierarchy recursively
    void displayHierarchy(Employee* node, int depth) {
        if (!node) return;
        cout << string(depth * 2, ' ') << node->name << endl;
        for (Employee* subordinate : node->subordinates) {
            displayHierarchy(subordinate, depth + 1);
        }
    }

    // Helper function to delete the subtree
    void deleteSubtree(Employee* node) {
        for (Employee* subordinate : node->subordinates) {
            deleteSubtree(subordinate);
        }
        delete node;
    }

public:
    OrgChart() : root(nullptr) {}

    ~OrgChart() {
        deleteSubtree(root);
    }

    // Add a new employee under a manager
    void addEmployee(const string& employeeName, const string& managerName = "") {
        Employee* employee = new Employee(employeeName);
        employeeMap[employeeName] = employee;

        if (managerName.empty()) {
            if (!root) {
                root = employee;
                cout << "Added " << employeeName << " as the root of the organization.\n";
            } else {
                cout << "Error: Root already exists.\n";
                delete employee;
            }
        } else {
            if (employeeMap.find(managerName) != employeeMap.end()) {
                Employee* manager = employeeMap[managerName];
                manager->subordinates.push_back(employee);
                cout << "Added " << employeeName << " under " << managerName << ".\n";
            } else {
                cout << "Error: Manager " << managerName << " not found.\n";
                delete employee;
            }
        }
    }

    // Remove an employee and their subtree
    void removeEmployee(const string& employeeName) {
        if (employeeMap.find(employeeName) == employeeMap.end()) {
            cout << "Error: Employee " << employeeName << " not found.\n";
            return;
        }

        Employee* employee = employeeMap[employeeName];

        // If the employee is the root, delete the whole tree
        if (employee == root) {
            deleteSubtree(root);
            root = nullptr;
            employeeMap.clear();
            cout << "Removed the entire organization.\n";
            return;
        }

        // Find the manager and remove the employee from their subordinates
        for (auto& pair : employeeMap) {
            Employee* manager = pair.second;
            auto it = find(manager->subordinates.begin(), manager->subordinates.end(), employee);
            if (it != manager->subordinates.end()) {
                manager->subordinates.erase(it);
                break;
            }
        }

        deleteSubtree(employee);
        employeeMap.erase(employeeName);
        cout << "Removed " << employeeName << " and their subordinates.\n";
    }

    // Display the organizational hierarchy
    void displayHierarchy() {
        if (!root) {
            cout << "The organization is empty.\n";
            return;
        }
        cout << "Organizational Hierarchy:\n";
        displayHierarchy(root, 0);
    }
};

// Main function to demonstrate the organizational chart
int main() {
    OrgChart org;

    // Add employees
    org.addEmployee("CEO");
    org.addEmployee("CTO", "CEO");
    org.addEmployee("CFO", "CEO");
    org.addEmployee("Engineer1", "CTO");
    org.addEmployee("Engineer2", "CTO");
    org.addEmployee("Accountant", "CFO");

    // Display hierarchy
    org.displayHierarchy();

    // Remove an employee
    org.removeEmployee("CTO");

    // Display hierarchy after removal
    org.displayHierarchy();

    return 0;
}
