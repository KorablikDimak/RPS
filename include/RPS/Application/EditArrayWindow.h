#ifndef RPS_Application_EditArrayWindow_H
#define RPS_Application_EditArrayWindow_H

#include <QDialog>

#include "Repository.h"
#include "Array.h"

namespace RPS::Application
{
    QT_BEGIN_NAMESPACE
    namespace Ui
    {
        class EditArrayWindow;
    }
    QT_END_NAMESPACE

    class EditArrayWindow : public QDialog
    {
    Q_OBJECT

    public:
        explicit EditArrayWindow(const Repository<Array<double>>* repository,
                                 const Array<double>& array, QWidget* parent = nullptr) noexcept;
        ~EditArrayWindow() override;

    signals:
        void Updated() const;

    private:
        Ui::EditArrayWindow* _ui;
        Array<double> _array;
        const Repository<Array<double>>* _repository;

    private slots:
        void SaveButtonClicked() noexcept;
        void CancelButtonClicked() noexcept;
        void SortButtonClicked() noexcept;
        void DeleteButtonClicked() noexcept;
    };
}

#endif