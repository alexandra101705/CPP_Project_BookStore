#pragma once 
#include "Service.h"

class ConsoleUI {

private:
	BookService& service;

public:
	ConsoleUI(BookService& service) noexcept :service{ service } {};
	ConsoleUI(const ConsoleUI& ot) = delete;
	void printMenu();
	void uiAdd();
	void uiDelete();
	void uiModify();
	void uiUndo();
	void uiFind();
	void uiFilter();
	void uiSort();
	void printAllBooks();
	void printBooks(const vector<Book>& printBooks);
	void run();
	void addDefaultBooks();


	void runBooksCart();
	void printBooksCartMenu();
	void uiEmptyBooksCart();
	void uiAddToBooksCart();
	void uiAddRandomBooksToCart();
	void uiPrintBooksFromCart();
	void uiExport();
};