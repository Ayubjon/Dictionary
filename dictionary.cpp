#include <bits/stdc++.h>

template<class Key, class Value>
class dictionary
{
public:
    virtual ~dictionary() = default;

    virtual const Value& get(const Key& key) const = 0;
    virtual void set(const Key& key, const Value& value) = 0;
    virtual bool is_set(const Key& key) const = 0;
};


template<class Key>
class not_found_exception : public std::exception
{
public:
    virtual const Key& get_key() const noexcept = 0;
};



template<class Key>
class key_not_found_exception : public not_found_exception<Key>
{
private:
    Key key;
public:

    key_not_found_exception(const Key& k) {
        this->key = k;
    }

    const Key& get_key() const noexcept {
        return key;
    }
};



template<class Key, class Value>
class my_dictionary : dictionary<Key, Value> {
private:
    std::map<Key, Value> dict;

public:
    const Value& get(const Key& key) const {
        if (is_set(key)) {
            return dict.find(key)->second;
        } else {
            throw key_not_found_exception<Key>(key);
        }
    }

    void set(const Key& key, const Value& value) {
        dict[key] = value;
    }

    bool is_set(const Key& key) const {
        return dict.find(key) != dict.end();
    }
};

void test() {
    my_dictionary<int, int> d;
    d.set(1, 3);
    std::cout << (d.is_set(1) ? 1 : 0) << "\n";
    std::cout << (d.is_set(2) ? 1 : 0) << "\n";
    std::cout << d.get(1) << "\n";
    try {
        std::cout << d.get(4) << "\n";
    } catch (key_not_found_exception<int> e) {
        std::cout << "caught an exception. Key: " << e.get_key() << "\n";
    }
}


int main() {
    test();

    return 0;
}
