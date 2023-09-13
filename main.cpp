#include <mutex>
#include <iostream>
#include <thread>


namespace my
{
	class Data
	{
		private:
			std::mutex m_;
			int a_;

		public:

			Data(int a) : a_(a)
			{}

			~Data()
			{}
	}

  void swap(Data& A, Data& B)
  {
    
  }
}

int main()
{
	std::ios_base::sync_with_stdio(false);

	return 0;
}
