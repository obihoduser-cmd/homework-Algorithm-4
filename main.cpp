
#include <iostream>
#include <stdexcept>

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int count;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    ~DoublyLinkedList() {
        clear();
    }

    // Добавление элемента в конец списка
    void push_back(const T& value) {
        Node* newNode = new Node(value);

        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        count++;
    }

    // Удаление последнего элемента
    void pop_back() {
        if (tail == nullptr)
            throw std::underflow_error("List is empty");

        Node* temp = tail;
        tail = tail->prev;

        if (tail != nullptr) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }

        delete temp;
        count--;
    }

    // Вывод списка в прямом порядке
    void print() const {
        Node* current = head;

        std::cout << "[";

        while (current != nullptr) {
            std::cout << current->data;

            if (current->next != nullptr)
                std::cout << ", ";

            current = current->next;
        }

        std::cout << "]" << std::endl;
    }

    // Вывод списка в обратном порядке
    void printReverse() const {
        Node* current = tail;

        std::cout << "[";

        while (current != nullptr) {
            std::cout << current->data;

            if (current->prev != nullptr)
                std::cout << ", ";

            current = current->prev;
        }

        std::cout << "]" << std::endl;
    }

    // Обмен соседних элементов
    void swapPairs() {
        Node* current = head;

        while (current != nullptr && current->next != nullptr) {
            Node* first = current;
            Node* second = current->next;

            // Сохраняем следующий элемент после пары
            Node* nextPair = second->next;

            // Меняем связи между элементами
            first->next = nextPair;
            second->prev = first->prev;
            second->next = first;
            first->prev = second;

            // Обновляем предыдущий элемент
            if (second->prev != nullptr) {
                second->prev->next = second;
            }
            else {
                head = second;
            }

            // Обновляем следующий элемент
            if (nextPair != nullptr) {
                nextPair->prev = first;
            }
            else {
                tail = first;
            }

            // Переходим к следующей паре
            current = nextPair;
        }
    }

    // Получение размера списка
    int size() const {
        return count;
    }

    // Очистка списка
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }

        tail = nullptr;
        count = 0;
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    DoublyLinkedList<int> list;

    // Добавляем элементы
    for (int i = 1; i <= 5; i++) {
        list.push_back(i * 10);
    }

    std::cout << "=== Двусвязный список ===" << std::endl;

    std::cout << "Прямой порядок: ";
    list.print();

    std::cout << "Обратный порядок: ";
    list.printReverse();

    std::cout << "\n=== Метод swapPairs() ===" << std::endl;

    list.swapPairs();

    std::cout << "После обмена соседних элементов: ";
    list.print();

    std::cout << "Обратный порядок после обмена: ";
    list.printReverse();

    std::cout << "\nРазмер списка: " << list.size() << std::endl;

    list.pop_back();

    std::cout << "После pop_back: ";
    list.print();

    return 0;
}
