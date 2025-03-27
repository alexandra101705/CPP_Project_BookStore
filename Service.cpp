#pragma once
#include "Service.h"
#include <assert.h>
#include <string>
#include <fstream>


void BookService::addBook(string titlu, string autor, string gen, int an)
{
	Book b{ titlu, autor, gen, an };
	val.valideaza(b);
	repo.store(b);
	undoActions.push_back(new UndoAdauga{ repo, b });
}


/////////////////////////////////////////////////////////////////////////////////////

void BookService::deleteBook(string titlu, string autor, string gen, int an)
{
	Book b{ titlu, autor, gen, an };
	repo.delete_book(b);
	undoActions.push_back(new UndoSterge{ repo, b });
}


/////////////////////////////////////////////////////////////////////////////////////

void BookService::undo()
{
	if (undoActions.empty())
		throw BookException{ "Nu se mai poate face undo.\n" };

	ActiuneUndo* act = undoActions.back();
	act->doUndo();
	undoActions.pop_back();
	delete act;
}

BookService::~BookService()
{
	for (auto act : undoActions) {
		delete act;
	}
}


/////////////////////////////////////////////////////////////////////////////////////

void BookService::modifyBook(string titlu, string autor, string gen_nou, int an_nou)
{
	Book new_book = Book{ titlu, autor, gen_nou, an_nou };
	Book old_book = repo.update_book(titlu, autor, gen_nou, an_nou);
	undoActions.push_back(new UndoModifica{ repo, old_book, new_book });
}

/////////////////////////////////////////////////////////////////////////////////////

const Book& BookService::findBook(string titlu, string autor)
{
	return repo.find_book(titlu, autor);
}

/////////////////////////////////////////////////////////////////////////////////////

const  vector<Book> BookService::filter_by_title(const string titlu)
{
	vector<Book> filteredBooks;
	const vector<Book>& all_books = getAllBooks();

	/*
	for (size_t i = 0; i < all_books.size(); i++)
		if (all_books[i].getTitlu() == titlu) {
			filteredBooks.push_back(all_books[i]);
		}
	*/

	std::copy_if(all_books.begin(), all_books.end(), back_inserter(filteredBooks),
		[titlu](const Book& b) noexcept {
			return b.getTitlu() == titlu;
		});

	return filteredBooks;
}

/////////////////////////////////////////////////////////////////////////////////////

const  vector<Book> BookService::filter_by_year(const int an)
{
	vector<Book> filteredBooks;
	const vector<Book>& all_books = getAllBooks();

	/*
	for (size_t i = 0; i < all_books.size(); i++)
		if (all_books[i].getAn() == an) {
			filteredBooks.push_back(all_books[i]);
		}
	*/

	std::copy_if(all_books.begin(), all_books.end(), back_inserter(filteredBooks),
		[an](const Book& b) noexcept {
			return b.getAn() == an;
		});
	return filteredBooks;
}

/////////////////////////////////////////////////////////////////////////////////////

vector<Book> BookService::sortByTitle() {
	vector<Book> sorted_title{ repo.getAllBooks() };

	sort(sorted_title.begin(), sorted_title.end(), compare_title);

	return sorted_title;
}

/////////////////////////////////////////////////////////////////////////////////////

vector<Book> BookService::sortByAuthor() {
	vector<Book> sorted_author{ repo.getAllBooks() };

	sort(sorted_author.begin(), sorted_author.end(), compare_author);

	return sorted_author;
}

/////////////////////////////////////////////////////////////////////////////////////

vector<Book> BookService::sortByYear() {
	vector<Book> sorted_year{ repo.getAllBooks() };

	sort(sorted_year.begin(), sorted_year.end(), compare_year);

	return sorted_year;
}
//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

void BookService::emptyBooksCart() {
	booksList.emptyBooksCart();
}

void BookService::addToBooksCart(string titlu, string autor) {
	const Book& book = repo.find_book(titlu, autor);
	booksList.addBookToCart(book);
}

int BookService::addRandomBooksToCart(int numar) {
	booksList.addRandomBooks(this->getAllBooks(), numar);
	return (int)booksList.getAllBooksFromCart().size();
}

vector<Book> BookService::getAllBooksFromCart() {
	return booksList.getAllBooksFromCart();
}

int BookService::getNrBooksFromCart() {
	return (int)booksList.getAllBooksFromCart().size();
}

