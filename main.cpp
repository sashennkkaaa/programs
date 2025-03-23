#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class han_tower {
private:
    int** towers;
    int* size_towers;
    int disks;

public:
    han_tower(int d, int source) : disks(d) {
        towers = new int*[3];
        size_towers = new int[3]{0, 0, 0};
        for (int i = 0; i < 3; ++i) {
            towers[i] = new int[d];
        }
        for (int i = d; i >= 1; --i) {
            towers[source - 1][size_towers[source - 1]++] = i;
        }
        board();
    }
    ~han_tower() {
        for (int i = 0; i < 3; ++i) {
            delete[] towers[i];
        }
        delete[] towers;
        delete[] size_towers;
    }

    void board() {
        cout << "\n������� ��������� �����:\n\n";
        cout << "   I         II         III\n";
        cout << "----------------------------\n";
        for (int a = disks - 1; a >= 0; --a) {
            for (int b = 0; b < 3; ++b) {
                if (a < size_towers[b]) {
                    cout << setw(4) << towers[b][a];
                }
                else {
                    cout << setw(4) << " ";
                }
                cout << "       ";
            }
            cout << endl;
        }
        cout << "----------------------------\n";

    }

    void algorithm(int disk, int source, int dest, int helper) {
        if (disk > 0) {
            algorithm(disk - 1, source, helper, dest);
            cout << "����������� ���� " << disk << " � ����� " << source << " �� ����� " << dest << endl;
            moving(disk, source - 1, dest - 1);
            algorithm(disk - 1, helper, dest, source);
        }
    }

    void moving(int disk, int source, int dest) {
        towers[dest][size_towers[dest]++] = disk;
        size_towers[source]--;
        board();
    }



};
int pr_disks(const string& prompt, bool checkMinValue = false) {
    int input;
    while (true) {
        cout << prompt;
        cin >> input;
        if (cin.fail() || input <= 0 || (checkMinValue && input < 3)) {
            cin.clear(); // ������� ���� ������
            while (cin.get() != '\n'); // ������� �����
            if (checkMinValue && input < 3 && input > 0) {
                cout << "������! ������� ����� �� ����� 3.\n";
            } else {
                cout << "������! ������� ������������� �����.\n";
            }
        } else {
            while (cin.get() != '\n'); // ������� �����
            return input;
        }
    }
}
int pr_towers(const string& prompt, int source = -1) {
    int input;
    while (true) {
        cout << prompt;
        cin >> input;
        if (cin.fail() || input < 1 || input > 3 || (source != -1 && input == source)) {
            cin.clear(); // ������� ���� ������
            while (cin.get() != '\n'); // ������� �����
            if (source != -1 && input == source) {
                cout << "������! ��������� ����� � ����� ���������� ���������. ���������� �����!\n";
            } else {
                cout << "������! ������� ����� �� 1 �� 3.\n";
            }
        } else {
            while (cin.get() != '\n'); // ������� �����
            return input;
        }
    }
}
int main() {
    setlocale(LC_ALL, "RUS");
    int disk = pr_disks("���������� ������: ", true);
    int source = pr_towers("��������� ����� (1, 2, 3): ");
    int dest = pr_towers("����� ���������� (1, 2, 3): ", source);
    han_tower game(disk, source);
    cout << "������������������ �����:\n";
    game.algorithm(disk, source, dest, 6 - source - dest);
    system("pause>nul");
    return 0;
}
