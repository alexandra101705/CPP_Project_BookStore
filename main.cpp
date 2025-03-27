#include "Lab1011.h"
#include "BookStoreGUI.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   
	//BookRepository repo;
	BookRepositoryFile repo{ "book.txt" };

	BookValidator val;
	BookService srv{ repo, val };
	BookStoreGUI gui{ srv };

    gui.show();

    return a.exec();
}
