#pragma once

#include <QAbstractTableModel>
#include "Book.h"
#include <vector>

using namespace std;

class MyTableModel : public QAbstractTableModel
{
    Q_OBJECT

private:
    vector<Book> allBooks;

public:
    MyTableModel(const vector<Book>& books, QObject* parent = nullptr) : 
        QAbstractTableModel(parent), allBooks(books) {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override
    {
        return allBooks.size();
    }
    int columnCount(const QModelIndex& parent = QModelIndex()) const override
    {
        return 4;
    }
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
    {
        if (role == Qt::DisplayRole) {
            const Book& book = allBooks[index.row()];
            if (index.column() == 0)
                return QString::fromStdString(book.getTitlu());
            if (index.column() == 1)
                return QString::fromStdString(book.getAutor());
            if (index.column() == 2)
                return QString::fromStdString(book.getGen());
            if (index.column() == 3)
                return QString::number(book.getAn());

        }
        return QVariant();


    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override
    {
        if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
            switch (section) {
            case 0:
                return QVariant(QString("Titlu"));
            case 1:
                return QVariant(QString("Autor"));
            case 2:
                return QVariant(QString("Gen"));
            case 3:
                return QVariant(QString("An"));
            }
        }
        return QVariant();
    }

    void setBooks(const vector<Book>& books)
    {
        beginResetModel();
        allBooks = books;
        endResetModel();
    }
};