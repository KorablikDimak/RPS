#include <QApplication>

#include "MainWindow.h"
#include "Storage.h"
#include "Repository.h"
#include "Array.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    const RPS::Application::Storage storage("settings.json");
    const RPS::Application::Repository<RPS::Application::Array<double>> repository(storage);
    RPS::Application::MainWindow window(repository);

    window.show();
    return QApplication::exec();
}