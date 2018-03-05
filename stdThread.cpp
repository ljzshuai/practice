#include <thread>
#include <string>
#include <future>
#include <iostream>

/*
  std::future<int> result1(std::async(fun,1,2));
  绑定一个函数在调用result1.get()获取结果之前尽可能的被异步执行(分离线程)完毕

  std::future<int> result1(std std::async(std::launch::async,fun,1,2)); 强制异步
  如果强制异步了，即使future到了result1到了生命周期程序也会堵塞的等待异步 函数完成

  std::future<int> result1(std std::async(std::launch::deferred,fun,1,2)); 
  不调用get 绝不启动

  出现异常会保存着 直到调用get
  get只能调用一次 	result1.valid() 查看状态

  std::shared_future<int> result1 = std::async(fun, 1, 2);
  std::shared_future<int> result1 = std::async(fun, 1, 2).share();
  auto result1 = std::async(fun, 1, 2).share();
  result1 将保存结果或异常，多次调用get会获取用一个结果或异常
*/
int fun(int i,int j)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	return 0;
}
void test_future_async()
{
	//std::future<int> result1(std::async(fun,1,2));
	auto result1 = std::async(fun, 1, 2);
	int result2 = fun(2,1);
	int result = result1.get();
	
	std::cout << result << std::endl;
}


/*
		std::this_thread::get_id();
		std::thread::hardware_concurrency(); 获取核数
		获取其它线程的数据
*/
int fun_pormise(std::promise<std::string> &str)
{
	std::string data;
	std::cin >> data;
	str.set_value(data);
	//str.set_value_at_thread_exit(data);//线程结束后赋值
	return 0;
}
void test_pormise()
{
	std::promise<std::string> value;
	std::thread thd(fun_pormise, std::ref(value));

	std::future<std::string> thd_value(value.get_future());
	std::cout << thd_value.get() << std::endl;
	thd.join();
}

/*
	std::mutex 同一线程多次锁定抛出异常
	std::recursive_mutex 允许一个线程多次锁定，在最近一次unlock时释放lock

	std::mutex::try_lock();
	std::lock_guard<std::mutex>lg(g_mutex,std::adopt_lock);
	尝试获取锁 获取失败返回false

	std::timed_mutex::try_lock_for();
	std::recursive_timed_mutex::try_lock_for();
	进行特定时长的获取请求

	std::lock(mutex1,mutex2);
	std::lock_guard<std::mutex>lg(mutex1,std::adopt_lock);
	std::lock_guard<std::mutex>lg(mutex2,std::adopt_lock);
	一次性尝试获取多个锁 返回时获取成功 失败抛出异常
	std::try_lock(mutex1,mutex2);
	std::lock_guard<std::mutex>lg(mutex1,std::adopt_lock);
	std::lock_guard<std::mutex>lg(mutex2,std::adopt_lock);
	**try_lock不存在死锁回避，但会按照参数顺序进行锁定
*/
std::mutex g_mutex;
std::recursive_mutex g_recu_mutex;
void test_mutex()
{
	std::lock_guard<std::mutex>lg(g_mutex,std::adopt_lock);

	
	{
		std::lock_guard<std::mutex>lg(g_mutex);
	}

	{
		std::lock_guard<std::recursive_mutex>lg(g_recu_mutex);
	}
}
int main()
{

	test_pormise();
	std::system("pause");
}