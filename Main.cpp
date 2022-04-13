#include <iostream>
#include <stdexcept>
#include "string"
#include "Matrix.hpp"
#include <sstream>
#include <fstream>
using namespace zich;
using namespace std;



int main(){

    string str;
    vector<double> a = {2,0, -5,
                        6, -3, 4,
                        -6, 0, 9};

    Matrix mat1{a, 3, 3};
    Matrix mat2{a, 3, 3};
	do
	{
		cout << "welcome to the main program," << endl;
        cout << "insert 'input' to insert matices by yourself" << endl;
		cout << "or write 'example' to see different matrices" << endl;
		cout << "write exit for shut down the program" << endl;
		
		cin >> str;
		if(str!="exit"){
            if(str!="example"&&str!="input"){
                cout << "try a different input\n" << endl;
            }
			else {
                if(str=="example"){

                vector<double> v1;
                vector<double> v2;
                for (int i=0; i<16; i++){
                    v1.push_back((rand()%40)-20);
                    v2.push_back((rand()%40)-20);
                }
                Matrix mat3{v1, 4, 4};
                mat1=mat3;
                Matrix mat4{v2, 4, 4};
                mat2=mat4;
			}
                else{
                    try
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "insert the first matrix for example '[1 2 3], [4 5 6], [7 8 9]'" << endl;
                        cin >> mat1;
                        cout << "insert the second matrix for example '[1 2 3], [4 5 6], [7 8 9]'" << endl;
                        cin >> mat2;

                    }
                    catch(const invalid_argument& e)
                    {
                        cout << e.what() << endl;
                        cout << "try a different input\n" << endl;
                    }	
                }
                cout<<"mat1 is:"<<endl;
                cout<<mat1<<endl;
                cout<<"mat2 is:"<<endl;
                cout<<mat2<<endl;
                cout<<"mat1+mat2 is:"<<endl;
                cout<<mat1+mat2<<endl;
                cout<<"mat1-mat2 is:"<<endl;
                cout<<mat1-mat2<<endl;
                cout<<"mat1*mat2 is:"<<endl;
                cout<<mat1*mat2<<endl;
                cout<<"mat1*2 is:"<<endl;
                cout<<mat1*2<<endl;
                cout<<"mat1>mat2 is:"<< (mat1>mat2) <<endl;
                cout<<"mat1==mat2 is:"<< (mat1==mat2) <<endl;
                cout<<"mat1<mat2 is:"<< (mat1<mat2) <<endl;
                cout<<"mat1>=mat2 is:"<< (mat1>=mat2) <<endl;
                cout<<"mat1<=mat2 is:"<< (mat1<=mat2) <<endl;
                cout<<"++mat1 is:"<<endl;
                cout<<++mat1<<endl;
                cout<<"--mat2 is:"<<endl;
                cout<<--mat2<<endl;
                }
                
		
	    } 
    }while (str!="exit");

}
