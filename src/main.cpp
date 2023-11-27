#include "../include/Bookshelf.h"

using namespace std;

int main(){

    Bookshelf x;
    bool done= false;
    
    while(!done){
    	cout<< "Inserire il comando da eseguire: premere P se si vuole inserire un libro nella libreria, E per eliminare l'ultimo libro aggiunto, Q per chiudere lo stream buffer, R per ritornare un libro, B per prendere in prestito un libro" << endl; 
        char request;
        cin>>request;
    	switch(request){
    		
    			
            case 'p':
    		case 'P':{

                Book new_book;

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
					cout<<"L'Isbn non rispetta lo standard (visualizzare questo link: " << url;
                    cout << " per istruzioni sullo standard). Vuoi generare un isbn valido? Inserire Y per generarlo"<<endl;

					char k;
					cin >> k;
                    cout << k;

                    if(k != 'Y' && k != 'y'){
                        break;
                    }

                    //uso il costruttore di base per generare un isbn valido, visto che lo stesso utilizza l'algoritmo
                    //di generazione di un isbn valido casuale
                    lib_isbn = Isbn();
                    cout<<" ho creato l'isbn " << lib_isbn << " per questo libro" << endl;
				
				}

                cout << "se vuoi inserire anche la data, premi Y" << endl;
                
                char a;
                Date date;
                int day;
                int month;
                int year;
                cin >> a;

                if(a == 'y' || a == 'Y'){
                    cout << "ok, inserire il giorno, il mese e l'anno separati da uno spazio" << endl;
                    cin >> day >> month >> year;
                    try{
                        date = Date(day, Month(month), year);
                    }
                    catch(Date::Invalid_argument e){
                        cout << "inserita data non valida, inizializzata alla data di default" << endl;
                    }
                    catch(Year::Invalid_year e){
                        cout << " inserito anno non valido, inizializzato alla data di default" << endl;
                    }

                    //uso il costruttore che richiede anche la data
                    new_book = Book(nome, cognome, titolo, lib_isbn, date);
                }
                else{
                    new_book = Book(nome, cognome, titolo, lib_isbn);
                }
                x.push_back(new_book);

                cout << "ok, ho aggiunto il libro alla tua libreria! Stato attuale della libreria: " << endl;
                printBookshelf(x);
                cout << endl;
				
    			break;
            }
    			
            case 'e':
    		case 'E': {
                x.pop_back();
    			break;
    			
            }

            case 'b':
    		case 'B':{

            }
    			
            case 'q':
    		case 'Q':{ 

                done = true;
    			break;
            }
    			
            default:   cout<<"Hai inserito un comando non valido"<<endl;
    		
    	}
    
    }
    
}
