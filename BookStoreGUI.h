#pragma once

#include <QtWidgets/QApplication>
#include <QLabel>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include <QListWidget>

#include "Service.h"
#include "CosGUI.h"
#include "MyTableView.h"

using namespace std;

class BookCartWindow;

class BookStoreGUI : public QWidget {
	friend class BookCartWindow;

private:

	BookService& service;

	//--------------adaugare, stergere si modificare---------------------------------------------------

	QLabel* label_titlu = new QLabel{ "Titlul: " };  //A QLabel is a widget in Qt used to display text or an image. 
	QLabel* label_autor = new QLabel{ "Autorul: " }; //Here, QLabel is used to create labels for user interface.
	QLabel* label_gen = new QLabel{ "Genul: " };
	QLabel* label_an = new QLabel{ "Anul de aparitie: " };

	
	QLineEdit* editTitlu;  //A QLineEdit is a widget in Qt used for single-line text input. 
	QLineEdit* editAutor;  // It's essentially a text box where the user can input text or numbers.
	QLineEdit* editGen;
	QLineEdit* editAn;

	QPushButton* AddBook_button;

	QPushButton* DeleteBook_button;

	QPushButton* ModifyBook_button;

	QPushButton* FindBook_button;

	
	//--------------lab 10 - clasa----------------------------------------------
	
	QGroupBox* genBox = new QGroupBox(tr("Nr de carti dupa gen"));
	
	QPushButton* Undo_button;

	QPushButton* ReloadData_button;

	QPushButton* Exit_button;

	QPushButton* OpenCart_button;
	BookCartWindow* bookCartWindow;

	QPushButton* CosCRUDGUI_button;
	QPushButton* CosReadOnlyGUI_button;

	//QTableWidget* tableBooks;
	QTableView* tableBooks;
	MyTableModel* myTableModel;

	QListWidget* listBooks;

	//----------gestionare cos------------------------------------------------
	QGroupBox* groupBox_cos = new QGroupBox(tr("Gestionare cos"));
  

	QPushButton* AddBookCos_button;

	//--------------goleste cosul---------------------------------------------------

	QPushButton* EmptyCart_button;


	//--------------adauga random in cos---------------------------------------------------

	QLabel* nrCarti_label = new QLabel{ "Nr de carti pe care doriti sa le adaugati: " };
	QLineEdit* nrCarti_edit;
	QPushButton* AddRandomToCart_button;

	QTableWidget* tableBooksCart;

	//-------------gestionare cos----------------------------------------------------------

	//--------------sortare-----------------------------------------------------

	QGroupBox* groupBox_sort = new QGroupBox(tr("Tip sortare"));
	QRadioButton* radioSort_Titlu = new QRadioButton(QString::fromStdString("Titlu"));  //Radio buttons are UI elements that allow users to choose 
	QRadioButton* radioSort_Autor = new QRadioButton(QString::fromStdString("Autor"));  //one option from a set of mutually exclusive options.
	QRadioButton* radioSort_An = new QRadioButton(QString::fromStdString("An"));
	QPushButton* SortBooks_button;

	//--------------filtrare-----------------------------------------------------

	QGroupBox* groupBox_filter = new QGroupBox(tr("Filtrare"));

	QLabel* filterTitlu_label = new QLabel{ "Titlul dupa care se face filtrarea: " };
	QLineEdit* filterTitlu_edit;
	QPushButton* FilterTitlu_button;

	QLabel* filterAn_label = new QLabel{ "Anul dupa care se face filtrarea: " };
	QLineEdit* filterAn_edit;
	QPushButton* FilterAn_button;

	//-------------------------------------------------------------------------

	void intializeGUIComponents();
	void connectSignalsSlots();
	void reloadBookList(vector<Book> allBooks);

public:
	BookStoreGUI(BookService& book_service) : service{ book_service } {
		intializeGUIComponents();
		connectSignalsSlots();
		reloadBookList(service.getAllBooks());
	}

	void guiAddBook();
	void guiDeleteBook();
	void guiModifyBook();
	void guiFindBook();
	void guiUndoBook();
	void guiOpenBookCartWindow();
	
public slots:
	// --------------lab 10 - clasa----------------------------------------------
	void showNrBooksByGenre(const QString& genre);
};



//clasa de Cos pentru lab 11, intre timp am imbunatatit implementarea pt cos :)
class BookCartWindow : public QWidget, public Observer
{
private:
	BookStoreGUI& bookStoreGUI;

	//--------------adaugare in cos---------------------------------------------------

	QLabel* label_titlu = new QLabel{ "Titlul: " };  //A QLabel is a widget in Qt used to display text or an image. 
	QLabel* label_autor = new QLabel{ "Autorul: " }; //Here, QLabel is used to create labels for user interface.


	QLineEdit* editTitlu;  //A QLineEdit is a widget in Qt used for single-line text input. 
	QLineEdit* editAutor;  // It's essentially a text box where the user can input text or numbers.

	QPushButton* AddBook_button;

	//--------------goleste cosul---------------------------------------------------

	QPushButton* EmptyCart_button;


	//--------------adauga random in cos---------------------------------------------------

	QLabel* nrCarti_label = new QLabel{ "Nr de carti pe care doriti sa le adaugati: " };
	QLineEdit* nrCarti_edit;
	QPushButton* AddRandomToCart_button;

	//--------------export cart---------------------------------------------------

	QLabel* numeFisier_label = new QLabel{ "Numele fisieruui in care doriti sa salvati cosul: " };
	QLineEdit* numeFisier_edit;
	QPushButton* ExportCart_button;

	QPushButton* Exit_button;

	QTableWidget* tableBooks;

	void intializeCartComponents();
	void connectSignalsSlots_CART();
	void reloadBookList_CART(vector<Book> cartBooks);

	void update() override {
		reloadBookList_CART(bookStoreGUI.service.getAllBooksFromCart());
	}
	
public:
	BookCartWindow(BookStoreGUI& gui, QWidget* parent = nullptr) : QWidget(parent), bookStoreGUI(gui) {
		intializeCartComponents();
		connectSignalsSlots_CART();
		reloadBookList_CART(bookStoreGUI.service.getAllBooksFromCart());
	}

	void guiAddBookToCart();
	void guiEmptyBooksCart();
	void guiAddRandomBooksToCart();
	void guiExportCart();
};
