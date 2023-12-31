#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <conio.h>
#include <fstream>
#define SPACE 10
using namespace std;


class Node {		//RED BLACK TREE
    string Name;  		int Semester, id;
    
	Node* right;   		Node* left;
	Node* parent;		int color;

    public:
    	
    Node() { id = color = 0;   left = right = parent = NULL;}
    
		void setValue(int id) 						{ this->id = id; 				}
		int getValue()  							{ return id; 			    	}
		void setName(string Name) 					{ this->Name = Name; 			}
		string getName()  							{ return Name; 			    	}
		void setSemester(int Semester) 				{ this->Semester = Semester; 	}
		int getSemester()  							{ return Semester; 				}
	

		void setcolor(int a)						{color = a;}	
		int getcolor()								{return color;}
		void setLeft(Node* a)						{left = a;}
		Node* getLeft()								{return left;} 	
		void setRight(Node* a)						{right = a;}
		Node* getRight()							{return right;} 
		void setParent(Node* a)						{parent = a;}
		Node* getParent()							{return parent;} 
	
};


class Students {
	
	Node* Root;
	Node* CN;
	Node* NN;
	Node* LCN;
	Node* TNULL;
	long long Total;
	
	public:


	Students(){
		
		Total = 0;
		TNULL = new Node;
		TNULL->setcolor(0);
		Root = CN = LCN = NN = TNULL;
	}
		
	void setRoot(Node* R){
		Root = R;
	}
	Node* getRoot(){
		return Root;
	}


	void RightRotate(Node* Y){
		
		Node* X  = Y->getLeft();
		Node* XR = X->getRight();
		
		
		Y->setLeft(XR);
		if(XR!=TNULL)
		XR->setParent(Y);
		X->setParent(Y->getParent());
		
		if(Y->getParent()==NULL){
			
			Root = X;
			
		}else if(Y == Y->getParent()->getLeft()){
			
				Y->getParent()->setLeft(X);
				
		}else {
			
				Y->getParent()->setRight(X);
		}
		
		X->setRight(Y);
		Y->setParent(X);

	}	
	
	void LeftRotate(Node* Y){
		
		Node* X  = Y->getRight();
		Node* XL = X->getLeft();
		
		Y->setRight(XL);
		if(XL!=TNULL)
		XL->setParent(Y);
		X->setParent(Y->getParent());
		
		
		if(Y->getParent()==NULL){
			
			Root = X;
			
		}else if(Y == Y->getParent()->getLeft()){
			
				Y->getParent()->setLeft(X);
				
		}else {
			
				Y->getParent()->setRight(X);
		}
		
		X->setLeft(Y);
		Y->setParent(X);
	
	}
	

	Node* Minimum(Node* N){
	
		if(N == NULL){
			cout<<"\n\t\t\t\t\t\t\tTREE IS EMPTY!";return N;		
		}

		while(N->getLeft() != TNULL){
			N = N->getLeft();
		}
	
		return N;
	}	
		


	void fixInsert(Node* k){
		Node* u;
	
		while (k->getParent()->getcolor() == 1) {
			
			if (k->getParent() == k->getParent()->getParent()->getRight()) {
				u = k->getParent()->getParent()->getLeft(); // uncle 
				if (u->getcolor() == 1) {
					// case 3.1			
					u->setcolor (0);
					k->getParent()->setcolor(0);
					k->getParent()->getParent()->setcolor(1) ;
					k = k->getParent()->getParent();
				} else {
					if (k == k->getParent()->getLeft()) {
						// case 3.2.2
						k = k->getParent();
						RightRotate(k);
					}
					// case 3.2.1
					k->getParent()->setcolor(0);
					k->getParent()->getParent()->setcolor(1);
					LeftRotate(k->getParent()->getParent());
				}
			} else {
				u = k->getParent()->getParent()->getRight(); // uncle
				
				if (u->getcolor() == 1) {
					// mirror case 3.1
					u->setcolor(0);
					k->getParent()->setcolor(0);
					k->getParent()->getParent()->setcolor(1) ;
					k = k->getParent()->getParent();	
				} else {
					if (k == k->getParent()->getRight()) {
						// mirror case 3.2.2
						k = k->getParent();
						LeftRotate(k);
					}
					// mirror case 3.2.1
					k->getParent()->setcolor(0);
					k->getParent()->getParent()->setcolor(1);
					RightRotate(k->getParent()->getParent());
				}
			}
			if (k == Root) {
				break;
			}
		}

		Root->setcolor (0);
	}


