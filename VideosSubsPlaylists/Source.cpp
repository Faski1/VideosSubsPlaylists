#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>

using namespace std;

enum Pristup { PRIVATE, PUBLIC };
char * crt = "\n------------------------------------------------------\n";

template <class T1, class T2>
class Kolekcija {
	int _trenutno;
	T1 * _elementi;
	T2 * _elementi2;
public:
	Kolekcija() {
		_trenutno = 0;
		_elementi = nullptr;
		_elementi2 = nullptr;
	}

	~Kolekcija() {
		delete[]_elementi;
		delete[]_elementi2;
		_elementi = nullptr;
		_elementi2 = nullptr;
	}

	Kolekcija(const Kolekcija& kolekcija) {
		_trenutno = kolekcija._trenutno;
		_elementi = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];

		for (int i = 0; i < _trenutno; i++) {
			_elementi[i] = kolekcija._elementi[i];
			_elementi2[i] = kolekcija._elementi2[i];
		}
	}

	Kolekcija& operator=(const Kolekcija& kolekcija) {
		if (this != &kolekcija) {
			delete[]_elementi;
			delete[]_elementi2;

			_trenutno = kolekcija._trenutno;
			_elementi = new T1[_trenutno];
			_elementi2 = new T2[_trenutno];

			for (int i = 0; i < _trenutno; i++) {
				_elementi[i] = kolekcija._elementi[i];
				_elementi2[i] = kolekcija._elementi2[i];
			}
		}
		return *this;
	}

	void AddElement(T1 a, T2 b) {
		T1 * temp1 = new T1[_trenutno + 1];
		T2 * temp2 = new T2[_trenutno + 1];
		for (int i = 0; i < _trenutno; i++) {
			temp1[i] = _elementi[i];
			temp2[i] = _elementi2[i];
		}

		temp1[_trenutno] = a;
		temp2[_trenutno] = b;

		delete[]_elementi;
		delete[]_elementi2;

		_elementi = temp1;
		_elementi2 = temp2;

		_trenutno++;
	}

	int getTrenutno() { return _trenutno; }

	T1 & getT1(int lokacija) { return _elementi[lokacija]; }

	T2 & getT2(int lokacija) { return _elementi2[lokacija]; }

	friend ostream & operator<<(ostream & cout, Kolekcija & k) {
		for (int i = 0; i < k.getTrenutno(); i++)
			cout << k.getT1(i) << "\t" << k.getT2(i) << endl;
		return cout;
	}
};

class DatumVrijeme {
	int * _dan;
	int * _mjesec;
	int * _godina;
	int * _sati;
	int * _minuti;
public:
	DatumVrijeme() {
		_dan = nullptr;
		_mjesec = nullptr;
		_godina = nullptr;
		_sati = nullptr;
		_minuti = nullptr;
	}

	DatumVrijeme(int d, int m, int g, int h, int mm) {
		_dan = new int(d);
		_mjesec = new int(m);
		_godina = new int(g);
		_sati = new int(h);
		_minuti = new int(mm);
	}

	DatumVrijeme(const DatumVrijeme & d) {
		_dan = new int(*d._dan);
		_mjesec = new int(*d._mjesec);
		_godina = new int(*d._godina);
		_sati = new int(*d._sati);
		_minuti = new int(*d._minuti);
	}

	DatumVrijeme & operator=(const DatumVrijeme & d) {
		if (this != &d) {
			delete _dan;
			delete _mjesec;
			delete _godina;
			delete _sati;
			delete _minuti;
			_dan = new int(*d._dan);
			_mjesec = new int(*d._mjesec);
			_godina = new int(*d._godina);
			_sati = new int(*d._sati);
			_minuti = new int(*d._minuti);
		}
		return *this;
	}

	~DatumVrijeme() {
		delete _dan;
		delete _mjesec;
		delete _godina;
		delete _sati;
		delete _minuti;
		_dan = nullptr;
		_mjesec = nullptr;
		_godina = nullptr;
		_sati = nullptr;
		_minuti = nullptr;
	}

	bool operator== (DatumVrijeme datum) {
		if (*_dan == *datum._dan && *_mjesec == *datum._mjesec && *_godina == *datum._godina && *_sati == *datum._sati && *_minuti == *datum._minuti) {
			return true;
		}
		return false;
	}

	friend ostream & operator<<(ostream & cout, DatumVrijeme d) {
		cout << *d._dan << "." << *d._mjesec << "." << *d._godina << " " << *d._sati << ":" << *d._minuti;
		return cout;
	}
};

class Video {
	string _ime;
	int _trajanje;
	DatumVrijeme _uploadTime;
public:
	Video(string ime, int trajanje, DatumVrijeme ut) {
		_ime = ime;
		_trajanje = trajanje;
		_uploadTime = ut;
	}

