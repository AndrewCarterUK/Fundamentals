#include <vector>
#include <stdexcept>

template<typename K, typename V>
struct record_t {
    K key;
    V value;
};

template<typename K, typename V>
class bucket
{
    public:
        void insert(K key, V value) {
            auto record{ new record_t<K, V> };
            record->key = key;
            record->value = value;

            if (find(key) != -1) {
                throw std::runtime_error("Key already exists");
            }

            data.push_back(record);
        }

        V get(K key) {
            int index{ find(key) };

            if (index == -1) {
                throw std::runtime_error("Could not find key");
            }

            return data[index]->value;
        }

        bool has(K key) {
            return find(key) != -1;
        }

        void remove(K key) {
            int index{ find(key) };

            if (index == -1) {
                throw std::runtime_error("Could not find key");
            }

            delete data[index];

            data.erase(data.begin() + index);
        }

        std::size_t size() {
            return data.size();
        }

        ~bucket() {
            for (std::size_t i = 0; i < data.size(); i++) {
                delete data[i];
            }
        }

    private:
        std::vector<record_t<K, V> *> data;

        int find(K key) {
            int data_size{ static_cast<int>(data.size()) };

            for (int i = 0; i < data_size; i++) {
                if (data[i]->key == key) {
                    return i;
                }
            }

            return -1;
        }
};

template<typename K>
using hash_function_t = int (*) (K key);

template<typename K, typename V>
class hash_table
{
    public:
        hash_table(hash_function_t<K> hash_function, int base = 100) : m_hash_function(hash_function), m_base(base) {
            m_table = new bucket<K, V>[base];
        }

        void insert(K key, V value) {
            m_table[hash(key)].insert(key, value);
        }

        V get(K key) {
            return m_table[hash(key)].get(key);
        }

        bool has(K key) {
            return m_table[hash(key)].has(key);
        }

        void remove(K key) {
            m_table[hash(key)].remove(key);
        }

        std::size_t size() {
            std::size_t total_size = 0;

            for (int i = 0; i < m_base; i++) {
                total_size += m_table[i].size();
            }

            return total_size;
        }

        ~hash_table()
        {
            delete[] m_table;
        }

    private:
        bucket<K, V> * m_table;
        hash_function_t<K> m_hash_function;
        int m_base;

        int hash(K key) {
            return m_hash_function(key) % m_base;            
        }
};
