#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

class Graphs {
public:
    struct Graph {
        int32_t vertex_count;
        int32_t start_vertex;
        std::vector<std::vector<int64_t>> matrix;
    };
    struct Result {
        int32_t vertex_count = 0;
        int32_t start_vertex = -1;
        std::vector<std::string> distances;
    };

    static const int64_t INFINITY_LENGTH = INT_MAX;

public:


   
    static void write_file(Result& res, Graph& g) {
        std::string filename = "Dijkstra_" + std::to_string(res.vertex_count) + "_" + std::to_string(res.start_vertex + 1) + ".txt";
        std::ofstream fout(filename);
        if (fout.is_open()) {
            fout << "Количество точек " << g.vertex_count << "\n";
            for (int i = 0; i < res.vertex_count; i++) {
                for (int j = 0; j < res.vertex_count; j++) {
                    if (g.matrix[i][j] == INFINITY_LENGTH)g.matrix[i][j] = 0;
                    fout << g.matrix[i][j] << "\t";
                }fout << "\n";
            }

            for (int i = 0; i < res.vertex_count; i++) {
                fout << res.distances[i] << std::endl;
            }
            fout.close();
        }
    }


};
