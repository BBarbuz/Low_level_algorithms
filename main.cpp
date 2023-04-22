    #include <cstdlib>
    #include <ctime>
    #include <fstream>
    #include <iostream>
    #include <sstream>
    #include <string>

// Możliwość uruchomienia funkcji pauzy i czyszczenia konsoli zarówno na
// Windowsie jak i na Linuxie
#if defined(_WIN32)
#define PLATFORM_NAME "windows" // Windows
#elif defined(_WIN64)
#define PLATFORM_NAME "windows" // Windows
#elif defined(__CYGWIN__) && !defined(_WIN32)
#define PLATFORM_NAME "windows" // Windows (Cygwin POSIX under Microsoft Window)
#elif defined(__linux__)
#define PLATFORM_NAME                                                          \
  "linux" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
#endif

using namespace std;

struct student {
    string imie;
    string nazwisko;
    int punkty;
};

// Funkcje właściwe dla systemu operacujnego
void systemClear() {
    if (PLATFORM_NAME == "Windows")
        system("cls");
    else if (PLATFORM_NAME == "linux") {
        std::system("clear");
    }
}

void systemPause() {
    if (PLATFORM_NAME == "windows") {
        system("pause");
    } else if (PLATFORM_NAME == "linux") {
        string dummy;
        cout << "Enter to continue..." << endl;
        cin.ignore();
        getline(cin, dummy);
    }
}

// operacje na tablicy liczbowej, sortowania itp. LAB1
void przydzielPamiec1D(int *&tab, int n) { tab = new int[n]; }

void usunTablice1D(int *&tab) { delete[] tab; }

void wyswietl1D(int *tab, int n) {
    for (int i = 0; i < n; i++)
        cout << tab[i] << " ";

    cout << endl;
    systemPause();
}

void sortowaniePrzezWybor(int tab[],int n) //n - ilość elementów do posortowania
{
    int mn_index; //zmienna pomocnicza przechowująca indeks komórki
    //z minimalną wartością
    for(int i=0;i<n-1;i++)
    {
        mn_index = i;
        for(int j=i+1;j<n;j++) //pętla wyszukuje najmniejszy element w podzbiorze nieposortowanym
            if(tab[j]<tab[mn_index])
                mn_index = j;

        //zamiana elementu najmniejszego w podzbiorze z pierwszą pozycją nieposortowaną
        swap(tab[i], tab[mn_index]);
    }
}


void sortowaniePrzezWstawianie(int *tab, int n, int tryb) {
    int pom, j;

    if (tryb == 0)
        for (int i = 1; i < n; i++) {

            pom = tab[i];
            j = i - 1;

            while (j >= 0 && tab[j] < pom) {
                tab[j + 1] = tab[j];
                --j;
            }
            tab[j + 1] = pom;
        }
    else {
        for (int i = 1; i < n; i++) {

            pom = tab[i];
            j = i - 1;

            while (j >= 0 && tab[j] > pom) {
                tab[j + 1] = tab[j];
                --j;
            }
            tab[j + 1] = pom;
        }
    }
}

void sortowanieBabelkowe(int *tab, int n, int tryb) {
    int pom = 0;

    if (tryb == 0)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - 1; j++)
                if (tab[j] < tab[j + 1]) {
                    pom = tab[j];
                    tab[j] = tab[j + 1];
                    tab[j + 1] = pom;
                }
        }
    else
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - 1; j++)
                if (tab[j] > tab[j + 1]) {
                    pom = tab[j];
                    tab[j] = tab[j + 1];
                    tab[j + 1] = pom;
                }
        }
}

void wypelnijTablice1D(int *tab, int n, int a, int b) {
    for (int i = 0; i < n; i++)
        tab[i] = rand() % (b - a + 1) + a;
}

void znajdzMinimalnyElement(int *tab, int n) {
    int mini = tab[0];

    for (int i = 0; i < n; i++) {
        if (tab[i] < mini)
            mini = tab[i];
    }
    cout << "Minimalny element tablicy: " << mini << endl;
    systemPause();
}

void znajdzMaksymalnyElement(int *tab, int n) {
    int maxi = tab[0];

    for (int i = 0; i < n; i++) {
        if (tab[i] > maxi)
            maxi = tab[i];
    }
    cout << "Maksymalny element tablicy: " << maxi << endl;
    systemPause();
}

