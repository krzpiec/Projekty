
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip> 
#include <vector>
#include <vld.h>
#include "Funkcje.h"

void dodajmiastojakoelement(miasto *& pHeadOdwiedzone, miasto *& pTailOdwiedzone, miasto *& kopiamiasta, polaczenia *& kopiadrog)
{

	if (not pHeadOdwiedzone)
	{
		pHeadOdwiedzone = kopiamiasta;
		pHeadOdwiedzone->pnext = nullptr;
		pHeadOdwiedzone->pprev = nullptr;
		pHeadOdwiedzone->pDrogi = kopiadrog;
		pTailOdwiedzone = pHeadOdwiedzone;
		return;
	}

	kopiamiasta->pprev = pTailOdwiedzone;
	kopiamiasta->pnext = nullptr;
	kopiamiasta->pDrogi = kopiadrog;
	pTailOdwiedzone->pnext = kopiamiasta;
	pTailOdwiedzone = kopiamiasta;
	return;
}

bool wczytaj(miasto *& pHeadmiast, miasto *& pTailmiast, const std::string & nazwa)
{
	std::ifstream plik;
	plik.open(nazwa);
	if (not plik.good())
	{
		return false;
	}
	std::string linia;

	int licz = 0;
	int skad = 0;
	int dokad = 0;
	int droga = 0;
	std::string del = "()->,:";
	while (std::getline(plik, linia))
	{
		for (int i = 0; i < del.length(); i++)
		{
			size_t pos = linia.find_first_of(del[i]); // linia.find_first_of (del);
			if (pos != std::string::npos)
				linia.replace(linia.begin() + pos, linia.begin() + pos + 1, " ");
		}
		//std::cout << linia << std::endl;
		std::stringstream ss(linia);

		double temp = 0;
		while (ss)
		{
			if (ss >> temp)
			{
				switch (licz)
				{
				case 0:
				{
					skad = temp;
					licz++;
					break;
				}
				case 1:
				{
					dokad = temp;
					licz++;
					break;
				}
				case 2:
				{
					droga = temp;
					licz = 0;
					//std::cout << skad << " " << dokad << " " << droga << std::endl;
					dodajdomiast(pHeadmiast, pTailmiast, skad, dokad, droga);
					break;
				}

				}
			}
		}
	}
	plik.close();
	return true;
}

void dodajdopol(polaczenia *& pkorzen, const int dokad, const double droga)
{

	if (not pkorzen)//drzewo polaczen jest puste
		pkorzen = new polaczenia{ dokad ,droga , 0, 0, 0 };

	else // w drzewie polaczen juz cos jest 
	{
		auto p = pkorzen;

		while (p)
		{

			if (droga < p->droga) // idziemy w lewo
			{
				if (p->plewy)  // jezeli istnieje pLewy
					p = p->plewy;
				else
				{
					p->plewy = new polaczenia{ dokad,droga ,  0, 0 ,p };
					p = nullptr;
				}
			}
			else  // idziemy w prawo
			{
				if (p->pprawy)
					p = p->pprawy;
				else
				{
					p->pprawy = new polaczenia{ dokad,droga ,  0, 0 ,p };
					p = nullptr;
				}
			}
		}
	}
}

void dodajdomiast(miasto *& pHeadmiast, miasto *& pTailmiast, const int skad, const int dokad, const double droga)
{
	if (not pHeadmiast)//Lista jest pusta
	{
		pHeadmiast = new miasto{ skad, 0 , 0 , 0 };
		pTailmiast = pHeadmiast;
		dodajdopol(pHeadmiast->pDrogi, dokad, droga);
		return;
	}
	miasto * p = pHeadmiast;
	while (p)
	{
		if (p->nazwa == skad)
		{
			dodajdopol(p->pDrogi, dokad, droga);
			return;
		}
		p = p->pnext;
	}

	auto wstaw = new miasto{ skad,  0,0, pTailmiast };
	dodajdopol(wstaw->pDrogi, dokad, droga);
	pTailmiast->pnext = wstaw;
	pTailmiast = wstaw;

	return;

}

