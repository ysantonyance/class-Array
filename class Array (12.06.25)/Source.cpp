#include <iostream>
#include <windows.h>
#include <algorithm>
using namespace std;

// написати корисний, зрозумілий тип для роботи з динамічним масивом (поки що з елементами типу інт)

class Array {
	int* data; // покажчик на майбутній динамічний масив
	unsigned int length;

public:
	Array() {
		data = nullptr;
		length = 0;
		cout << "Created an empty array\n";
	}

	Array(int ar[], unsigned int size) {
		if (size > 1000000) throw "error!\n";

		// якщо в класі є поле-покажчик, то іноді прямо в конструкторі треба буде ВИДІЛЯТИ ПАМ'ЯТЬ динамічно під цей покажчик
		length = size;
		data = new int[length];
		for (int i = 0; i < length; i++) {
			data[i] = ar[i];
		}
		cout << "Created not an empty array with " << size << " elements\n";
	}

	// конструктор - метод, в який ми потрапляємо пілся створення об'єкта (записуємо значення в поля, виділяємо пам'ять під поля-покажчики)
	// деструктор - метод, який викликається АВТОМАТИЧНО безпсередньо перед тим, як об'єкт буде знищено.
	// 1) там можна зробити роздруківку і переконатися що об'єкт перестане існувати
	// 2) пам'ять виділена під поля-покажчики може бути вівільнена САМЕ ТАМ

	void Print() const {
		if (length == 0) {
			cout << "They array is empty, I can't show anything :(\n";
		}
		else {
			cout << "Elements of the array: ";
			for (int i = 0; i < length; i++)
			{
				cout << data[i];
				cout << (i == length - 1 ? "." : ", ");
			}
			cout << "\n";
		}
	}

	unsigned int GetLength() const {
		return length;
	}

	void AddToBack(int value) {
		// робимо новий масив, в якому буде на 1 елемент більше
		int* temp = new int[length + 1];
		// переганяємо елементи зі старого масиву в новий
		for (int i = 0; i < length; i++)
		{
			temp[i] = data[i];
		}
		// в кінець нового масиву додаємо передане значення через параметр
		temp[length] = value;
		// старий масив треба почистити, інакше буде виток пам'яті
		delete[] data;
		// переставляємо основний покажчик зі старого масива (якого доречі уже і не існує), на новий масив
		data = temp;
		// так як відбулося додавання 1 елемента в кінець масиву, то його довжина стала +1 
		length++;
	}

	void RemoveFromBack() {
		if (length == 0) {
			cout << "I have nothing to delete, since the array is empty!\n";
			return; // якщо нема чого видаляти, то просто нічого не робимо
			// throw "Помилка! Елементів нема!";
		}
		length--;
		int* temp = new int[length];
		for (int i = 0; i < length; i++)
			temp[i] = data[i];
		delete[] data;
		data = temp;
	}

	void AddToFront(int value) {
		// робимо новий масив, в якому буде на 1 елемент більше
		int* temp = new int[length + 1];
		// переганяємо елементи зі старого масиву в новий
		for (int i = 0; i < length; i++)
		{
			temp[i + 1] = data[i];
		}
		// на початок нового масиву додаємо передане значення через параметр
		temp[0] = value;
		// старий масив треба почистити, інакше буде виток пам'яті
		delete[] data;
		// переставляємо основний покажчик зі старого масива (якого доречі уже і не існує), на новий масив
		data = temp;
		// так як відбулося додавання 1 елемента в кінець масиву, то його довжина стала +1 
		length++;
	}

	void RemoveFromFront() {
		if (length == 0) {
			cout << "I have nothing to delete, the array is empty!\n";
			return; // якщо нема чого видаляти, то просто нічого не робимо
			// throw "Помилка! Елементів нема!";
		}
		length--;
		int* temp = new int[length];
		for (int i = 1; i < length + 1; i++)
			temp[i - 1] = data[i];
		delete[] data;
		data = temp;
	}

	void SortAZ() {
		sort(data, data + length);
	}