void SredniaTablicy(int *tab, int n) {
    float srednia = 0;

    for (int i = 0; i < n; i++) {
        srednia += tab[i];
    }
    cout << "Srednia elementow tablicy wynosi: " << srednia / n << endl;
    systemPause();
}

void Sortowanie_quick_sort(int *tab, int lewy, int prawy) {
    if (prawy <= lewy)
        return;

    int i = lewy - 1, j = prawy + 1,
            pivot = tab[(lewy + prawy) / 2]; // wybieramy punkt odniesienia

    while (1) {
        // szukam elementu wiekszego lub rownego piwot stojacego
        // po prawej stronie wartosci pivot
        while (pivot > tab[++i])
            ;

        // szukam elementu mniejszego lub rownego pivot stojacego
        // po lewej stronie wartosci pivot
        while (pivot < tab[--j])
            ;

        // jesli liczniki sie nie minely to zamień elementy ze soba
        // stojace po niewlasciwej stronie elementu pivot
        if (i <= j)
            // funkcja swap zamienia wartosciami tab[i] z tab[j]
            swap(tab[i], tab[j]);
        else
            break;
    }

    if (j > lewy)
        Sortowanie_quick_sort(tab, lewy, j);
    if (i < prawy)
        Sortowanie_quick_sort(tab, i, prawy);
}

// Menu operacji na tablicy liczbowej
void tablicaMenu() {
    int wybor = 1;
    int a, b;
    int pom = 0, n = 9;
    int *tab;
    przydzielPamiec1D(tab, n);

    while (wybor > 0) {
        cout << "Dostępne operacje na tablicy liczbowej: " << endl << endl;

        cout << "	1.	Wygeneruj nowe liczby w tablicy" << endl;
        cout << "	2.	Posortuj tablice sortowaniem babelkowym (malejaco)"
             << endl;
        cout << "	3.	Posortuj tablice sortowaniem babelkowym (rosnaco)"
             << endl;
        cout << "	4.	Posortuj tablice sortowaniem przez wstawainie "
                "(malejaco)"
             << endl;
        cout << "	5.	Posortuj tablice sortowaniem przez wstawianie (rosnaco)"
             << endl;
        cout << "	6.	Znajdz maksymalny element tablicy" << endl;
        cout << "	7.	Znajdz minimalny element tablicy" << endl;
        cout << "	8.	Policz srednia tablicy" << endl;
        cout << "	9.	Wyswietl tablice" << endl;
        cout << "	10.	Zmien wielkosc tablicy" << endl;
        cout << "	11.	Posortuj algorytmem Quick Sort" << endl;
        cout << "	0.	Wroc do menu glownego" << endl;
        cout << "Wybor: ";
        cin >> wybor;
        cout << endl;

        switch (wybor) {
            case 1:
                cout << "Podaj zakres generowanych wartosci (od ... do): ";
                cin >> a;
                cin >> b;
                wypelnijTablice1D(tab, n, a, b);
                wyswietl1D(tab, n);
                break;
            case 2:
                sortowanieBabelkowe(tab, n, 0);
                wyswietl1D(tab, n);
                break;
            case 3:
                sortowanieBabelkowe(tab, n, 1);
                wyswietl1D(tab, n);
                break;
            case 4:
                sortowaniePrzezWstawianie(tab, n, 0);
                wyswietl1D(tab, n);
                break;
            case 5:
                sortowaniePrzezWstawianie(tab, n, 1);
                wyswietl1D(tab, n);
                break;
            case 6:
                znajdzMaksymalnyElement(tab, n);
                break;
            case 7:
                znajdzMinimalnyElement(tab, n);
                break;
            case 8:
                SredniaTablicy(tab, n);
                break;
            case 9:
                wyswietl1D(tab, n);
                break;
            case 10:
                cout << "Podaj wielkosc: ";
                cin >> n;
                usunTablice1D(tab);
                przydzielPamiec1D(tab, n);
                wypelnijTablice1D(tab, n, a, b);
                break;
            case 11:
                Sortowanie_quick_sort(tab, 0, n - 1);
                wyswietl1D(tab, n);
                break;
            case 0:
                usunTablice1D(tab);
                systemPause();
                break;
        }
        systemClear();
    }
}

// operacje wyszukiwania wzorca w tekscie, wyszukiwanie bijekcyjne LAB2
void wczytajTekstWzorzec(string *wsk_tekst, string *wsk_wzorzec) {
    cout << "Podaj wartosci dla tekst i wzorzec (tekst <enter> wzorzec): ";
    cin.ignore();
    getline(cin, *wsk_tekst);
    getline(cin, *wsk_wzorzec);
}

