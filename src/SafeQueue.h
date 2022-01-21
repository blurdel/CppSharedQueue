#ifndef SAFEQUEUE_H_
#define SAFEQUEUE_H_

#include <mutex>
#include <optional>
#include <queue>


template <typename T>
class SafeQueue {
public:
	SafeQueue() = default;
	SafeQueue(const SafeQueue<T>&) = delete;
	SafeQueue& operator=(const SafeQueue<T>&) = delete;

	SafeQueue(const SafeQueue<T>&& other) {
		std::lock_guard<std::mutex> lock(mtx);
		que = std::move(other.que);
	}

	virtual ~SafeQueue() {}

	void push(const T&);
	std::optional<T> pop();
	long size();

private:
	std::queue<T> que;
	std::mutex mtx;
};


template <typename T>
void SafeQueue<T>::push(const T& t)
{
	std::lock_guard<std::mutex> lock(mtx);
	que.push(t);
}

template <typename T>
std::optional<T> SafeQueue<T>::pop()
{
	std::lock_guard<std::mutex> lock(mtx);
	if (que.empty()) {
		return {};
	}
	T front = que.front();
	que.pop();
	return front;
}

template <typename T>
long SafeQueue<T>::size()
{
	std::lock_guard<std::mutex> lock(mtx);
	return que.size();
}

#endif