	void rbTransplant(Node* X, Node* Y){
		if (X->getParent() == NULL) {
			Root = Y;
		} else if (X == X->getParent()->getLeft()){
			X->getParent()->setLeft(Y);
		} else {
			X->getParent()->setRight(Y);
		}
		Y->setParent(X->getParent());
	}	
	

	void fixDelete(Node* X){
		Node*  s;
		
		while (X != Root && X->getcolor() == 0) {
			
			if (X == X->getParent()->getLeft()) {
				s = X->getParent()->getRight();
				if (s->getcolor() == 1) {
					// case 3.1
					s->setcolor(0) ;
					X->getParent()->setcolor(1);
					LeftRotate(X->getParent());
					s = X->getParent()->getRight();
				}

				if (s->getLeft()->getcolor() == 0 && s->getRight()->getcolor() == 0) {
					// case 3.2
					s->setcolor(1) ;
					X = X->getParent();
				} else {
					if (s->getRight()->getcolor() == 0) {
						// case 3.3
						s->getLeft()->setcolor(0);
						s->setcolor(1) ;
						RightRotate(s);
						s = X->getParent()->getRight();
					} 

					// case 3.4
					s->setcolor ( X->getParent()->getcolor());
					X->getParent()->setcolor(0);
					s->getRight()->setcolor(0) ;
					LeftRotate(X->getParent());
					X = Root;
				}
			} else {
				s = X->getParent()->getLeft();
				if (s->getcolor() == 1) {
					// case 3.1
					s->setcolor(0);
					X->getParent()->setcolor(1) ;
					RightRotate(X->getParent());
					s = X->getParent()->getLeft();
			    }

				if (s->getRight()->getcolor() == 0 && s->getLeft()->getcolor() == 0) {
					// case 3.2
					s->setcolor(1);
					X = X->getParent();
				} else {
					if (s->getLeft()->getcolor() == 0) {
						// case 3.3
						s->getRight()->setcolor(0) ;
						s->setcolor(1) ;
						LeftRotate(s);
						s = X->getParent()->getLeft();
					} 

					// case 3.4
					s->setcolor(X->getParent()->getcolor());
					X->getParent()->setcolor(0) ;
					s->getLeft()->setcolor(0);
					RightRotate(X->getParent());
					X = Root;
				} 
	    	}
		
	    }
	    X->setcolor(0);
    }
	void UpdateTree() {
			fstream file;
			file.open("Students.txt", ios :: in);
			if (file) {     
				int id,t;		string name;	
				//getline(file, name);		//to ignore the first blank line in file
				while (!file.eof()) {
					file >> id >> name >> t ;
					Add(id, name, t);
				}
				file.close();
			}
		}
		
		
	void SaveFile(Node* A){
			fstream file;
			if( A != TNULL) {
					
				file.open("Students1.txt", ios :: out | ios :: app );
				file<<endl<<setw(20)<<A->getValue();
				file<<setw(20)<<A->getName();
				file<<setw(20)<<A->getSemester();
				file.close();
				SaveFile(A->getLeft());
				SaveFile(A->getRight());	
			}
		}
		
		void DeleteFile() 		{remove("Students.txt");}
		
		void UpdateFile() {
			DeleteFile();
			rename("Students1.txt", "Students.txt");
		}
		
		
		
