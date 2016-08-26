#ifndef MYSET_H
#define MYSET_H

#include <set>
#include <string>




template <class T>
class MySet : public std::set<T>
{
public:
  MySet();
  MySet set_intersection(const MySet& other);
  MySet set_union(const MySet& other);
};



template <class T>
MySet<T>::MySet() {}

template <class T>
MySet<T> MySet<T>::set_intersection(const MySet& other) {
	MySet<T> newSet;
	typename std::set<T>::iterator it;
	typename std::set<T>::iterator tor;

	for (it = other.begin(); it != other.end(); ++it) {
		for (tor = this->begin(); tor != this->end(); ++tor) {
			if (*it == *tor) newSet.insert(*it);
		}
	}
	return newSet;
}

template <class T>
MySet<T> MySet<T>::set_union(const MySet& other) {
	MySet<T> newSet;
	typename std::set<T>::iterator it;
	typename std::set<T>::iterator it2;

	for (it = this->begin(); it != this->end(); ++it) {
		newSet.insert(*it);
	}

	for (it2 = other.begin(); it2 != other.end(); ++it2) {
		newSet.insert(*it2);
	}

	return newSet;
}


#endif
