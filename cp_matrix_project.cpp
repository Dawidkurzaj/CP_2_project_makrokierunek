#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class mymatrix
{

public:			// rows(m) x columns(n)
    int m = 0;
    int n = 0;
    int oper = 0;
    vector < double >vmatrix;
    vector < double >inversmatrix;
    vector <double> error = {0};
    void matrix_dimensions(int mrow , int mcol){ //ustaw wymiary macierzy
        m = mrow;
        n = mcol;
        vmatrix.resize(m*n);
        inversmatrix.resize(m*n);
        //cout<<"Size:"<<vmatrix.size();
    };
    
       double& operator()(int mrow,int mcol){ //przepisanie wartości do macierzy
       	if(mrow*mcol>m*n){
       		cout<<"Element outside dimensions: "<<m<<"x"<<n<<"\n";
       		return error[0];
		   }else{
		   	return vmatrix[((mrow-1)*n)+(mcol-1)];
		   	
		   }
    };
	 
	 double det(){ // obliczenia wyznacznika macierzy
	 
	 	if(m == n){
	 		
	double mat[m][m];		//row col metodą macierzy trójkątnej
    int count = 0;
    int loop = 0;
    int swa = 0;
    int p = 0;
    double dziel; 
	double determinant = 1;
    for (int i = 0; i < m; i++)
      {
	for (int j = 0; j < m; j++)
	  {
	    mat[i][j] = vmatrix[count];
	    count++;
	  }
      }

    for (int i = 0; i < m - 1; i++)
      {
	for (int j = i + 1; j < m; j++)
	  {
	      if(mat[i][i] != 0) // Jeżeli element == 0 znandź inny element !=0 w kolumnie
	      {
	        dziel = mat[j][i] / mat[i][i];  
	      }else{
	          p = i+1;
	          do{
	              if(p < m){
	                if(mat[p][i] != 0 && i <m){
	                    for(int h = i;h<m;h++){
	                        swa = mat[i][h];
	                        mat[i][h] = mat[p][h];
	                        mat[p][h] = swa;
	                    }
	                  determinant = determinant * (-1);
	                  dziel = mat[j][i] / mat[i][i];
	                  loop = 1;
	                }else{
	                    p++;
	                }  
	              }else{
	                  loop = 1;
	              }

	          }while(loop == 0);
  
	      }

	    for (int k = i; k < m; k++)
	      {

		mat[j][k] = (mat[j][k] - (dziel * mat[i][k]));
	      }
	  }

      }
    for (int i = 0; i < m; i++)
      {
	determinant = determinant * mat[i][i];
      }
    //cout << "Determinant is equal:" << determinant<<endl;;
    
    return determinant;	
	 		
		 }else{
		 	cout<<"Matrix is not square matrix"<<endl;
		 	return 0;
		 }
		 
	 };
    
      double invers ()
  {

    double mat[m][m], idt[m][m];		//row col
    double count = 0;
    double loop = 0;
    double swa = 0;
    int p = 0;
    double mnoz =0;
    double mnozidt =0;
    double dziel = 1, determinant = 1;
    determinant = det(); //obliczanie wyznacznika 
    if(determinant !=0)
    {
    for (int i = 0; i < m; i++)
      {
	for (int j = 0; j < m; j++)
	  {
	    mat[i][j] = vmatrix[count]; // zapisanie vectora do tablicy
	    if(i == j){
	        idt[i][j] = 1;
	    }else {
	        idt[i][j] = 0;
	    }
	    count++;
	  }
      }

    for (int i = 0; i < m; i++)
      {
          if(mat[i][i] != 0)
	      {
	        dziel = mat[i][i];
	        for(int g = i;g<m;g++)
          {
              mat[i][g] = mat[i][g]/dziel; //dzielenie rzędu by otrzymać 1 na pozycji mat[i][i]
          }
          for(int g = 0;g<m;g++){
              idt[i][g] = idt[i][g]/dziel; //dzielenie rzędu
          }
	      }else{
	          p = i+1;
	          do{
	              if(p < m){
	                if(mat[p][i] != 0 && i <m){ //zamiana rzędów gdy pozycja mat[i][i] = 0
	                    for(int h = i;h<m;h++){
	                        swa = mat[i][h];
	                        mat[i][h] = mat[p][h];
	                        mat[p][h] = swa;
	                    }
	                  loop = 1;
	                }else{
	                    p++;
	                }  
	              }else{
	                  loop = 1;
	              }

	          }while(loop == 0);
  
	      }
	      
	for (int j = 0; j < m; j++)
	  {
	      mnoz = mat[j][i];
	      if(j != i){
	          for(int f = 0;f<m;f++){ //modyfikowanie elementów macierzy
	              mat[j][f] = mat[j][f] -(mnoz * mat[i][f]);
	              idt[j][f] = idt[j][f] -(mnoz * idt[i][f]);
	          }
	               
	      }
        
	  }



      }    	

	cout << endl;
	count = 0; 
	cout<<"Inverse matrix:\n";
	for (int i = 0; i < m; i++)
	  {
	    for (int j = 0; j < m; j++)
	      {
	      	inversmatrix[count] = idt[i][j]; //przypisanie elementów macierzy odwrotnej do vectora
			cout  << idt[i][j] << " ";
			count++;
	      }
	    cout << "\n";
	  }
	      	
	}else{
		cout<<"Det = 0\n";
	}

  };
  
mymatrix & operator= (const mymatrix & retmatrix)
  {
    
    switch(retmatrix.oper){
    	case 0:
    		
    	break;
    	
    	case 1:
    		vmatrix.resize(retmatrix.m*retmatrix.n);
    		//cout<<"C m:"<<retmatrix.m<<" n:"<<retmatrix.n;
    		m = retmatrix.m;
    		n = retmatrix.n;
		    for (int i = 0; i < retmatrix.vmatrix.size (); i++)
     		 {
     		 //	cout<<"C: "<<retmatrix.vmatrix[i]<<"\n";
				vmatrix[i] =retmatrix.vmatrix[i];
     		 }
    		return *this;
		
    	break;
    	
    	case 2:
    		
    	break;
	}
	return *this;
  };

};

