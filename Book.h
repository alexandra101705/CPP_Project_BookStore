#pragma once
#include <string>
#include <iostream>
using namespace std;

class BookException {
	string msg;
public:
	BookException(const string& m) :msg{ m } {};
	string getErrorMessage()const { return msg; }
};

class Book {

private:
	string titlu{ "" };
	string autor{ "" };
	string gen{ "" };
	int an{ 0 };
public:
	Book() = delete;
	Book(string titlu, string autor, string gen, int an) :titlu{ titlu }, autor{ autor }, gen{ gen }, an{ an } {};

	Book(const Book& ot) :titlu{ ot.titlu }, autor{ ot.autor }, gen{ ot.gen }, an{ ot.an } {
		//cout << "[Book] Copy constructor apelat.\n";
	};

	string getTitlu() const;
	string getAutor() const;
	string getGen() const;
	int getAn() const noexcept;

	void setTitlu(string titluNou);
	void setAutor(string autorNou);
	void setGen(string genNou);
	void setAn(int anNou) noexcept;

	bool operator==(const Book& other) const noexcept {
		return (other.titlu == this->titlu && other.autor == this->autor);
	}

	friend std::ostream& operator<<(std::ostream& stream, const Book& b);
};


/**
 * @brief: Compara doua carti dupa titlu
 * @return: true daca titlul cartii b1 este mai miv dppdv lexicografic
 *               fata de titlul cartii b2
 *          false, altfel
 *          -daca este acelasi titlu, se compara genurile
 */
bool compare_title(const Book& b1, const Book& b2);


/**
 * @brief: Compara doua carti dupa autor

 * @return: true daca autrul cartii b1 este mai mic dppdv lexicografic
 *               fata de autorul cartii b2
 *          false, altfel
 *          -daca este acelasi autor, se compara genurile
 */
bool compare_author(const Book& b1, const Book& b2);


/**
 * @brief: Compara doua carti dupa an

 * @return: true daca anul cartii b1 este mai mic fata de anul cartii b2
 *          false, altfel
 *           -daca este acelasi an, se compara genurile
 */
bool compare_year(const Book& b1, const Book& b2);




void testeDomain();