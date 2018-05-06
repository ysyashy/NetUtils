#ifndef __UTILSCONFIGURE_H
#define __UTILSCONFIGURE_H

#include <string>

namespace yang {

enum class CompressType {
    NoCompress,
    QuickLZ,
    FastLz
};
enum class SecretType {
    NoSecret,
    RC4,
    DES
};

class UtilsConfigure {
public:
    static UtilsConfigure *getInstance();
    static void destoryConfigure();
private:
    UtilsConfigure();
    ~UtilsConfigure();
private:
    static UtilsConfigure *_instance;

    /* getter and setter */
public:
    void setCompressType(CompressType ctype);
    void setSecretType(SecretType stype);
    void setSecretKey(const std::string &key);

    CompressType getCompressType();
    SecretType getSecretType();
    std::string getSecretKey();
private:
    CompressType _compressType; /* compress type */
    SecretType _secretType;     /* secret type */
    std::string _secretKey;
};

}

#endif
