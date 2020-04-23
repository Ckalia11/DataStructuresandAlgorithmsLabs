// Chetan Kalia 20771400
// Rodgrigo Elustondo 20737136

#ifndef DRONES_MANAGER_HPP
#define DRONES_MANAGER_HPP
#include <string>
using namespace std;

// Dronerecord * val = new DroneRecord(value);

// PURPOSE: Models a container that stores individual drone records
class DronesManager {
protected:
    // PURPOSE: Internal/private data structure that models a drone record
    struct DroneRecord {
    	// CONSTRUCTORS
    	// empty/default constructor
    	DroneRecord() : prev(NULL), next(NULL), droneID(0), range(0), yearBought(0) {}

    	// droneID-only constructor
    	DroneRecord(unsigned int newDroneID) : prev(NULL), next(NULL), 
			droneID(newDroneID), range(0), yearBought(0) {}
			
		// full parametric constructor
        DroneRecord(unsigned int newDroneID, unsigned int newRange,
			unsigned int newYearBought, string newDroneType,
			string newManufacturer, string newDescription, string newBatteryType) :
				prev(NULL), next(NULL), droneID(newDroneID), range(newRange), 
				yearBought(newYearBought), droneType(newDroneType),
				manufacturer(newManufacturer), description(newDescription), 
				batteryType(newBatteryType) {}

		// drone ID, range, and year bought stored as unsigned ints
        unsigned int droneID, range, yearBought;
        // drone type, manufacturer, description, and battery type stored as strings
		string droneType, manufacturer, description, batteryType;

		// pointers to the prev and next nodes
        DroneRecord* prev;
        DroneRecord* next;
    };
    
 	// PURPOSE: Optional helper method to get the DroneRecord pointer using drone index
	// this method will not be used in testing
    DroneRecord* getDroneRecord(unsigned int) const;

    // a pointer to the first node in the list
    DroneRecord* first;
    // a pointer to the last node in the list
    DroneRecord* last;
    // the number of elements in the list
    unsigned int size;    

    // copy constructor; not to be used for this assignment
    DronesManager(const DronesManager& rhs) {}
    // assignment operator; not to be used for this assignment
    DronesManager& operator=(const DronesManager& rhs) {}
    
public:
	// EXPLICIT CONSTRUCTOR AND DESTRUCTOR
	// PURPOSE: Creates a new empty DronesManager
	DronesManager();
	// PURPOSE: Destroys this instance and frees up all dynamically allocated memory
	~DronesManager();
	// PURPOSE: Comparison operator to compare two DroneRecord instances
	friend bool operator==(const DronesManager::DroneRecord& lhs, 
					const DronesManager::DroneRecord& rhs);
	// PURPOSE: Setup DronesManagerTest as friend so tests have access to private variables
	friend class DronesManagerTest;
	
	// ACCESSORS
	// PURPOSE: Returns the number of elements in the list
	unsigned int get_size() const;
	
	// PURPOSE: Checks if the list is empty; returns true if the list is empty, false otherwise
	bool empty() const;
	
	// PURPOSE: Returns the value at the given index in the list
	// if index is invalid, returns last element; if the list is empty, returns DroneRecord(0)	
	DroneRecord select(unsigned int index) const;
	
	// PURPOSE: Searches for the given value, and returns the index of this value if found	
	// if not found, returns the size of the list; if the list is empty, returns 0
	unsigned int search(DroneRecord val) const;
	
	// PURPOSE: Prints all the elements in the list to the console
	void print() const;
	
	// MUTATORS
	// PURPOSE: Inserts a value into the list at a given index; the list is not sorted
	// if the index is invalid, insertion is rejected
	bool insert(DroneRecord val, unsigned int index);
	
	// PURPOSE: Inserts a value at the beginning of the list; the list is not sorted
	bool insert_front(DroneRecord val);
	
	// PURPOSE: Inserts a value at the end of the list; the list is not sorted
	bool insert_back(DroneRecord val);
	
	// PURPOSE: Deletes a value from the list at the given index
	bool remove(unsigned int index);
	
	// PURPOSE: Deletes a value from the beginning of the list
	bool remove_front();
	
	// PURPOSE: Deletes a value at the end of the list
	bool remove_back();
	
	// PURPOSE: Replaces value at the given index with the given value; the list is not sorted	
	// if the index is invalid, replacement is rejected
	bool replace(unsigned int index, DroneRecord val);    
	
	// PURPOSE: Reverses the linked list
	bool reverse_list();
};

// PURPOSE: Allows record storage in sorted ascending or descending order based on drone ID value
class DronesManagerSorted : public DronesManager {	
public:
	// ACCESSORS
	// PURPOSE: Returns true if the list is sorted in ascending (non-descending) order
	bool is_sorted_asc() const;
	
	// PURPOSE: Returns true if the list is sorted in descending (non-ascending) order
	bool is_sorted_desc() const;
	
	// MUTATORS
	// PURPOSE: Inserts a value so that the list remains sorted in ascending order
	// if the list is not sorted in appropriate order, insertion is rejected
	bool insert_sorted_asc(DroneRecord val);
	
	// PURPOSE: Inserts a value so that the list remains sorted in descending order
	// if the list is not sorted in appropriate order, insertion is rejected
	bool insert_sorted_desc(DroneRecord val);
	
	// PURPOSE: Sorts the list into ascending (non-descending) order
	void sort_asc();
	
	// PURPOSE: Sorts the list into descending (non-ascending) order
	void sort_desc();
};
#endif 
