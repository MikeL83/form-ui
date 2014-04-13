#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QDate>
#include <QScopedPointer>
#include <memory>

namespace Ui
{
class MainWindow;
}

class QTabWidget;
class QLineEdit;
class QLabel;
class QAction;
class QMenu;
class QVBoxLayout;
class QDialogButtonBox;
class QString;
class QCloseEvent;
class QPlainTextEdit;
class QComboBox;
class QPushButton;
class QDateEdit;
class QRadioButton;
class Logic;

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    const quint32 MagicNumber;
    ~MainWindow();

  protected:
    void closeEvent(QCloseEvent *event);

  private slots:
    void accept();
    void checkCharacterLengthForFields(QString);
    void checkCharacterLengthForMultiLineFields();
    void changeDateOfBirth(QDate);
    void loadUser();
    void sendEmail();
    void callCell();
    void checkSettings();

  private:
    Ui::MainWindow *ui;

    void createWidgets();
    void createLayout();
    void createConnections();
    void createActions();
    void createMenus();
    bool checkRequiredFields();

    QTabWidget *tabWidget;
    QVBoxLayout *page1Layout;
    QVBoxLayout *page2Layout;
    QDialogButtonBox *buttonBox;
    QComboBox *comboBox;
    QPushButton *contactEmail;
    QPushButton *contactCell;
    QLineEdit *firstNameEdit;
    QLineEdit *middleNameEdit;
    QLineEdit *lastNameEdit;
    QDateEdit *dateOfBirthEdit;
    QPlainTextEdit *addressEdit;
    QLineEdit *cityEdit;
    QLineEdit *stateEdit;
    QLineEdit *postcodeEdit;
    QLineEdit *companyEdit;
    QLineEdit *emailEdit;
    QLineEdit *designationEdit;
    QPlainTextEdit *bioEdit;
    QLineEdit *mobileEdit;
    QLineEdit *settingsEdit;
    QLabel *firstNameLabel;
    QLabel *middleNameLabel;
    QLabel *lastNameLabel;
    QLabel *dateOfBirthLabel;
    QLabel *addressLabel;
    QLabel *cityLabel;
    QLabel *stateLabel;
    QLabel *postcodeLabel;
    QLabel *companyLabel;
    QLabel *emailLabel;
    QLabel *designationLabel;
    QLabel *bioLabel;
    QLabel *mobileLabel;
    QLabel *settingsLabel;
    QRadioButton *radioButton1;
    QRadioButton *radioButton2;

    QAction *separatorAction;
    QAction *loadAction;
    QAction *exitAction;

    QMenu *fileMenu;

    QHash<QString, QString> preferences;

    std::unique_ptr<Logic> logic;
};

#endif // MAINWINDOW_H
