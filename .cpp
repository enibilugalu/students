#include <iostream> // Podklyuchaem biblioteku dlya vvod/vyvod v konsol
#include <string>   // Podklyuchaem biblioteku dlya raboty so strokkami

using namespace std; // Ispol'zuem prostranstvo imen std, chtoby ne pisat std:: pered kazhdym ob'ektom

struct Student // Opredelyaem strukturu Student
{
    string name;    // Imya studenta
    string surname; // Familiya studenta
    int age;        // Vozrast studenta
};

Student* students = nullptr; // Ukazatel' na dinamicheskiy massiv studentov
int studentCount = 0;        // Tekushchee kolichestvo studentov
int capacity = 0;            // Tekushchaya vmeschaemost' massiva

void resizeArray() // Funktsiya dlya uvelicheniya razmera massiva
{
    int newCapacity = (capacity == 0) ? 2 : capacity * 2; // Esli capacity = 0, ustanavlivaem 2, inache udvaivaem
    Student* newArray = new Student[newCapacity];         // Sozdaem novyy massiv bol'shego razmera
    for (int i = 0; i < studentCount; i++)                // Kopiruem dannye iz starogo massiva
    {
        newArray[i] = students[i]; // Kopiruem odnogo studenta
    }
    delete[] students;            // Udalaem staryy massiv
    students = newArray;          // Ukazatel' teper' ukazyvaet na novyy massiv
    capacity = newCapacity;       // Obnovlyaem znachenie capacity
}

void showMenu() // Vyvod menyu v konsol
{
    cout << "\nMenu:\n";                    // Zagolovok menyu
    cout << "1. Show all students\n";       // Punkt 1: pokazat' vsekh studentov
    cout << "2. Add student\n";             // Punkt 2: dobavit' studenta
    cout << "3. Edit student\n";            // Punkt 3: redaktirovat' studenta
    cout << "4. Delete student\n";          // Punkt 4: udalit' studenta
    cout << "0. Exit\n";                    // Punkt 0: vykhod iz programmy
    cout << "Choose an option: ";           // Zapros vybora
}

void showStudents() // Vyvod spiska studentov
{
    if (studentCount == 0) // Esli spisok pust
    {
        cout << "Student list is empty.\n"; // Soobshchenie o pustom spiske
        return;                             // Vyhod iz funktsii
    }
    for (int i = 0; i < studentCount; i++) // Prokhod po vsem studentam
    {
        cout << i + 1 << ". " << students[i].name << " "      // Vyvod nomera i imeni
            << students[i].surname << ", age: " << students[i].age << "\n"; // Vyvod familii i vozrasta
    }
}

void addStudent() // Dobavlenie novogo studenta
{
    if (studentCount >= capacity) // Esli net mesta v massive
    {
        resizeArray(); // Uvelichivaem razmer massiva
    }
    Student add; // Sozdaem novyy ob'ekt Student
    cout << "Enter name: ";     // Zapros imeni
    cin >> add.name;            // Vvod imeni
    cout << "Enter surname: ";  // Zapros familii
    cin >> add.surname;         // Vvod familii
    cout << "Enter age: ";      // Zapros vozrasta
    cin >> add.age;             // Vvod vozrasta

    students[studentCount++] = add; // Dobavlyaem studenta v massiv i uvelichivaem schetchik
    cout << "Student added.\n";     // Soobshchenie ob uspeshnom dobavlenii
}

void changeStudent() // Redaktirovanie dannykh studenta
{
    if (studentCount == 0) // Esli net studentov
    {
        cout << "No students to edit.\n"; // Soobshchenie ob otsutstvii studentov
        return;                            // Vyhod iz funktsii
    }
    showStudents(); // Pokazyvaem spisok studentov
    cout << "Enter student number to edit: "; // Zapros nomera studenta
    int index;
    cin >> index; // Vvod nomera
    if (index <= 0 || index > studentCount) // Proverka na korrektnost'
    {
        cout << "Invalid number.\n"; // Soobshchenie ob oshibke
        return;                      // Vyhod iz funktsii
    }
    index--; // Preobrazovanie v indeks massiva
    cout << "Enter new name: ";     // Zapros novogo imeni
    cin >> students[index].name;    // Vvod novogo imeni
    cout << "Enter new surname: ";  // Zapros novoy familii
    cin >> students[index].surname; // Vvod novoy familii
    cout << "Enter new age: ";      // Zapros novogo vozrasta
    cin >> students[index].age;     // Vvod novogo vozrasta

    cout << "Student data updated.\n"; // Soobshchenie ob uspeshnom obnovlenii
}

void deleteStudent() // Udaleniye studenta
{
    if (studentCount == 0) // Esli net studentov
    {
        cout << "No students to delete.\n"; // Soobshchenie ob otsutstvii studentov
        return;                              // Vyhod iz funktsii
    }
    showStudents(); // Pokazyvaem spisok studentov
    cout << "Enter student number to delete: "; // Zapros nomera dlya udaleniya
    int index;
    cin >> index; // Vvod nomera
    if (index <= 0 || index > studentCount) // Proverka na korrektnost'
    {
        cout << "Invalid number.\n"; // Soobshchenie ob oshibke
        return;                      // Vyhod iz funktsii
    }
    index--; // Preobrazovanie v indeks massiva
    for (int i = index; i < studentCount - 1; i++) // Sdvig vsekh studentov vpravo
    {
        students[i] = students[i + 1]; // Kopiruem sleduyushchego studenta na mesto udalennogo
    }
    studentCount--; // Umenshaem kolichestvo studentov
    cout << "Student deleted.\n"; // Soobshchenie ob uspeshnom udalenii
}

int main() // Glavnaya funktsiya programmy
{
    while (true) // Beskonechnyy tsikl menyu
    {
        showMenu(); // Vyvod menyu
        int choice;
        cin >> choice; // Vvod vybora pol'zovatelya
        switch (choice) // Obrabotka vybora
        {
        case 1:
            showStudents(); // Pokazat' studentov
            break;
        case 2:
            addStudent(); // Dobavit' studenta
            break;
        case 3:
            changeStudent(); // Redaktirovat' studenta
            break;
        case 4:
            deleteStudent(); // Udalit' studenta
            break;
        case 0:
            cout << "Exit.\n"; // Vyvod soobshcheniya o vykhode
            delete[] students; // Ochistka pamyati
            return 0;          // Zavершение programmy
        default:
            cout << "Invalid choice, try again.\n"; // Soobshchenie ob oshibke vybora
        }
    }
}
