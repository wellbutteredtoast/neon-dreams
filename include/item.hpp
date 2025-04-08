#ifndef ITEM_HPP
#define ITEM_HPP

#include <vector>
#include <string>
#include <stdint.h>

using namespace std;

class Item {
	public:
		Item(int id, string asset, vector<string> info, vector<string> attrs);
		~Item();
		int item_id;
		string item_asset_path;
		vector<string> item_info;
		vector<string> attributes;

	private:

};

#endif // item.hpp
