#include "CosGUI.h"

void CosCRUDGUI::intializeCartComponents()
{


	QHBoxLayout* main_layout = new QHBoxLayout;  //a layout manager that arranges child widgets horizontally) 
	this->setLayout(main_layout);                //and sets it as the layout for the current widget (this).

	QWidget* left = new QWidget;                 //a generic widget in Qt
	QVBoxLayout* left_layout = new QVBoxLayout;  //a layout manager that arranges child widgets in a vertical column
	left->setLayout(left_layout);

	//--------------sterge cosul------------------------------------------------------------------------------------

	EmptyCart_button = new QPushButton("Goleste cosul");
	left_layout->addWidget(EmptyCart_button);

	//--------------adauga random in cos----------------------------------------------------------------------------
	QWidget* addRandom = new QWidget;
	QFormLayout* addRandom_layout = new QFormLayout;
	addRandom->setLayout(addRandom_layout);

	nrCarti_edit = new QLineEdit();
	addRandom_layout->addRow(nrCarti_label, nrCarti_edit);
	AddRandomToCart_button = new QPushButton("Adauga carti random");
	addRandom_layout->addWidget(AddRandomToCart_button);

	left_layout->addWidget(addRandom);

	//--------------tabelul cu carti---------------------------------------------------------------------------------

	//componenta din dreapta contine tabelul cu carti
	QWidget* right = new QWidget;
	QVBoxLayout* right_layout = new QVBoxLayout;
	right->setLayout(right_layout);

	int nr_lines = 1;
	int nr_columns = 4;
	this->tableBooks = new QTableWidget{ nr_lines, nr_columns };

	//setam header-ul tabelului
	QStringList table_HeaderList;
	table_HeaderList << "Titlu" << "Autor" << "Gen" << "An";
	this->tableBooks->setHorizontalHeaderLabels(table_HeaderList);

	//redimensioneaza celulele din tabel in fucntie de continut
	this->tableBooks->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	right_layout->addWidget(tableBooks);

	//--------------tabelul cu carti--------------------------------------------------------------------------------

	main_layout->addWidget(left);
	main_layout->addWidget(right);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CosCRUDGUI::connectSignalsSlots_CART() {
	cos.addObserver(this);
	QObject::connect(EmptyCart_button, &QPushButton::clicked, this, &CosCRUDGUI::guiEmptyBooksCart);

	QObject::connect(AddRandomToCart_button, &QPushButton::clicked, this, &CosCRUDGUI::guiAddRandomBooksToCart);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CosCRUDGUI::reloadBookList_CART(vector<Book> cartBooks) {
	this->tableBooks->clearContents();
	this->tableBooks->setRowCount(cartBooks.size());

	int line_number = 0;
	for (auto& book : cartBooks)
	{
		this->tableBooks->setItem(line_number, 0, new QTableWidgetItem(QString::fromStdString(book.getTitlu())));
		this->tableBooks->setItem(line_number, 1, new QTableWidgetItem(QString::fromStdString(book.getAutor())));
		this->tableBooks->setItem(line_number, 2, new QTableWidgetItem(QString::fromStdString(book.getGen())));
		this->tableBooks->setItem(line_number, 3, new QTableWidgetItem(QString::number(book.getAn())));
		line_number++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CosCRUDGUI::guiEmptyBooksCart()
{
	cos.emptyBooksCart();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CosCRUDGUI::guiAddRandomBooksToCart()
{
	int nr_carti = this->nrCarti_edit->text().toInt();
	nrCarti_edit->clear();
	cos.addRandomBooks(allBooks, nr_carti);
}