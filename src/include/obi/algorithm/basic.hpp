#include <iterator>
#include <map>
#include <stdexcept>
#include <type_traits>
#include "../meta/has_member.hpp"

namespace obi { namespace algorithm {

    // count occurences in containers /////////////////////////////////////////
    template<typename Iterator, typename Int = int>
    std::map<typename std::iterator_traits<Iterator>::value_type,Int>
    count_occurrences(Iterator begin, Iterator end) {
        using Key = typename std::iterator_traits<Iterator>::value_type;
        std::map<Key,Int> result;
        for(auto it = begin; it != end; it++) {
            auto found = result.find(*it);
            if (found != result.end()) {
                found->second++;
            } else {
                result[*it] = Int(1);
            }
        }
        return result;
    }

    //add endable if
    template<typename Container, typename Int = int>
    auto count_occurrences(const Container& container) {
        using Iterator = decltype(std::begin(container));
        return count_occurrences<Iterator,Int>(std::begin(container), std::end(container));
    }


    // mege maps //////////////////////////////////////////////////////////////
    template <typename Map, typename Predicate>
    auto& merge_maps(Map& result, const Map& in, Predicate predicate = std::less<>() ) {
        for (auto it = in.begin(); it != in.end(); it++) {
            auto found = result.find(it->first);
            if(found != result.end()){
                if (predicate(found->second,it->second)){
                    result[it->first] = it->second;
                }
            } else {
                result[it->first] = it->second;
            }
        }
        return result;
    }

    template <typename Iterator
             ,typename Predicate
             ,typename = std::enable_if_t<obi::meta::is_input_iterator<Iterator>::value>
             >
    auto merge_maps(Iterator begin, Iterator end, Predicate predicate = std::less<>()) {
        using PairType = typename std::iterator_traits<Iterator>::value_type;
        std::map<typename PairType::T1,typename PairType::T2> result;
        for (auto it = begin; it != end; it++) {
            merge_maps(result, *it);
        }
        return result;
    }

}} // obi::algorithm