int BookService::exportCart(string file_name)
{
	file_name += ".cvs";
	ofstream outFile(file_name);
	if (outFile.is_open()) {
		outFile << "Titlu, Autor, Gen, An\n";
		for (const Book& book : getAllBooksFromCart()) {
			outFile << book.getTitlu() << ", "
				<< book.getAutor() << ", "
				<< book.getGen() << ", "
				<< book.getAn() << "\n";
		}
		return 0;
	}
	else
		return 1;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

map<string, int> BookService::createMapGen()
{
	vector<Book> vector_carti = repo.getAllBooks();

	map<string, int> genNrMap;

	for (const Book& book : vector_carti)
	{
		const string& gen = book.getGen();

		if (genNrMap.find(gen) != genNrMap.end())
			genNrMap[gen]++;
		else
			genNrMap[gen] = 1;
	}

	return genNrMap;
}

int BookService::getNumberBooksByGenre(const string& gen) {
	map<string, int> genNrMap = createMapGen();

	if (genNrMap.find(gen) != genNrMap.end())
		return genNrMap[gen];
	else
		return 0; //genul nu a fost gasit, returneaza 0
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void testAddService()
{
	BookRepository testRepo;
	BookValidator testValid;
	BookService testService{ testRepo, testValid };

	testService.addBook("Singur pe lume", "Hector Malot", "fictiune", 1878);
	testService.addBook("Toate panzele sus!", "Radu Tudoran", "actiune", 1954);
	testService.addBook("Un apartament la Paris", "Michelle Gable", "istorie", 2015);

	assert(testService.getAllBooks().size() == 3);
	try {
		testService.addBook("Toate panzele sus!", "Radu Tudoran", "actiune", 1954);
	}
	catch (RepoException&) {
		assert(true);
	}

	try {
		testService.addBook("Carte", "", "actiune", 1954);
	}
	catch (ValidationException&) {
		assert(true);
	}

	try {
		testService.addBook("CARTE", "Radu Tudoran", "a", 1954);
	}
	catch (ValidationException&) {
		assert(true);
	}

	try {
		testService.addBook("", "Radu Tudoran", "actiune", 1954);
	}
	catch (ValidationException&) {
		assert(true);
	}

	try {
		testService.addBook("Carte", "Radu Tudoran", "actiune", 2025);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessages() == "Anul aparitiei nu poate fi peste 2024. \n");
	}
}

void testDeleteService()
{
	BookRepository testRepo;
	BookValidator testValid;
	BookService testService{ testRepo, testValid };

	testService.addBook("Singur pe lume", "Hector Malot", "fictiune", 1878);
	testService.addBook("Toate panzele sus!", "Radu Tudoran", "actiune", 1954);
	testService.addBook("Un apartament la Paris", "Michelle Gable", "istorie", 2015);

	testService.deleteBook("Toate panzele sus!", "Radu Tudoran", "actiune", 1954);
	assert(testService.getAllBooks().size() == 2);
}

void testFindService()
{
	BookRepository testRepo;
	BookValidator testValid;
	BookService testService{ testRepo, testValid };

	testService.addBook("Singur pe lume", "Hector Malot", "fictiune", 1878);
	testService.addBook("Toate panzele sus!", "Radu Tudoran", "actiune", 1954);
	testService.addBook("Un apartament la Paris", "Michelle Gable", "istorie", 2015);

	assert(testService.findBook("Singur pe lume", "Hector Malot").getAn() == 1878);
}

void testModifyService()
{
	BookRepository testRepo;
	BookValidator testValid;
	BookService testService{ testRepo, testValid };

	testService.addBook("Singur pe lume", "Hector Malot", "fictiune", 1878);
	testService.addBook("Toate panzele sus!", "Radu Tudoran", "actiune", 1954);
	testService.addBook("Un apartament la Paris", "Michelle Gable", "istorie", 2015);

	testService.modifyBook("Un apartament la Paris", "Michelle Gable", "favorit", 1950);

	assert(testService.findBook("Un apartament la Paris", "Michelle Gable").getAn() == 1950);
	assert(testService.findBook("Un apartament la Paris", "Michelle Gable").getGen() == "favorit");
}

void testFilterService()
{
	BookRepository testRepo;
	BookValidator testValid;
	BookService testService{ testRepo, testValid };

	testService.addBook("Singur pe lume", "Hector Malot", "fictiune", 1878);
	testService.addBook("Toate panzele sus!", "Radu Tudoran", "actiune", 1954);
	testService.addBook("Singur pe lume", "Michelle Gable", "istorie", 2015);

	const  vector<Book>& filtered_books = testService.filter_by_title("Singur pe lume");
	assert(filtered_books.size() == 2);

	const  vector<Book>& filtered_books_2 = testService.filter_by_year(2000);
	assert(filtered_books_2.size() == 0);
	const  vector<Book>& filtered_books_3 = testService.filter_by_year(1878);
	assert(filtered_books_3.size() == 1);
}

void testSortService()
{
	BookRepository testRepo;
	BookValidator testValid;
	BookService testService{ testRepo, testValid };

	testService.addBook("Singur pe lume", "Hector Malot", "fictiune", 2023);
	testService.addBook("Toate panzele sus!", "Radu Tudoran", "actiune", 1954);
	testService.addBook("In ape adanci", "Paula Hawkins", "thriller", 2017);


	const  vector<Book>& sorted_books_title = testService.sortByTitle();
	assert(sorted_books_title[1].getTitlu() == "Singur pe lume");

	const  vector<Book>& sorted_books_author = testService.sortByAuthor();
	assert(sorted_books_author[2].getGen() == "actiune");

	const  vector<Book>& sorted_books_year = testService.sortByYear();
	assert(sorted_books_year[1].getTitlu() == "In ape adanci");

	Book book4{ "Trandafirii pierduti", "Paula Hawkins", "istorie", 2017 };
	testRepo.store(book4);

	const  vector<Book>& sorted_books_year_gen = testService.sortByYear();
	assert(sorted_books_year_gen[1].getTitlu() == "Trandafirii pierduti");
	assert(sorted_books_year_gen[2].getTitlu() == "In ape adanci");

	Book book5{ "Trandafirii pierduti", "Autor", "arta", 2015 };
	testRepo.store(book5);

	const  vector<Book>& sorted_books_title_gen = testService.sortByTitle();
	assert(sorted_books_title_gen[3].getAutor() == "Autor");
	assert(sorted_books_title_gen[4].getAutor() == "Paula Hawkins");

	const  vector<Book>& sorted_books_author_gen = testService.sortByAuthor();
	assert(sorted_books_author_gen[2].getGen() == "istorie");
	assert(sorted_books_author_gen[3].getGen() == "thriller");
}

void testBooksCart()
{
	BookRepository testRepo;
	BookValidator testValid;
	BookService testService{ testRepo, testValid };

	testService.addBook("Singur pe lume", "Hector Malot", "fictiune", 1878);
	testService.addBook("Toate panzele sus!", "Radu Tudoran", "actiune", 1954);
	testService.addBook("Un apartament la Paris", "Michelle Gable", "istorie", 2015);
	testService.addBook("Casa din strada Sirenelor", "Octavian Soviany", "superstitii", 2017);
	testService.addBook("Cianura pentru un suras", "Rodica Ojog-Brasoveanu", "thriller", 1990);

	testService.addRandomBooksToCart(4);
	assert(testService.getAllBooksFromCart().size() == 4);
	assert(testService.getAllBooksFromCart().size() == testService.getNrBooksFromCart());
	testService.emptyBooksCart();
	assert(testService.getNrBooksFromCart() == 0);

	testService.addRandomBooksToCart(6);
	assert(testService.getNrBooksFromCart() == 5);
	testService.emptyBooksCart();

	testService.addToBooksCart("Un apartament la Paris", "Michelle Gable");
	assert(testService.getNrBooksFromCart() == 1);

	try {
		testService.addToBooksCart("carte", "Michelle Gable");
	}
	catch (RepoException&) {
		assert(true);
	}
}

void testExport()
{
	BookRepository testRepo;
	BookValidator testValid;
	BookService testService{ testRepo, testValid };

	assert(testService.exportCart("fisier") == 0);
	assert(testService.exportCart("restricted_directory/fisier") == 1);
}

void testCreateMap()
{
	BookRepository testRepo;
	BookValidator testValid;
	BookService testService{ testRepo, testValid };

	testService.addBook("Singur pe lume", "Hector Malot", "fictiune", 1878);
	testService.addBook("Toate panzele sus!", "Radu Tudoran", "actiune", 1954);
	testService.addBook("Un apartament la Paris", "Michelle Gable", "fictiune", 2015);
	testService.addBook("Casa din strada Sirenelor", "Octavian Soviany", "superstitii", 2017);
	testService.addBook("Cianura pentru un suras", "Rodica Ojog-Brasoveanu", "thriller", 1990);

	map<string, int> testMap;
	testMap = testService.createMapGen();

	assert(testMap["fictiune"] == 2);
	assert(testMap["thriller"] == 1);
	assert(testMap.size() == 4);
}

void testUndo()
{
	BookRepository testRepo;
	BookValidator testValid;
	BookService testService{ testRepo, testValid };

	testService.addBook("Singur pe lume", "Hector Malot", "fictiune", 1878);
	testService.addBook("Toate panzele sus!", "Radu Tudoran", "actiune", 1954);
	testService.addBook("Un apartament la Paris", "Michelle Gable", "fictiune", 2015);

	testService.undo();
	assert(testService.getAllBooks().size() == 2);
	testService.undo();
	testService.undo();
	assert(testService.getAllBooks().size() == 0);
	try {
		testService.undo();
	}
	catch (BookException& ex) {
		assert(ex.getErrorMessage() == "Nu se mai poate face undo.\n");
	}

	testService.addBook("Singur pe lume", "Hector Malot", "fictiune", 1878);
	testService.addBook("Toate panzele sus!", "Radu Tudoran", "actiune", 1954);
	testService.addBook("Un apartament la Paris", "Michelle Gable", "fictiune", 2015);

	testService.deleteBook("Un apartament la Paris", "Michelle Gable", "fictiune", 2015);
	testService.undo();
	assert(testService.getAllBooks().size() == 3);

	testService.modifyBook("Singur pe lume", "Hector Malot", "aa", 1900);
	testService.undo();
	assert(testService.findBook("Singur pe lume", "Hector Malot").getGen() == "fictiune");
}

void testeService()
{
	testAddService();
	testDeleteService();
	testFindService();
	testModifyService();
	testFilterService();
	testSortService();
	testBooksCart();
	testExport();

	testCreateMap();

	testUndo();
}
