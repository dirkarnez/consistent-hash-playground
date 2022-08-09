#include <iostream>
#include <functional>
#include <map>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

class server
{
public:
    string name;
};

template <typename T>
class consistent_hash
{
private:
    map<int, T> ring;
    int number_of_replicas;
    function<int(const T &)> hash_function;

public:
    consistent_hash(vector<T> nodes, int number_of_replicas, function<int(const T &)> hash_function)
    {
        cout << "consistent_hash()" << endl;

        this->ring = map<int, T>();
        this->number_of_replicas = number_of_replicas;
        this->hash_function = hash_function;

        for_each(nodes.cbegin(), nodes.cend(), [this](const T &node)
                 { this->add(node); });
    }

    void add(T node)
    {
        // for (int i = 0; i < this->number_of_replicas; i++)
        // {
            // circle.put(hashFunction.hash(node.toString() + i), node);
            auto ring_pair = pair<int, T>{this->hash_function(node), node};
            ring.insert(ring_pair);
        //}
    }

    void remove(T node)
    {
        // for (int i = 0; i < this->number_of_replicas; i++)
        // {
            // circle.remove(hashFunction.hash(node.toString() + i));
            
            ring.erase(this->hash_function(node));
        //}
    }

    T get(int hash)
    {
        // if (ring.empty())
        // {
        //     return nullptr;
        // }

        //int hash = hash_function(key);
        auto search = ring.find(hash);
        if (search == ring.end())
        { // not exists
            auto iter = ring.upper_bound(hash);
            // cout << (iter == ring.cend()) << endl;
            // cout <<  ring.cbegin()->first << endl;
            
            hash = iter == ring.cend() ? ring.cbegin()->first : iter->first;
        }

        return ring.at(hash);
    }
};

int main()
{
    int number_of_replicas = 10;

    server server_a{"A"};
    server server_b{"B"};

    vector<server> servers = {server_a, server_b};
    consistent_hash<server> consistent_hash_on_servers(servers, number_of_replicas, [](const server &s)
                                                       { return hash<string>{}(s.name); });
                                                       
    int h = hash<string>{}("yoyoyo");
    auto s = consistent_hash_on_servers.get(h);
    cout << s.name << endl;
    consistent_hash_on_servers.remove(server_b);

    s = consistent_hash_on_servers.get(h);
    cout << s.name << endl;

    std::cin.get();
    return 0;
}