	void Shuffle() {
		for (int i = 0; i < 10000; i++)
		{
			int ri1 = rand() % length;
			int ri2 = rand() % length;
			swap(data[ri1], data[ri2]);
		}
	}

	void Add10RandomNumbers() {
		for (int i = 0; i < 10; i++)
			AddToBack(rand() % 100);
	}

	// приклад деструктора
	// деструктор не можна перевантажити, він ніколи не приймає параметрів!
	~Array() {
		if (data != nullptr) {
			delete[] data;
		}
		cout << "The object was deleted and the memory cleared!\n";
	}

	// конструктор копіювання
	// 
	Array(Array& original) {
		this->length = original.length;
		this->data = new int[this->length];
		for (int i = 0; i < this->length; i++)
		{
			this->data[i] = original.data[i];
		}
	}

	// домашнее задание
	void Insert(int value, int index)
	{
		int* temp = new int[length + 1];
		int count = 0;
		for (int i = 0; i < index; i++)
		{
			if (index > 0)
				temp[i] = data[i];
			count++;
		}
		temp[count] = value;
		for (int i = index; i < length + 1; i++)
		{
			temp[i + 1] = data[i];
		}
		delete[] data;
		data = temp;
		length++;
	}

	void RemoveAt(int index)
	{
		if (length == 0)
		{
			cout << "I have nothing to delete, the array is empty!\n";
			return;
		}
		int* temp = new int[length - 1];
		for (int i = 0; i < index; i++)
		{
			if (index >= 0)
				temp[i] = data[i];
			else
			{
				cout << "index can't be negative\n";
				return;
			}
		}
		//temp[count] = value;
		for (int i = index + 1; i < length; i++)
		{
			temp[i - 1] = data[i];
		}
		delete[] data;
		data = temp;
		length--;
	}

	void RemoveByValue(int value)
	{
		int* temp = new int[length];
		int count = 0;
		int index = 0;
		for (int i = 0; i < length; i++)
		{
			if (data[i] == value)
				count++;
			else
				temp[index++] = data[i];
		}
		delete[] data;
		data = temp;
		length -= count;
	}

	void Clear()
	{
		delete[] data;
		data = nullptr;
		length = 0;
		cout << "The memory is cleared, pointer and length reset\n";
	}

	bool IsEmpty()
	{
		if (length == 0)
		{
			//cout << "The array is empty\n";
			return true;
		}
		else
		{
			//cout << "The array is NOT empty\n";
			return false;
		}
	}

	int IndexOf(int value)
	{
		for (int i = 0; i < length; i++)
		{
			if (data[i] == value)
			{
				cout << "We found the element you're searching for!\nIt's under this index: ";
				return i;
			}
		}
		return -1;
	}

	int LastIndexOf(int value)
	{
		for (int i = length; i > 0; i--)
		{
			if (data[i] == value)
			{
				cout << "We found the element you're searching for!\nIt's under this index: ";
				return i;
			}
		}
		return -1;
	}

	void Reverse()
	{
		int* temp = new int[length];
		for (int i = 0; i < length; i++)
			temp[i] = data[length - i - 1];
		delete[] data;
		data = temp;
	}
};

int main() {
	SetConsoleOutputCP(1251);
	srand(time(0));

	// ar[] = { 1, 2, 3, 4, 3, 6};

	Array original;
	original.Add10RandomNumbers();
	original.Print();

	//original.Insert(10, 5);
	//original.RemoveAt(1);
	// 
	int random = rand() % 100;
	//original.RemoveByValue(random);
	//cout << "Deleting this element: " << random << "\n";
	//
	//original.Clear();
	//cout << boolalpha;
	//cout << original.IsEmpty() << "\n";
	//cout << original.IndexOf(random) << "\n";
	//cout << original.LastIndexOf(random) << "\n";
	//original.Reverse();
	original.Print();

	//Array copy = original;
	// Array copy(original); // виклик конструктору копіювання! КК
	//copy.Print();
}