void wyswietlTekstWzorzec(string tekst, string wzorzec) {
    cout << "Tekst: " << tekst << "     Wzorzec: " << wzorzec << endl;
    // cout << "Tekst: "<<tekst.length()<<"     Wzorzec: "<<
    // wzorzec.length()<<endl;
    systemPause();
}

void znajdzWzorzecNaiwny(string tekst, string wzorzec) {

    cout << "Indeksy tekstu gdzie rozpoczyna sie wzorzec: ";

    int j, pom, licz;
    for (int i = 0; i < tekst.length() - wzorzec.length() + 1; i++) {
        j = 0;
        if (tekst[i] == wzorzec[j]) {
            pom = i;
            licz = 1;
            for (int x = i + 1; x < i + wzorzec.length(); x++) {
                j++;
                if (tekst[x] == wzorzec[j]) {
                    licz++;
                } else {
                    break;
                }
            }
            if (licz == wzorzec.length())
                cout << pom << ", ";
        }
    }
    cout << endl;
    systemPause();
}

void stworzTablice(string tekst, int tab_dopasowan[]) {
    int a = 0;

    tab_dopasowan[0] = 0;
    int i = 1;

    while (i < tekst.size()) {
        if (tekst[i] == tekst[a]) {
            a++;
            tab_dopasowan[i] = a;
            i++;
        } else {
            if (a != 0)
                a = tab_dopasowan[a - 1];
            else {
                tab_dopasowan[i] = 0;
                i++;
            }
        }
    }
}

void znajdzWzorzecKMP(string tekst, string wzorzec) {

    cout << "Indeksy tekstu gdzie rozpoczyna sie wzorzec: ";

    int tab_dopasowan[wzorzec.size()];
    stworzTablice(wzorzec, tab_dopasowan);
    int i = 0;
    int j = 0;
    while (i < tekst.size()) {
        if (wzorzec[j] == tekst[i]) {
            i++;
            j++;
        }

        if (j == wzorzec.size()) {
            cout << i - j << ", ";
            j = tab_dopasowan[j - 1];
        } else if (i < tekst.size() && wzorzec[j] != tekst[i]) {
            if (j != 0)
                j = tab_dopasowan[j - 1];
            else
                i++;
        }
    }

    cout << endl;
    systemPause();
}

// Menu operacji na wyrazach
void wyrazyMenu() {
    int wybor = 1;
    string tekst, wzorzec;
    string *wsk_tekst = &tekst;
    string *wsk_wzorzec = &wzorzec;

    wczytajTekstWzorzec(wsk_tekst,
                        wsk_wzorzec); // pierwsze wczytanie tekstu i wzorca
    systemClear();

    while (wybor != 0) {
        cout << "Dostepne operacje na wyrazach" << endl << endl;
        cout << " 1. Wprowadz nowe dane" << endl;
        cout << " 2. Wyswietl obecny tekst oraz wzorzec" << endl;
        cout << " 3. Znajdz wzorce tekstu (algorytm naiwny)" << endl;
        cout << " 4. Znajdz wzorce tekstu (algorytm KNP)" << endl;
        cout << " 0. Wroc do menu glownego" << endl;
        cout << "Wybor: ";
        cin >> wybor;
        cout << endl;

        switch (wybor) {
            case 1:
                wczytajTekstWzorzec(wsk_tekst, wsk_wzorzec);
                break;
            case 2:
                wyswietlTekstWzorzec(tekst, wzorzec);
                break;
            case 3:
                znajdzWzorzecNaiwny(tekst, wzorzec);
                break;
            case 4:
                znajdzWzorzecKMP(tekst, wzorzec);
                break;
            case 0:
                wybor = 0;
                break;
        }
        systemClear();
    }
}

void wyswietlDaneStudentow(student *&tab, int liczbaStudentow) {
    for (int i = 0; i < liczbaStudentow; i++) {
        cout << tab[i].imie << " " << tab[i].nazwisko
             << "   punkty: " << tab[i].punkty << endl;
    }
    systemPause();
}

