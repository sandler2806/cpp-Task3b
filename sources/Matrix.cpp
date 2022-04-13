#include <iostream>
#include "Matrix.hpp"
using namespace zich;
using namespace std;


Matrix::Matrix(vector<double> arr, int rowSize, int columnSize){
    if(arr.size()!=rowSize*columnSize){
        throw invalid_argument( "\nthe vector size is not equal to row size*column size" );
    }
    if(rowSize<=0||columnSize<=0){
        throw invalid_argument( "\nrow or column size must be positive" );
    }
    for (int i = 0; i < rowSize; ++i) {
        mat.push_back(vector<double>());
        for (int j = 0; j < columnSize; ++j) {
            int index=i*columnSize+j;
            mat.at(static_cast<unsigned long>(i)).push_back(arr.at(static_cast<unsigned long>(index)));
        }
    }
}

Matrix Matrix::operator+(const Matrix &other) const {
    if(this->mat.size()!=other.mat.size()||this->mat.at(0).size()!=other.mat.at(0).size()){
        throw invalid_argument( "\nThe matrices are not the same size" );
    }
    vector<double>vector;
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            vector.push_back(this->mat.at(i).at(j)+other.mat.at(i).at(j));
        }
    }
    return Matrix{vector, static_cast<int>(this->mat.size()), static_cast<int>(this->mat.at(0).size())};
}

Matrix Matrix::operator+() {
    vector<double> vector;
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            vector.push_back(this->mat.at(i).at(j));
        }
    }
    return Matrix{vector, static_cast<int>(this->mat.size()), static_cast<int>(this->mat.at(0).size())};
}

Matrix& Matrix::operator+=(const Matrix &other) {
    if(this->mat.size()!=other.mat.size()||this->mat.at(0).size()!=other.mat.at(0).size()){
        throw invalid_argument( "\nThe matrices are not the same size" );
    }
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            if(this->mat.at(i).at(j)!=0){
                this->mat.at(i).at(j)+=other.mat.at(i).at(j);
            }
        }
    }
    return *this;
}

Matrix Matrix::operator-(const Matrix &other) const {
    if(this->mat.size()!=other.mat.size()||this->mat.at(0).size()!=other.mat.at(0).size()){
        throw invalid_argument( "\nThe matrices are not the same size" );
    }
    vector<double>vector;
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            vector.push_back(this->mat.at(i).at(j)-other.mat.at(i).at(j));
        }
    }
    return Matrix{vector, static_cast<int>(this->mat.size()), static_cast<int>(this->mat.at(0).size())};
}

Matrix Matrix::operator-() {
    vector<double> vector;
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            if(this->mat.at(i).at(j)!=0){
                vector.push_back(-1*this->mat.at(i).at(j));
            }
            else{
                vector.push_back(this->mat.at(i).at(j));
            }
        }
    }
    return Matrix{vector, static_cast<int>(this->mat.size()), static_cast<int>(this->mat.at(0).size())};
}

Matrix& Matrix::operator-=(const Matrix &other) {
    if(this->mat.size()!=other.mat.size()||this->mat.at(0).size()!=other.mat.at(0).size()){
        throw invalid_argument( "\nThe matrices are not the same size" );
    }
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            if(this->mat.at(i).at(j)!=0){
                this->mat.at(i).at(j)-=other.mat.at(i).at(j);
            }
        }
    }
    return *this;
}

std::ostream &zich::operator<<(ostream &output, const Matrix &matrix) {
    string str;
    if(matrix.mat.empty()||matrix.mat.at(0).empty()){
        throw invalid_argument( "\nthe matrix is empty" );
    }
    // convert the matrix to string
    for (unsigned long i = 0; i < matrix.mat.size(); ++i) {
        str+='[';
        for (unsigned long j = 0; j < matrix.mat.at(0).size(); ++j) {
            double x=matrix.mat.at(i).at(j);
            str+= to_string(x);
            str.erase ( str.find_last_not_of('0') + 1, string::npos );
            if(isdigit(str[str.length()-1])==0){
                str[str.length()-1]=' ';
            }
            else{
                str+=' ';
            }
        }
        str.erase ( str.length()-1);
        str+="]\n";
    }
    str.pop_back();
    return output<<str;
}

