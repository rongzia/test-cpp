#include <iostream>
using namespace std;

class Query_thd {
public:
	void init(int thread_id);
	void * get_next_query();
	int q_idx;                          /// get_next_query() 每被调用一次，该值就增加 1
#if WORKLOAD == YCSB
	void * queries;
#else
	tpcc_query * queries;
#endif
	char pad[64 - sizeof(void *) - sizeof(int)];
    // drand48_data buffer;
};

int main() {

cout << "size of class: " << sizeof(Query_thd) << endl;
	return 0;
}