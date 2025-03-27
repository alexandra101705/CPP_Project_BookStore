#pragma once

#include "Book.h"
#include <vector>
#include <string>

using namespace std;

class ValidationException {
	vector<string> errorMsg;

public:
	ValidationException(vector<string> errorMessages) : errorMsg{ errorMessages } {};

	string getErrorMessages()
	{
		string mesaj = "";
		for (const string e : errorMsg)
			mesaj += e + "\n";
		return mesaj;
	}
};

class BookValidator {

public:
	void valideaza(const Book& b)
	{
		vector<string> errors;
		if (b.getTitlu().length() < 1)
			errors.push_back("Titlul trebuie sa aiba cel putin un caracter. ");
		if (b.getAutor().length() < 2)
			errors.push_back("Autorul trebuie sa aiba cel putin 2 caractere. ");
		if (b.getGen().length() < 2)
			errors.push_back("Genul trebuie sa aiba cel putin 2 caractere. ");
		if (b.getAn() > 2024)
			errors.push_back("Anul aparitiei nu poate fi peste 2024. ");

		if (errors.size() > 0)
			throw ValidationException(errors);
	}
};