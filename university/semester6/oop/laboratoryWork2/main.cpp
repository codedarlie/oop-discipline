#include <iostream>
#include <vector>

class Matrix {
private:
    unsigned int rows;
    unsigned int columns;
    std::vector<std::vector<int>> data;

public:
    Matrix(unsigned int r, unsigned int c, const int value = 0): rows{r}, columns{c} {
        data = std::vector<std::vector<int>> (r);
        for (auto& i: data) {
            i = std::vector<int> (c, value);
        }
    }
    Matrix(const int value = 0): Matrix(1, 1, value) {};
    Matrix(const Matrix& m): rows{m.rows}, columns{m.columns} {
    // Matrix(const Matrix& m): rows{m.rows}, columns{m.columns}, data{std::vector<std::vector<int>> (rows) } {
        data = m.data;
        // for (int i = 0; i < data.size(); ++i) {
            // data[i] = std::vector<int> (columns);
            // for (int k = 0; k < data[i].size(); ++k) {
                // data[i][k] = m.data[i][k];
            // }
        // }       
    }
    Matrix(Matrix&& m): rows{std::move(m.rows)}, columns{std::move(m.columns)}, data{std::move(m.data)} {
        m.rows = 0;
        m.columns = 0;
    } 
        

    void setValue(const unsigned int i, const unsigned int j, const int value) {
        if (i < rows && j < columns) {
            data[i][j] = value;
            return;
        }
        throw;
    }
    const int getConstValue(const unsigned int i, const unsigned int j) const {
        if (!(i < rows && j < columns)) {
            throw;
        }
        return data[i][j];
    }
    void transpose() {
        std::vector<std::vector<int>> data2(columns);
        for (int i = 0; i < data2.size(); ++i) {
            data2[i] = std::vector<int> (rows);
            for (int k = 0; k < data2[i].size(); ++k) {
                data2[i][k] = data[k][i];
            }
        }
        data = std::move(data2);
        std::swap(columns, rows);
    }
    void toTheIdentityMatrix() {
        for (int i = 0; i < data.size(); ++i) {
            for (int k = 0; k < data[i].size(); ++k) {
                if (i == k) data[i][k] = 1;
                else data[i][k] = 0;
            }
        }
        std::cout << *this;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    os << "Matrix (" << m.rows << ", " << m.columns << "):\n";
    for (auto& i: m.data) {
        for (auto& k: i) {
            os << k << ' ';
        }
        os << '\n';
    }

    return os;
}

int main() {

    Matrix m (5, 4, 3);

    std::cout << m;

    return 0;
}