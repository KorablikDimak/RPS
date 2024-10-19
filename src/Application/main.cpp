#include <QApplication>

#include "MainWindow.h"
#include "Storage.h"
#include "Api.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    const RPS::Application::Storage storage("settings.json");
    const RPS::Application::Api api(storage);
    RPS::Application::MainWindow window(api);

    window.show();
    return QApplication::exec();
}