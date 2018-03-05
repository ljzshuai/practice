#include <thread>
#include <string>
#include <future>
#include <iostream>

/*
  std::future<int> result1(std::async(fun,1,2));
  ��һ�������ڵ���result1.get()��ȡ���֮ǰ�����ܵı��첽ִ��(�����߳�)���

  std::future<int> result1(std std::async(std::launch::async,fun,1,2)); ǿ���첽
  ���ǿ���첽�ˣ���ʹfuture����result1�����������ڳ���Ҳ������ĵȴ��첽 �������

  std::future<int> result1(std std::async(std::launch::deferred,fun,1,2)); 
  ������get ��������

  �����쳣�ᱣ���� ֱ������get
  getֻ�ܵ���һ�� 	result1.valid() �鿴״̬

  std::shared_future<int> result1 = std::async(fun, 1, 2);
  std::shared_future<int> result1 = std::async(fun, 1, 2).share();
  auto result1 = std::async(fun, 1, 2).share();
  result1 �����������쳣����ε���get���ȡ��һ��������쳣
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
		std::thread::hardware_concurrency(); ��ȡ����
		��ȡ�����̵߳�����
*/
int fun_pormise(std::promise<std::string> &str)
{
	std::string data;
	std::cin >> data;
	str.set_value(data);
	//str.set_value_at_thread_exit(data);//�߳̽�����ֵ
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
	std::mutex ͬһ�̶߳�������׳��쳣
	std::recursive_mutex ����һ���̶߳�������������һ��unlockʱ�ͷ�lock

	std::mutex::try_lock();
	std::lock_guard<std::mutex>lg(g_mutex,std::adopt_lock);
	���Ի�ȡ�� ��ȡʧ�ܷ���false

	std::timed_mutex::try_lock_for();
	std::recursive_timed_mutex::try_lock_for();
	�����ض�ʱ���Ļ�ȡ����

	std::lock(mutex1,mutex2);
	std::lock_guard<std::mutex>lg(mutex1,std::adopt_lock);
	std::lock_guard<std::mutex>lg(mutex2,std::adopt_lock);
	һ���Գ��Ի�ȡ����� ����ʱ��ȡ�ɹ� ʧ���׳��쳣
	std::try_lock(mutex1,mutex2);
	std::lock_guard<std::mutex>lg(mutex1,std::adopt_lock);
	std::lock_guard<std::mutex>lg(mutex2,std::adopt_lock);
	**try_lock�����������رܣ����ᰴ�ղ���˳���������
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