std::istream &zich::operator>>(istream &input, Matrix &matrix) {
    matrix.mat.clear();
    string number;
    string str;
    double num=0;
    unsigned long row=0;
    unsigned long column=0;
    matrix.mat.push_back(vector<double>());
    if (input.get()!='['){
        throw invalid_argument( "\nthe input is not valid" );
    }
    for(char c=0; input.get(c)&&c!='\n';){
        str+=c;
        if(c==']'&&isdigit(str.at(str.length()-2))==0) {
            throw invalid_argument( "\nthe input is not valid" );
        }
        if (c=='['){
            if(str.at(str.length()-2)!=' '||str.at(str.length()-3)!=','){
                throw invalid_argument( "\nthe input is not valid" );
            }
            column=0;
            matrix.mat.push_back(vector<double>());
            row++;
        }
        else if((c==' '|| c==']')&&number.length()!=0){
            cout<<number<<endl;
            num= stod(number);
            cout<<num<<endl;
            matrix.mat.at(row).push_back(num);
            column++;
            number="";
        }
        else if (isdigit(c)!=0||c=='-'||c=='.'){
            number+=c;
        }
    }
    if(str.at(str.length()-1)!=']') {
        throw invalid_argument( "\nthe input is not valid" );
    }

        return input;
}

Matrix zich::operator*(double scalar, const Matrix &matrix) {
    vector<double>vector;
    for (unsigned long i = 0; i < matrix.mat.size(); ++i) {
        for (unsigned long j = 0; j < matrix.mat.at(0).size(); ++j) {
            if(matrix.mat.at(i).at(j)!=0){
                vector.push_back(scalar*matrix.mat.at(i).at(j));
            }
            else{
                vector.push_back(matrix.mat.at(i).at(j));
            }
        }
    }
    return Matrix{vector, static_cast<int>(matrix.mat.size()), static_cast<int>(matrix.mat.at(0).size())};
}

Matrix Matrix::operator*(double scalar) const {
    return scalar*(*this);
}
Matrix& Matrix::operator*=(const Matrix& matrix){
    *this=*this*matrix;
    return *this;
}
Matrix& Matrix::operator*=(double scalar){
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            if(this->mat.at(i).at(j)!=0){
                this->mat.at(i).at(j)*=scalar;
            }
        }
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix &other) const {
    if(this->mat.at(0).size()!=other.mat.size()){
        throw invalid_argument( "\nmultiple metrics is valid only if the column size of the first equal to the row size of the second" );
    }

    vector<double> vector;
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < other.mat.at(0).size(); ++j) {
            double sum=0;
            for (unsigned long k = 0; k < other.mat.size(); ++k) {
                sum+= this->mat.at(i).at(k)*other.mat.at(k).at(j);
            }
            vector.push_back(sum);
        }
    }
    return Matrix{vector, static_cast<int>(this->mat.size()), static_cast<int>(other.mat.at(0).size())};
}

bool Matrix::operator==(const Matrix &other)const {
    if(this->mat.size()!=other.mat.size()||this->mat.at(0).size()!=other.mat.at(0).size()){
        throw invalid_argument( "\nThe matrices are not the same size" );
    }
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            if(this->mat.at(i).at(j)!=other.mat.at(i).at(j)){
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &other)const {
    if(this->mat.size()!=other.mat.size()||this->mat.at(0).size()!=other.mat.at(0).size()){
        throw invalid_argument( "\nThe matrices are not the same size" );
    }
    return !(*this==other);
}

bool Matrix::operator>(const Matrix &other)const {
    if(this->mat.size()!=other.mat.size()||this->mat.at(0).size()!=other.mat.at(0).size()){
        throw invalid_argument( "\nThe matrices are not the same size" );
    }
    double sumA=0;
    double sumB=0;
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            sumA+=this->mat.at(i).at(j);
            sumB+=other.mat.at(i).at(j);
        }
    }
    return sumA>sumB;
}

bool Matrix::operator>=(const Matrix &other)const {
    if(this->mat.size()!=other.mat.size()||this->mat.at(0).size()!=other.mat.at(0).size()){
        throw invalid_argument( "\nThe matrices are not the same size" );
    }
    return *this==other||*this>other;
}

bool Matrix::operator<(const Matrix &other)const {
    if(this->mat.size()!=other.mat.size()||this->mat.at(0).size()!=other.mat.at(0).size()){
        throw invalid_argument( "\nThe matrices are not the same size" );
    }
    return other>*this;
}

bool Matrix::operator<=(const Matrix &other)const {
    if(this->mat.size()!=other.mat.size()||this->mat.at(0).size()!=other.mat.at(0).size()){
        throw invalid_argument( "\nThe matrices are not the same size" );
    }
    return other>=*this;
}

Matrix& Matrix::operator++() {
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            this->mat.at(i).at(j)++;
        }
    }
    return *this;
}

Matrix Matrix::operator++(int dummy_flag_for_postfix_increment) {
    Matrix copy = *this;
    ++(*this);
    return copy;
}

Matrix& Matrix::operator--() {
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            this->mat.at(i).at(j)--;
        }
    }
    return *this;
}

Matrix Matrix::operator--(int dummy_flag_for_postfix_increment) {
    Matrix copy = *this;
    --(*this);
    return copy;
}