	void AddStudents() {
        	fstream file;		int size, val;
        	cout<<"How Many Students You Want To add:  ";   	cin>>size;
        	for(int j = 1;j <= size; j++) {
            	cout<<"\n*****Enter Student#"<<j<<" Details*****\n";    
            		
				file.open("Students.txt", ios :: out | ios :: app );
			
				int i;		cout<<"\nEnter The Student ID   :    ";	cin>>i;		file<<endl<<setw(20)<<i;
				string n;	cout<<"\nEnter The Student Name :    ";	cin>>n;		file<<setw(20)<<n;
				int t;	    cout<<"\nEnter The Student Semester :";	cin>>t;		file<<setw(20)<<t;
				
				Add(i, n, t);
				file.close();
        	}
    	}
    	
    	
    void Add(int v, string n, int t) {	
		
			NN = new Node;    	
			NN->setValue(v);			
			NN->setName(n);
			NN->setSemester(t);
											    
            NN->setLeft (TNULL);
			NN->setRight(TNULL);	
			NN->setParent(NULL);
			NN->setcolor(1);
			
			
        if (Root == TNULL){
			Root = NN;
			NN->setcolor(0);
			return;
		}

		CN = Root;
			
		while(CN != TNULL){
				
			LCN = CN;
				
			if(v < CN->getValue()){
				   CN = CN->getLeft();	
			}else  CN = CN->getRight();
	
			}
			
		if(v < LCN->getValue()) LCN->setLeft(NN);
		else                    LCN->setRight(NN);
		
		NN->setParent(LCN);	
	
	
		if(NN->getParent()->getParent() == NULL) return;
		fixInsert(NN);
    }
	
	
	void Search() {
		
    		int v;		cout<<"Enter Student ID:  ";   cin>>v;
    		
    		CN = Root;
	 
			while(CN != TNULL && CN->getValue() != v){
				LCN = CN;
	    		if(v < CN->getValue()) CN = CN->getLeft();
				else   				   CN = CN->getRight();
			 }

	 		
			if(CN != TNULL) {
				cout<<"\n*****Student Record Found*****\n\n";
				cout<<"NAME:      "<<CN->getName()<<endl;
				cout<<"SEMESTER:  "<<CN->getSemester()<<endl;
				cout<<"\n***********************\n";
			}  
			else { cout<<"\n*****Student Record Not Found*****\n"; } 
	}	

	
	void Update() {
			Search();		char choice;
					
			if(CN != TNULL) {
				int id,t;		string name; 		
				do {
					cout<<"\n\tXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n"
		      			<<"\n\t\t        Main Menu               \n"
		      			  "\n\tXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\n"
		      			  "\t1-> UPDATE NAME\n"
             	 		  "\t2-> UPDATE SEMESTER\n"
              			  "\t3-> MAIN MENU\n"
              			  "\t\t\t Choice = ";   cin>>choice;  system("cls");
            		switch(choice) {
                		case '1':	cout<<"\nEnter New Name     = ";  cin>>name;CN->setName(name); break;
                		case '2':	cout<<"\nEnter New Semester = ";  cin>>t;   CN->setSemester(t);    break;   
            		}   system("cls");
				}while(choice != '3');
				SaveFile(Root);		UpdateFile();
			}
	}

	void Delete() {

		Search();
		
		Node* W = CN;
		Node* Y = W ;
		Node* X = TNULL;

		if(CN == TNULL)
			return;
		
		cout<<" AND DELTED SUCCESSFULLY!";
		
		int y_original_color = Y->getcolor();
		
		if (W->getLeft() == TNULL) {
			X = W->getRight();
			rbTransplant(W, W->getRight());
		} else if (W->getRight() == TNULL) {
			X = W->getLeft();
			rbTransplant(W, W->getLeft());
		} else {
			Y = Minimum(W->getRight());
			y_original_color = Y->getcolor();
			X = Y->getRight();
			
			if (Y->getParent() == W) {
				X->setParent(Y);
			} else {
				rbTransplant(Y, Y->getRight());
				Y->setRight(W->getRight());
				Y->getRight()->setParent(Y);
			}

			rbTransplant(W, Y);
			Y->setLeft(W->getLeft())  ;
			Y->getLeft()->setParent(Y) ;
			Y->setcolor(W->getcolor());
		}
		delete W;
		if (y_original_color == 0){
			fixDelete(X);
		}
		SaveFile(Root);		UpdateFile();
	}
	
	void DisplayAll() {
			fstream file;
			file.open("Students.txt", ios :: in);
	
			if (!file) {      cout<<"\n****** No File Created ******\n";         }
	
			else {
				string view;
				
				cout<<"\n\t________________________________________________________________"<<"\n\n";
  				cout<<"\t"<<setw(10)<<"ID"<<setw(18)<<"NAME"<<setw(19)<<"SEMESTER";
  				cout<<"\n\t________________________________________________________________";
				getline(file, view);		//to ignore the first blank line in file
				while (!file.eof()) {
					getline(file, view);
					cout<<"\n\n"<<view;
				} 
				file.close();	
			}
		}
		
		
	void DisplayTree(Node* r, int space) {
			if (r == TNULL)  return;
    		space += SPACE; 
    		DisplayTree(r->getRight(), space); 
    		cout << endl;
    		for (int i = SPACE; i < space; i++)     cout << " ";  
    		cout << r->getValue() << "\n";
			for (int i = SPACE; i < space; i++)     cout << " ";  
    		cout << r->getName() << "\n";
    		for (int i = SPACE; i < space; i++) 	cout << " "; 
    		cout << r->getSemester() << "\n";
    		DisplayTree(r->getLeft(), space); 
		}
		
			void DeleteTree() {
			if(Root == TNULL)	return;	
			
			Node* temp;		CN = Root->getLeft();
			while(CN != TNULL) {
				temp = CN;
				CN = CN->getLeft();
				delete temp;
			}
			
			CN = Root->getRight();
			while(CN!= TNULL) {
				temp = CN;
				CN = CN->getRight();
				delete temp;
			}
			CN= Root;			delete CN;		
			DeleteFile();			Root = TNULL;
		}
};