	Video(const Video& video) {
		_ime = video._ime;
		_trajanje = video._trajanje;
		_uploadTime = video._uploadTime;
	}

	Video& operator= (const Video& video) {
		if (this != &video) {
			_ime = video._ime;
			_trajanje = video._trajanje;
			_uploadTime = video._uploadTime;
		}
		return *this;
	}

	bool operator== (Video video) {
		if (_ime == video._ime && _trajanje == video._trajanje && _uploadTime == video._uploadTime) {
			return true;;
		}
		return false;;
	}

	friend ostream & operator<<(ostream & cout, Video & v) {
		cout << v._ime << "(" << v._trajanje << ") --> " << "Upload time: " << v._uploadTime;
		return cout;
	}

	string getIme() { return _ime; }
};

class Playlist {
	string _naziv;
	Pristup * _pristup;
	vector<Video*>_video;
public:
	Playlist(string naziv, Pristup p) {
		_naziv = naziv;
		_pristup = new Pristup(p);
	}

	Playlist(const Playlist& playlist) {
		_naziv = playlist._naziv;
		_pristup = new Pristup(*playlist._pristup);
		_video = playlist._video;
	}

	Playlist& operator= (const Playlist& playlist) {
		if (this != &playlist) {
			delete _pristup;

			_naziv = playlist._naziv;
			_pristup = new Pristup(*playlist._pristup);
			_video = playlist._video;
		}
		return *this;
	}

	void AddVideo(Video video) {
		Video* v = new Video(video);
		//onemoguciti ponavljanje videa istog naziva
		for (int i = 0; i < _video.size(); i++) {
			if (*_video[i] == *v) {
				return;
			}
		}
		_video.push_back(v);
	}

	bool operator==(Playlist playlist) {
		if (_naziv == playlist._naziv && *_pristup == *playlist._pristup && _video == playlist._video) {
			return true;
		}
		return false;
	}

	vector<Video*> getVideo() { return _video; }

	Pristup getPristup() { return *_pristup; }

	string getNaziv() { return _naziv; }

	friend ostream & operator<<(ostream & cout, Playlist & p) {
		cout << "Naziv: " << p._naziv << endl;
		cout << "Videa: " << endl;
		for (int i = 0; i < p._video.size(); i++)
			cout << *p._video[i] << endl;
		return cout;
	}
};

class User {
	char * _ime;
	string _username;
	Kolekcija<DatumVrijeme, User *> * _subskripcije;
	vector<Playlist*> _playliste;
public:
	User(string ime, string username) {
		_ime = new char[ime.size() + 1];
		strcpy_s(_ime, ime.size() + 1, ime.c_str());
		_username = username;
		_subskripcije = new Kolekcija<DatumVrijeme, User*>;
	}

	User(const User& user) {
		int size = strlen(user._ime) + 1;
		_ime = new char[size];
		strcpy_s(_ime, size, user._ime);
		_username = user._username;
		_subskripcije = new Kolekcija<DatumVrijeme, User*>(*user._subskripcije);
		_playliste = user._playliste;
	}

	User& operator= (const User& user) {
		if (this != &user) {
			delete[] _ime;
			delete _subskripcije;

			int size = strlen(user._ime) + 1;
			_ime = new char[size];
			strcpy_s(_ime, size, user._ime);
			_username = user._username;
			_subskripcije = new Kolekcija<DatumVrijeme, User*>(*user._subskripcije);
			_playliste = user._playliste;
		}
		return *this;
	}

	~User() {
		delete[]_ime;
		_ime = nullptr;
		for (int i = 0; i < _subskripcije->getTrenutno(); i++) {
			delete _subskripcije->getT2(i);
			_subskripcije->getT2(i) = nullptr;
		}
		delete _subskripcije;
		_subskripcije = nullptr;
	}

	string GetUsername() {
		return  _username;
	}

	void AddPlaylist(Playlist playlist) {
		Playlist* p = new Playlist(playlist);
		//onemoguciti dodavanje playlista sa istim nazivom
		for (int i = 0; i < _playliste.size(); i++) {
			if (*_playliste[i] == *p) {
				return;
			}
		}
		_playliste.push_back(p);
	}

	vector<Playlist*> GetPlayliste() {
		return _playliste;
	}

	void operator()(DatumVrijeme datum, User user) {
		//preklopiti operator za dodavanje subskripcija(prvi parametar je datum subskripcije)
		User* u = new User(user);
		_subskripcije->AddElement(datum, u);
	}

