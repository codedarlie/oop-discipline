#include <iostream>
#include <vector>

class Matrix {
protected:
    size_t rows;
    size_t columns;
    std::vector<std::vector<int>> data;

public:
    Matrix(): rows{0}, columns{0} {
        std::cout << "Matrix::Constructor()\n";
    }
    Matrix(size_t r, size_t c, const int v = 0): rows{r}, columns{c} {
        std::cout << "Matrix::Constructor(rows, columns, value)\n";
        data = std::vector<std::vector<int>> (r);
        for (auto& i: data) {
            i = std::vector<int> (c, v);
        }
    }
    Matrix(const int value): Matrix(1, 1, value) {
        std::cout << "Matrix::Constructor(value)\n";
    };
    Matrix(const Matrix& m): rows{m.rows}, columns{m.columns}, data{m.data} {
        std::cout << "Matrix::Copy Constructor\n";
    }
    Matrix(Matrix&& m): rows{m.rows}, columns{m.columns}, data{std::move(m.data)} {
        std::cout << "Matrix::Move Constructor\n";
        m.rows = 0;
        m.columns = 0;
    } 
    
    void setValue(size_t i, size_t j, const int value) {
        std::cout << "Matrix::setValue()\n";
        if (i >= rows || j >= columns) throw std::out_of_range("Ошибка: Вышли за границы.\n");
        data[i][j] = value;
        return;
    }   
    void setRangeValue(size_t i1, size_t i2, size_t j1, size_t j2, const int value) {
        std::cout << "Matrix::setRangeValue()\n";
        if ((i1 >= rows) || (i2 > rows) || (j1 >= columns) || (j2 > columns)) throw std::out_of_range("Ошибка: Вышли за границы.\n");
        
        for (size_t i = i1; i < i2; ++i) {
            for (size_t j = j1; j < j2; ++j) {
                data[i][j] = value;
            }
        }
    }
    const int getValue(size_t i, size_t j) const {
        std::cout << "Matrix::getValue() const\n";
        if (i >= rows || j >= columns) throw std::out_of_range("Ошибка: Вышли за границы.\n");
        return data[i][j];
    }
    int& getValue(size_t  i, size_t j) {
        std::cout << "Matrix::getValue()\n";
        if (i >= rows || j >= columns) throw std::out_of_range("Ошибка: Вышли за границы.\n");
        return data[i][j];
    }
    size_t getRowsSize() const {
        std::cout << "Matrix::getRowsSize() ";
        return rows;
    }
    size_t getColumnsSize() const {
        std::cout << "Matrix::getColumnsSize() ";
        return columns;
    }
    const std::vector<std::vector<int>>& getData() const {
        std::cout << "Matrix::getData()\n";
        return data;
    }
    
