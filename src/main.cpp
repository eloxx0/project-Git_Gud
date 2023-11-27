#include "../include/Bookshelf.h"

using namespace std;

int main(){

    Bookshelf x;
    bool value= true;
    
    while(value){
    	cout<< "Inserire il comando da eseguire: premere P se si vuole inserire un libro nella libreria, E per eliminare un elemento, Q per chiudere lo stream buffer, R per ritornare un libro, B per prendere in prestito un libro"; 
      	char request;
      	cin>>request;
    	switch(request){
    		
    			
    		case 'P':	{
    		
    			cout<<"Inserire dati libro:"<<endl;
				cout<<"Inserire titolo"<<endl;
				string titolo;
				cin>> titolo;
				cout<<"Inserire nome dell'autore"<<endl;
				string nome;
				cin>> nome;
				cout<<"Inserire cognome dell'autore"<<endl;
				string cognome;
				cin>> cognome;
				cout<<"Inserire data del libro"<<endl;
				int data;
				cin>> data;
				cout<<"Inserire isbn"<<endl;
				/*try{
				
					string isbnvalid;
					cin>> isbnvalid;
					

				
				}
				
				catch(Invalid_Isbn_Argument()){
					cout<<"Vuoi generare un isbn valido? Inserire Y per generarlo"<<endl;
					string k;
					cin>>k;
					string newisbn= generate_isbn();
				
				}
				
				}	*/
  				
    			break;
    			
    		case 'E': x.pop_back();	
    			break;
    			
    		case 'B':
    			
    		case 'Q': value=true;
    			break;
    			
    		default:	cout<<"Hai inserito un comando non valido"<<endl;
    		
    	}
    
    }
    return 0;
    
}
