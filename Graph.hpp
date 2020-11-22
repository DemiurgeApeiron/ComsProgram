#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

template <class T>
class GraphVertex {
   private:
    T val;
    std::vector<int> adj;

   public:
    ~GraphVertex(){};
    GraphVertex(){};
    GraphVertex(T _val) { val = _val; };

    T get_val() { return val; };
    void set_val(T _val) { val = _val; };

    std::vector<int> get_adj() { return adj; };
    void add_to_adj(int idx) { adj.push_back(idx); };
};

template <class T>
class Graph {
   private:
    std::vector<GraphVertex<T> > nodes;
    bool is_directed;

   public:
    ~Graph(){};
    Graph(bool _is_directed = false) { is_directed = _is_directed; };

    int getNofNodes() {
        for (size_t i = 0; i < nodes.size(); i++) {
            cout << nodes[i].get_val() << endl;
        }
        return nodes.size();
    }

    void add_node(T val) {
        GraphVertex<T> node(val);
        nodes.push_back(node);
    };

    void add_edge(int src, int dst) {
        nodes[src].add_to_adj(dst);
        if (!is_directed)
            nodes[dst].add_to_adj(src);
    };

    vector<int> BFSr(int start_vertex, vector<int> &visited, queue<int> &order) {
        cout << "actual node: " << nodes[start_vertex].get_val() << endl;
        if (!order.empty()) {
            order.pop();
        }
        if (find(visited.begin(), visited.end(), start_vertex) == visited.end()) {
            visited.push_back(start_vertex);

            vector<int> temporalAdj = nodes[start_vertex].get_adj();
            cout << "pre loop " << endl;
            for (size_t i = 0; i < temporalAdj.size(); i++) {
                cout << "pre if" << endl;
                if (find(visited.begin(), visited.end(), temporalAdj[i]) == visited.end()) {
                    cout << "Value: " << temporalAdj[i] << endl;
                    order.push(temporalAdj[i]);
                }
                cout << "pos if " << endl;
            }
            cout << "pos loop" << endl;
            BFSr(order.front(), visited, order);
        } else {
            if (!order.empty() && find(visited.begin(), visited.end(), order.front()) == visited.end()) {
                BFSr(order.front(), visited, order);
            }
        }
        return (visited);
    }

    vector<int> DFSr(int start_vertex, vector<int> &visited, stack<int> &order) {
        cout << "actual node: " << nodes[start_vertex].get_val() << endl;
        if (!order.empty()) {
            order.pop();
        }
        if (find(visited.begin(), visited.end(), start_vertex) == visited.end()) {
            visited.push_back(start_vertex);

            vector<int> temporalAdj = nodes[start_vertex].get_adj();
            cout << "pre loop " << endl;
            for (size_t i = 0; i < temporalAdj.size(); i++) {
                cout << "pre if" << endl;
                if (find(visited.begin(), visited.end(), temporalAdj[i]) == visited.end()) {
                    cout << "ValueAdded: " << nodes[temporalAdj[i]].get_val() << endl;
                    order.push(temporalAdj[i]);
                }
                cout << "pos if " << endl;
            }
            cout << "pos loop" << endl;
            DFSr(order.top(), visited, order);
        }

        if (!order.empty()) {
            order.pop();
            cout << "endl " << nodes[order.top()].get_val() << endl;
        } else {
            cout << "empty " << endl;
        }

        if (!order.empty() && find(visited.begin(), visited.end(), order.top()) == visited.end()) {
            DFSr(order.top(), visited, order);
        }

        return (visited);
    }

    void BFS(int start_vertex) {
        vector<int> visited;
        queue<int> order;
        visited = BFSr(start_vertex, visited, order);
        for (size_t i = 0; i < visited.size(); i++) {
            cout << nodes[visited[i]].get_val() << ", ";
        }
    };

    void DFS(int start_vertex) {
        vector<int> visited;
        stack<int> order;
        visited = DFSr(start_vertex, visited, order);
        for (size_t i = 0; i < visited.size(); i++) {
            cout << nodes[visited[i]].get_val() << ", ";
        }
    }
};

#endif