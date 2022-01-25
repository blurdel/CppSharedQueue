#ifndef SAFEQUEUE_H_
#define SAFEQUEUE_H_

#include <mutex>
#include <optional>
#include <queue>


class non_empty_queue : public std::exception {
public:
	explicit non_empty_queue(std::string pMsg) {
		mWhat = std::move(pMsg);
	}
	const char* what() const noexcept override {
		return mWhat.c_str();
	}

private:
	std::string mWhat;
};


template <typename T>
class SafeQueue {
public:
	SafeQueue() = default;
	SafeQueue(const SafeQueue<T>&) = delete;
	SafeQueue& operator=(const SafeQueue<T>&) = delete;

	SafeQueue(const SafeQueue<T>&& other) {
		std::lock_guard<std::mutex> lock(mMtx);
		if (!mQue.empty()) {
			throw non_empty_queue{ "Moving into a non-empty queue" };
		}
		mQue = std::move(other.mQue);
	}

	virtual ~SafeQueue() {
		std::lock_guard<std::mutex> lock(mMtx);
		if (!mQue.empty()) {
			throw non_empty_queue{ "Destroying a non-empty queue" };
		}
	}

	void push(const T& t) {
		std::lock_guard<std::mutex> lock(mMtx);
		mQue.push(t);
	}

	std::optional<T> pop() {
		std::lock_guard<std::mutex> lock(mMtx);
		if (mQue.empty()) {
			return {};
		}
		T front = mQue.front();
		mQue.pop();
		return front;
	}

	long size() const {
		std::lock_guard<std::mutex> lock(mMtx);
		return mQue.size();
	}

private:
	std::queue<T> mQue;
	mutable std::mutex mMtx;
};


#endif
