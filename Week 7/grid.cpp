#include <list>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <queue>
#include <iterator>
#include <iostream>
#include <string>

template <typename T>
class Graph {
        typename std::unordered_map<T, std::list<T> > adj;
    public:
        Graph() {};

        void add_vertex(const T& v);

        int num_vertices() const {
            return this->adj.size();
        }

        void add_edge(const T& from, const T& to);

        typename std::unordered_map<T, std::list<T> >::const_iterator cbegin() const {
            return adj.cbegin();
        }

        typename std::unordered_map<T, std::list<T> >::const_iterator cend() const {
            return adj.cend();
        }

        typename std::list<T>::const_iterator edges_begin(const T& v) const {
            return adj.at(v).cbegin();
        }

        typename std::list<T>::const_iterator edges_end(const T& v) const {
            return adj.at(v).cend();
        }
};

// -----------------------------------------------------------

template <typename T>
void Graph<T>::add_vertex(const T& v) {
    if (this->adj.find(v) != this->adj.end()) {
        return;
    }
    adj.insert({v, std::list<T>()});
}

template <typename T>
void Graph<T>::add_edge(const T& from, const T& to) {
    auto from_iter = this->adj.find(from);
    auto to_iter = this->adj.find(to);
    if (from_iter == this->adj.end() || to_iter == this->adj.end()) {
        throw std::invalid_argument("One of the vertices is not in the graph");
    }
    from_iter->second.push_back(to);
}

// -----------------------------------------------------------

namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int>& p) const {
            return 1000 * p.first + p.second;
        }
    };
}

int main() {
}