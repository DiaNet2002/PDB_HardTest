#include <ctime>
#include "Graph.cpp"
class Algorithms :Graphs {
public:
    static std::vector<std::string> RezStr(std::vector<std::vector<int64_t>> DIST, const Graph& graph) {
        clock_t start = clock();
        std::vector<std::string> rez(graph.vertex_count);
        rez[graph.start_vertex] = std::to_string(graph.start_vertex + 1) + "->" + std::to_string(graph.start_vertex + 1) + "\tРасстояние 0";
        for (int i = 0; i < graph.vertex_count; i++) {
            if (i != graph.start_vertex)
                for (int j = 0; j < DIST[i].size() - 1; j++) {
                    if (DIST[i][j] != 0) {

                        rez[i] = rez[i] + std::to_string(DIST[i][j]);
                        if (j < DIST[i].size() - 2) rez[i] = rez[i] + "->";
                    }

                }
        }
        for (int j = 0; j < graph.vertex_count; j++) {
            if (j != graph.start_vertex)
                rez[j] = rez[j] + "\tРасстояние " + std::to_string(DIST[j][DIST[j].size() - 1]);

        }
        std::cout  << (clock() - start) << "\t";
        return rez;
    }
    static Result Dijkstra(const Graph& graph) {

        if (graph.vertex_count == 0) {
            return {
                graph.vertex_count,
                graph.start_vertex,
                {}
            };
        }
        clock_t start = clock();
        std::vector<std::vector<int64_t>> w(graph.vertex_count);
        std::vector<int64_t> distances = graph.matrix[graph.start_vertex];
        std::vector<bool>  v(graph.vertex_count);
        std::vector<std::vector<int64_t>> DIST(graph.vertex_count);
        int index;
        for (int i = 0; i < graph.vertex_count; i++) {
            DIST[i].resize(graph.vertex_count);
            w[i].resize(graph.vertex_count);
        }
        for (int i = 0; i < graph.vertex_count; i++) {
            v[i] = false; DIST[i].push_back(graph.start_vertex + 1);
            for (int j = 0; j < graph.vertex_count; j++) {
                w[i][j] = graph.matrix[i][j];
            }
        }

        distances[graph.start_vertex] = 0;
        v[graph.start_vertex] = true;
        for (int i = 0; i < graph.vertex_count; i++) {
            int64_t min = INFINITY_LENGTH;
            for (int j = 0; j < graph.vertex_count; j++) {
                if (!v[j] && distances[j] < min) {
                    min = distances[j];
                    index = j;
                }
            }
            v[index] = true;
            for (int j = 0; j < graph.vertex_count; j++) {
                if (!v[j] && w[index][j] != INFINITY_LENGTH && distances[index] != INFINITY_LENGTH
                    && distances[index] + w[index][j] < distances[j]) {
                    DIST[j] = DIST[index];
                    DIST[j].push_back(index + 1);
                    distances[j] = distances[index] + w[index][j];
                }

            }

        }
        for (int j = 0; j < graph.vertex_count; j++) {
            DIST[j].push_back(j + 1); DIST[j].push_back(distances[j]);
        }
        std::cout <<  (clock() - start ) << "\t\t";
        return {
            graph.vertex_count,
            graph.start_vertex,
            RezStr(DIST,graph)
        };
    };

    static Result FordBellman(const Graph& graph) {

        if (graph.vertex_count == 0) {
            return {
                    graph.vertex_count,
                    graph.start_vertex,
                    {}
            };
        }
        clock_t start = clock();
        std::vector<int64_t> distances(graph.vertex_count, INFINITY_LENGTH);
        std::vector<std::vector<int64_t>> DIST(graph.vertex_count);
        int index = 0;


        struct Edge {
            int32_t u, v;
            int64_t w;
        };

        std::vector<Edge> edges;
        for (int32_t u = 0; u < graph.vertex_count; ++u) {
            for (int32_t v = 0; v < graph.vertex_count; ++v) {
                if (graph.matrix[u][v] < INFINITY_LENGTH) {
                    edges.push_back({ u, v, graph.matrix[u][v] });
                }
            }
        }

        distances[graph.start_vertex] = 0;
        for (int k = 0; k < graph.vertex_count - 1; ++k) {
            for (int j = 0; j < edges.size(); j++) {
                if (distances[edges[j].v] != INFINITY_LENGTH && distances[edges[j].v] + edges[j].w < distances[edges[j].u]) {
                    DIST[edges[j].u] = DIST[edges[j].v];
                    DIST[edges[j].u].push_back(edges[j].v + 1);

                    distances[edges[j].u] = distances[edges[j].v] + edges[j].w;

                }
            }
        }
        for (int j = 0; j < graph.vertex_count; j++) {
            DIST[j].push_back(j + 1); DIST[j].push_back(distances[j]);
        }
        std::cout <<  (clock() - start) << "\t\t";
        return {
            graph.vertex_count,
            graph.start_vertex,
            RezStr(DIST,graph)
        };
    }
};