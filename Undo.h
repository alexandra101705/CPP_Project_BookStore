#pragma once
#include "Book.h"
#include "Repository.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo
{
	Book book_added;
	RepoAbstract& repo;
public:
	UndoAdauga(RepoAbstract& repo, const Book& b) :repo{ repo }, book_added{ b } {}

	void doUndo() override {
		repo.delete_book(book_added);
	}

};

class UndoSterge : public ActiuneUndo
{
	Book book_deleted;
	RepoAbstract& repo;
public:
	UndoSterge(RepoAbstract& repo, const Book& b) :repo{ repo }, book_deleted{ b } {}

	void doUndo() override {
		repo.store(book_deleted);
	}
};

class UndoModifica : public ActiuneUndo
{
	Book old_book;
	Book new_book;
	RepoAbstract& repo;
public:
	UndoModifica(RepoAbstract& repo, const Book& b1, const Book& b2) :repo{ repo }, old_book{ b1 }, new_book{ b2 } {}

	void doUndo() override {
		repo.delete_book(new_book);
		repo.store(old_book);
	}
};