void wczytajTabliceStudentow(student *&tab, int &liczbaStudentow) {
    string sciezka, linia, pomoc;
    ifstream plik;
    char sredniki;
    // student* tab;
    sciezka = "studenci.csv";
    plik.open(sciezka);
    plik >> liczbaStudentow;
    // alokowanie pamięci w tab o dlugosci liczbaStudentow
    // elementem tablicy jest struktura student(imie, nazwisko, punkty)

    for (int i = 0; i < 2; i++)
        plik >> sredniki;
    // cout << liczbaStudentow;
    tab = new student[liczbaStudentow];
    for (int i = 0; i < liczbaStudentow; i++) {
        plik >> linia;
        stringstream ss(linia);
        getline(ss, tab[i].imie, ';');
        getline(ss, tab[i].nazwisko, ';');
        getline(ss, pomoc);
        tab[i].punkty = atoi(pomoc.c_str());
        // cout << tab[i].imie << " " << tab[i].nazwisko <<"   punkty: "<<
        // tab[i].punkty<<endl;
    }
    plik.close();
}

void wyszukiwanieBisekcyjne(student *&tab, int p, int szukana) {
    p = p - 1;
    int l = 0;
    int sr;
    int slodziak = 0;
    while (l <= p) {
        sr = (l + p) / 2;

        if (tab[sr].punkty == szukana) {
            slodziak = 1;
            cout << tab[sr].imie << " " << tab[sr].nazwisko
                 << "   punkty: " << tab[sr].punkty << endl;
        }

        if (tab[sr].punkty > szukana)
            p = sr - 1;
        else
            l = sr + 1;
    }

    if (slodziak == 0) {
        cout << "Zaden student nie uzyskal okreslonej liczby punktow" << endl;
    }
    systemPause();
}

void SortStudentow(student *&tab, int &liczbaStudentow, int szuk) {
    int pom = 0;
    for (int i = 0; i < liczbaStudentow; i++) {
        for (int j = 0; j < liczbaStudentow - 1; j++)
            if (tab[j].punkty > tab[j + 1].punkty) {
                pom = tab[j].punkty;
                tab[j].punkty = tab[j + 1].punkty;
                tab[j + 1].punkty = pom;
            }
    }
    wyszukiwanieBisekcyjne(tab, liczbaStudentow, szuk);
}

// Menu operacji na wyrazach
void wyszukiwanieMenu() {
    int wybor = 1;

    while (wybor != 0) {
        cout << "Dostepne operacje na tabeli studenci" << endl << endl;
        cout << " 1. Wyswietl dane studentow" << endl;
        cout << " 2. Wyszukiwanie bisekcyjne. Wyszukaj studentow o okreslonej "
                "liczbie punktow"
             << endl;
        cout << " 0. Wroc do menu glownego" << endl << endl;

        student *tab;
        int liczbaStudentow;
        wczytajTabliceStudentow(
                tab,
                liczbaStudentow); // działa tylko na kompilatorze używajacym clanga
        cout << "     Dane studentow zostaly wczytane z pliku" << endl;

        cout << "Wybor: ";
        cin >> wybor;
        cout << endl;

        switch (wybor) {
            case 1:
                wyswietlDaneStudentow(tab, liczbaStudentow);
                break;
            case 2:
                int szuk;
                cout << "Podaj szukana liczbe punktow: ";
                cin >> szuk;
                cout << endl;
                SortStudentow(tab, liczbaStudentow, szuk);

                break;
            case 0:
                wybor = 0;
                break;
        }
        systemClear();
    }
}


struct elementHeap{
    int number;
    elementHeap* next;
};

void pushHeap(elementHeap* &stack, int value){
    elementHeap* el = new elementHeap;
    el -> number = value;
    el -> next = stack;
    stack = el;
}

void popHeap(elementHeap* &stack){
    elementHeap* temp = stack;
    stack = stack -> next;
    delete temp;
}

bool isEmptyHeap(elementHeap* stack){
    if(stack==nullptr)
        return true;
    return false;
}

int topHeap(elementHeap* stack){
    return stack -> number;

}


struct elementQueue{
    char character;
    elementQueue* next;
};

struct queue{
    elementQueue* head;
    elementQueue* tail;
};

void pushQueue(queue &q, char value){
    elementQueue* el = new elementQueue;
    el -> character = value;
    el -> next = nullptr;
    if(q.tail!= nullptr)
        q.tail->next=el;
    else
        q.head=el;
    q.tail=el;
}

void popQueue(queue &q){
    elementQueue* temp = q.head;
    q.head = q.head -> next;
    delete temp;
    if(q.head== nullptr)
        q.tail= nullptr;
}

