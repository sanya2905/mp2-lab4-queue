#include <iostream>
#include <clocale>

#include "TJobStream.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    /* -------------------------------------------- */
    int capacity;
    cout << "Мощность вычислительной системы (максимальное количество заданий): ";
    cin >> capacity;

    double intensity;
    cout << "Интенсивность потока заданий (от 0 до 1): ";
    cin >> intensity;

    double performance;
    cout << "Производительность вычислительной системы (от 0 до 1): ";
    cin >> performance;

    int T;
    cout << "Количество тактов: ";
    cin >> T;

    cout << endl;
    /* -------------------------------------------- */

    TJobStream JobStream(capacity, intensity, performance);

    for (int i = 0; i < T; i++)
    {
        JobStream.CreateTasks();
        JobStream.RunCycle();
    }

    const auto& status = JobStream.GetStatus();

    cout << "Количество поступивших в систему заданий: " << status.Total << endl;
    cout << "Количество отказов в обслуживании из-за переполнения очереди: " << (100 * status.RejectionPercentage()) << "%" << endl;
    cout << "Среднее количество тактов выполнения задания: " << JobStream.AverageCycles() << endl;
    cout << "Количество тактов простоя процессора из-за отсутствия заданий: " << (100 * JobStream.GetProc().GetStatus().IdlePercentage()) << "%" << endl;

    return 0;
}