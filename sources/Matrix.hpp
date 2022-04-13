#include <string> // for string class
#include <vector>
using namespace std;
namespace zich{
    class Matrix {
        vector<vector<double>> mat;

    public:
        Matrix(vector<double> arr,int,int);
        Matrix operator+(const Matrix& other) const;
        Matrix operator+();
        Matrix& operator+=(const Matrix& other);

        Matrix operator-(const Matrix& other) const;
        Matrix operator-();
        Matrix& operator-=(const Matrix& other);

        Matrix operator*(const Matrix& other) const;
        Matrix operator*(double scalar) const;
        Matrix& operator*=(double scalar);
        Matrix& operator*=(const Matrix& matrix);
        friend Matrix operator*(double scalar,const Matrix& matrix);

        Matrix& operator++();
        // postfix increment:
        Matrix operator++(int dummy_flag_for_postfix_increment);

        Matrix& operator--();
        // postfix increment:
        Matrix operator--(int dummy_flag_for_postfix_increment);


        bool operator==(const Matrix& other)const;
        bool operator!=(const Matrix& other)const;
        bool operator>(const Matrix& other)const;
        bool operator>=(const Matrix& other)const;
        bool operator<(const Matrix& other)const;
        bool operator<=(const Matrix& other)const;

        friend std::ostream& operator<< (std::ostream& output, const Matrix& matrix);
        friend std::istream& operator>> (std::istream& input , Matrix& matrix);
    };
}