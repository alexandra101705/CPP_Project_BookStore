#include "BookStoreGUI.h"
#include <map>

using namespace std;

void BookStoreGUI::intializeGUIComponents() {


	QHBoxLayout* main_layout = new QHBoxLayout;  //a layout manager that arranges child widgets horizontally) 
	this->setLayout(main_layout);                //and sets it as the layout for the current widget (this).
	
	QWidget* left = new QWidget;                 //a generic widget in Qt
	QVBoxLayout* left_layout = new QVBoxLayout;  //a layout manager that arranges child widgets in a vertical column
	left->setLayout(left_layout);

	//--------------adaugare,stergere si modifica------------------------------------------------------------------------------------

	QWidget* form = new QWidget;
	QFormLayout* form_layout = new QFormLayout;   //A QFormLayout in Qt is a layout manager designed to arrange widgets in a form-like structure.
	form->setLayout(form_layout);
	
	editTitlu = new QLineEdit;
	editAutor = new QLineEdit;
	editGen = new QLineEdit;
	editAn = new QLineEdit;
	
	form_layout->addRow(label_titlu, editTitlu);
	form_layout->addRow(label_autor, editAutor);
	form_layout->addRow(label_gen, editGen);
	form_layout->addRow(label_an, editAn);

    //Create the layout for the add, delete and modify buttons
	QWidget* add_delete_modify = new QWidget;
	QHBoxLayout* add_delete_modify_layout = new QHBoxLayout;
	add_delete_modify->setLayout(add_delete_modify_layout);
	
	AddBook_button = new QPushButton("Adauga");
	add_delete_modify_layout->addWidget(AddBook_button);

	DeleteBook_button = new QPushButton("Sterge");
	add_delete_modify_layout->addWidget(DeleteBook_button);

	ModifyBook_button = new QPushButton("Modifica");
	add_delete_modify_layout->addWidget(ModifyBook_button);

	FindBook_button = new QPushButton("Cauta");
	add_delete_modify_layout->addWidget(FindBook_button);

	form_layout->addRow(add_delete_modify);
	left_layout->addWidget(form);


	//--------------lab 10 - clasa------------------------------------------------------------------------------------
	/*
	map<string, int> genNrMap = service.createMapGen();
	QVBoxLayout* genLayout = new QVBoxLayout;

	for (const auto& pair : genNrMap) {
		QPushButton* genreButton = new QPushButton(QString::fromStdString(pair.first));
		genLayout->addWidget(genreButton);
		connect(genreButton, &QPushButton::clicked, [=]() {
			showNrBooksByGenre(genreButton->text());
			});
	}
	genBox->setLayout(genLayout);

	left_layout->addWidget(genBox);
	*/


	
	//--------------undo--------------------------------------------------------------------------------------------

	Undo_button = new QPushButton("Undo");
	left_layout->addWidget(Undo_button);


	 //--------------reload data--------------------------------------------------------------------------------------

	 ReloadData_button = new QPushButton("Afiseaza toate cartile (reload data)");
	 left_layout->addWidget(ReloadData_button);

	 //--------------exit--------------------------------------------------------------------------------------------

	 Exit_button = new QPushButton("Exit");
	 left_layout->addWidget(Exit_button);
     
	 //--------------imagine--------------------------------------------------------------------------------------------

	 QLabel* imageLabel = new QLabel;
	 QPixmap image("carte.jpg"); // Load the image

	 // Resize the image
	 QPixmap resizedImage = image.scaled(200, 150);

	 imageLabel->setPixmap(resizedImage);


	 left_layout->addWidget(imageLabel);

	//--------------tabelul cu carti---------------------------------------------------------------------------------

	//componenta din dreapta contine tabelul cu carti
	QWidget* right = new QWidget;
	QVBoxLayout* right_layout = new QVBoxLayout;
	right->setLayout(right_layout);

	/*
	int nr_lines = 5;
	int nr_columns = 4;
	this->tableBooks = new QTableWidget{ nr_lines, nr_columns };

    //setam header-ul tabelului
	QStringList table_HeaderList;
	table_HeaderList << "Titlu" << "Autor" << "Gen" << "An";
	this->tableBooks->setHorizontalHeaderLabels(table_HeaderList);

	//redimensioneaza celulele din tabel in fucntie de continut
	this->tableBooks->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	*/

	this->tableBooks = new QTableView();
	vector<Book> all_books = service.getAllBooks();
	this->myTableModel = new MyTableModel(all_books, this);

	this->tableBooks->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	tableBooks->setModel(myTableModel);

	right_layout->addWidget(tableBooks);

	//--------------tabelul cu carti--------------------------------------------------------------------------------

	//--------------lista cu carti---------------------------------------------------------------------------------
	
	QWidget* list = new QWidget;                  
	QVBoxLayout* list_layout = new QVBoxLayout;   
	list->setLayout(list_layout);

	QLabel* listHeader = new QLabel("Titlu    |    Autor    |    Gen    |    An");
	listHeader->setAlignment(Qt::AlignCenter);  

	list_layout->addWidget(listHeader);

	listBooks = new QListWidget;
	vector<Book> allBooks = service.getAllBooks();
	for (auto& book : allBooks)
	{
		QString itemText = QString::fromStdString(book.getTitlu() + "  |  " + book.getAutor() + "  |  " + book.getGen() + "  |  " + to_string(book.getAn()));
		listBooks->addItem(itemText);
	}

	list_layout->addWidget(listBooks);
	//--------------lista cu carti---------------------------------------------------------------------------------

	//--------------sortare--------------------------------------------------------------------------------------------

	QVBoxLayout* sortRadioBox_layout = new QVBoxLayout;
	this->groupBox_sort->setLayout(sortRadioBox_layout);
	sortRadioBox_layout->addWidget(radioSort_Titlu);
	sortRadioBox_layout->addWidget(radioSort_Autor);
	sortRadioBox_layout->addWidget(radioSort_An);

	SortBooks_button = new QPushButton("Sorteaza cartile");
	sortRadioBox_layout->addWidget(SortBooks_button);

	right_layout->addWidget(groupBox_sort);

	//--------------filtrare--------------------------------------------------------------------------------------------

	QFormLayout* formFilter_layout = new QFormLayout;
	this->groupBox_filter->setLayout(formFilter_layout);

	filterTitlu_edit = new QLineEdit();
	formFilter_layout->addRow(filterTitlu_label, filterTitlu_edit);
	FilterTitlu_button = new QPushButton("Filtreaza dupa titlu");
	formFilter_layout->addWidget(FilterTitlu_button);

	filterAn_edit = new QLineEdit();
	formFilter_layout->addRow(filterAn_label, filterAn_edit);
	FilterAn_button = new QPushButton("Filtreaza dupa an");
	formFilter_layout->addWidget(FilterAn_button);

	right_layout->addWidget(groupBox_filter);

	//-----------------gestionare cos------------------------------------------------------------------------------------------------

	QVBoxLayout* cart_layout = new QVBoxLayout;  //a layout manager that arranges child widgets in a vertical column
	groupBox_cos->setLayout(cart_layout);

	//--------------adaugare in cos------------------------------------------------------------------------------------

	AddBookCos_button = new QPushButton("Adauga carte in cos");
	cart_layout->addWidget(AddBookCos_button);

	//--------------sterge cosul------------------------------------------------------------------------------------

	EmptyCart_button = new QPushButton("Goleste cosul");
	cart_layout->addWidget(EmptyCart_button);

	//--------------adauga random in cos----------------------------------------------------------------------------

	QWidget* addRandom = new QWidget;
	QFormLayout* addRandom_layout = new QFormLayout;
	addRandom->setLayout(addRandom_layout);

	nrCarti_edit = new QLineEdit();
	addRandom_layout->addRow(nrCarti_label, nrCarti_edit);
	AddRandomToCart_button = new QPushButton("Adauga carti random");
	addRandom_layout->addWidget(AddRandomToCart_button);

	cart_layout->addWidget(addRandom);

	//--------------book cart window-------------------------------------------------------------------------------------------

	OpenCart_button = new QPushButton("Deschide cosul de inchirieri carti LAB 11");
	cart_layout->addWidget(OpenCart_button);

	QWidget* cosuri = new QWidget;
	QHBoxLayout* cosuri_layout = new QHBoxLayout;
	cosuri->setLayout(cosuri_layout);

	CosCRUDGUI_button = new QPushButton("Cos CRUD GUI");
	cosuri_layout->addWidget(CosCRUDGUI_button);

	CosReadOnlyGUI_button = new QPushButton("Cos READ ONLY GUI");
	cosuri_layout->addWidget(CosReadOnlyGUI_button);

	cart_layout->addWidget(cosuri);

	//--------------imagine biblioteca--------------------------------------------------------------------------------------------

	QLabel* imageLabel2 = new QLabel;
	QPixmap image2("biblioteca.jpg"); // Load the image

	// Resize the image
	QPixmap resizedImage2 = image2.scaled(150, 200);

	imageLabel2->setPixmap(resizedImage2);

	cart_layout->addWidget(imageLabel2);

	main_layout->addWidget(left);
	main_layout->addWidget(right);
	//main_layout->addWidget(list);
	main_layout->addWidget(groupBox_cos);

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void BookStoreGUI::reloadBookList(vector<Book> allBooks) {

	myTableModel->setBooks(allBooks);
	/*
	this->tableBooks->clearContents();
	this->tableBooks->setRowCount(allBooks.size());

	int line_number = 0;
	for (auto& book : allBooks)
	{
		this->tableBooks->setItem(line_number, 0, new QTableWidgetItem(QString::fromStdString(book.getTitlu())));
		this->tableBooks->setItem(line_number, 1, new QTableWidgetItem(QString::fromStdString(book.getAutor())));
		this->tableBooks->setItem(line_number, 2, new QTableWidgetItem(QString::fromStdString(book.getGen())));
		this->tableBooks->setItem(line_number, 3, new QTableWidgetItem(QString::number(book.getAn())));
		line_number++;
	}
	*/
	listBooks->clear();
	
	for (const auto& book : allBooks)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(book.getTitlu() + " | " + book.getAutor() + " | " + book.getGen() + " | " + to_string(book.getAn())));
		listBooks->addItem(item);
	}

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void BookStoreGUI::connectSignalsSlots() {
	QObject::connect(AddBook_button, &QPushButton::clicked, this, &BookStoreGUI::guiAddBook);

	QObject::connect(DeleteBook_button, &QPushButton::clicked, this, &BookStoreGUI::guiDeleteBook);

	QObject::connect(ModifyBook_button, &QPushButton::clicked, this, &BookStoreGUI::guiModifyBook);

	QObject::connect(FindBook_button, &QPushButton::clicked, this, &BookStoreGUI::guiFindBook);

	QObject::connect(Undo_button, &QPushButton::clicked, this, &BookStoreGUI::guiUndoBook);

	QObject::connect(Exit_button, &QPushButton::clicked, this, &BookStoreGUI::close);

	connect(SortBooks_button, &QPushButton::clicked, [&]() {
		if (this->radioSort_Titlu->isChecked())
			this->reloadBookList(service.sortByTitle());
		else if (this->radioSort_Autor->isChecked())
			this->reloadBookList(service.sortByAuthor());
		else
			this->reloadBookList(service.sortByYear());
		});

	connect(FilterTitlu_button, &QPushButton::clicked, [&]() {
		string titlu_filtrare = this->filterTitlu_edit->text().toStdString();
		filterTitlu_edit->clear();
		this->reloadBookList(service.filter_by_title(titlu_filtrare));
		});

	connect(FilterAn_button, &QPushButton::clicked, [&]() {
		int an_filtrare = this->filterAn_edit->text().toInt();
		filterAn_edit->clear();
		this->reloadBookList(service.filter_by_year(an_filtrare));
		});

	//--------------book cart window-------------------------------------------------------------------------------------------

	QObject::connect(OpenCart_button, &QPushButton::clicked, this, &BookStoreGUI::guiOpenBookCartWindow);

	QObject::connect(CosCRUDGUI_button, &QPushButton::clicked, [&]() {
		vector<Book> all_books = service.getAllBooks();
		auto gui = new CosCRUDGUI{service.getBooksCart(), all_books};
		gui->show();
		});

	QObject::connect(CosReadOnlyGUI_button, &QPushButton::clicked, [&]() {
		auto gui = new CosReadOnlyGUI{ service.getBooksCart() };
		gui->show();
		});

	//--------------book cart window-------------------------------------------------------------------------------------------

	connect(ReloadData_button, &QPushButton::clicked, [&]() {
		this->reloadBookList(service.getAllBooks());
		});



	//------imi completeaza QLineEdit-urile cand selectez din lista------
	QObject::connect(listBooks, &QListWidget::itemSelectionChanged, [&]() {
		auto lista_selectat = listBooks->selectedItems();
		if (lista_selectat.isEmpty())
		{
			editTitlu->setText("");
			editAutor->setText("");
			editGen->setText("");
			editAn->setText("");
		}
		else {
			auto selected_item = lista_selectat.at(0);
			QStringList item_details = selected_item->text().split(" | ");
			QString titlu = item_details[0];
			QString autor = item_details[1];
			QString gen = item_details[2];
			QString an = item_details[3];
			editTitlu->setText(titlu);
			editAutor->setText(autor);
			editGen->setText(gen);
			editAn->setText(an);
		}
		});
	/*
	//------imi completeaza QLineEdit-urile cand selectez din tabel------
	QObject::connect(tableBooks, &QTableWidget::itemSelectionChanged, [&]() {
		auto lista_selectat = tableBooks->selectedItems();
		if (lista_selectat.isEmpty())
		{
			editTitlu->setText("");
			editAutor->setText("");
			editGen->setText("");
			editAn->setText("");
		}
		else {
			int row = lista_selectat.first()->row();
			QString titlu = tableBooks->item(row, 0)->text();
			QString autor = tableBooks->item(row, 1)->text();
			QString gen = tableBooks->item(row, 2)->text();
			QString an = tableBooks->item(row, 3)->text();
			editTitlu->setText(titlu);
			editAutor->setText(autor);
			editGen->setText(gen);
			editAn->setText(an);
		}
		});
	
	//-----------gestioneaza cosul-----------------
	
	QObject::connect(AddBookCos_button, &QPushButton::clicked, [this]() {
		auto lista_selectat = tableBooks->selectedItems();
		if (!lista_selectat.isEmpty())
		{
			int row = lista_selectat.first()->row();
			string titlu = tableBooks->item(row, 0)->text().toStdString();
			string autor = tableBooks->item(row, 1)->text().toStdString();

			service.addToBooksCart(titlu, autor);
			QMessageBox::information(this, "Info", QString::fromStdString("Carte adaugata cu succes in cos"));
		    
			tableBooks->clearSelection();
		}
		else
			QMessageBox::warning(this, "Warning", QString::fromStdString("Selecteaza o carte."));
		});
*/


//------imi completeaza QLineEdit-urile cand selectez din lista------

	QObject::connect(tableBooks->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tableBooks->selectionModel()->selectedIndexes().isEmpty()) {
			editTitlu->setText("");
			editAutor->setText("");
			editGen->setText("");
			editAn->setText("");
		}
		else {
			auto selected_item = tableBooks->selectionModel()->selectedIndexes().at(0).row();
			auto titluIndex = tableBooks->model()->index(selected_item, 0);
			auto autorIndex = tableBooks->model()->index(selected_item, 1);
			auto genIndex = tableBooks->model()->index(selected_item, 2);
			auto anIndex = tableBooks->model()->index(selected_item, 3);
			auto titlu = tableBooks->model()->data(titluIndex, Qt::DisplayRole).toString();
			auto autor = tableBooks->model()->data(autorIndex, Qt::DisplayRole).toString();
			auto gen = tableBooks->model()->data(genIndex, Qt::DisplayRole).toString();
			auto an = tableBooks->model()->data(anIndex, Qt::DisplayRole).toString();
			editTitlu->setText(titlu);
			editAutor->setText(autor);
			editGen->setText(gen);
			editAn->setText(an);
		}
		});

	QObject::connect(AddBookCos_button, &QPushButton::clicked, [this]() {
		if (!tableBooks->selectionModel()->selectedIndexes().isEmpty()) {
			auto selected_item = tableBooks->selectionModel()->selectedIndexes().at(0).row();
			auto titluIndex = tableBooks->model()->index(selected_item, 0);
			auto autorIndex = tableBooks->model()->index(selected_item, 1);
			QString titlu = tableBooks->model()->data(titluIndex, Qt::DisplayRole).toString();
			QString autor = tableBooks->model()->data(autorIndex, Qt::DisplayRole).toString();
			
			service.addToBooksCart(titlu.toStdString(), autor.toStdString());
			QMessageBox::information(this, "Info", QString::fromStdString("Carte adaugata cu succes in cos"));

			tableBooks->clearSelection();
		}
		else {
			QMessageBox::warning(this, "Warning", QString::fromStdString("Selecteaza o carte."));
		}
		});
	QObject::connect(EmptyCart_button, &QPushButton::clicked, [this]() {
		this->service.emptyBooksCart();
		});

	QObject::connect(AddRandomToCart_button, &QPushButton::clicked, [this]() {
		int nr_carti = this->nrCarti_edit->text().toInt();
		nrCarti_edit->clear();
		service.addRandomBooksToCart(nr_carti);
		});
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void BookStoreGUI::guiAddBook()
{
	try {
		//luam informatiile din QLineEdit
		string titlu = editTitlu->text().toStdString();
		string autor = editAutor->text().toStdString();
		string gen = editGen->text().toStdString();
		int an = editAn->text().toInt();

		//golim QLineEdit-urile dupa apasarea butonului
		editTitlu->clear();
		editAutor->clear();
		editGen->clear();
		editAn->clear();

		this->service.addBook(titlu, autor, gen, an);
		this->reloadBookList(this->service.getAllBooks());

		//mesaj daca cartea a fost adaugata cu succes
		QMessageBox::information(this, "Info", QString::fromStdString("Carte adaugata cu succes"));

	}

	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BookStoreGUI::showNrBooksByGenre(const QString& genre) {
	int nrBooks = service.getNumberBooksByGenre(genre.toStdString());
	QMessageBox::information(this, "Nr de carti", QString("Nr de carti cu genul '%1': %2").arg(genre).arg(nrBooks));
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BookStoreGUI::guiDeleteBook()
{
	try {
		//luam informatiile din QLineEdit
		string titlu = editTitlu->text().toStdString();
		string autor = editAutor->text().toStdString();
		string gen = editGen->text().toStdString();
		int an = editAn->text().toInt();

		//golim QLineEdit-urile dupa apasarea butonului
		editTitlu->clear();
		editAutor->clear();
		editGen->clear();
		editAn->clear();

		this->service.deleteBook(titlu, autor, gen, an);
		this->reloadBookList(this->service.getAllBooks());

		//mesaj daca cartea a fost stearsa cu succes
		QMessageBox::information(this, "Info", QString::fromStdString("Carte stearsa cu succes"));
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void BookStoreGUI::guiModifyBook()
{
	try {
		//luam informatiile din QLineEdit
		string titlu = editTitlu->text().toStdString();
		string autor = editAutor->text().toStdString();
		string gen = editGen->text().toStdString();
		int an = editAn->text().toInt();

		//golim QLineEdit-urile dupa apasarea butonului
		editTitlu->clear();
		editAutor->clear();
		editGen->clear();
		editAn->clear();

		this->service.modifyBook(titlu, autor, gen, an);
		this->reloadBookList(this->service.getAllBooks());

		//mesaj daca cartea a fost modifcata cu succes
		QMessageBox::information(this, "Info", QString::fromStdString("Carte modificata cu succes"));
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void BookStoreGUI::guiFindBook()
{
	try {
		//luam informatiile din QLineEdit
		string titlu = editTitlu->text().toStdString();
		string autor = editAutor->text().toStdString();

		//golim QLineEdit-urile dupa apasarea butonului
		editTitlu->clear();
		editAutor->clear();
		editGen->clear();
		editAn->clear();

		const Book& b = this->service.findBook(titlu, autor);
		
		//construiesc un struct care sa contina datele despre carte
		QString message = "";
		message += "Titlu: " + QString::fromStdString(b.getTitlu()) + "\n";
		message += "Autor: " + QString::fromStdString(b.getAutor()) + "\n";
		message += "Gen: " + QString::fromStdString(b.getGen()) + "\n";
		message += "An aparitie: " + QString::number(b.getAn());

		//afisam cartea daca a fost gasita 
		QMessageBox::information(this, "Carte gasita", message);
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void BookStoreGUI::guiUndoBook()
{
	try {
		this->service.undo();
		this->reloadBookList(this->service.getAllBooks());

		//mesaj daca undo a fost realizat cu succes
		QMessageBox::information(this, "Info", QString::fromStdString("Undo realizat cu succes"));
	}
	catch (BookException& be) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(be.getErrorMessage()));
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void BookStoreGUI::guiOpenBookCartWindow()
{
	if (!bookCartWindow)
	{
		bookCartWindow = new BookCartWindow(*this);
		bookCartWindow->setAttribute(Qt::WA_DeleteOnClose);
	}
	bookCartWindow->show();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void BookCartWindow::intializeCartComponents()
{


	QHBoxLayout* main_layout = new QHBoxLayout;  //a layout manager that arranges child widgets horizontally) 
	this->setLayout(main_layout);                //and sets it as the layout for the current widget (this).

	QWidget* left = new QWidget;                 //a generic widget in Qt
	QVBoxLayout* left_layout = new QVBoxLayout;  //a layout manager that arranges child widgets in a vertical column
	left->setLayout(left_layout);

	//--------------adaugare in cos------------------------------------------------------------------------------------

	QWidget* form = new QWidget;
	QFormLayout* form_layout = new QFormLayout;   //A QFormLayout in Qt is a layout manager designed to arrange widgets in a form-like structure.
	form->setLayout(form_layout);

	editTitlu = new QLineEdit;
	editAutor = new QLineEdit;

	form_layout->addRow(label_titlu, editTitlu);
	form_layout->addRow(label_autor, editAutor);

	AddBook_button = new QPushButton("Adauga carte in cos");
	form_layout->addWidget(AddBook_button);

	left_layout->addWidget(form);

	//--------------sterge cosul------------------------------------------------------------------------------------

	EmptyCart_button = new QPushButton("Goleste cosul");
	form_layout->addWidget(EmptyCart_button);

	//--------------adauga random in cos----------------------------------------------------------------------------
	QWidget* addRandom = new QWidget;
	QFormLayout* addRandom_layout = new QFormLayout;
	addRandom->setLayout(addRandom_layout);

	nrCarti_edit = new QLineEdit();
	addRandom_layout->addRow(nrCarti_label, nrCarti_edit);
	AddRandomToCart_button = new QPushButton("Adauga carti random");
	addRandom_layout->addWidget(AddRandomToCart_button);

	left_layout->addWidget(addRandom);


	//--------------export cart-------------------------------------------------------------------------------------

	QWidget* export_cart = new QWidget;
	QFormLayout* export_layout = new QFormLayout;
	export_cart->setLayout(export_layout);

	numeFisier_edit = new QLineEdit();
	export_layout->addRow(numeFisier_label, numeFisier_edit);
	ExportCart_button = new QPushButton("Exporta cosul");
	export_layout->addWidget(ExportCart_button);

	left_layout->addWidget(export_cart);


	//--------------exit--------------------------------------------------------------------------------------------

	Exit_button = new QPushButton("Exit");
	left_layout->addWidget(Exit_button);

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


void BookCartWindow::connectSignalsSlots_CART() {
	bookStoreGUI.service.getBooksCart().addObserver(this);

	QObject::connect(AddBook_button, &QPushButton::clicked, this, &BookCartWindow::guiAddBookToCart);

	QObject::connect(EmptyCart_button, &QPushButton::clicked, this, &BookCartWindow::guiEmptyBooksCart);

	QObject::connect(AddRandomToCart_button, &QPushButton::clicked, this, &BookCartWindow::guiAddRandomBooksToCart);

	QObject::connect(ExportCart_button, &QPushButton::clicked, this, &BookCartWindow::guiExportCart);
		
	QObject::connect(Exit_button, &QPushButton::clicked, this, &BookStoreGUI::close);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void BookCartWindow::reloadBookList_CART(vector<Book> cartBooks) {
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


void BookCartWindow::guiAddBookToCart()
{
	try {
		//luam informatiile din QLineEdit
		string titlu = editTitlu->text().toStdString();
		string autor = editAutor->text().toStdString();

		//golim QLineEdit-urile dupa apasarea butonului
		editTitlu->clear();
		editAutor->clear();
		

		bookStoreGUI.service.addToBooksCart(titlu, autor);
		this->reloadBookList_CART(bookStoreGUI.service.getAllBooksFromCart());

		//mesaj daca cartea a fost adaugata cu succes
		QMessageBox::information(this, "Info", QString::fromStdString("Carte adaugata cu succes in cos"));

	}

	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void BookCartWindow::guiEmptyBooksCart()
{
	bookStoreGUI.service.emptyBooksCart();
	this->reloadBookList_CART(bookStoreGUI.service.getAllBooksFromCart());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void BookCartWindow::guiAddRandomBooksToCart()
{
	int nr_carti = this->nrCarti_edit->text().toInt();
	nrCarti_edit->clear();
	try {
		int numar_adaugat = bookStoreGUI.service.addRandomBooksToCart(nr_carti);
		//construiesc un struct care sa contina datele despre carte
		QString message = "";
		message += "S au adaugat " + QString::number(numar_adaugat) + " carti in cos.\n";
	

		//afisam cartea daca a fost gasita 
		QMessageBox::information(this, "Info", message);
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}

	this->reloadBookList_CART(bookStoreGUI.service.getAllBooksFromCart());
}

void BookCartWindow::guiExportCart()
{
	string nume_fisier = this->numeFisier_edit->text().toStdString();
	numeFisier_edit->clear();
	
	int succes = bookStoreGUI.service.exportCart(nume_fisier);
	
	if( succes == 0)
		//afisam cartea daca a fost gasita 
		QMessageBox::information(this, "Info", QString::fromStdString("Export realizat cu succes!\n"));
	else
	    QMessageBox::warning(this, "Warning", QString::fromStdString("Nu s - a gasit, fisierul, exportul nu a putut fi realizat.\n"));
}