bool isEmptyQueue(queue q){
    if(q.head== nullptr)
        return true;
    else
        return false;
}

char firstQueue(queue q){
    return q.head -> character;
}

// Menu operacji na stosie i liscie
void implementacjaStosu() {
    int wybor = 1;

    elementHeap* stack=nullptr;

    queue q;
    q.head=nullptr;
    q.tail=nullptr;

    systemClear();

    while (wybor != 0) {
        cout << "Dostepne operacje na stosie" << endl << endl;
        cout << " 1. push" << endl;
        cout << " 2. pop" << endl;
        cout << " 3. isEmpty" << endl;
        cout << " 4. top" << endl;
        cout << " 5. Odwrocenie kolejnosci znaki1.txt" << endl;
        cout << endl;
        cout << "Dostepne operacje na kolejce" << endl << endl;
        cout << " 6. push" << endl;
        cout << " 7. pop" << endl;
        cout << " 8. isEmpty" << endl;
        cout << " 9. first" << endl;\
        cout << " 10. Usuniecie wszystkich elementow kolejki" << endl;
        cout << " 11. Wczytanie z pliku znaki2.txt" << endl;
        cout << " 0. Wroc do menu glownego" << endl;
        cout << "Wybor: ";
        cin >> wybor;
        cout << endl;

        char c;
        switch (wybor) {
            case 1:
                int liczbaDoStosu;
                cout << "Podaj liczbe (push): "<<endl;
                cin >> liczbaDoStosu;
                pushHeap(stack, liczbaDoStosu);
                break;

            case 2:
                if(isEmptyHeap(stack)) {
                    cout << "Stos jest pusty"<<endl;
                    systemPause();
                    break;
                }
                cout << "Liczba zostala usunieta ze stosu (pop) "<<endl;
                popHeap(stack);
                systemPause();
                break;

            case 3:
                if(isEmptyHeap(stack))
                    cout<<"Stos jest pusty"<<endl;
                else{
                    cout<<"Stos nie jest pusty"<<endl;
                    systemPause();
                }
                break;

            case 4:
                if(isEmptyHeap(stack)) {
                    cout << "Stos jest pusty" << endl;
                    systemPause();
                    break;
                }
                cout << "Liczba na szczyycie stosu (top): ";
                cout << topHeap(stack)<<endl;
                systemPause();
                break;

            case 5: {
                ifstream wej("znaki1.txt", std::ios::binary);

                while (wej.get(c)) {
                    //cout<< c;         // Wyswietlanie znak po znaku w normalnej kolejnosci
                    pushHeap(stack, int(c));
                }
                wej.close();

                ofstream wyj("wynik.txt", std::ios::binary);


                while (!isEmptyHeap(stack)) {
                    c = char(topHeap(stack));
                    wyj << c;
                    cout << c;
                    popHeap(stack);
                }
                cout << endl;

                systemPause();
                break;
            }

            case 6:
                char charDoKolejki;
                cout << "Podaj znak (push): "<<endl;
                cin >> charDoKolejki;
                pushQueue(q, charDoKolejki);
                break;

            case 7:
                if(isEmptyQueue(q)) {
                    cout << "Kolejka jest pusta"<<endl;
                    systemPause();
                    break;
                }
                popQueue(q);
                cout << "Liczba zostala usunieta z kolejki (pop) "<<endl;
                systemPause();
                break;

            case 8:
                if(isEmptyQueue(q))
                    cout<<"Kolejka jest pusta"<<endl;
                else{
                    cout<<"Kolejka nie jest pusta"<<endl;
                    systemPause();
                }
                break;

            case 9:
                if(isEmptyQueue(q)) {
                    cout << "Kolejka jest pusta" << endl;
                    systemPause();
                    break;
                }
                cout << "Pierwszy znak w kolejce (first): ";
                cout << firstQueue(q)<<endl;
                systemPause();
                break;

            case 10:
                cout<< "Usuwane elementy: ";
                while(!isEmptyQueue(q)) {
                    cout<<firstQueue(q)<<" ";
                    popQueue(q);
                }
                cout<<endl;
                systemPause();
                break;

            case 11: {
                string plik = "znaki2.txt";
                ifstream wej("znaki2.txt", std::ios::binary);

                while (wej.get(c)) {
                    //cout<< int(c);         // Wyswietlanie znak po znaku w normalnej kolejnosci
                    if(int(c)>=65&&int(c)<=90)
                        pushQueue(q, c);
                }
                wej.close();
                cout << endl;
                systemPause();
                break;
            }

            case 0:
                wybor = 0;
                break;
        }
        systemClear();
    }
}


