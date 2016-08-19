#include <iostream>

#include <math.h>

#include <QDesktopWidget>
#include <QMainWindow>
#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

#include <QListWidget>
#include <QKeyEvent>
#include <QShortcut>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <QIcon>
#include <QSystemTrayIcon>

#include <QtGui/QApplication>

#include <botan/botan.h>

#define DEFAULTFILENAME "passwords.crypt"

class Fenetre : public QMainWindow
{
  Q_OBJECT

  private :
    /* Elements globaux */
    QDesktopWidget *desktop;
    
    int slection;
    QWidget *mainWidget;
    QVBoxLayout *mainLayout;
    
    QByteArray openPass;
    QIcon *icon;
    QSystemTrayIcon *trayIcon;

    /* Elements graphiques : Password daemon */
    
    QWidget *passwordMainWidget;
    
    QAction *passwordsAction;
    QMenu *passwordsMenu;
    
    QVBoxLayout *passwordMainLayout;
    QListWidget *passList;
    QLineEdit *passLabel;
   
    QShortcut * copy;
    
    QByteArray passPopUp();
    
    void makePasswordWidget(void);
    void processData(void);
    void addPassTitle(QByteArray);

    void crypt();
    void decryptPass();

    /* Elements graphiques Files handler */
    QWidget *filesMainWidget;    
    QVBoxLayout *filesMainLayout;

    QAction *fileAction;
    QMenu *fileMenu;
    QPushButton *cryptButton;
    QLineEdit *passFileLine;
    
    QFile *passFile;
    
    void makeFilesWidget(void);
    
       
    /* Cryptographie */
    QString cryptFile(QString);
    QByteArray encrypt(QByteArray);
    QByteArray encrypt(QByteArray,QByteArray);
    QByteArray decrypt(QByteArray);
    char encrypt(char, char);
    char decrypt(char, char);
    
  public :
    Fenetre();
    ~Fenetre();
    
  public slots :
    void findPass(void);
    void copier();
    void setPasswordsWidget();
    void setFilesWidget();
    void cryptFile();
    void activate();
    
  protected:
    virtual bool eventFilter(QObject*,QEvent*);
};