#include "UtilsConfigure.h"

namespace yang {

UtilsConfigure *UtilsConfigure::_instance = nullptr;

UtilsConfigure::UtilsConfigure()
    : _compressType(CompressType::NoCompress)
    , _secretType(SecretType::NoSecret)
{
}
UtilsConfigure::~UtilsConfigure()
{
}

UtilsConfigure *UtilsConfigure::getInstance()
{
    if(nullptr == _instance) _instance = new UtilsConfigure();
    return _instance;
}

void UtilsConfigure::destoryConfigure()
{
    if(nullptr != _instance) { delete _instance; _instance = nullptr; }
}

void UtilsConfigure::setCompressType(CompressType ctype)
{
    _instance->_compressType = ctype;
}

void UtilsConfigure::setSecretType(SecretType stype){
    _instance->_secretType = stype;
}

void UtilsConfigure::setSecretKey(const std::string &key)
{
    _instance->_secretKey = key;
}

CompressType UtilsConfigure::getCompressType()
{
    return _instance->_compressType;
}

SecretType UtilsConfigure::getSecretType()
{
    return _instance->_secretType;
}

std::string UtilsConfigure::getSecretKey()
{
    return _instance->_secretKey;
}

}