struct elementList{
    int number;
    elementList* next;
    elementList* prev;
};

struct double_list{
    elementList* head;
    elementList* tail;
    int counter=0;
};

void add_tailList(double_list &l, int value){
    elementList* el = new elementList;
    el->number=value;
    el->next= nullptr;
    el->prev=nullptr;
    if(l.tail!=nullptr){
        l.tail->next=el;
        el->prev=l.tail;
    }
    else{
        l.head=el;
    }
    l.tail=el;
    l.counter++;
}

void add_headList(double_list &l, int value){
    elementList* el=new elementList;
    el->number=value;
    el->next=nullptr;
    el->prev=nullptr;
    if(l.head!=nullptr){
        l.head->prev=el;
        el->next=l.head;
    }
    else{
        l.tail=el;
    }
    l.head=el;
    l.counter++;
}

void add_positionList(double_list &l, int value, int position){
    auto* temp=l.head;
    int i=1;
    while(i<position-1){
        temp=temp->next;
        i++;
    }
    auto el=new elementList;
    el->number=value;
    el->prev=temp;
    el->next=temp->next;
    temp->next->prev=el;
    temp->next=el;
    l.counter++;
}

void delete_tailList(double_list &l){
    auto* temp=l.tail;
    int i=1;
    if(l.counter==1){
        l.tail= nullptr;
        l.head= nullptr;
    }
    else{
        l.tail=l.tail->prev;
        l.tail->next=nullptr;
    }
    delete temp;
    l.counter--;
}

void delete_headList(double_list &l){
    auto temp = l.head;
    if(l.counter==1){
        l.tail= nullptr;
        l.head=nullptr;
    }
    else{
        l.head=l.head->next;
        l.head->prev=nullptr;
    }
    delete temp;
    l.counter--;
}

void delete_positionList(double_list &l, int position){
    auto* temp=l.head;
    int i=1;
    while(i<position-1){
        temp=temp->next;
        i++;
    }
    auto* temp_us=temp->next;
    temp->next=temp_us->next;
    temp->next->prev=temp;
    delete temp_us;
    delete temp;
    l.counter--;
}

bool isEmptyList(double_list &l){
    if(l.head== nullptr)
        return true;
    else
        return false;
}

void showList(double_list &l){
    int i=1;
    auto temp=l.head;
    while(i<=l.counter){
        cout<<temp->number<<" ";
        temp=temp->next;
        i=i+1;
    }
    delete temp;
}

void showListBackwards(double_list &l){
    int i=l.counter;
    auto temp=l.tail;
    while(i>=1){
        cout<<temp->number<<" ";
        temp=temp->prev;
        i=i-1;
    }
    delete temp;
}

void showMinList(double_list &l){
    int i=1, mini = l.head->number, pozycja = 0;
    auto temp=l.head;
    while(i<=l.counter){
        if(mini > temp->number){
            mini = temp->number;
            pozycja = i-1;
        }

        temp=temp->next;
        i=i+1;
    }
    delete temp;

    cout<< "Minimalna wartosc to: "<<mini << "  na pozycji: "<<pozycja;
}

void deleteList(double_list &l){
    int i=1;
    while(i<=l.counter)
        delete_headList(l);

}


