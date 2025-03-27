#pragma once
#include "Book.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include "Observer.h"

using std::vector;

class BooksCart : public Observable
{
	vector<Book> rentedBooksCart;

public:
	BooksCart() = default;

	/**
	 * @brief: Adauga o carte de inchiriat in cos
	 * @param b: cartea care se adauga
	 */
	void addBookToCart(const Book& b)
	{
		this->rentedBooksCart.push_back(b);
		notify();
	}

	/**
	 * @brief: Sterge toate cartile din cos
	 */
	void emptyBooksCart()
	{
		this->rentedBooksCart.clear();
		notify();
	}


	/**
	 * @brief: Adauga un numar dat de carti(in mod aleator)
	 * @param booksList: vector de carti din care se adauga aleatoriu
	 * @param numar: numerul de carti care se adauga
	 */
	void addRandomBooks(vector<Book> booksList, int numar)
	{
		//amestecam lista de carti din care se extrag cartile pentru cos
		shuffle(booksList.begin(), booksList.end(), std::default_random_engine(std::random_device{}()));
		while (rentedBooksCart.size() < numar && booksList.size() > 0)
		{
			rentedBooksCart.push_back(booksList.back());
			booksList.pop_back();
		}
		notify();
	}

	const vector<Book>& getAllBooksFromCart()
	{
		return this->rentedBooksCart;
	}
};

