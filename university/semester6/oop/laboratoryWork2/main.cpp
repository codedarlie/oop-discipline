#include <iostream>
#include <vector>

class Matrix {
protected:
    unsigned int rows;
    unsigned int columns;
    std::vector<std::vector<int>> data;

public:
    Matrix(const unsigned int r, const unsigned int c, const int value = 0): rows{r}, columns{c} {
        std::cout << this << ": Matrix(r, c, value)\n";
        data = std::vector<std::vector<int>> (r);
        for (auto& i: data) {
            i = std::vector<int> (c, value);
        }
    }
    Matrix(const int value = 0): Matrix(1, 1, value) {};
    Matrix(const Matrix& m): rows{m.rows}, columns{m.columns}, data{m.data} {
        std::cout << this << ": Matrix(const Matrix& m)\n";
    }
    Matrix(Matrix&& m): rows{std::move(m.rows)}, columns{std::move(m.columns)}, data{std::move(m.data)} {
        std::cout << this << ": Matrix(Matrix&& m)\n";
        m.rows = 0;
        m.columns = 0;
    } 
    
    void setValue(const unsigned int i, const unsigned int j, const int value) {
        std::cout << this << ": setValue(i, j, value)\n";
        if (i < rows && j < columns) {
            data[i][j] = value;
            return;
        }
        throw;
    }
    void setRangeValue(const unsigned int i1, const unsigned int i2, const unsigned int j1, const unsigned int j2, const int value) {
        if ((i1 >= rows) || (i2 > rows) || (j1 >= columns) || (j2 > columns)) throw;
        
        for (int i = i1; i < i2; ++i) {
            for (int j = j1; j < j2; ++j) {
                data[i][j] = value;
            }
        }
    }
    const int getValue(const unsigned int i, const unsigned int j) const {
        std::cout << this << ": getValue(i, j)\n";
        if (!(i < rows && j < columns)) {
            throw;
        }
        return data[i][j];
    }
    size_t getRowsSize() const {
        return rows;
    }
    size_t getColumnsSize() const {
        return columns;
    }
    bool isEmpty() const;

