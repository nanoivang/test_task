#include "item.h"

Item::Item(int type, QString name, QString imagePath)
    : mName(name)
    , mType(type)
    , mImagePath(imagePath)
{

}

Item::~Item()
{

}
