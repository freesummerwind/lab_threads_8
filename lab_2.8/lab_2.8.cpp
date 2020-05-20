#include "lab_2.8.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

std::mutex MyMutex;

void maxElement(vector<int16_t>::iterator first, vector<int16_t>::iterator last, int16_t& res)
{
	while (first != last)
	{
		if (*first > res) res = *first;
		++first;
	}
	std::lock_guard<std::mutex> locked(MyMutex);
	cout << "Thread: " << std::this_thread::get_id() << "; max number: " << res << endl;
}

int main()
{
	vector<int16_t> arr(10000); // использую этот тип ради экономии памяти
	srand(time(0));
	for (int16_t& i : arr)
	{
		i = rand();
		i -= 16384;
	}
	int16_t m1, m2, m3, m4; 
	std::thread t1(maxElement, arr.begin(), arr.begin() + 2500, std::ref(m1)), 
		t2(maxElement, arr.begin() + 2500, arr.begin() + 5000, std::ref(m2)),
		t3(maxElement, arr.begin() + 5000, arr.begin() + 7500, std::ref(m3)),
		t4(maxElement, arr.begin() + 7500, arr.end(), std::ref(m4));
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	cout << "\nMaximum number in array: " << 
		std::max(std::max(m1, m2), std::max(m3, m4)) << endl;
	return 0;
}