    virtual void transpose() {
        std::cout << this << ": transpose()\n";
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
    void fill(const int value) {
        for (auto& i: data) {
            for (auto& k: i) k = value;
        }
        
    }
    virtual void resize(const unsigned r, const unsigned c, const int value = 0) {
        if (!r && c || r && !c) throw;
        data.resize(r);
        for (int i = rows; i < r; ++i) {
            data[i] = std::vector<int> (columns, value);
        }
        for (auto& i: data) {
            i.resize(c);
            for (int k = columns; k < c; ++k) {
                i[k] = value;
            }
        }
        columns = c;
        rows = r;
    }
    
    void swap(const unsigned i1, const unsigned j1, const unsigned i2, const unsigned j2) {
        if (!(i1 < rows && i1 < rows && j1 < columns && j2 < columns)) {
            throw;
        }
        std::swap(data[i1][j1], data[i2][j2]);
    }
    void clear() {
        data.clear();
        rows = 0;
        columns = 0;
    }

    Matrix minor(const unsigned int i, const unsigned int j) {
        if (i >= rows || j >= columns) throw;

        Matrix m(rows - 1, columns - 1);

        int m_i {0};
        for (int k = 0; k < rows; ++k) {
            if (k == j) continue;
            int m_j {0};
            for (int q = 0; q < columns; ++q) {
                if (q == i) continue;
                m.data[m_i][m_j] = data[k][q];
                ++m_j;
            }
            ++m_i;
        }
        return m;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

    virtual ~Matrix() {
        std::cout << this << ": ~Matrix()\n";
        rows = 0;
        columns = 0;
        data.clear();
    }
};

bool Matrix::isEmpty() const {
    return data.empty();
}
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

class SquareMatrix: public Matrix {
private:
    using Matrix::resize;

public:
    SquareMatrix(const unsigned int i = 1, const int value = 0): Matrix(i, i, value) {
        std::cout << this << ": SquareMatrix(i, value)\n";
    }
    SquareMatrix(const SquareMatrix& m): Matrix(m) {
        std::cout << this << ": SquareMatrix(const SquareMatrix&)\n";
    }
    SquareMatrix(SquareMatrix&& m): Matrix(std::move(m)) {
        std::cout << this << ": SquareMatrix(SquareMatrix&&)\n";
    }

    size_t getSize() const {
        std::cout << this << ": getSize()\n";
        return rows;
    }
    
    void transpose() {
        for (int i = 0; i < rows; ++i) {
            for (int k = 1 + i; k < rows; ++k) {
                swap(i, k, k, i);
            }
        }
        
        /*  2 3 4 5 6
        5 3 1 3 2
        1 2 3 4 5
        2 3 4 5 9
        1 3 2 1 3  */
    }
    const int trace() const {
        if (!rows) throw;

        int num {0};
        for (int i = 0; i < rows; ++i) {
            num += data[i][i];
        }
        return num;
    }
    
    void resize(const unsigned r, const int value = 0) {
        Matrix::resize(r, r, value);
    }
    void makeIdentity() {
        std::cout << this << ": makeIdentity()\n";
        
        for (int i = 0; i < data.size(); ++i) {
            for (int k = 0; k < data[i].size(); ++k) {
                if (i == k) data[i][k] = 1;
                else data[i][k] = 0;
            }
        }
        std::cout << *this;
    }
    
    
    // Переделать.
    // size_t getRowsSize() const = delete;
    // size_t getColumnsSize() const = delete;
    
    // const int determinant() const;   // Нахождение детерминанты
    // SquareMatrix inverse() const;   // Нахождение обратной матрицы
    
    
    friend std::ostream& operator<<(std::ostream& os, const SquareMatrix& m);
    
    ~SquareMatrix() {
        std::cout << this << ": ~SquareMatrix()\n";
    }
};

std::ostream& operator<<(std::ostream& os, const SquareMatrix& m) {
    os << "SquareMatrix (" << m.rows << ", " << m.columns << "):\n";
    for (auto& i: m.data) {
        for (auto& k: i) {
            os << k << ' ';
        }
        os << '\n';
    }
    return os;
}

int main() {
    #define c std::cout

    // PART 1: Constructors
    Matrix m1;
    c << m1;
    Matrix m2(3);
    c << m2;
    Matrix m3(6, 4);
    c << m3;
    Matrix* m4 = new Matrix(4, 3, 10);
    c << *m4;
    Matrix m5 = m3;
    c << m5;
    Matrix m6 = std::move(m5);
    c << m6;

    // PART 2: Methods
    m6.setValue(1, 2, 341);
    m6.transpose();
    m6.setValue(2, 4, 123123);
    c << m6.getValue(1,1);
    c << m6;
    m6.resize(7, 8, 9);
    c << m6;
    m6.resize(3, 4, 77);
    c << m6;
    m6.resize(0, 0, 17);
    c << m6;
    m6.resize(1, 3, 17);
    c << m6;
    m6.clear();
    c << m6.isEmpty() << '\n';
    m6.resize(4, 6, 52);
    c << m6;
    m6.resize(0, 0, 123123);
    c << m6 << m6.isEmpty() << '\n';
    m6.resize(10, 9, 5);
    c << m6.getRowsSize() << '\n';
    
    m6.setRangeValue(0, m6.getRowsSize(), 4, 5, 0);
    m6.setRangeValue(6, 7, 0, m6.getColumnsSize(), 0);
    m6.setRangeValue(1, 3, 1, 4, 0);    
    m6.setRangeValue(8, 10, 5, 8, 1);    
    c << m6;

    Matrix m7 = m6.minor(4, 6);
    c << m7;

    // PART 3: Derived Class Constructors
    SquareMatrix s1;
    c << s1;
    SquareMatrix s2(4, 100);
    c << s2;
    SquareMatrix s3 {std::move(s2)};
    SquareMatrix s4 {s3};

    // PART 4: Derived Class Methods
    s4.fill(6);
    c << s4;
    s4.makeIdentity();
    s4.setValue(2, 1, 6);
    c << s4;
    s4.getSize();
    s4.clear();
    s4.resize(7, 3);
    c << s4;

    return 0;
}