    bool isEmpty() const;
    virtual void transpose() {
        std::cout << "Matrix::transpose()\n";

        std::vector<std::vector<int>> data2(columns);
        for (size_t i = 0; i < data2.size(); ++i) {
            data2[i] = std::vector<int> (rows);
            for (size_t k = 0; k < data2[i].size(); ++k) {
                data2[i][k] = data[k][i];
            }
        }
        data = std::move(data2);

        std::swap(columns, rows);
    }
    Matrix minor(size_t i, size_t j) {
        std::cout << "Matrix::minor()\n";
        if (i >= rows || j >= columns) throw std::out_of_range("Ошибка: Вышли за границы.\n");

        Matrix m(rows - 1, columns - 1);

        int m_i {0};
        for (size_t k = 0; k < rows; ++k) {
            if (k == j) continue;
            int m_j {0};
            for (size_t q = 0; q < columns; ++q) {
                if (q == i) continue;
                m.data[m_i][m_j] = data[k][q];
                ++m_j;
            }
            ++m_i;
        }
        return m;
    }
    void fill(const int value) {
        std::cout << "Matrix::fill()\n";
        for (auto& i: data) {
            for (auto& k: i) k = value;
        }
        
    }
    virtual void resize(size_t r, size_t c, const int value = 0) {
        if (!r && c || r && !c) throw std::out_of_range("Ошибка: Вышли за границы.\n");

        std::cout << "Matrix::resize()\n";

        data.resize(r);
        for (size_t i = rows; i < r; ++i) {
            data[i] = std::vector<int> (columns, value);
        }
        for (auto& i: data) {
            i.resize(c);
            for (size_t k = columns; k < c; ++k) {
                i[k] = value;
            }
        }
        columns = c;
        rows = r;
    }
    void clear() {
        std::cout << "Matrix::clear()\n";
        data.clear();
        rows = 0;
        columns = 0;
    }
    void swap(size_t i1, size_t j1, size_t i2, size_t j2) {
        std::cout << "Matrix::swap()\n";
        
        if (!(i1 < rows && i1 < rows && j1 < columns && j2 < columns)) throw std::out_of_range("Ошибка: Вышли за границы.\n");
        
        std::swap(data[i1][j1], data[i2][j2]);
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

    virtual ~Matrix() {
        std::cout << "~Matrix::Destructor\n";
        rows = 0;
        columns = 0;
        data.clear();
    }
};

bool Matrix::isEmpty() const {
    std::cout << "Matrix::isEmpty()\n";
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
public:
    SquareMatrix(const unsigned int i = 1, const int value = 0): Matrix(i, i, value) {
        std::cout << "SquareMatrix(i, value)\n";
    }
    SquareMatrix(const SquareMatrix& m): Matrix(m) {
        std::cout << "SquareMatrix(const SquareMatrix&)\n";
    }
    SquareMatrix(SquareMatrix&& m): Matrix(std::move(m)) {
        std::cout << "SquareMatrix(SquareMatrix&&)\n";
    }

    size_t getSize() const {
        std::cout << "getSize()\n";
        return rows;
    }
    
    void transpose() {
        std::cout << "SquareMatrix::transpose()\n";
        for (size_t i = 0; i < rows; ++i) {
            for (size_t k = 1 + i; k < rows; ++k) {
                swap(i, k, k, i);
            }
        }
    }
    const int trace() const {
        if (!rows) throw std::out_of_range("Ошибка: Вышли за границы.\n");

        int num {0};
        for (size_t i = 0; i < rows; ++i) {
            num += data[i][i];
        }
        return num;
    }
    
    void resize(const unsigned r, const unsigned c, const int value = 0) {
        std::cout << "SquareMatrix::resize()\n";
        if (r != c) throw std::invalid_argument("Ошибка: rows должен быть равен columns.\n");

        Matrix::resize(r, r, value);
    }
    void makeIdentity() {
        std::cout << "SquareMatrix::makeIdentity()\n";
        
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t k = 0; k < data[i].size(); ++k) {
                if (i == k) data[i][k] = 1;
                else data[i][k] = 0;
            }
        }
    }
    
    size_t getRowsSize() const = delete;
    size_t getColumnsSize() const = delete;
    
    friend std::ostream& operator<<(std::ostream& os, const SquareMatrix& m);
    
    ~SquareMatrix() {
        std::cout << "~SquareMatrix()\n";
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

class MatrixCalculator {
private:
    const Matrix* m1;
    const Matrix* m2;

    enum class Operations {addition, substraction, multiplication, divide};
    
    void operate(Operations op, Matrix& m) const {
        int m1c = m1->getColumnsSize();
        int m1r = m1->getRowsSize();
        int m2c = m2->getColumnsSize();
        int m2r = m2->getRowsSize();
        if ((m1c != m2c) || (m1r != m2r) || !m1c || !m1r) throw std::runtime_error("Ошибка: Матрицы разного размера.\n");

        m.resize(m1c, m1r);
        for (size_t i = 0; i < m1c; ++i) {
            for (size_t k = 0; k < m1r; ++k) {
                int value {0};

                switch (op)
                {
                case Operations::addition:
                    value = m1->getValue(i, k) + m2->getValue(i, k);
                    break;
                case Operations::substraction:
                    value = m1->getValue(i, k) - m2->getValue(i, k);
                    break;
                case Operations::multiplication:
                    value = m1->getValue(i, k) * m2->getValue(i, k);
                    break;
                case Operations::divide:
                    if (!m2->getValue(i, k)) throw std::runtime_error("Ошибка: деление на ноль.\n");
                    value = m1->getValue(i, k) / m2->getValue(i, k);
                    break;

                default:
                    throw std::runtime_error("Ошибка: Не выбрана операция");
                    break;
                }

                m.setValue(i, k, value);
            }
        }
    }

public:
    MatrixCalculator(): m1{new Matrix()}, m2{new Matrix()} {
        std::cout << "MatrixCalculator()\n";
    } 
    MatrixCalculator(const Matrix* pm1, const Matrix* pm2): m1{new Matrix(*pm1)}, m2{new Matrix(*pm2)} {
        std::cout << "MatrixCalculator(Matrix*, Matrix*)\n";
    }
    MatrixCalculator(const unsigned int rows, const unsigned int columns, const int value = 0): m1{new Matrix(rows, columns, value)}, m2{new Matrix(rows, columns, value)} {
        std::cout << "MatrixCalculator(rows, columns, value)\n";
    }

    void addition(Matrix& m) {
        operate(Operations::addition, m);
    }
    void substraction(Matrix& m) {
        operate(Operations::substraction, m);
    }
    void multiplication(Matrix& m) {
        operate(Operations::multiplication, m);
    }
    void divide(Matrix& m) {
        operate(Operations::divide, m);
    }

    ~MatrixCalculator() {
        std::cout << "~MatrixCalculator()\n";
        delete m1;
        delete m2;
    }
};

class MatrixWrapper {
private:
    std::string name;
    std::string description;
    Matrix m;

public:
    MatrixWrapper(const MatrixWrapper& mw): m{mw.m}, name{mw.name}, description{mw.description} {
        std::cout << "MatrixWrapper constructor: " << name << "(mw)\n";
    }
    MatrixWrapper(const Matrix& matrix, const std::string& n = "Unnamed", const std::string& d = "No Description"): m{matrix}, name{n}, description{d} {
        std::cout << "MatrixWrapper constructor: " << name << "(matrix)\n";
    }

    const Matrix& getMatrix() const {
        return m;
    }
    std::string getName() const {
        return name;
    }
    void setDescription(const std::string& d) {
        description = d; 
    }
    void setName(const std::string& n) {
        name = n; 
    }

    friend std::ostream& operator<<(std::ostream& os, const MatrixWrapper& m);

    ~MatrixWrapper() {
        std::cout << "~MatrixWrapper: " << name << '\n';
    }
};

std::ostream& operator<<(std::ostream& os, const MatrixWrapper& m) {
    os << "\n——————————————————————\n| MatrixWrapper:\n| Name: " << m.name << "\n| Description: " << m.description << "\n| Size: " << m.m.getRowsSize() << ", " << m.m.getColumnsSize() << "\n| Inside: ";
    for (auto& i: m.m.getData()) {
        os << "| ";
        for (auto& k: i) {
            os << k << ' ';
        }
        os << '\n';
    }
    os << "——————————————————————\n\n";
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
    delete m4;
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
    s4.resize(7, 7, 3);
    c << s4;

    // PART 5: Polymophism
    Matrix* p = new SquareMatrix();

    p->resize(7, 7, 6);
    p->setRangeValue(0, 4, 0, 1, 5);
    p->setRangeValue(0, 4, 1, 3, 3);
    p->setRangeValue(0, 3, 3, 6, 8);
    p->setRangeValue(3, 4, 3, 6, 9);
    c << *p;
    p->transpose();
    c << *p;
    p->transpose();


    // PART 6: Compositions (Matrix* and Matrix)
    Matrix* p2 = new SquareMatrix(s4);
    c << *p2;
    MatrixCalculator mc (p, p2);
    Matrix* pr = new SquareMatrix();
    mc.substraction(*pr);
    c << *pr;
    delete p2;
    delete p;

    MatrixWrapper* mw2 = new MatrixWrapper(*pr, "SquareMatrix", "Substraction Result");
    c << *mw2;
    Matrix m8 = mw2->getMatrix();
    c << m8;

    delete pr;
    delete mw2;

    return 0;
}