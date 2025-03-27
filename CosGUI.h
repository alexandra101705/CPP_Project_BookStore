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
#include <QPainter>

#include "BooksCart.h"

using namespace std;

class CosCRUDGUI : public QWidget, public Observer
{
private:
	BooksCart& cos;
	vector<Book> allBooks;

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
		reloadBookList_CART(cos.getAllBooksFromCart());
	}

public:
	CosCRUDGUI(BooksCart& cart, const vector<Book>& books) : cos{ cart }, allBooks{ books } {
		intializeCartComponents();
		connectSignalsSlots_CART();
		reloadBookList_CART(cos.getAllBooksFromCart());
	}

	~CosCRUDGUI() {
		cos.addObserver(this);
	}

	void guiEmptyBooksCart();
	void guiAddRandomBooksToCart();
};


class CosReadOnlyGUI : public QWidget, public Observer
{
	BooksCart& cos;

public:
	CosReadOnlyGUI(BooksCart& cos) : cos{ cos } {
		cos.addObserver(this);
	};

	~CosReadOnlyGUI() {
		cos.removeObserver(this);
	}

	void update() override {
		repaint();
	}

	void paintEvent(QPaintEvent* ev) override
	{
		QPainter p{ this };
		int x = 10;
		
		for (auto& book : cos.getAllBooksFromCart())
		{
			QImage image("carte_mica.jpg");
			QImage scaledImage = image.scaled(book.getAn() / 10, book.getAn() / 10, Qt::KeepAspectRatio);
			p.drawImage(x, 0, scaledImage);
			x += book.getAn() / 10 + 10;
		}
	}

};