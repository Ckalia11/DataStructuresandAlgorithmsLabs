// Chetan Kalia 20771400
// Rodgrigo Elustondo 20737136

#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST
#include<iostream>
#include <vector>

#include "lab2_drones_manager.hpp"

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class DronesManagerTest {
public:
	// PURPOSE: New empty list is valid
	bool test1() {
		DronesManager manager;
		ASSERT_TRUE(manager.get_size() == 0)
		ASSERT_TRUE(manager.empty() == true)
		ASSERT_TRUE(manager.first == NULL)
		ASSERT_TRUE(manager.last == NULL)
	    return true;
	}
	
	// PURPOSE: insert_front() and insert_back() on zero-element list
	bool test2() {
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_back(DronesManager::DroneRecord(100));
	    
		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)
		ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last)
		ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last)
		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
		ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL)
		ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))	
	    return true;
	}
	
	// PURPOSE: select() and search() work properly
	bool test3() {
		DronesManager manager3, manager4;
		//test empty list
		ASSERT_TRUE(manager3.select(0).droneID == 0)
		ASSERT_TRUE(manager4.search(DronesManager::DroneRecord(100)) == 0)
		manager3.insert_front(DronesManager::DroneRecord(100));
		manager4.insert_front(DronesManager::DroneRecord(100));
		ASSERT_FALSE(manager3.select(0).droneID != manager4.select(0).droneID)
		ASSERT_TRUE(manager3.select(0).droneID == 100)
		ASSERT_TRUE(manager3.search(DronesManager::DroneRecord(100)) == manager4.search(DronesManager::DroneRecord(100)))
			// test invalid index
		ASSERT_TRUE(manager3.select(1).droneID == manager3.last->droneID)
		manager3.insert_front(DronesManager::DroneRecord(200));
		manager4.insert_front(DronesManager::DroneRecord(300));
		ASSERT_TRUE(manager3.select(0).droneID != manager4.select(0).droneID)
		// test value not found
		ASSERT_TRUE(manager3.search(DronesManager::DroneRecord(500)) == manager3.size)
		ASSERT_FALSE(manager4.search(DronesManager::DroneRecord(700)) != manager4.size)
		return true;
	}
	
	// PURPOSE: remove_front() and remove_back() on one-element list
	bool test4() {
		DronesManager manager5, manager6;
		//test empty list
		ASSERT_FALSE(manager5.remove_front() == true)
		manager5.insert_front(DronesManager::DroneRecord(100));
		manager5.remove_front();
		ASSERT_TRUE(manager5.first == NULL && manager5.first == manager5.last);
		ASSERT_TRUE(manager5.get_size() == 0);
		manager6.insert_front(DronesManager::DroneRecord(100));
		manager6.remove_back();
		ASSERT_TRUE(manager6.last == NULL && manager6.last == manager6.first);
		ASSERT_TRUE(manager6.get_size() == 0)
		ASSERT_TRUE(manager5.select(0).droneID == 0 && manager6.select(0).droneID == 0)
		return true;
	}
	
	// PURPOSE: replace() and reverse_list() work properly
	bool test5() {
		DronesManagerSorted manager7, manager8;
		//test empty list/ invalid rejection
		ASSERT_TRUE(manager7.reverse_list() == false && manager7.replace(0, DronesManager::DroneRecord(100)) == false)
		// test one element
		manager7.insert_front(DronesManager::DroneRecord(300));
		manager7.replace(0, DronesManager::DroneRecord(100));
		ASSERT_TRUE(manager7.get_size() == 1 && manager7.select(0).droneID == 100)
		manager7.reverse_list();	
		ASSERT_TRUE(manager7.reverse_list() == true)
		ASSERT_TRUE(manager7.first->prev == NULL && manager7.last->next == NULL)
		manager7.insert_front(DronesManager::DroneRecord(800));
		manager7.replace(1, DronesManager::DroneRecord(200));
		manager7.replace(0, DronesManager::DroneRecord(150));
		ASSERT_TRUE(manager7.select(1).droneID != 500 && manager7.select(1).droneID == 200 && manager7.select(0).droneID != manager7.select(1).droneID)
		//check if reverse list works well for lists with multiple elements
		for (int i = 0; i < manager7.get_size(); i++) {
			manager8.insert_back(DronesManager::DroneRecord(manager7.select(i)));
		}
		manager8.reverse_list();
		for (int i = 0; i < manager8.size; i++) {
			ASSERT_TRUE(manager8.select(i).droneID == manager7.select(manager7.get_size() - 1 - i).droneID)
		}
		return true;
	}
	
	// PURPOSE: insert_front() keeps moving elements forward
	bool test6() 	{
		DronesManager manager9;
		manager9.insert_front(DronesManager::DroneRecord(150));
		int num = 150;
		//check that index is increasing for ten iterations
		for (int i = 0; i < 10; i++) {
			int prev_index = manager9.search(DronesManager::DroneRecord(150));
			num = num + 50;
			manager9.insert_front(DronesManager::DroneRecord(num));
			ASSERT_TRUE(manager9.search(DronesManager::DroneRecord(150)) == prev_index + 1)
		}
		return true;
	}
	
	// PURPOSE: inserting at different positions in the list
	bool test7() {
		DronesManager manager10;
		//empty list and invalid index insertion
		ASSERT_TRUE(manager10.insert(DronesManager::DroneRecord(100), 0) == true && manager10.insert(DronesManager::DroneRecord(100), 1) == false)
		ASSERT_TRUE(manager10.get_size() == 1 && manager10.first != NULL && manager10.first == manager10.last)
		ASSERT_TRUE(manager10.first->prev == NULL && manager10.last->next == NULL)
		ASSERT_TRUE(manager10.insert(DronesManager::DroneRecord(200), manager10.get_size() - 1) == manager10.insert(DronesManager::DroneRecord(200), 0))
		ASSERT_TRUE(manager10.insert(DronesManager::DroneRecord(100), -1) == false && manager10.insert(DronesManager::DroneRecord(100), 3) == false)
		ASSERT_TRUE(manager10.select(0).droneID == 200 && manager10.select(0) == manager10.select(1) && manager10.select(2) == 100)
		return true;
	}
	
	// PURPOSE: try to remove too many elements, then add a few elements
	bool test8() {
		DronesManager manager11;
		int index = 50;
		for (int i = 0; i < 5; i++) {
			manager11.insert_back(DronesManager::DroneRecord(index + 50));
			index = index + 50;
		}
		for (int i = 0; i < 5; i++) {
			ASSERT_TRUE(manager11.remove_back() == true)
		}
		ASSERT_TRUE(manager11.remove_back() == false && manager11.remove_front() == false);
		return true;
	}
	
	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {
		DronesManager manager12;
		ASSERT_TRUE(manager12.insert(DronesManager::DroneRecord(100), 2) == false);
		ASSERT_TRUE(manager12.remove(0) == false);
		ASSERT_TRUE(manager12.insert(DronesManager::DroneRecord(100), 0) && manager12.insert_back(DronesManager::DroneRecord(200)) && manager12.insert_front(DronesManager::DroneRecord(150)))
		ASSERT_TRUE(manager12.remove(manager12.get_size() - 1) == true && manager12.select(0).droneID == 150);
		ASSERT_TRUE(manager12.insert(DronesManager::DroneRecord(200), 2) == false && manager12.insert(DronesManager::DroneRecord(300), 1) == true)
		ASSERT_TRUE(manager12.remove(1) && manager12.remove_front() && manager12.remove_back());
		ASSERT_TRUE(manager12.get_size() == 0)
		return true;
	}    
	
	// PURPOSE: inserts into an unsorted list, then sort the list
	bool test10() {
		DronesManagerSorted manager13, manager14;
		int counter = 100;
		manager13.insert_front(DronesManager::DroneRecord(500));
		manager13.insert_front(DronesManager::DroneRecord(200));
		manager13.insert_front(DronesManager::DroneRecord(600));
		manager13.insert_front(DronesManager::DroneRecord(100));
		manager13.insert_front(DronesManager::DroneRecord(300));
		manager13.insert_front(DronesManager::DroneRecord(900));
		for (int i = 0; i < manager13.get_size(); i++) {
			manager14.insert_front(manager13.select(i));
		}
		// check that it is not sorted
		ASSERT_FALSE(manager13.is_sorted_asc() || manager13.is_sorted_desc())
		ASSERT_FALSE(manager14.is_sorted_asc() || manager14.is_sorted_desc())
		manager13.sort_asc();
		ASSERT_TRUE(manager13.is_sorted_asc() == true)
		manager13.sort_desc();
		ASSERT_TRUE(manager13.is_sorted_desc() == true)
		return true;
	}  
	
	// PURPOSE: insert and remove into sorted manager in ascending order
	bool test11() {
		DronesManagerSorted manager15;
		int counter = 100;
		for (int i = 0; i < 10; i++) {
			manager15.insert_back(DronesManager::DroneRecord(counter));
			counter++;
		}
		ASSERT_TRUE(manager15.is_sorted_asc())
		manager15.insert_sorted_asc(DronesManager::DroneRecord(250));
		manager15.insert_sorted_asc(DronesManager::DroneRecord(320));
		manager15.insert_sorted_asc(DronesManager::DroneRecord(418));
		manager15.insert_sorted_asc(DronesManager::DroneRecord(765));
		ASSERT_TRUE(manager15.is_sorted_asc())
		// test elements larger than largest list value
		ASSERT_TRUE(manager15.insert_sorted_asc(DronesManager::DroneRecord(1050)));
		manager15.remove(2);
		manager15.remove_front();
		manager15.remove_back();
		manager15.remove(4);
		manager15.remove(5);
		manager15.remove(9);
		ASSERT_TRUE(manager15.is_sorted_asc())
		manager15.insert_sorted_asc(DronesManager::DroneRecord(95));
		manager15.insert_sorted_asc(DronesManager::DroneRecord(876));
		manager15.insert_sorted_asc(DronesManager::DroneRecord(233));
		manager15.insert_sorted_asc(DronesManager::DroneRecord(920));
		ASSERT_TRUE(manager15.is_sorted_asc())
		return true;
	}
	
	// PURPOSE: insert and remove into sorted manager in descending order
	bool test12() {
		DronesManagerSorted manager16;
		int counter = 100;
		for (int i = 0; i < 10; i++) {
			manager16.insert_front(DronesManager::DroneRecord(counter));
			counter++;
		}
		ASSERT_TRUE(manager16.is_sorted_desc())
		manager16.insert_sorted_desc(DronesManager::DroneRecord(250));
		manager16.insert_sorted_desc(DronesManager::DroneRecord(320));
		manager16.insert_sorted_desc(DronesManager::DroneRecord(418));
		manager16.insert_sorted_desc(DronesManager::DroneRecord(765));
		ASSERT_TRUE(manager16.is_sorted_desc())
		// test elements smaller than smallest list value
		ASSERT_TRUE(manager16.insert_sorted_desc(DronesManager::DroneRecord(80)));
		manager16.remove(2);
		manager16.remove_front();
		manager16.remove_back();
		manager16.remove(4);
		manager16.remove(5);
		manager16.remove(9);
		ASSERT_TRUE(manager16.is_sorted_desc())
		manager16.insert_sorted_desc(DronesManager::DroneRecord(95));
		manager16.insert_sorted_desc(DronesManager::DroneRecord(876));
		manager16.insert_sorted_desc(DronesManager::DroneRecord(233));
		manager16.insert_sorted_desc(DronesManager::DroneRecord(920));
		ASSERT_TRUE(manager16.is_sorted_desc())
		return true;
	}
};

#endif
