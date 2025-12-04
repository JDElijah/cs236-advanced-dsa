#pragma once
#include <vector> 
#include <functional>
#include <optional>

template <typename K, typename V> 
class SortedTableMap {
public: 
	// Entry Type
	struct Entry {
		K key; 
		V value; 
		Entry(const K& k, const V& v) : key(k), value(v) {}
	};

	// Type Aliases for readability
	using value_type = Entry; 
	using size_type = std::size_t; 
	using optional_value = std::optional<V>; 
	using const_entry_ptr = const Entry*; 
	using Comparator = std::function<bool(const K&, const K&)>; 
	using Table = std::vector<Entry>; 

private: 
	Table table; 
	Comparator comp;

public: 
	// Constructor 
	SortedTableMap() : comp(std::less<K>()) {}
	SortedTableMap(Comparator c) : comp(c) {}

	// size 
	size_type size() const { return table.size() }
	bool empty() const { return table.empty(); }

private: 
	
	// -----------------------------------------------------
	// Helper: Compare key with entry
	// Returns: 
	//	-1 if key < entry.key
	//	0 if key == entry.key
	//	+1 if key > entry.key
	// -----------------------------------------------------

	int compare(const K& key, const Entry& e) const {
		if (comp(key, e.key)) return -1;
		if (comp(e.key, key)) return 1; 
		return 0; // equal
	}

	// -----------------------------------------------------
	// Binary Search: return index where key should be or is
	// -----------------------------------------------------
	int ceilingIndex(const K& target) const {
		int low = 0; 
		int high = static_cast<int>(table.size() - 1);

		while (low < high) {
			int mid = (low + high) / 2; 
			int c = compare(target, table[mid]);

			if (c == 0)
				return mid;
			else if (c < 0)
				high = mid - 1;
			else
				low = mid + 1; 
		}
		return low; // insertion point 
	}

	//-----------------------------------------------------
	// Safe entry accessor (bounds checked) 
	// -----------------------------------------------------
	const_entry_ptr safeEntry(int i) const {
		if (i < 0 || i >= static_cast<int>(stable.size()))
			return nullptr; 
		return &table[i]; 
	}

};