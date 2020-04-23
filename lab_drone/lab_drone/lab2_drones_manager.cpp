// Chetan Kalia 20771400
// Rodgrigo Elustondo 20737136

#include "lab2_drones_manager.hpp"

// TODO: Implement all of the listed functions below
#include <iostream>
using namespace std;

DronesManager::DronesManager() {
	first = NULL;
	last = NULL;
	size = 0;
}

DronesManager::~DronesManager() {
	if (first != NULL) {
		DroneRecord* current = first;
		while (current->next) {
			DroneRecord* temp = current->next;
			delete current;
			current = temp;
		}
		first = NULL;
		last = NULL;
	}
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
	//check if drone id of both objects are the same
	if (lhs.droneID == rhs.droneID) {
		return true;
	}
	return false;
}


unsigned int DronesManager::get_size() const {
	return size;
}

bool DronesManager::empty() const {
	if (!first) {
		return true;
	}
	return false;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	if (!first) {
		return DroneRecord(0);
	}
	if (index >= size && index != 0) {
		return *last;
	}
	DroneRecord* end = first;
	int pointer = 0;
	while (pointer != index) {
		if (end->next) {
			end = end->next;
		}
		else {
			return *last;
		}
		pointer++;
	}
	return *end;	
}

unsigned int DronesManager::search(DroneRecord value) const {
	DroneRecord* val = new DroneRecord(value);
	if (!first) {
		return 0;
	}
	DroneRecord* end = first;
	int index = 0;
	while (end->droneID != val->droneID) {
		if (end->next) {
			end = end->next;
		}
		else {
			return size;
		}
		index++;
	}
	return index;
}

void DronesManager::print() const {
	cout << "("; // print the header data
	DroneRecord* end = first; // initialize end pointer
	while (end) { // iterate until NULL
		cout << "[" << end->droneID << "]"; // print node
		end = end->next;
		if (end) // print -> symbol between nodes
			cout << "->";
	}
	cout << ")\n"; // print the footer data
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
	if (index >= size && index != 0) {
		return false;
	}
	if (!first || index == 0) {
		insert_front(value);
	}
	else {
		DroneRecord* end = first;
		DroneRecord* val = new DroneRecord(value);
		int pointer = 0;
		while (pointer != index) {
			if (end->next) {
				end = end->next;
			}
			else {
				return false;
			}
			pointer++;
		}
		end = end->prev;
		val->next = end->next;
		end->next = val;
		val->prev = end;
		end = end->next->next;
		if (!end->next) {
			last = end;
		}
		end->prev = val;
		size++;
	}
	return true;
	}

bool DronesManager::insert_front(DroneRecord value) {
	DroneRecord* val = new DroneRecord(value);
	if (!first) {
		// next and prev already set to NULL
		first = val;
		last = val;
		val->next = NULL;
		val->prev = NULL;
	}
	//one node
	else if (!first->next) {
		first->prev = val;
		val->next = first;
		val->prev = NULL;
		last = first;
		first = val;
	}
	else { // base case: list with more than one node
		first->prev = val;
		val->next = first;
		val->prev = NULL;
		first = val;
	}
	size++;
	return true;
}

bool DronesManager::insert_back(DroneRecord value) {
	DroneRecord* val = new DroneRecord(value);
	if (!first) {
		first = val;
		last = val;
	}
	//one node
	else if (!first->next) {
		last->next = val;
		val->prev = last;
		val->next = NULL;
		first = last;
		last = val;
	}
	else { // base case: list with more than one node
		last->next = val;
		val->prev = last;
		val->next = NULL;
		last = val;
	}
	size++;
	return true;
}

bool DronesManager::remove(unsigned int index) {
	if (!first) {
		return false;
	}
	if (index >= size && index != 0) {
		return false;
	}
	if (index == 0) {
		remove_front();
	}
	else if (index == size - 1) {
		remove_back();
	}
	else {
		int pointer = 0;
		DroneRecord* end = first;
		while (pointer != index) {
			if (end->next) {
				end = end->next;
			}
			else {
				return false;
			}
			pointer++;
		}
		DroneRecord* val_next = end->next;
		DroneRecord* val_prev = end->prev;
		end = end->prev;
		delete end->next;
		end->next = val_next;
		end = end->next;
		end->prev = val_prev;
		size--;
		}
	return true;
}

bool DronesManager::remove_front() {
	if (!first) {
		return false;
	}
	if (!first->next) {
		delete first;
		first = NULL;
		last = NULL;
	}
	else {
		first = first->next;
		delete first->prev;
		first->prev = NULL;
	}
	size--;
	return true;
}

