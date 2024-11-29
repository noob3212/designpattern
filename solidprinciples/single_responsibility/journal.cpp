#include <iostream>
#include "boost/lexical_cast.hpp"
#include <string>
#include <vector>
#include <fstream>

/***
 * Idea of single responsibilty is class should have only reason to change.
 * Here in this example class Journal has one reason add.
 * If we add one more method save then there are two reasons for a class 
 * to change.
 *
 */

struct Journal{
	std::string title;
	std::vector<std::string> entries;

	explicit Journal(const std::string &title): title(title) {}
	void add(const std::string &entry);
	/*
	 * save is a problematic as per single responsibilty principle 
	 * A class should have only one reason to change .
	 * Suppose instead of saving on a file we want to save on cloud.
	 * Then our save method has to change  a lot of thing .
	 * Already we have a add function that requires to change a 
	 * lot of things when we suppose want to change entries with 
	 * timestamp.
	 * 
	 *
	 * void save(const std::string &filename);
	 * 
	 *
	 * */
	/*
	 * void save(const std::string &filename);
	 */
};

void Journal::add(const std::string &entry){

	static int count = 1;
	entries.push_back(boost::lexical_cast<std::string>(count++)+ ":" + entry);
}


/**
 * Moving this save to different class PersistanceManager
void Journal::save(const std::string &filename){

	ofstream ofs(filename);
	for(const auto &x: entries){
		ofs<< x<< endl;
	}
}

*/


struct PersistanceManager{
	static void save(const Journal &j , const std::string & filename){
		std::ofstream ofs(filename);
		for (auto &x: j.entries){
			ofs <<  x << std::endl;
		}
	}
};

int main(){
	Journal j{"Dear Diary"};
	j.add("I cried today");
	j.add("I ate a bug");

	PersistanceManager pm;
	pm.save(j,"save.txt");
}
