#include<stdint.h>
#include<stdio.h>
#include<string.h>
#include<string_view>
#include<vector>

static constexpr std::string_view msg{"Merry xmas"};
std::vector<size_t> hist{256,0};
static constexpr size_t hist_size {hist.capacity()};
static constexpr size_t TABLE_CAP{64};
std::vector<char> table{TABLE_CAP,0};
size_t table_size{0};
int main()
{ 
	auto msg_size = msg.size();
	for(auto i = 0; i < msg_size;i++){
		hist[msg[i]]++;
	}
}
