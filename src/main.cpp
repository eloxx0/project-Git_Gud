#include "../include/Bookshelf.h"
#include <limits>

using namespace std;

int int_from_char(char a){
    return (a - '0');
}


int main(){

    Bookshelf x;
    bool done= false;
    
    while(!done){
    	cout<< "Inserire il comando da eseguire:\n -Premere P se si vuole inserire un libro nella libreria\n -E per eliminare l'ultimo libro aggiunto\n -R per ritornare un libro\n -B per prendere in prestito un libro \n -Q per chiudere l'esecuzione del programma" << endl; 
        char request;
        cin>>request;
    	switch(request){
    		
    			
            case 'p':
    		case 'P':{

                Book dummy_book;

    			cout<<"Inserire dati libro:"<<endl;
				cout<<"Inserire titolo"<<endl;
				string titolo;

				getline(cin>>ws, titolo);

				cout<<"Inserire nome dell'autore"<<endl;

				string nome;

				getline(cin, nome);

				cout<<"Inserire cognome dell'autore"<<endl;

				string cognome;

				getline(cin, cognome);

				cout<<"Inserire isbn"<<endl;

                string isbn;

                //crea un oggetto Isbn utilizzando il costruttore di base.
                Isbn lib_isbn;
				try{
					cin>> isbn;
                    //quando assegno isbn, va a costruire un oggetto di tipo Isbn(isbn), quindi lancia eccezione se 
                    //l'input non è valido
                    lib_isbn = isbn;
				}
				
				catch(Isbn::Invalid_Isbn_Argument e){

                    string url = "https://it.wikipedia.org/wiki/ISBN";
					cout<<"L'Isbn non rispetta lo standard (visualizzare questo link: " << url
                        << " per istruzioni sullo standard, oppure visualizzare la libreria del progetto)."
                        << "Vuoi generare un isbn valido? y/n"<<endl;


                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
					char k;
					cin >> k;

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if(k != 'Y' && k != 'y'){
                        cout << "senza un isbn corretto non posso inserire il libro, ritorno al menu iniziale" << endl;
                        break;
                    }

                    //uso il costruttore di base per generare un isbn valido, visto che lo stesso utilizza l'algoritmo
                    //di generazione di un isbn valido casuale
                    lib_isbn = Isbn();
                    cout<<" ho creato l'isbn " << lib_isbn << " per questo libro" << endl;
				
				}

                cout << "Vuoi inserire anche la data? y/n" << endl;
                
                char a;
                cin >> a;
                //inizializzata dal costruttore di base al valore di default
                Date date;

                if(a == 'y' || a == 'Y'){
                    cout << "ok, inserire il giorno, il mese e l'anno separati da uno spazio" << endl;
                    int day;
                    int month;
                    int year;

                    //****necessario inserire tre input separati per procedere nell'esecuzione****
                    cin >> day;
                    cin >> month;
                    cin >> year;
                    //gestisce il caso in cui l'input non riceve interi corretti, pulendo il buffer di input
                    if (cin.fail()) {
                    cin.clear();
                    
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    try{
                        date = Date(day, Month(month), year);
                    }
                    catch(Date::Invalid_argument e){
                        cout << "inserita data non valida, inizializzata alla data di default" << endl;

                    }
                    catch(Year::Invalid_year e){
                        cout << " inserito anno non valido, inizializzato alla data di default" << endl;
                    }
                }
                else{
                    cout << "ok, utilizzo la data di default\n";
                }
             Book new_book = Book(nome, cognome, titolo, lib_isbn, date);
                x.push_back (new_book);

                cout << "ok, ho aggiunto il libro alla tua libreria! Stato attuale della libreria: " << endl;
                printBookshelf(x);
                cout << endl;
                
                //svuoto il buffer in modo da gestire il caso in cui in input ad a vengano passate
                //più stringhe
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

				
    			break;
            }
    			
            case 'e':
    		case 'E': {
                x.pop_back();
                cout << "eliminato l'ultimo libro aggiunto. Stato libreria:" << endl;
                printBookshelf(x);
    			break;
    			
            }

            case 'b':
    		case 'B':{

                cout << "Stato attuale della libreria: " << endl;
                   printBookshelf(x);
                   cout << endl;
                cout<<"Inserire isbn del libro che intende prendere in prestito:"<<endl;
                string isbn;
                
                cin>> isbn;
                if(string_isbn_valid(isbn)){
                    Isbn new_isbn(isbn);
                    //linear search
                    for(int i=0; i<x.size();i++){
                       //se isbn combaciano
                        if(new_isbn == x[i].getIsbn()){
                           //cambio lo stato del libro all'interno della libreria da disponibile a 
                           //non disponibile
                            borrow_book(x[i]);
                        }
                      }
                   
                } 
                else{
                    cout<<"Isbn non valido"<<endl;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            
            case 'r':
            case 'R': {

                cout<<"Inserire isbn sul libro che intende restituire:"<<endl;
                   string isbn;

                Isbn lib_isbn;
                cin>> isbn;
                if(string_isbn_valid(isbn)==true){
                    lib_isbn = isbn;
                    //poichè il confronto viene fatto tra gli isbn di un libro,
                    //che lo identificano univocamente, inizializzo il libro con il solo isbn in 
                    //modo da poter utilizzare il linearSearch e l'operatore == tra Book
                    Book dummy_book = Book("", "", "", lib_isbn);
                    /* for(int i=0; i<x.size();i++){ */
                    /*     //se isbn combaciano */
                    /*     if dummy_book==x[i]){ */
                    /*         //è possibile ritornare un libro solo se è già stato inserito */
                    /*         //all'interno della libreria, ma risulta non */
                    /*         //disponibile */
                    /*         return_book(x[i]); */
                    /*     }  */
                    /* } */

                    //uso il linear search, torna l'indice della bookshelf in cui 
                    //si trova il libro cercato, -1 se non è presente
                    int a = linearSearch(x, dummy_book);
                    if(a != -1){
                        return_book(x[a]);
                    }
                    else{
                        cout << "Ricordo che un libro può essere restituito solamente"
                            << "se era già in libreria e poi è stato preso in prestito."
                            << "impossibile restituire il libro richiesto";
                    }
                    cout << "Stato attuale della libreria: " << endl;
                    printBookshelf(x);
                    
                } 
                else{
                    cout<<"Isbn non valido"<<endl;
                }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
            	
            }
    			
            case 'q':
    		case 'Q':{ 
                cout << "ok, termino l'esecuzione del programma" << endl;
                done = true;
    			break;
            }
    			
            default:   cout<<"Hai inserito un comando non valido"<<endl;
    		
    	}
    
    }
    
}