	Video* TraziVideo(string naziv) {
		//traziti samo u subskripcijama, ne u svojim videima i vratiti nullptr ukoliko se ne nadje
		Video* pom = nullptr;
		for (int i = 0; i < _subskripcije->getTrenutno(); i++) {
			for (int j = 0; j <_subskripcije->getT2(i)->GetPlayliste().size(); j++) {
				for (int k = 0; k <_subskripcije->getT2(i)->GetPlayliste()[j]->getVideo().size(); k++) {
					if (_subskripcije->getT2(i)->GetPlayliste()[j]->getVideo()[k]->getIme() == naziv) {
						pom = new Video(*_subskripcije->getT2(i)->GetPlayliste()[j]->getVideo()[k]);
					}
				}
			}
		}
		return pom;
	}

	vector<Video*> StartsWith(char slovo) {
		vector<Video*> pom;
		for (int i = 0; i < _subskripcije->getTrenutno(); i++) {
			for (int j = 0; j <_subskripcije->getT2(i)->GetPlayliste().size(); j++) {
				for (int k = 0; k <_subskripcije->getT2(i)->GetPlayliste()[j]->getVideo().size(); k++) {
					if (_subskripcije->getT2(i)->GetPlayliste()[j]->getVideo()[k]->getIme().at(0) == slovo) {
						pom.push_back(_subskripcije->getT2(i)->GetPlayliste()[j]->getVideo()[k]);
					}
				}
			}
		}
		return pom;
	}

	friend ostream& operator<< (ostream& Cout, User& user) {
		Cout << "Ime: " << user._ime << "  " << "Username: " << user._username << endl;
		Cout << "Subskripcije: " << endl;
		for (int i = 0; i < user._subskripcije->getTrenutno(); i++) {
			Cout << user._subskripcije->getT1(i) << "  " << user._subskripcije->getT2(i)->GetUsername() << endl;
		}
		Cout << "Playliste: " << endl;
		for (int i = 0; i < user._playliste.size(); i++) {
			Cout << *user._playliste[i] << endl;
		}
		return Cout;
	}
};

int main() {

	DatumVrijeme danas(2, 9, 2017, 22, 6);
	DatumVrijeme jucer(1, 9, 2017, 22, 6);
	DatumVrijeme dsubs1(20, 9, 2017, 11, 31);
	DatumVrijeme dsubs2(30, 9, 2017, 12, 48);

	Video v1("Linux tutorials pt. 1", 15, danas);
	Video v2("Linux tutorials pt. 2", 20, danas);
	Video v3("Why Windows sucks", 90, danas);
	Video v4("TCP/IP", 30, jucer);
	Video v5("OSI Model", 30, jucer);
	Video v6("IoT", 45, danas);
	Video v7("Where to start", 15, danas);
	Video v8("Why Windows sucks", 15, jucer);

	Playlist prva("My playlist", PUBLIC);
	Playlist druga("Neam pojma", PRIVATE);
	Playlist treca("Treca playlista", PUBLIC);

	prva.AddVideo(v1);
	prva.AddVideo(v2);
	prva.AddVideo(v3);
	prva.AddVideo(v8); //onemoguciti ponavljanje videa istog naziva

	druga.AddVideo(v4);

	treca.AddVideo(v5);
	treca.AddVideo(v6);
	treca.AddVideo(v7);
	treca.AddVideo(v7);

	User echo("Erhad Husovic", "echo");
	User meca("Nedim Maric", "meca");
	User sef("Stefan Stanic", "sef");

	echo.AddPlaylist(prva); //onemoguciti dodavanje playlista sa istim nazivom
	sef.AddPlaylist(druga);
	sef.AddPlaylist(treca);


	echo(dsubs1, meca); //preklopiti operator za dodavanje subskripcija(prvi parametar je datum subskripcije)
	echo(dsubs2, sef);


	//traziti samo u subskripcijama, ne u svojim videima i vratiti nullptr ukoliko se ne nadje
	Video * pronadjen = echo.TraziVideo("Why Windows sucks");

	if (pronadjen != nullptr)
		cout << *pronadjen << crt;
	else
		cout << "Video nije pronadjen" << crt;

	Video * pronadjen1 = echo.TraziVideo("TCP/IP");

	if (pronadjen1 != nullptr)
		cout << *pronadjen1 << crt;
	else
		cout << "Video nije pronadjen" << crt;


	cout << "Videa koja pocinju sa slovom W: " << endl;
	vector<Video*> videa = echo.StartsWith('W');

	for (int i = 0; i < videa.size(); i++)
		cout << i + 1 << ". " << *videa[i] << endl;

	cout << crt;

	//u ispisu za subskripcije samo ispisati datum subskripcije te username korisnika
	cout << echo << endl;

	system("pause");
	return 0;
}