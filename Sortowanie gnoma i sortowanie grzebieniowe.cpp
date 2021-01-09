#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <fstream>

using namespace std;

int N;
clock_t start, stop;
double t1,t2;

// Funkcja sortujaca algorytmem sortowania gnoma
void gnomeSort(int arr[], int n)
{

    int index = 0;


    while (index < n)
    {
        if (index == 0)
            index++;
        if (arr[index] >= arr[index - 1])
            index++;
        else
        {
            swap(arr[index], arr[index - 1]);
            index--;
        }
    }
    return;
}

//Szukanie rozpietosci pomiedzy elementami
int getNextGap(int gap)
{
    // Podzielenie rozpietosci przez 1.3
    //co odrzuca czesc ulamkowa
    gap = (gap*10)/13;

    if (gap < 1)
        return 1;
    return gap;
}

// Funkcja sortujaca algorytmem sortowania grzebieniowego
void combSort(int a[], int n)
{
    // Inicjowanie rozpietosci
    int gap = n;

    // Zmienna do upewnienia siê, ze
    // petla dziala
    bool swapped = true;

    // w momencie, gdy rozpietosc jest wieksza od 1
    // iteracja powoduje zamiane elementow
    while (gap != 1 || swapped == true)
    {

        gap = getNextGap(gap);

        // Sprawdzenie, czy nastapila zamiana
        swapped = false;

        // Porównanie wszystkich elementow z obecna rozpietoscia
        for (int i=0; i<n-gap; i++)
        {
            if (a[i] > a[i+gap])
            {
                swap(a[i], a[i+gap]);
                swapped = true;
            }

        }

    }
}

//funkcja uzytkowa do posortowania
void printArray(int arr[], int n)
{
    cout<< "Posortowane liczby to:  ";
    for (int i = 0; i < n; i++)
        cout<< arr[i] << " ";
    cout<< "\n";

}

//przeprowadzenie testów
void test_1()
{
	int a[] = {1, 10, 22, 12, 32, 234, 123, 33, 33, 21, 812, 1727, 88, 3, 112, 32, 6, 2, 21, 23, 3, 4, 0, 7, 97,9998, 811, 77, 643};
    int n = sizeof(a) / sizeof(a[0]);

    gnomeSort(a, n);
    printArray(a, n);

    ofstream plik1("rozwiazanie1.txt"); //zapis rozwiazania do pliku
    for (int i=0; i<n; i++)
        plik1<<(" %d ", a[i])<<endl;

    plik1.close();

}

void test_2()
{
	int b[] = {1, 10, 22, 12, 32, 234, 123, 33, 33, 21, 812, 1727, 88, 3, 112, 32, 6, 2, 21, 23, 3, 4, 0, 7, 97,9998, 811, 77, 643};
    int n = sizeof(b)/sizeof(b[0]);

    combSort(b, n);
    printArray(b, n);


    ofstream plik1("rozwiazanie2.txt"); //zapis rozwiazania do pliku
    for (int i=0; i<n; i++)
        plik1<<(" %d ", b[i])<<endl;

    plik1.close();

}


int main ()
{
	cout<<"1 - Test sortowania gnoma"<<endl<<endl;
	cout<<"2 - Test sortowania grzebieniowego"<<endl<<endl;
	cout<<"3 - Pseudolosowe + porownanie czasu dzialania"<<endl<<endl;
	cout<<"4 - Odczyt z pliku - Sortowanie gnoma"<<endl<<endl;
	cout<<"5 - Odczyt z pliku - Sortowanie grzebieniowe"<<endl<<endl;


	 int sposob;
	 cout<<"Wybierz sposob dzialania programu: ";
	 cin>>sposob;
	 //Stworzenie  menu, w ktorym bedzie mozna wybrac sposob dzialania programu
	 switch (sposob)
	{

	case 1: test_1();
    break;

	case 2: test_2();
	break;

	case 3: {
	      cout<<"Podaj ilosc elementow w tablicy: ";
    cin>>N;

     while(cin.fail() || N<=0)
    {
        cout << "Blad! Prosze podac poprawna liczbe!" << endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> N;
    }

    //dynamiczna alokacja tablicy
    int *arr;
    arr=new int [N];

    int *arr2;
    arr2=new int [N];

    //inicjowanie generatora
    srand(time(NULL));

    //wczytywanie losowych liczb do tablicy
    for(int i=0; i<N; i++)
    {
        arr[i] = rand()%100000+1;
    }

    //przepisanie tablicy do tablicy2
    for(int i=0; i<N; i++)
    {
       arr2[i]=arr[i];
    }

    //czas sortowania gnoma

    cout<<"Prosze czekac! Trwa sortowanie gnoma."<<endl;
    start = clock();
    gnomeSort(arr,N);
    stop = clock();
    t1 = (double)(stop-start) / CLOCKS_PER_SEC;
    cout<<endl<<"Czas sortowania gnoma: "<<t1<<" s"<<endl<<endl;


    //czas sortowania grzebieniowego

    cout<<endl<<"Prosze czekac! Trwa sortowanie grzebieniowe"<<endl;
    start = clock();
    combSort(arr2, N);
    stop = clock();
    t2 = (double)(stop-start) / CLOCKS_PER_SEC;
    cout<<endl<<"Czas sortowania grzebieniowego: "<<t2<<" s"<<endl;



    delete [] arr;
    delete [] arr2;

     ofstream plik1("rozwiazanie3.txt"); //zapis rozwiazania do pliku

        plik1<<"Czas wykonania sortowania gnoma to: "<<t1<<endl;
        plik1<<"Czas wykonania sortowania grzebieniowego to: "<<t2<<endl;

        plik1.close();

    break;
	}


	case 4: { int  g[500]={0};
	    int n = 0;
	    fstream z;
	    z.open("plik1.txt",ios::in); //odczytujemy dane z pliku

	    if(!z)
        {
            cout<<"Nie udalo sie otworzyc pliku"; //w razie nieudanej proby odczytu wyswietli sie komunikat
            getchar();
            return 1;
        }
        while (!z.eof())
            z>>g[n++];

            z.close();


    gnomeSort(g, n);
    printArray(g, n);//odczytane liczby z pliku zostaja posortowane

    z.close();

    ofstream plik1("rozwiazanie4.txt");
    for (int i=0; i<n; i++)
        plik1<<(" %d ", g[i])<<endl;

        plik1.close();


        break;

	}
	case 5: {
	    int  t[1000]={0};
	    int n = 0;
	    fstream z;
	    z.open("plik1.txt",ios::in); //odczytujemy dane z pliku

	    if(!z)
        {
            cout<<"Nie udalo sie otworzyc pliku"; //w razie nieudanej proby odczytu wyswietli sie komunikat
            getchar();
            return 1;
        }
        while (!z.eof())
            z>>t[n++];

            z.close();


        combSort(t, n);
        printArray(t ,n);

    z.close();


    ofstream plik1("rozwiazanie5.txt");
    for (int i=0; i<n; i++)
        plik1<<(" %d ", t[i])<<endl;

        plik1.close();

	}

	}

    getchar();

    return 0;

    }




