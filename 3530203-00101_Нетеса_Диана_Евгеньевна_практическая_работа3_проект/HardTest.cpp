#include <iostream>
#include<Windows.h>
#include "Algorithms.cpp"

class Console
{
public:

    static Graphs::Graph GenerateMatrix( int N, int R) {
        Graphs::Graph g;
        clock_t start = clock();
        int64_t m;
        srand(time(0));
        g.vertex_count=N;
        g.matrix.resize(N);
        for (int i = 0; i < N; i++)  g.matrix[i].resize(N);
        for (int i = 0; i <N; i++) {
            for (int j = i; j < N; j++) {
                if (i == j) {
                    g.matrix[i][j] = Graphs::INFINITY_LENGTH;
                    continue;
                }
                if (rand() % 100 < R) {
                    g.matrix[i][j] = Graphs::INFINITY_LENGTH;
                    continue;
                }
                m = rand() % 50;
                if (m == 0) { m = 10; }
                g.matrix[i][j] = m;
                g.matrix[j][i] = m;
            }
        }
        g.start_vertex = 0;
        std::cout <<  (clock() - start)<<"\t\t";
        
        return g;
    }
    static void WriteAns(Graphs::Result rez, Graphs::Graph g) {
        std::cout << std::endl;
        clock_t start = clock();
        Graphs::write_file(rez, g);
        for (int i = 0; i < rez.vertex_count; i++) {
            std::cout << rez.distances[i] << '\n';
        }
        std::cout << "\tРекомендательная информация:" <<
            "\nВыше представлены крайтчайшие пути из начальной точки во все остальные, с указанием промежуточных точек." <<
            "\nВам необходимо количество провода равного расстоянию между точками." <<
            "\nЕсли данные указаны не верно или Вы хотите сделать рассчет по новым данным или выйти  нажмите 'e'\n";
        std::cout << "WriteANS "<<(clock() - start) << "\t\t";
        do {
            char A;
            std::cin >> A;
            if (A == 'e') break;
        } while (true);
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Graphs::Graph g; Graphs::Result rez;
    std::cout << "Num\tN\tR\tGenerate\tDijkstra\tResult\tFordBellmana\tResult\n";
    clock_t start = clock();
    int N=100, R;
    std::string f1;
    std::ifstream input_file(f1);
    std::vector<Graphs::Graph> VG(60);
    for (int i = 0; i < 60; i++) {
        
        if (i == 0) {
            R = 0;
             f1 = "100_0.txt";
        }
        if (i == 20) {
            R = 30;
             f1 = "100_30.txt";
        }
        if (i == 40) {
            R = 70;
            f1 = "100_70.txt";
        }
        std::ifstream input_file(f1);
        std::string line;
        getline(input_file, line);
        VG[i].vertex_count = stoi(line);
        VG[i].matrix.resize(VG[i].vertex_count);
        for (int j = 0; j < VG[i].vertex_count; j++) {
            VG[i].matrix[j].resize(VG[i].vertex_count, 0);
        }
        for (int j = 0; j < VG[i].vertex_count; j++) {
            getline(input_file, line);
            std::istringstream iss(line);
            for (int k = 0; k < VG[i].vertex_count; k++) {
                int64_t value;
                iss >> value;
                if (value == 0) value = Graphs::INFINITY_LENGTH;
                VG[i].matrix[j][k] = value;
            }
        }
        VG[i].start_vertex = 0;
        std::cout << "\n" << i << "\t" << N << "\t" << R << "\t";
        g = Console::GenerateMatrix(N, R);
        rez = Algorithms::Dijkstra(g);
        rez = Algorithms::FordBellman(g);
    }
    input_file.close();
    for (int i = 60; i < 180; i++) {
        if (i == 60) {
            N = 1500;
            R = 0;
        }
        if (i == 80) R = 30;
        if (i == 100) R = 70;
        if (i == 120) {
            N = 15000; R = 0;
        }
        if (i == 140) R = 30;
        if (i == 160) R = 70;
        std::cout <<"\n"<< i << "\t" << N << "\t" << R << "\t";
        g = Console::GenerateMatrix(N, R);
        rez = Algorithms::Dijkstra(g);
        if(i<60)
        rez = Algorithms::FordBellman(g);
    }
}
