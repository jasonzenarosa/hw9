#include <vector>
using namespace std;

template <typename Key, typename Value>
class MapArray{
    vector<pair<Key, Value>> vec;
public:
    class iterator{
        pair<Key, Value>* current;
    public:
        using iterator_category = random_access_iterator_tag;
        using value_type = MapArray::value_type;
        using pointer = value_type*;
        using reference = value_type&;
        using difference_type = ptrdiff_t;

        explicit iterator(pointer const ptr = nullptr) : current(ptr){}
        iterator& operator++(){
            current++;
            return *this;
        }
        iterator& operator--(){
            current--;
            return *this
        }
        iterator operator++(int){
            pair<Key, Value>* tmp = current;
            ++current;
            return iterator(tmp);
        }
        iterator operator--(int){
            pair<Key, Value>* tmp = current;
            --current;
            return iterator(tmp);
        }
        iterator& operator+=(difference_type const d){
            current += d;
            return *this;
        }
        iterator& operator-=(difference_type const d){
            current -= d;
            return *this;
        }
        friend iterator operator+(iterator i, difference_type const d){
            return iterator(i.current + d);
        }
        friend iterator operator+(difference_type const d, iterator i){
            return iterator(i.current + d);
        }
        friend iterator operator-(iterator i, difference_type const d){
            return iterator(i.current - d);
        }
        friend iterator operator-(difference_type const d, iterator i){
            return iterator(i.current - d);
        }
        friend difference_type operator-(iterator const i, iterator const j){
            return i.current - j.current;
        }
        auto operator <=> (iterator const& other) const = default{
            if (this->current < other.current) return -1;
            if (this->current == other.current) return 0;
            if (this->current > other.current) return 1;
        }
        reference operator*()const{
            return *(this->current);
        }
        pointer operator->() const{
            return this->current;
        }
        reference operator[](difference_type const d) const{
            return *(this->current + d);
        }
    };
    static_assert(std::random_access_iterator<iterator>);
    using value_type = pair<Key, Value>//???;
    using key_type = Key;
    using mapped_type = Value;
    using pointer = value_type*;
    using reference = value_type&;
    using const_reference = const reference;

    iterator begin(){
        return iterator(vec.data());
    }
    iterator end(){
        return iterator(vec.data() + vec.size());
    }
    Values& operator[](Key const& key){
        for (auto& p : vec){
            if (p.first == key){
                return p.second;
            }
        }
        vec.emplace_back(key, Value());
        return vec.back().second;
    }
};