// Menu operacji na listach
void implementacjaList(){
    int wybor=1;

    double_list l;
    l.counter=0;
    int liczbaDoListy;
    int pozycja;


    while(wybor!=0){
        cout << "Dostepne operacje na liscie: " <<endl<<endl;
        cout << "  1. Dodawanie elementu na koniec listy (add_tail)" << endl;
        cout << "  2. Dodawanie elementu na poczatek listy (add_head)" << endl;
        cout << "  3. Dodawanie elementu na wskazana pozycje listy (add_position)" << endl;
        cout << "  4. Usuniecie elementu z konca listy (delete_tail)" << endl;
        cout << "  5. Usuniecie elementu z poczatku listy (delete_head)" << endl;
        cout << "  6. Usuniecie elementu z wskazanej pozycji listy (delete_position)" << endl;
        cout << "  7. Sprawdzenie czy lista jest pusta (isEmptyList)" << endl;
        cout << "  8. Wyswietlanie listy (showList)" << endl;
        cout << "  9. Wyswietlanie listy od konca (showListBackward)" << endl;
        cout << "  10. Wyswietlanie najmniejszego elementu w liscie (showMinList)" << endl;
        cout << "  0. Wroc do menu glownego (usuniecie listy i zwolnienie pamieci)" << endl;
        cout << "Wybor: ";
        cin >> wybor;
        cout<<endl;

        switch(wybor) {
            case 1:
                cout << "Podaj liczbe: "<<endl;
                cin >> liczbaDoListy;
                add_tailList(l, liczbaDoListy);
                break;

            case 2:
                cout << "Podaj liczbe: "<<endl;
                cin >> liczbaDoListy;
                add_headList(l, liczbaDoListy);
                break;

            case 3:
                cout << "Podaj pozycje: "<<endl;
                cin >> pozycja;
                cout << "Podaj liczbe: "<<endl;
                cin >> liczbaDoListy;
                add_positionList(l, liczbaDoListy, pozycja);
                break;

            case 4:
                if(isEmptyList(l)) {
                    cout << "Lista jest pusta"<<endl;
                    systemPause();
                    break;
                }
                delete_tailList(l);
                break;

            case 5:
                if(isEmptyList(l)) {
                    cout << "Lista jest pusta"<<endl;
                    systemPause();
                    break;
                }
                delete_headList(l);
                break;

            case 6:
                if(isEmptyList(l)) {
                    cout << "Lista jest pusta"<<endl;
                    systemPause();
                    break;
                }
                cout << "Podaj pozycje: "<<endl;
                cin >> pozycja;
                delete_positionList(l,pozycja);
                break;

            case 7:

                if(isEmptyList(l)) {
                    cout << "Lista jest pusta"<<endl;
                    systemPause();
                    break;
                }
                cout << "Lista nie jest pusta"<<endl;
                break;

            case 8:
                if(isEmptyList(l)) {
                    cout << "Lista jest pusta"<<endl;
                    systemPause();
                    break;
                }
                showList(l);
                cout<<endl;
                systemPause();
                break;

            case 9:
                showListBackwards(l);
                cout<<endl;
                systemPause();
                break;

            case 10:
                showMinList(l);
                cout<<endl;
                systemPause();
                break;

        }
    }
    deleteList(l);
}


struct node{
    int key;
    node* parent;
    node* left;
    node* right;
};


node* makeNode(int value){
    auto n=new node;
    n->key=value;
    n->left= nullptr;
    n->right= nullptr;
    n->parent= nullptr;
    return n;
}

void addNode(node* &root, int value){
    if(root==nullptr){
        root=makeNode(value);
        return;
    }
    auto temp = root;
    while(true){
        if(value>=temp->key){
            if(temp->right== nullptr){
                temp->right=makeNode(value);
                temp->right->parent=temp;
                return;
            }
            else{
                temp=temp->right;
            }
        }
        else{
            if(temp->left== nullptr){
                temp->left= makeNode(value);
                temp->left->parent=temp;
                return;
            }
            else{
                temp=temp->left;
            }
        }
    }
}

node* findNode(node* root, int value){
    while (root!= nullptr){
        if(root->key==value){
            return root;
        }
        if(value>root->key){
            root=root->right;
        }
        else{
            root=root->left;
        }
    }
    return nullptr;
}

void inorder(node* root){
    if(root!= nullptr){
        inorder(root->left);
        cout<<root->key<<" ";
        inorder(root->right);
    }
}

void preorder(node* root){
    if(root!= nullptr){
        cout<<root->key<<" ";
        inorder(root->left);
        inorder(root->right);
    }
}

void postorder(node* root){
    if(root!= nullptr){
        inorder(root->left);
        inorder(root->right);
        cout<<root->key<<" ";
    }
}

node* findSuccessor(node* n){
    if(n->right!=nullptr){
        n=n->right;
        while(n->left!= nullptr)
            n=n->left;
        return n;
    }
    auto temp=n->parent;
    while(temp!=nullptr&&temp->left!=n){
        n=temp;
        temp = temp->parent;
    }
    return temp;
}