bool wypiszmiasta(miasto * pHeadmiast)
{
	if (not pHeadmiast)
	{
		std::cout << "Lista jest pusta";
		return false;
	}

	std::cout << "START" << std::endl;
	while (pHeadmiast)
	{
		std::cout << pHeadmiast->nazwa << " ";
		pHeadmiast = pHeadmiast->pnext;
	}
	std::cout << std::endl;
	std::cout << "STOP" << std::endl;
	return true;
}

miasto * znajdzpoNazwie(miasto * pHeadmiast, const int nazwa)
{
	if (pHeadmiast == nullptr) //lista pusta 
		return pHeadmiast;
	while (pHeadmiast)
	{
		if (pHeadmiast->nazwa == nazwa)
			return pHeadmiast;
		pHeadmiast = pHeadmiast->pnext;
	}
	return nullptr; //nie znaleziono
}

bool znajdzpoAdresie(miasto * pHeadmiast, miasto * szukana)
{
	if (not pHeadmiast)
	{
		return false;
	}
	auto p = pHeadmiast;
	while (p)
	{
		if (p == szukana)
			return true;
		p = p->pnext;
	}
	return false;
}

void wypiszpol(polaczenia * proot, int wciecie)
{
	const int MNOZNIK = 4;
	if (proot)  // jezeli drzewo jest niepuste
	{
		wypiszpol(proot->plewy, wciecie + 1);
		std::cout << std::setw(wciecie * MNOZNIK) << proot->dokad << "-" << proot->droga << std::endl;
		wypiszpol(proot->pprawy, wciecie + 1);
	}
}

void usunMiasto(miasto *& pHeadmiast, miasto *& pTailmiast, miasto * &dousuniecia)
{
	if (not pHeadmiast)
	{
		return;
	}

	if (pHeadmiast == dousuniecia)
	{
		pHeadmiast = pHeadmiast->pnext;
		if (pHeadmiast)
			pHeadmiast->pprev = nullptr;
		return;
	}
	if (pTailmiast == dousuniecia)
	{
		pTailmiast = pTailmiast->pprev;
		if (pTailmiast)
			pTailmiast->pnext = nullptr;
		return;
	}
	auto temp = pHeadmiast;
	while (temp->pnext != nullptr && temp->pnext != dousuniecia)
		temp = temp->pnext;

	if (temp->pnext == nullptr)
		return;


	if (temp->pnext == dousuniecia)
	{
		auto p = temp->pnext->pnext;
		//usundrzewopol(temp->pnext->pDrogi);
		//delete temp->pnext;
		temp->pnext = p;
		p->pprev = temp;
		return;
	}
}

void usundrzewopol(polaczenia *& pDrogi)
{
	if (pDrogi)
	{
		usundrzewopol(pDrogi->plewy);
		usundrzewopol(pDrogi->pprawy);

		delete pDrogi;
		pDrogi = nullptr;
	}
}

void wypiszodkon(miasto * ptail)
{
	if (ptail == nullptr)
	{
		std::cout << "Lista jest pusta";
		return;
	}

	std::cout << "START" << std::endl;
	while (ptail)
	{
		std::cout << ptail->nazwa << " ";
		ptail = ptail->pprev;
	}
	std::cout << std::endl;
	std::cout << "STOP" << std::endl;
}

void przenies(miasto *& pHeadmiast, miasto *& pTailmiast, miasto *& pHeadOdwiedzone, miasto *& pTailOdwiedzone, miasto *& doprzeniesienia)
{
	if (not pHeadmiast)
		return;
	miasto *p = pHeadmiast;
	while (p)
	{
		if (p == doprzeniesienia)
		{
			usunMiasto(pHeadmiast, pTailmiast, p);
			dodajmiastojakoelement(pHeadOdwiedzone, pTailOdwiedzone, p, p->pDrogi);
			return;
		}
		p = p->pnext;
	}
	return;
}

