#pragma once
#include <string>
#include <algorithm>
#include <map>

#include "Repository.h"
#include "Validators.h"
#include "BooksCart.h"
#include "Undo.h"


class BookService {

private:
	RepoAbstract& repo;
	BookValidator& val;
	vector<ActiuneUndo*> undoActions;

	BooksCart booksList;

public:
	BookService(BookRepository& repo, BookValidator& val) noexcept :repo{ repo }, val{ val } {};
	~BookService();

	BooksCart& getBooksCart() {
		return this->booksList;
	}

	//constructor de copiere
	//punem delete fiindca nu vrem sa se faca nicio copie la Service
	//(in aplicatie avem 1 singur Service)
	BookService(const BookService& ot) = delete;

	/*
	Adauga o carte.
	*@param titlu: titlul cartii care se adauga (string)
	*@param autor: autorul cartii care se adauga (string)
	*@param gen: genul cartii care se adauga (string)
	*@durata an: anul cartii care se adauga (int)
	*
	* @throws:
	*	RepoException daca mai exista carte cu titlu si autorul dat
	*	ValidationException daca cartea nu este valida
	*/
	void addBook(string titlu, string autor, string gen, int an);

	/*
	Sterge o carte.
	*@param titlu: titlul cartii ce se doreste a fi stearsa (string)
	*@param autor: autorul cartii ce se doreste a fi stearsa (string)
	*@return: -
	*@throws:  RepoException daca nu  exista carte cu titlu si autorul dat
	*/
	void deleteBook(string titlu, string autor, string gen, int an);


	/**
	 * @brief modifica genul si anul unei carti cu titlul si autorul dat (apeleaza  update_book din repo)
	 * @param titlu: titlul cartii care trebuie modificata (string)
	 * @param autor: autorul cartii care trebuie modificata (string)
	 * @param gen_nou: noul gen (string)
	 * @param an_nou: noul an (int)
	 * @return: -
	 * @throws:  RepoException daca nu  exista carte cu titlu si autorul dat
	 */
	void modifyBook(string titlu, string autor, string gen_nou, int an_nou);


	/**
	 * @brief: returneaza cartea ce are titlul si autorul dat sau exceptie daca nu exista
	 * @param titlu: titlul cartii cautate (string)
	 * @param autor: autorul cartii cautate (string)
	 * @return: cartea cautata (Book&)
	 * @throws: RepoException daca nu  exista carte cu titlu si autorul dat
	 */
	const Book& findBook(string titlu, string autor);

	/*
	 * @brief: Returneaza un vector cu toate cartile
	 *  @return:  vector cu toate cartile
	*/
	const  vector<Book>& getAllBooks() noexcept {
		return this->repo.getAllBooks();
	}


	/**
	 * @brief returneaza un vector in care apar cartile cu titlul dat
	 * @param titlu: titlul dupa care se face filtrarea (string)
	 * @return: vector<Book>
	 */
	const  vector<Book>  filter_by_title(const string titlu);


	/**
	 * @brief returneaza un vector in care apar cartile cu anul dat
	 * @param an: anul dupa care se face filtrarea (int)
	 * @return: vector<Book>
	 */
	const  vector<Book> filter_by_year(const int an);



	/**
	 * @brief: returneaza un nou vector in care apar cartile sortate dupa titlu
	 * @return: vectot<Book>
	 */
	vector<Book> sortByTitle();


	/**
	 * @brief: returneaza un nou vector in care apar cartile sortate dupa autor
	 * @return: vectot<Book>
	 */
	vector<Book> sortByAuthor();

	/**
	 * @brief: returneaza un nou vector in care apar cartile sortate dupa an
	 * @return: vectot<Book>
	 */
	vector<Book> sortByYear();

	///////////////////////////////////////////////

	/**
	 * @brief:sterge toate cartile din cos
	 * @return: -
	 */
	void emptyBooksCart();

	/**
	 * @brief: Adauga o carte in cos
	 * @param titlu: titlul cartii care se doreste a fi adaugata
	 * @param autor: autorul cartii care se doreste a fi adaugata
	 * @throws: RepoException daca nu exista carte cu titlul si autorul dat
	 *
	 */
	void addToBooksCart(string titlu, string autor);

	/**
	 * @brief: Adauga un numar dat de carti in cos(aleatoriu)
	 * @param numar: nr e carti de adaugat
	 * @return: numarul de carti care s au adaugat de fapr(int)
	 */
	int addRandomBooksToCart(int numar);

	/**
	 * @brief: returneaza un vector ce contie cartile din cos
	 * @return: vector de carti
	 */
	vector<Book> getAllBooksFromCart();

	/**
	 * @brief: returneaza numarul de carti din cos
	 * @return: int
	 */
	int getNrBooksFromCart();

	int exportCart(string file_name);


	map<string, int> createMapGen();

	int getNumberBooksByGenre(const string& gen);


	void undo();
};

void testeService();


