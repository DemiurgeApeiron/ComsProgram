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
    // este metodo te permite consegir el valor del nodo
    T get_val() { return val; };
    // este metodo permite establecer el valor de un nodo
    void set_val(T _val) { val = _val; };
    // este emtodo regresa los vecinos del nodo
    std::vector<int> get_adj() { return adj; };
    // este metodo permite añadir una arista entre los vectores
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
    // este metodo consige el numero de verices que tiene el grafo
    int getNofNodes() {
        return nodes.size();
    }
    // esta funcion permite encontrar el indice de el vertice del grafo
    int find(T val) {
        if (!nodes.empty()) {
            for (size_t i = 0; i < nodes.size(); i++) {
                if (nodes[i].get_val() == val) {
                    return (i);
                }
            }
        }
        return (-1);
    }
    // esta funcion permite encontrar el indice de el vertice del grafo en el que el nodo tiene una estructura de tipo pair o map
    int findPM(T val) {
        if (!nodes.empty()) {
            for (size_t i = 0; i < nodes.size(); i++) {
                if (nodes[i].get_val().first == val.first) {
                    return (i);
                }
            }
        }
        return (-1);
    }
    // este metodo te permite recuperar el valor del vertice
    T getVertex(int index) { return nodes[index].get_val(); }

    vector<T> getConnectionsToVertex(int indexVertex) {
        vector<T> connections;
        for (size_t i = 0; i < nodes.size(); i++) {
            vector<int> neighbours = nodes[i].get_adj();
            for (size_t j = 0; j < neighbours.size(); j++) {
                if (nodes[indexVertex].get_val() == nodes[neighbours[j]].get_val()) {
                    connections.push_back(nodes[i].get_val());
                }
            }
        }
        return (connections);
    }
    // este metodo te permite imprimir todas los vertices que tienen una arista apuntando a un vertice espesifico
    vector<T> getConnectionsToVertexPM(int indexVertex) {
        vector<T> connections;
        for (size_t i = 0; i < nodes.size(); i++) {
            vector<int> neighbours = nodes[i].get_adj();
            for (size_t j = 0; j < neighbours.size(); j++) {
                if (nodes[indexVertex].get_val().first == nodes[neighbours[j]].get_val().first) {
                    connections.push_back(nodes[i].get_val());
                }
            }
        }
        return (connections);
    }
    // este metodo te permite consegir todos los vecinos de un vertice
    vector<T> getNeighbours(int index) {
        vector<T> neighboursVals;
        vector<int> neighbours = nodes[index].get_adj();
        for (size_t i = 0; i < neighbours.size(); i++) {
            neighboursVals.push_back(nodes[neighbours[i]].get_val());
        }
        return (neighboursVals);
    }
    // este metodo te permite agregar un vertice
    void add_node(T val) {
        GraphVertex<T> node(val);
        nodes.push_back(node);
    };
    // este metodo te permite agregar una arista entre dos vertices
    void add_edge(int src, int dst) {
        nodes[src].add_to_adj(dst);
        if (!is_directed) {
            nodes[dst].add_to_adj(src);
        }
    };
    // este metodo te permite imprimir el grafo a lo horizontal
    vector<int> BFSr(int start_vertex, vector<int> &visited, queue<int> &order) {
        cout << "actual node: " << nodes[start_vertex].get_val() << endl;
        if (!order.empty()) {
            order.pop();
        }
        if (std::find(visited.begin(), visited.end(), start_vertex) == visited.end()) {
            visited.push_back(start_vertex);

            vector<int> temporalAdj = nodes[start_vertex].get_adj();
            cout << "pre loop " << endl;
            for (size_t i = 0; i < temporalAdj.size(); i++) {
                cout << "pre if" << endl;
                if (std::find(visited.begin(), visited.end(), temporalAdj[i]) == visited.end()) {
                    cout << "Value: " << temporalAdj[i] << endl;
                    order.push(temporalAdj[i]);
                }
                cout << "pos if " << endl;
            }
            cout << "pos loop" << endl;
            BFSr(order.front(), visited, order);
        } else {
            if (!order.empty() && std::find(visited.begin(), visited.end(), order.front()) == visited.end()) {
                BFSr(order.front(), visited, order);
            }
        }
        return (visited);
    }
    // este metodo te permite imprimir el grafo a lo profundo
    vector<int> DFSr(int start_vertex, vector<int> &visited, stack<int> &order) {
        cout << "actual node: " << nodes[start_vertex].get_val() << endl;
        if (!order.empty()) {
            order.pop();
        }
        if (std::find(visited.begin(), visited.end(), start_vertex) == visited.end()) {
            visited.push_back(start_vertex);

            vector<int> temporalAdj = nodes[start_vertex].get_adj();
            cout << "pre loop " << endl;
            for (size_t i = 0; i < temporalAdj.size(); i++) {
                cout << "pre if" << endl;
                if (std::find(visited.begin(), visited.end(), temporalAdj[i]) == visited.end()) {
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

        if (!order.empty() && std::find(visited.begin(), visited.end(), order.top()) == visited.end()) {
            DFSr(order.top(), visited, order);
        }

        return (visited);
    }
    // este metodo llama a la imprecion horizontal
    void BFS(int start_vertex) {
        vector<int> visited;
        queue<int> order;
        visited = BFSr(start_vertex, visited, order);
        for (size_t i = 0; i < visited.size(); i++) {
            cout << nodes[visited[i]].get_val() << ", ";
        }
    };
    // este metodo llama a la imprecion profunda
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