void deleteNode(node* &root, node* deleteNode){
    auto temp1 = new node;
    auto temp2 = new node;
    if(deleteNode->left== nullptr || deleteNode->right== nullptr){
        temp1=deleteNode;
    }
    else{
        temp1 = findSuccessor(deleteNode);
    }

    if(temp1 -> left!= nullptr){
        temp2=temp1->left;
    }
    else{
        temp2=temp1->right;
    }

    if(temp2!= nullptr){
        temp2->parent=temp1->parent;
    }

    if(temp1->parent== nullptr){
        root=temp2;
    }
    else{
        if(temp1==temp1->parent->left){
            temp1->parent->left=temp2;
        }
        else{
            temp1 -> parent->right=temp2;
        }
    }

    if(temp1!=deleteNode){
        deleteNode->key=temp1->key;
    }
    delete temp1;
    delete temp2;
}

bool isEmptyTree(node* root){
    if(root == nullptr)
        return true;
    return false;
}

void implementacjaBST(){
    int wybor=1;

    node* tree;
    tree = nullptr;
    int value;

    while(wybor!=0){
        cout << "Dostepne operacje na liscie: " <<endl<<endl;
        cout << "  1. Dodawanie elementu do drzewa (addNode)" << endl;
        cout << "  2. Wyswietlanie drzewa (inorder)" << endl;
        cout << "  3. Wyswietlanie drzewa (preorder)" << endl;
        cout << "  4. Wyswietlanie drzewa (postorder)" << endl;
        cout << "  5 Usuniecie wybranego elementu (deleteNode)" << endl;
        cout << "  6 Sprawdzenie czy drzewo jest puste (isEmpty)" << endl;
        cout << "  0. Wroc do menu glownego (usuniecie drzewa)" << endl;
        cout << "Wybor: ";
        cin >> wybor;
        cout<<endl;

        switch (wybor) {
            case 1:
                cout<<"Podaj liczbe: ";
                cin>>value;
                cout<<endl;
                cout<<"Drzewo przed dodaniem: "<<endl;
                inorder(tree);
                if(findNode(tree, value)!= nullptr){
                    cout<< "Wezel o podanej wartosci klucza juz istnieje!";
                    break;
                }
                addNode(tree, value);
                cout<<endl<<"Drzewo po dodaniu: "<<endl;
                inorder(tree);
                cout<<endl;
                cin.get();
                break;

            case 2:
                inorder(tree);
                cout<<endl;
                break;

            case 3:
                preorder(tree);
                cout<<endl;
                break;

            case 4:
                postorder(tree);
                cout<<endl;
                break;

            case 5:
                cout<<"Podaj liczbe: ";
                cin>>value;
                cout<<endl;
                if(findNode(tree, value)== nullptr){
                    cout<< "Wezel o podanej wartosci klucza nie istnieje!"<<endl;
                    break;
                }
                cout<<"Drzewo przed dodaniem: "<<endl;
                inorder(tree);
                deleteNode(tree, findNode(tree, value));
                cout<<endl<<"Drzewo po dodaniu: "<<endl;
                inorder(tree);
                break;

            case 6:
                if(isEmptyTree(tree))
                    cout<<"Drzewo jest puste"<<endl;
                else
                    cout<<"Drzewo nie jest puste"<<endl;


        }
        systemPause();
    }
}


int main(int argc, char **argv) {

    int wybor;

    srand(time(nullptr));

    do {
        cout << "  ------  MENU GLOWNE ------  " << endl << endl;
        cout << "  1. Operacje na tablicy liczbowej (Lab1)" << endl;
        cout << "  2. Operacje na wyrazach (Lab2)" << endl;
        cout << "  3. Wyszukiwanie z pliku studenci.csv (Lab2)" << endl;
        cout << "  4. Operacje na stosie i kolejce (Lab3)" << endl;
        cout << "  5. Operacje na liscie (Lab3)" << endl;
        cout << "  6. Operacje na drzewnie BST (Lab4)" << endl;
        cout << "  0. Zakonczenie programu" << endl;
        cout << "Wybor: ";
        cin >> wybor;
        cout << endl;

        switch (wybor) {
            case 1:
                tablicaMenu();
                systemClear();
                break;
            case 2:
                wyrazyMenu();
                systemClear();
                break;
            case 3:
                wyszukiwanieMenu();
                systemClear();
                break;
            case 4:
                implementacjaStosu();
                systemClear();
                break;
            case 5:
                implementacjaList();
                systemClear();
                break;
            case 6:
                implementacjaBST();
                systemClear();
                break;
            case 0:
                break;
        }
    } while (wybor != 0);

    return 0;
}