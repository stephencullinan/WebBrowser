#ifndef PRELOADER_H
#define PRELOADER_H
#include "component.h"
#include <QString>
class PreLoader : public Component
{
public:
    PreLoader();
private:
    void createControl();
};
#endif // PRELOADER_H