bool DronesManager::remove_back() {
	if (!first) {
		return false;
	}
	if (!first->next) {
		delete first;
		first = NULL;
		last = NULL;
	}
	else {
		last = last->prev;
		delete last->next;
		last->next = NULL;
	}
	size--;
	return true;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
	if (!first) {
		return false;
	}
	if (index >= size && index != 0) {
		return false;
	}
	DroneRecord* val = new DroneRecord(value);
	if (index == 0) {
		//one element
		if (!first->next) {
			val->next = first->next;
			val->prev = NULL;
			first = val;
			last = val;
		}
		//more than one element
		else {
			val->next = first->next;
			val->prev = NULL;
			first = val;
		}
	}
	else if (index == size - 1) {
		//case of one element already handled above
		val->prev = last->prev;
		val->next = NULL;
		last = last->prev;
		last->next = val;
		last = val;
	}
	else {
		DroneRecord* end = first;
		int pointer = 0; 
		while (pointer != index) {
			if (end->next) {
				end = end->next;
			}
			else {
				return false;
			}
			pointer++;
		}
		val->next = end->next;
		end = end->prev;
		val->prev = end;
		end->next = val;
		end = end->next->next;
		end->prev = val;
	}
	return true;
}

bool DronesManager::reverse_list() {
	if (!first) {
		return false;
	}
	if (!first->next) {
		return true;
	}

	DroneRecord* end = first;

	while (end != NULL) {
		DroneRecord* temp = end->next;
		end->next = end->prev;
		end->prev = temp;

		if (temp == NULL) {
			last = first;
			first = end;
		}
		end = temp;
	}
	return true;
}

bool DronesManagerSorted::is_sorted_asc() const {
	DroneRecord* end = first;
	if (!first) {
		return false;
	}
	if (!first->next) {
		return true;
	}
	while (end->next) {
		DroneRecord* temp = end;
		end = end->next;
		if (end->droneID < temp->droneID) {
			return false;
		}
	}
	return true;
}

bool DronesManagerSorted::is_sorted_desc() const {
	DroneRecord* end = first;
	if (!first) {
		return false;
	}
	if (!first->next) {
		return true;
	}
	while (end->next) {
		DroneRecord* temp = end;
		end = end->next;
		if (end->droneID > temp->droneID) {
			return false;
		}
	}
	return true;
}

bool DronesManagerSorted::insert_sorted_asc(DroneRecord value) {
	DroneRecord* val = new DroneRecord(value);
	if (is_sorted_asc() == false) {
		return false;
	}
	if (val->droneID > last->droneID) {
		insert_back(*val);
	}
	else {
		DroneRecord* end = first;
		int pointer = 0;
		while (val->droneID >= end->droneID) {
			if (end->next) {
				end = end->next;
			}
			else {
				return false;
			}
			pointer++;
		}
		insert(*val, pointer);
	}
	return true;
}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord value) {
	DroneRecord* val = new DroneRecord(value);
	if (is_sorted_desc() == false) {
		return false;
	}
	if (val->droneID < last->droneID) {
		insert_back(*val);
	}
	else {
		DroneRecord* end = first;
		int pointer = 0;
		while (val->droneID <= end->droneID) {
			if (end->next) {
				end = end->next;
			}
			else {
				return false;
			}
			pointer++;
		}
		insert(value, pointer);
	}
	return true;
}

void DronesManagerSorted::sort_asc() {
	if (!first) {
		cout << "linked list is empty" << endl;
	}
	if (!first->next) {
		cout << "list has one item so it is already sorted" << endl;
	}

	DroneRecord* end;
	DroneRecord* end_1 = NULL;
	int swapped, i;

	do
	{
		swapped = 0;
		end = first;

		while (end->next != end_1)
		{
			if (end->droneID > end->next->droneID)
			{
				swap(end->droneID, end->next->droneID);
				swapped = 1;
			}
			end = end->next;
		}
		end_1 = end;
	} 
	
	while (swapped);
	
}
    
void DronesManagerSorted::sort_desc() {
	if (!first) {
		cout << "linked list is empty" << endl;
	}
	if (!first->next) {
		cout << "list has one item" << endl;
	}

	int swapped, i;
	DroneRecord* end;
	DroneRecord* end_1 = NULL;

	do
	{
		swapped = 0;
		end = first;

		while (end->next != end_1)
		{
			if (end->droneID < end->next->droneID)
			{
				swap(end->droneID, end->next->droneID);
				swapped = 1;
			}
			end = end->next;
		}
		end_1 = end;
	} 
	
	while (swapped);
}