miasto *NajblizszeMiasto(polaczenia *pDrogi, miasto * pHeadmiast, miasto * Start, double & droga)
{
	if (not pDrogi)
		return nullptr;
	if (not pDrogi->plewy)
	{
		if (pDrogi->dokad == Start->nazwa && pHeadmiast == nullptr) // do przeniesiena jeden element i konczymy z tym
		{
			droga = pDrogi->droga;
			return Start;
		}
		miasto * najblizsze = znajdzpoNazwie(pHeadmiast, pDrogi->dokad);
		droga = pDrogi->droga;
		if (!najblizsze)
			najblizsze = nastepnyistniejacy(pDrogi, pDrogi, pHeadmiast, droga);
		return najblizsze;
	}
	else
	{
		polaczenia * p = pDrogi;
		while (p->plewy)
			p = p->plewy;
		if (p->dokad == Start->nazwa && pHeadmiast->pnext == nullptr) // do przeniesiena jeden element i konczymy z tym
			return Start;
		miasto * najblizsze = znajdzpoNazwie(pHeadmiast, p->dokad);
		droga = p->droga;
		if (!najblizsze)
			najblizsze = nastepnyistniejacy(pDrogi, p, pHeadmiast, droga);
		return najblizsze;
	}

}

void PrzyblizonaTrasaKuriera(double & przebytadroga, miasto *& pHeadmiast, miasto *& pTailmiast, miasto * Poprzednie, miasto * Aktualne, miasto *& pHeadOdwiedzone, miasto *& pTailOdwiedzone, miasto * Start)
{
	if (not Aktualne || not pHeadmiast)
		return;

	double droga = 0;
	Poprzednie = Aktualne;
	przenies(pHeadmiast, pTailmiast, pHeadOdwiedzone, pTailOdwiedzone, Poprzednie);
	Aktualne = NajblizszeMiasto(Poprzednie->pDrogi, pHeadmiast, Start, droga);

	PrzyblizonaTrasaKuriera(przebytadroga, pHeadmiast, pTailmiast, Poprzednie, Aktualne, pHeadOdwiedzone, pTailOdwiedzone, Start);

	if (not pHeadmiast && Aktualne == nullptr)
	{
		przenies(pHeadOdwiedzone, pTailOdwiedzone, pHeadmiast, pTailmiast, Poprzednie);
		return;
	}

	if (not pHeadmiast)
		przebytadroga += droga;

	while (Aktualne && pHeadmiast)
	{
		przenies(pHeadOdwiedzone, pTailOdwiedzone, pHeadmiast, pTailmiast, Aktualne);
		Aktualne = nastepnyistniejacynazwa(Poprzednie->pDrogi, Aktualne->nazwa, droga, pHeadmiast);
		PrzyblizonaTrasaKuriera(przebytadroga, pHeadmiast, pTailmiast, Poprzednie, Aktualne, pHeadOdwiedzone, pTailOdwiedzone, Start);
		if (not pHeadmiast)
			przebytadroga += droga;
	}

	return;

}


