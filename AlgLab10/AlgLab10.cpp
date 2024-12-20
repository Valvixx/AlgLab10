#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

vector<vector<int>> generateWeightedAdjacencyMatrix(int size) {
    vector<vector<int>> matrix(size, vector<int>(size, 0));
    srand(time(0));

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            int weight = rand() % 10 + 1;
            if (rand() % 2 == 1) {
                matrix[i][j] = weight;
                matrix[j][i] = weight;
            }
        }
    }

    return matrix;
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            cout << setw(3) << value << " ";
        }
        cout << endl;
    }
}

vector<int> bfsDistances(const vector<vector<int>>& graph, int start) {
    int size = graph.size();
    vector<int> distances(size, INT32_MAX);
    queue<int> q;

    q.push(start);
    distances[start] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int i = 0; i < size; ++i) {
            if (graph[current][i] && distances[i] > distances[start] + graph[current][i]) {
                q.push(i);
                distances[i] = distances[current] + graph[current][i];
                
            }
        }
    }

    return distances;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int graphSize, startVertex;

    cout << "Введите количество вершин графа: ";
    cin >> graphSize;

    vector<vector<int>> adjacencyMatrix = generateWeightedAdjacencyMatrix(graphSize);

    cout << "Матрица смежности взвешенного графа:" << endl;
    printMatrix(adjacencyMatrix);

    cout << "\nВведите начальную вершину (0 - " << graphSize - 1 << "): ";
    cin >> startVertex;

    if (startVertex < 0 || startVertex >= graphSize) {
        cout << "Начальная вершина вне диапазона" << endl;
        return 1;
    }

    vector<int> distances = bfsDistances(adjacencyMatrix, startVertex);

    cout << "\nРасстояния от вершины " << startVertex << ":" << endl;
    for (int i = 0; i < distances.size(); ++i) {
        if (distances[i] != -1)
            cout << "Вершина " << i << ": " << distances[i] << endl;
        else
            cout << "Вершина " << i << ": недостижима" << endl;
    }

    return 0;
}