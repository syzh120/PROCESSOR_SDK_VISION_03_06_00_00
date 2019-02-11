#ifndef __VPSIO_H__
#define __VPSIO_H__

#ifdef GENERIC_ARM
#include <include/link_api/system_trace.h> /* This is coming from Vision SDK */
#endif
#include <iostream>

namespace vps
{

class ostream
{
    friend ostream& operator<<(ostream& source, int val);
    friend ostream& operator<<(ostream& source, unsigned int val);
    friend ostream& operator<<(ostream& source, short val);
    friend ostream& operator<<(ostream& source, float val);
    friend ostream& operator<<(ostream& source, double val);
    friend ostream& operator<<(ostream& source, std::string val);
    friend ostream& operator<<(ostream& source, std::ostream val);
    friend ostream& operator<<(ostream& source, vps::ostream val);

public:
    ostream()
    {}
};

extern ostream cout;
extern ostream endl;

}
#endif
