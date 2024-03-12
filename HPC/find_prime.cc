/*
	** find_prime.cc
	** g++ find_prime.cc -ltbb -lrt -o find_prime
	** -ltbb for tbb library
	** -lrt for tbb::tick_count::now() using clock_gettime()
	*/
	#include<iostream>
	#include<tbb/tbb.h>
	using namespace std;
	using namespace tbb;

	int is_prime(int x)
	{
		int i;
		if (x <= 1) {		
			return 0;
		}
		for (i = 2; i * i <= x; ++i) {
			if (x % i == 0) {	
				return 0;
			}
		}
		return 1;
	}

	class FindPrime {
	 public:
		void operator() (const blocked_range < size_t > &r)const {
			for (size_t i = r.begin(); i != r.end(); ++i) {
				if (is_prime(i)) {
					cout << i << endl;
				}
			}
		}
	};

	int main(int argc, char *argv[])
	{
		size_t end = 10000;
		if (argc > 1 && atoi(argv[1]) > 0) {
			end = atoi(argv[1]);
		}
		parallel_for(blocked_range < size_t > (0, end), FindPrime());
		return 0;
	}