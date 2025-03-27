#pragma once
#include "Book.h"
#include <vector>
#include <map>
#include <algorithm>
#include <utility> 
#include <string>

using std::vector;
using std::map;
using std::pair;

class RepoException {
private:
	string errorMsg;

public:
	RepoException(string errorMsg) :errorMsg{ errorMsg } {};
	string getErrorMessage() {
		return this->errorMsg;
	}
};

class RepoAbstract {
public:
	virtual void store(const Book& b) = 0;
	virtual void delete_book(const Book& b) = 0;
	virtual bool exist_book(const Book& b) = 0;
	virtual const Book& find_book(string titlu, string autor) = 0;
	virtual int find_book_index(string titlu, string autor) = 0;
	virtual const Book update_book(string titlu, string autor, string gen_nou, int an_nou) = 0;
	virtual const vector<Book>& getAllBooks() noexcept = 0;
	virtual ~RepoAbstract() = default;
};




class BookRepository : public RepoAbstract {
private:
	vector<Book> allBooks;

public:

	BookRepository() = default;

	~BookRepository() {};


	//constructor de copiere
	//punem delete fiindca nu vrem sa se faca nicio copie la Repository
	//(in aplicatie avem 1 singur Repo)
	BookRepository(const BookRepository& ot) = delete;

	/*
	Adauga o carte in lista
	@param b: carte care se adauga (Book)
	@return: -
	@throws: RepoException daca o carte cu acelasi titlu si acelasi autor exista deja
	*/
	void store(const Book& b) override;

	/**
	 * Sterge o carte din lista
	 * @param titlu: titlu cartii ce dorim sa fie stearsa (string)
	 * @param autor: autorul cartii ce dorim sa fie stearsa (string)
	 * @throws: RepoException daca nu exista o carte de sters
	 */
	void delete_book(const Book& b) override;


	/*
	Verififca daca o carte data exista n lista
	@param b: cartea care se cauta in lista
	@return: true daca cartea exista, false altfel
	*/
	bool exist_book(const Book& b) override;


	/*
	Cauta o carte cu titlul si autorul dat

	@param titlu: titlul dupa care se cauta
	@param autor: autorul dupa care se cauta
	@returns: cartea cu titlul si autorul dat (daca exista)
	@throws: RepoException daca nu exista carte cu titlul si autorul dat*/
	const Book& find_book(string titlu, string autor) override;


	/**
	 * @brief: cauta o anumita carte dupa titlu si autor
	 * @param titlu: titlul cartii cautate (string)
	 * @param autor: autorul cartii cautate (string)
	 * @return: indexul pe care se afla cartea in vector sau -1 daca nu exista
	 */
	int find_book_index(string titlu, string autor) override;


	/**
	 * @brief modifica genul si anul unei carti cu titlul si autorul dat (apeleaza  update_book din repo)
	 * @param titlu: titlul cartii care trebuie modificata (string)
	 * @param autor: autorul cartii care trebuie modificata (string)
	 * @param gen_nou: noul gen (string)
	 * @param an_nou: noul an (int)
	 * @return: -
	 * @throws:  RepoException daca nu  exista carte cu titlu si autorul dat
	 */
	const Book update_book(string titlu, string autor, string gen_nou, int an_nou) override;


	/*
	Returneaza o lista cu toate cartile
	@return: lista cu cartile (vector<Book>&)
	*/
	const vector<Book>& getAllBooks() noexcept override;


};

class BookRepositoryFile : public BookRepository
{
private:
	string filename;

	/**
	 * @brief: Incarca datele din fisier
	 */
	void loadFromFile();

	/**
	 * @brief: Salveaza datele in fisier
	 */
	void saveToFile();

public:
	BookRepositoryFile(string file_name) :BookRepository(), filename(file_name) {
		loadFromFile();
	};
	void store(const Book& b) override;

	void delete_book(const Book& b) override;

	const Book update_book(string titlu, string autor, string gen_nou, int an_nou) override;

};

class BookRepositoryInMap : public RepoAbstract
{
private:
	map<pair<string, string>, Book> allBooks;

	double probabilitate;
	void determina_prob() const;


public:
	BookRepositoryInMap() = default;

	~BookRepositoryInMap() {};

	BookRepositoryInMap(const BookRepositoryInMap& ot) = delete;

	explicit BookRepositoryInMap(double probabilitate);

	void store(const Book& b) override;
	void delete_book(const Book& b) override;
	bool exist_book(const Book& b) override;
	const Book& find_book(string titlu, string autor) override;
	int find_book_index(string titlu, string autor) override;
	const Book update_book(string titlu, string autor, string gen_nou, int an_nou) override;
	const vector<Book>& getAllBooks() noexcept override;

};

void testeRepo();
void testeRepoFile();
void testeRepoMap();