mymatrix operator+ (mymatrix firstmatrix, mymatrix secondmatrix)
{
  mymatrix calc;
  if (firstmatrix.m == secondmatrix.m && firstmatrix.n == secondmatrix.n)
    {
    	calc.vmatrix.resize(firstmatrix.m*firstmatrix.n);
        
      for (int i = 0; i < firstmatrix.vmatrix.size (); i++)
	{
	  calc.vmatrix[i] = firstmatrix.vmatrix[i] + secondmatrix.vmatrix[i];

	}
	    calc.m = firstmatrix.m;
	    calc.n = firstmatrix.n;
	    calc.oper = 1;
      return calc;
    }else{
        
        return calc;
    }


}

mymatrix operator- (mymatrix firstmatrix, mymatrix secondmatrix)
{
  mymatrix calc;
  if (firstmatrix.m == secondmatrix.m && firstmatrix.n == secondmatrix.n)
    {
    	calc.vmatrix.resize(firstmatrix.m*firstmatrix.n);
        
      for (int i = 0; i < firstmatrix.vmatrix.size (); i++)
	{
	  calc.vmatrix[i] = firstmatrix.vmatrix[i] - secondmatrix.vmatrix[i];

	}
	    calc.m = firstmatrix.m;
	    calc.n = firstmatrix.n;
	    calc.oper = 1;
      return calc;
    }else{
        
        return calc;
    }


}

mymatrix operator* (mymatrix firstmatrix, mymatrix secondmatrix) // row2 = column1 ; rows(m) x columns(n) ; AB = rowA x columnB
{
  mymatrix calc;
  int matc = 0;
  int mcount = 0;
  if (firstmatrix.n == secondmatrix.m)
    {
    	calc.vmatrix.resize(firstmatrix.m*secondmatrix.n);
    	calc.m = firstmatrix.m;
    	calc.n = secondmatrix.n;
        
    for(int k=0, g=0;k<firstmatrix.m;k++,g=g+firstmatrix.n)
    {
    	for(int j=0;j<secondmatrix.n;j++,mcount++)
            {
            	matc = 0;
                for(int i=0;i<secondmatrix.m;i++)
                {
                    matc = matc + (firstmatrix.vmatrix[g+i] * secondmatrix.vmatrix[j+(secondmatrix.n*i)]);
                }
                calc.vmatrix[mcount] = matc;
                //cout<<"C:"<<calc.vmatrix[j*(k+1)]<<endl;
            }
	}
        
      calc.oper = 1;      
      return calc;
    }else{
        
        return calc;
    }


}

mymatrix operator* (mymatrix firstmatrix, double matrixmulti) // row2 = column1 ; rows(m) x columns(n) ; AB = rowA x columnB
{
  mymatrix calc;
    	calc.vmatrix.resize(firstmatrix.m*firstmatrix.n);
    	calc.m = firstmatrix.m;
    	calc.n = firstmatrix.n;
        
    for(int i;i<calc.vmatrix.size();i++)
    {
                calc.vmatrix[i] = firstmatrix.vmatrix[i]  * matrixmulti;
	}
        
      calc.oper = 1;      
      return calc;



}

ostream& operator<<(ostream& out , mymatrix disp){
	out<<"\nmatrix of dim:"<<disp.m<<"x"<<disp.n;
	disp.vmatrix.resize(disp.m*disp.n);
	for(int i=0;i<disp.vmatrix.size ();i++){
		if(i % disp.n == 0){
			out<<"\n";
		}
			out<<disp.vmatrix[i]<<" ";
	}
	return out;
}

ifstream& operator>>(ifstream& matrixread , mymatrix &matrixin){
	int row =0, col= 0;
	matrixread>>row>>col;
	matrixin.matrix_dimensions(row,col);
	for(int i;i<matrixin.vmatrix.size();i++){
		matrixread>>matrixin.vmatrix[i];	
	}
	return matrixread;
}

ofstream& operator<<(ofstream& matrixsave , mymatrix &matrixout){

	matrixsave<<matrixout.m<<" "<<matrixout.n;
	for(int i;i<matrixout.vmatrix.size();i++){
		matrixsave<<" "<<matrixout.vmatrix[i];
	}
	return matrixsave;
}

main ()
{
	double determ = 0;
  mymatrix X, Y, Z,K,S;
  	Y.matrix_dimensions(1,3);
	Z.matrix_dimensions(3,3);
	K.matrix_dimensions(3,3);
	S.matrix_dimensions(1,1);
	S(1,1) = 4; 
  Y.vmatrix ={1, 2, 3}; //można tak wpisać, ale vector może przyjąc więcej elementów niż powinno się mieścić w rozmiarze macierzy 
  Z.vmatrix ={ 7, 9,13,45,4,6,5,2,3};
 //Z.vmatrix = {5,5,5,5};
  X = Y * Z;
  cout<<X;
  Y(1,3) = 77; // poprawne wpisywanie elementów do macierzy
  cout<<Y;
   determ = S.det();
   Z.invers();
  cout<<"Determinant: "<<determ<<endl;
  
  	ifstream inp;
	inp.open ("matrix.txt");
		inp >> K;
		cout<<K;
	inp.close();
	
	  	ofstream oo;
	oo.open ("matrix1.txt");
		oo << Z;
		cout<<Z;
	oo.close();
  return 0;
}

