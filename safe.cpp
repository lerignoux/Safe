#include "Fenetre.h"

int main(int argc, char** argv)
{
  QApplication application(argc, argv);
  new Fenetre();

  return application.exec();
}