miasto * nastepnyistniejacy(polaczenia *pDrogi, polaczenia * Aktualny, miasto * pHeadmiast, double & droga)
{
	if (not pDrogi || not Aktualny)
		return nullptr;
	if (Aktualny->pprawy != nullptr) // przeskocz na prawy i do oporu w lewo
	{
		Aktualny = Aktualny->pprawy;
		while (Aktualny->plewy)
			Aktualny = Aktualny->plewy;
		miasto * dozwrotu = znajdzpoNazwie(pHeadmiast, Aktualny->dokad);
		if (dozwrotu)
		{
			droga = Aktualny->droga;
			return dozwrotu;
		}
		else
		{
			miasto * proba = nastepnyistniejacy(pDrogi, Aktualny, pHeadmiast, droga);
			return proba;
		}
	}
	else
	{
		while (Aktualny->rodzic) //idz do gory az nie element nie bedzie lewym potomkiem
		{
			if (Aktualny->rodzic->plewy == Aktualny)
			{
				miasto * dozwrotu = znajdzpoNazwie(pHeadmiast, Aktualny->rodzic->dokad);
				if (dozwrotu)
				{
					droga = Aktualny->rodzic->droga;
					return dozwrotu;
				}
				else
				{
					miasto * proba = nastepnyistniejacy(pDrogi, Aktualny->rodzic, pHeadmiast, droga);
					return proba;
				}
			}
			Aktualny = Aktualny->rodzic;
		}
		return nullptr; //brak potomka
	}
}

miasto * nastepnyistniejacynazwa(polaczenia *pDrogi, int nazwa, double & droga, miasto * pHeadmiast)//jak droga rowna to po prawo jest
{
	if (not pDrogi || not pHeadmiast)
		return nullptr;
	if (droga == pDrogi->droga && nazwa == pDrogi->dokad)
	{
		miasto * dozwrotu = nastepnyistniejacy(pDrogi, pDrogi, pHeadmiast, droga);
		return dozwrotu;
	}
	if (droga == pDrogi->droga && nazwa != pDrogi->dokad)//dwa miasta o tej samej wartosci polaczenia
	{
		if (pDrogi->pprawy)
		{
			miasto * dozwrotu = nastepnyistniejacy(pDrogi, pDrogi->pprawy, pHeadmiast, droga);
			return dozwrotu;
		}
		else
			return nullptr;//celem tej f jest znalezienie elementu a nastepnie wywolanie kolejnej f znajdujacej nastepnik, jezeli droga sie zgadza a nazwa nie i pprawy nie istnieje to znacyz ze takiego miasta nie ma
	}
	if (droga < pDrogi->droga)
	{
		if (pDrogi->plewy)
		{
			miasto * dozwrotu = nastepnyistniejacynazwa(pDrogi->plewy, nazwa, droga, pHeadmiast);
			return dozwrotu;
		}
		else
			return nullptr;
	}
	else
	{
		if (pDrogi->pprawy)
		{
			miasto * dozwrotu = nastepnyistniejacynazwa(pDrogi->pprawy, nazwa, droga, pHeadmiast);
			return dozwrotu;
		}
		else
			return nullptr;
	}
	return nullptr;//nic nie znalazl
}

bool PlikWyjsciowy(miasto * pHeadmiast, double droga, const std::string & output)
{
	std::ofstream plik;
	plik.open(output);
	if (not plik.good())
		return false;
	int startowe = pHeadmiast->nazwa;
	plik << "Kolejnosc odwiedzania miast: ";
	while (pHeadmiast)
	{
		plik << pHeadmiast->nazwa;
		plik << " - ";
		pHeadmiast = pHeadmiast->pnext;
	}
	plik << startowe << std::endl;
	plik << "Przebyta droga: " << droga << std::endl;
	plik.close();
	return true;
}

void usunwszystko(miasto *& pHeadmiast, miasto *& pTailmiast, miasto *& pHeadOdwiedzone, miasto *& pTailOdwiedzone)
{
	miasto * p = pHeadmiast;
	while (p)
	{
		auto temp = p->pnext;
		usundrzewopol(p->pDrogi);
		delete p;
		p = temp;
	}

	pHeadmiast = nullptr;
	pTailmiast = nullptr;

	miasto * p2 = pHeadOdwiedzone;
	while (p2)
	{
		auto temp = p2->pnext;
		usundrzewopol(p2->pDrogi);
		delete p2;
		p2 = temp;
	}
	pHeadOdwiedzone = nullptr;
	pTailOdwiedzone = nullptr;

	return;
}

