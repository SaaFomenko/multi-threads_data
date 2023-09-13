#include <chrono>
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

			Data(int a = 0) : a_(a)
			{}

			std::mutex& mutex()
			{
				return m_;
			}

			int get()
			{
				return a_;
			}

			void set(int a)
			{
				a_ = a;
			}

			~Data()
			{}
	};

  	void swap_lock(Data& A, Data& B)
  	{
		int temp = 0;

		A.mutex().lock();
		temp = A.get();
		A.set(B.get());
		A.mutex().unlock();

		B.mutex().lock();
		B.set(temp);
		B.mutex().unlock();
  	}

  	void swap_scoped_lock(Data& A, Data& B)
  	{
		int temp = 0;

		std::scoped_lock lk(A.mutex(), B.mutex());
		temp = A.get();
		A.set(B.get());

		B.set(temp);
  	}

  	void swap_unique_lock(Data& A, Data& B)
  	{
		int temp = 0;

		std::unique_lock la(A.mutex(), std::defer_lock);
		temp = A.get();
		A.set(B.get());

		std::unique_lock lb(B.mutex(), std::defer_lock);
		B.set(temp);

		std::lock(la, lb);
  	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);

	my::Data A(1);
	my::Data B(2);

	std::cout << "A = " << A.get() << '\n';
	std::cout << "B = " << B.get() << '\n';

	auto start = std::chrono::steady_clock::now();
	std::thread t(my::swap_lock, std::ref(A), std::ref(B)); // Best perfomance.
	//std::thread t(my::swap_scoped_lock, std::ref(A), std::ref(B));
	//std::thread t(my::swap_unique_lock, std::ref(A), std::ref(B));
	if (t.joinable())
		t.join();
	auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "Swap A, B\n";
	std::cout << "A = " << A.get() << '\n';
	std::cout << "B = " << B.get() << "\n\n";

	std::cout << "Performance: " << elapsed_seconds.count() << "s\n";

	return 0;
}
