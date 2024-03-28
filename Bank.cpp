#include <iostream>
#include <string>
#define random(min, max) min + rand() % (max - min + 1)
using namespace std;
class Client;
class Bank;


class Client {
	friend class Bank;
private:
	string firstName;
	string lastName;
	int age;
	int bankAccount;
	double balance = 0;
	int id;
	static int lastId;
	Client(string firstName, string lastName, int age, int bankAccount) {
		this->firstName = firstName;
		this->lastName = lastName;
		this->age = age;
		this->id = lastId++;
		this->bankAccount = bankAccount;
	}

	void info() {
		cout << "Client id: " << this->id << endl;
		cout << "Client first name: " << this->firstName << endl;
		cout << "Client last name: " << this->lastName << endl;
		cout << "Client age: " << this->age << endl;
		cout << "Client bank account: " << this->bankAccount << endl;
		cout << "Client balance: " << this->balance << endl;
	}

};

class Bank {
private:
	int size = 0;
	Client** clients = new Client*[size];
	int createBankAccount() {
		int account = 0;
		bool flag = 1;
		do {
			for (int i = 0; i < 8; i++) {
				account *= 10;
				account += random(1, 9);
			}
			for (int i = 0; i < size; i++) {
				if (account == clients[i]->bankAccount) continue;
			}
			flag = 0;
		} while (flag);
		return account;
	}
	void addClient(Client* client) {
		Client** buf = new Client * [size + 1];
		for (int i = 0; i < size; i++) {
			buf[i] = clients[i];
		}
		buf[size] = client;
		delete[] clients;
		clients = buf;
		size++;
	}
public:
	string name;
	Bank(string name) {
		this->name = name;
	}
	void renameBank(string name) {
		this->name = name;
	}
	void showClientById(int id) {
		int index = -1;
		for (int i = 0; i < size; i++) {
			if (clients[i]->id == id) {
				index = i;
				break;
			}
		}
		if (index == -1) {
			cout << "Client not found" << endl << endl;
			return;
		}
		clients[index]->info();
	}
	Bank(const Bank& bank) {
		this->name = bank.name;
		this->size = bank.size;
		clients = new Client*[size];
		for (int i = 0; i < size; i++) {
			this->clients[i] = bank.clients[i];
		}
	}
	Bank operator = (const Bank& bank) {
		this->name = bank.name;
		this->size = bank.size;
		for (int i = 0; i < size; i++) {
			this->clients[i] = bank.clients[i];
		}
	}
	void createClient(string firstName, string lastName, int age) {
		int bankAccount = createBankAccount();
		Client* client = new Client(firstName, lastName, age, bankAccount);
		addClient(client);
	}
	void bankInfo() {
		cout << "Bank name: " << name << endl;
		if (size == 0) {
			cout << "There are 0 clients" << endl;
		}
		for (int i = 0; i < size; i++) {
			clients[i]->info();
			cout << endl;
		}
	}
	void removeClient(int id) {
		int index = -1;
		for (int i = 0; i < size; i++) {
			if (clients[i]->id == id) {
				index = i;
				break;
			}
		}
		if (index == -1) {
			cout << "Client not found" << endl << endl;
			return;
		}
		Client** buf = new Client * [size - 1];
		for (int i = 0; i < index; i++) {
			buf[i] = clients[i];
		}
		for (int i = index + 1; i < size; i++) {
			buf[i - 1] = clients[i];
		}
		delete[] clients;
		clients = buf;
		size--;
	}
	void changeBalance(double value, int bankAccount) {
		int index = -1;
		for (int i = 0; i < size; i++) {
			if (clients[i]->bankAccount == bankAccount) {
				index = i;
				break;
			}
		}
		if (index == -1) {
			cout << "Client not found" << endl << endl;
			return;
		}
		if (clients[index]->balance + value < 0) {
			cout << "Client have not enough money" << endl << endl;
			return;
		}
		clients[index]->balance += value;
	}
	void updateClient(string firstName, string lastName, int age, int id) {
		int index = -1;
		for (int i = 0; i < size; i++) {
			if (clients[i]->id == id) {
				index = i;
				break;
			}
		}
		if (index == -1) {
			cout << "Client not found" << endl << endl;
			return;
		}
		clients[index]->firstName = firstName;
		clients[index]->lastName = lastName;
		clients[index]->age = age;
	}
	void transaction(int senderBankAccount, int takerBankAccount, double value) {
		int senderIndex = -1;
		for (int i = 0; i < size; i++) {
			if (clients[i]->bankAccount == senderBankAccount) {
				senderIndex = i;
				break;
			}
		}
		if (senderIndex == -1) {
			cout << "Sender not found" << endl << endl;
			return;
		}
		int takerIndex = -1;
		for (int i = 0; i < size; i++) {
			if (clients[i]->bankAccount == takerBankAccount) {
				takerIndex = i;
				break;
			}
		}
		if (takerIndex == -1) {
			cout << "Taker not found" << endl << endl;
			return;
		}
		if (clients[senderIndex]->balance - value < 0) {
			cout << "Sender have not enough money" << endl << endl;
			return;
		}
		clients[senderIndex]->balance -= value;
		clients[takerIndex]->balance += value;
	}
	~Bank() {
		for (int i = 0; i < size; i++) {
			delete clients[i];
		}
		delete[] clients;
	}
};
int Client::lastId = 1;
int main()
{
	srand(time(NULL));
	int action;
	Bank bk1("Bank number one");
	Bank bk2("Bank number two");
	while (true) {
		int action;
		cout << "incert: \ncreate bank(1), \nremove bank(2), \nbank info(3), \ncopy bank(4), \nrename bank()\n";
		cout << "create client(), \nremove client(), \nchange client balance(), \nclient info(), update client(), \ntransaction()";
		cin >> action;
		switch (action) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			cout << "Which bank do you want to rename: " << bk1.name << "(1), " << bk2.name << "(2)\n";
			cin >> action;
			switch (action) {
			case 1:

				break;
			case 2:
				break;
			}
		}

	}
	bk1.createClient("Peter", "Grifin", 28);
	//bk1.createClient("Alexey", "Mitko", 21);
	bk1.bankInfo();

}