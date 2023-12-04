#include <iostream>
#include <mutex>
#include <thread>

class Data
{
public:
	Data(int&& v, bool&& b, char&& ch) : val(v), b(b), ch(ch) {};
	Data(int& v, bool& b, char& ch) : val(v), b(b), ch(ch) {};
	~Data(){};
	std::mutex m;
	int val{ 0 };
	bool b{ false };
	char ch{ 0 };

private:
	

};

void swap(Data& d1, Data& d2)
{
	int tmp_val;
	bool tmp_b;
	char tmpchar;

	std::lock(d1.m, d2.m);
	tmp_val = d1.val;
	tmp_b = d1.b;
	tmpchar = d1.ch;

	d1.val = d2.val;
	d1.b = d2.b;
	d1.ch = d2.ch;
	d2.val = tmp_val;
	d2.b = tmp_b;
	d2.ch = tmpchar;

	d1.m.unlock();
	d2.m.unlock();
}

void swap1(Data& d1, Data& d2)
{
	int tmp_val;
	bool tmp_b;
	char tmpchar;

	std::scoped_lock scl(d1.m, d2.m);
	tmp_val = d1.val;
	tmp_b = d1.b;
	tmpchar = d1.ch;

	d1.val = d2.val;
	d1.b = d2.b;
	d1.ch = d2.ch;
	d2.val = tmp_val;
	d2.b = tmp_b;
	d2.ch = tmpchar;
}

void swap2(Data& d1, Data& d2)
{
	int tmp_val;
	bool tmp_b;
	char tmpchar;

	std::unique_lock ul(d2.m, std::defer_lock);
	std::unique_lock ul1(d1.m, std::defer_lock);
	tmp_val = d1.val;
	tmp_b = d1.b;
	tmpchar = d1.ch;

	d1.val = d2.val;
	d1.b = d2.b;
	d1.ch = d2.ch;
	d2.val = tmp_val;
	d2.b = tmp_b;
	d2.ch = tmpchar;
	std::lock(ul,ul1);
}

int main()
{
	Data dat1(1, false, 10 );
	Data dat2(2, true, 22);

	std::thread t1(swap, std::ref(dat1), std::ref(dat2));
	std::thread t2(swap, std::ref(dat1), std::ref(dat2));

	std::thread t3(swap1, std::ref(dat1), std::ref(dat2));
	std::thread t4(swap1, std::ref(dat1), std::ref(dat2));


	std::thread t5(swap2, std::ref(dat1), std::ref(dat2));
	std::thread t6(swap2, std::ref(dat1), std::ref(dat2));

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();

	return 0;
}
