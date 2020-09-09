// Copyright - 2020 - Jan Christoph Uhde <Jan@UhdeJC.com>
// Please see LICENSE.md for license or visit https://github.com/extcpp/basics

#include <functional>
#include <list>
#include <mutex>
#include <unordered_map>

#ifndef EXT_UTIL_LRU_CACHE_HEADER
#define EXT_UTIL_LRU_CACHE_HEADER

namespace ext::util {

template <typename Key, typename Value>
class lru_cache {
public:
	lru_cache(size_t max_size) : _max_size{max_size} { }
    lru_cache(lru_cache const&) = delete;

	void put(const Key& key, const Value& value) {
		std::lock_guard<std::mutex> guard(_mut);
		auto found = _map.find(key);

	    if (found == _map.end()) {
	        if (_map.size() + 1 > _max_size) {
	            auto last = _list.crbegin();
	            _map.erase(last->first);
	            _list.pop_back();
	        }

	        _list.emplace_front(key, value);
	        _map[key] = _list.begin();
	    } else {
	        found->second->second = value;
	        _list.splice(_list.cbegin(), _list, found->second);
	    }
	}

	const std::pair<Value, bool> get(const Key& key, std::function<void(Value&)> update) {
	std::lock_guard<std::mutex> guard(_mut);
	    auto found = _map.find(key);
	    if (found == _map.end()) {
	        return {Value{}, false};
	    } else {
	        update(found->second->second);
	        _list.splice(_list.begin(), _list, found->second);
	        return {found->second->second, true};
	    }
	}

	const std::pair<Value, bool> get(const Key& key) {
	std::lock_guard<std::mutex> guard(_mut);
	    auto found = _map.find(key);
	    if (found == _map.end()) {
	        return {Value{}, false};
	    } else {
	        _list.splice(_list.begin(), _list, found->second);
	        return {found->second->second, true};
	    }
	}

	bool exists(const Key& key) const noexcept {
		std::lock_guard<std::mutex> guard(_mut);
	    return _map.find(key) != _map.end();
	}

	bool update_if_exists(const Key& key, std::function<void(Value&)> update) {
		std::lock_guard<std::mutex> guard(_mut);
		auto found = _map.find(key);
		if (found != _map.end()) {
			update(found->second->second);
			return true;
		} else {
			return false;
		}

	}

	size_t size() const noexcept {
	    std::lock_guard<std::mutex> guard(_mut);
	    return _map.size();
	}

    // fast clean up of expired values
    //void remove_all_matching_predicate(...);
    //void remove_past_value_matching_predicate(...);

private:
	std::list<std::pair<Key, Value>> _list;
	std::unordered_map<Key, decltype(_list.begin())> _map;
	size_t _max_size;
	mutable std::mutex _mut;
};

}     // namespace ext::util
#endif // EXT_UTIL_LRU_CACHE_HEADER
