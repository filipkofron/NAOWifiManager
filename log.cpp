#include "log.h"
#include "globals.h"

boost::shared_ptr<std::ofstream> _outfile;

std::ostream& Log()
{
#if !LOCAL_TEST
  if (!_outfile)
  {
    _outfile = boost::shared_ptr<std::ofstream>(new std::ofstream);
    _outfile->open("/tmp/wifi.log");
  }
  return *_outfile;
#else // LOCAL_TEST
  return std::cout;
#endif // LOCAL_TEST
}
